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

#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>

#include "./private_serial.hpp"

namespace bip = boost::interprocess;

SerialIPC *SerialIPC::instance = nullptr;

/**
holds the boost specific objects
*/
struct SerialIPC::boost_struct {
   public:
    bip::named_mutex mutex;
    bip::managed_shared_memory managed_shm;

   public:
    /*
    create only for ArdunioWrapper
    open only for test library
    */
#ifndef CONSUMER
    boost_struct() : mutex(bip::create_only, "serial_mutex"), managed_shm{bip::create_only, "serial_sm", 1048576} {
    }
#else
    boost_struct() : mutex(bip::open_only, "serial_mutex"), managed_shm(bip::open_only, "serial_sm") {
    }
#endif
    ~boost_struct() {
#ifndef CONSUMER
        /*
        Removes boost objects required as shared memory and mutexes are presistent
        Only required by the ArduinoWrapper library not the test library
        */
        bip::named_mutex::remove("serial_mutex");
        bip::shared_memory_object::remove("serial_sm");
#endif
    }
};

SerialIPC::SerialIPC() {
#ifndef CONSUMER
    // clears any existing shared memory and removes named mutex
    bip::shared_memory_object::remove("serial_sm");
    bip::named_mutex::remove("serial_mutex");
#endif

    try {
        this->boost_objs = new boost_struct();
    } catch (bip::interprocess_exception &e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Cannot find shared memory or named mutex"
                  << "\n";
        throw std::bad_alloc();
    }

    try {
#ifndef CONSUMER
        this->queue = this->boost_objs->managed_shm.construct<Buffers>("something")(64, this->boost_objs->managed_shm.get_segment_manager());
#else
        this->queue = this->boost_objs->managed_shm.find<Buffers>("something").first;
        if (this->queue == nullptr) {
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
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    this->queue->push_back(c);
    return 1;
}

int SerialIPC::read() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    int temp = this->queue->at(0);
    this->queue->pop_front();
    return temp;
}

int SerialIPC::peek() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    int temp = this->queue->at(0);
    return temp;
}

int SerialIPC::availableForWrite() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    int cap = this->queue->capacity();
    int size = this->queue->size();
    return (cap - size);
}

int SerialIPC::available() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    return this->queue->size();
}

void SerialIPC::flush() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    while (this->queue->size() > 0) {
    }
}