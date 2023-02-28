/*
    Copyright (C) 2023 Melvin Pynadath

    This file is part of ArduinoWrapper.

    ArduinoWrapper is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ArduinoWrapper is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ArduinoWrapper.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "./serial.hpp"

#include <stdint.h>

#include <boost/circular_buffer.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>

namespace bip = boost::interprocess;

using Segment = bip::managed_shared_memory;
using Mgr = Segment::segment_manager;
template <typename T>
using Alloc = bip::allocator<T, Mgr>;

template <typename T>
using Ring = boost::circular_buffer<T, Alloc<T>>;

using Buffers = Ring<uint8_t>;

#define T_BUFFER_SIZE 64
#define R_BUFFER_SIZE 64

namespace bip = boost::interprocess;

SerialIPC *SerialIPC::instance = nullptr;

/**
 * @brief holds the transmit and receive buffers
 *
 */
struct SerialIPC::Data {
   public:
    Buffers *t_buffer;
    Buffers *r_buffer;

    Data() {
        t_buffer = nullptr;
        r_buffer = nullptr;
    }
};

/**
 * @brief holds the boost specific objects
 *
 */
struct SerialIPC::boost_struct {
   public:
    bip::named_mutex r_mutex;
    bip::named_mutex t_mutex;
    bip::managed_shared_memory managed_shm;

   public:
    /*
    create only for ArduinoWrapper
    open only for test library
    */
#ifndef CONSUMER
    boost_struct() : r_mutex(bip::create_only, "r_serial_mutex"), t_mutex(bip::create_only, "t_serial_mutex"), managed_shm{bip::create_only, "serial_sm", 1048576} {
    }
#else
    boost_struct() : r_mutex(bip::open_only, "r_serial_mutex"), t_mutex(bip::open_only, "t_serial_mutex"), managed_shm(bip::open_only, "serial_sm") {
    }
#endif
    ~boost_struct() {
#ifndef CONSUMER
        /*
        Removes boost objects required as shared memory and mutexes are persistent
        Only required by the ArduinoWrapper library not the test library
        */
        bip::named_mutex::remove("r_serial_mutex");
        bip::named_mutex::remove("t_serial_mutex");
        bip::shared_memory_object::remove("serial_sm");
#endif
    }
};

SerialIPC::SerialIPC() {
#ifndef CONSUMER
    // clears any existing shared memory and removes named r_mutex
    bip::shared_memory_object::remove("serial_sm");
    bip::named_mutex::remove("t_serial_mutex");
    bip::named_mutex::remove("r_serial_mutex");
#endif

    try {
        this->boost_objs = new boost_struct();
    } catch (bip::interprocess_exception &e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Cannot find shared memory or named r_mutex"
                  << "\n";
        throw std::bad_alloc();
    }

    data = new Data();

    try {
#ifndef CONSUMER
        data->t_buffer = this->boost_objs->managed_shm.construct<Buffers>("t_buffer_n")(T_BUFFER_SIZE, this->boost_objs->managed_shm.get_segment_manager());
#else
        data->t_buffer = this->boost_objs->managed_shm.find<Buffers>("t_buffer_n").first;
        if (data->t_buffer == nullptr) {
            throw bip::bad_alloc();
        }
#endif
    } catch (bip::bad_alloc &e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Failed to find object in shared memory"
                  << "\n";
        throw std::bad_alloc();
    }
    try {
#ifndef CONSUMER
        data->r_buffer = this->boost_objs->managed_shm.construct<Buffers>("r_buffer_n")(R_BUFFER_SIZE, this->boost_objs->managed_shm.get_segment_manager());
#else
        data->r_buffer = this->boost_objs->managed_shm.find<Buffers>("r_buffer_n").first;
        if (data->r_buffer == nullptr) {
            throw bip::bad_alloc();
        }
#endif
    } catch (bip::bad_alloc &e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Failed to find object in shared memory"
                  << "\n";
        throw std::bad_alloc();
    }
}

SerialIPC::~SerialIPC() {
    delete this->boost_objs;
}

size_t SerialIPC::write(uint8_t c) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->t_mutex));
    data->t_buffer->push_back(c);
    return 1;
}

int SerialIPC::read() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->r_mutex));
    int temp = -1;
    try {
        temp = data->r_buffer->at(0);
    } catch (boost::wrapexcept<std::out_of_range> &e) {
        temp = -1;
    }
    if (temp != -1) {
        data->r_buffer->pop_front();
    }
    return temp;
}

int SerialIPC::peek() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->r_mutex));
    int temp = data->r_buffer->at(0);
    return temp;
}

int SerialIPC::availableForWrite() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->t_mutex));
    int cap = data->t_buffer->capacity();
    int size = data->t_buffer->size();
    return (cap - size);
}

int SerialIPC::available() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->r_mutex));
    return data->r_buffer->size();
}

void SerialIPC::flush() {
    // no scoped lock to avoid deadlock
    while (true) {
        unsigned int size = T_BUFFER_SIZE;
        bool is_locked = this->boost_objs->t_mutex.try_lock();
        if (is_locked) {
            size = data->t_buffer->size();
            this->boost_objs->t_mutex.unlock();
        }
        if (size < T_BUFFER_SIZE) {
            break;
        }
    }
}

int SerialIPC::c_availableForWrite() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->r_mutex));
    int cap = data->r_buffer->capacity();
    int size = data->r_buffer->size();
    return (cap - size);
}

int SerialIPC::c_available() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->t_mutex));
    return data->t_buffer->size();
}

size_t SerialIPC::c_write(uint8_t c) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->r_mutex));
    data->r_buffer->push_back(c);
    return 1;
}

int SerialIPC::c_read() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->t_mutex));
    int temp = -1;
    try {
        temp = data->t_buffer->at(0);
    } catch (boost::wrapexcept<std::out_of_range> &e) {
        temp = -1;
    }
    if (temp != -1) {
        data->t_buffer->pop_front();
    }
    return temp;
}

void SerialIPC::c_flush() {
    while (true) {
        unsigned int size = R_BUFFER_SIZE;
        bool is_locked = this->boost_objs->r_mutex.try_lock();
        if (is_locked) {
            size = data->r_buffer->size();
            this->boost_objs->r_mutex.unlock();
        }
        if (size < R_BUFFER_SIZE) {
            break;
        }
    }
}
