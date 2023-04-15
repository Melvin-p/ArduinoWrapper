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

#include "eepromIPC.hpp"

#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>

namespace bip = boost::interprocess;

#define shm_size 1048576

struct eepromIPC::Data {
   public:
    std::array<uint8_t, E_BUFFER_SIZE> eeprom_buffer;

    Data() {
        eeprom_buffer.fill(255);
    }
};

struct eepromIPC::boost_struct {
   public:
    bip::named_mutex e_mutex;
    bip::managed_shared_memory managed_shm;
    std::string ard_ipc;

   public:
    /*
    create only for ArduinoWrapper
    open only for test library
    */
#ifndef CONSUMER
    boost_struct(std::string ard_ipc)
        : e_mutex(bip::create_only, (ard_ipc + "eeprom_mutex").c_str()),
          managed_shm{bip::create_only, (ard_ipc + "eeprom_sm").c_str(), shm_size},
          ard_ipc(ard_ipc) {
    }
#else
    boost_struct(std::string ard_ipc)
        : e_mutex(bip::open_only, (ard_ipc + "eeprom_mutex").c_str()),
          managed_shm{bip::open_only, (ard_ipc + "eeprom_sm").c_str()},
          ard_ipc(ard_ipc) {
    }
#endif
    ~boost_struct() {
#ifndef CONSUMER
        /*
        Removes boost objects required as shared memory and mutexes are persistent
        Only required by the ArduinoWrapper library not the test library
        */
        bip::named_mutex::remove((ard_ipc + "eeprom_mutex").c_str());
        bip::shared_memory_object::remove((ard_ipc + "eeprom_sm").c_str());
#endif
    }
};

eepromIPC::eepromIPC() {
    std::string out = "";
    auto value = getenv("ard_ipc");
    if (value != nullptr) {
        out.append(value);
    }
#ifndef CONSUMER
    // clears any existing shared memory and removes named r_mutex
    bip::shared_memory_object::remove((out + "eeprom_sm").c_str());
    bip::named_mutex::remove((out + "eeprom_mutex").c_str());
#endif

    try {
        this->boost_objs = new boost_struct(out);
    } catch (bip::interprocess_exception &e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Cannot find shared memory or mutexes"
                  << "\n";
        throw std::bad_alloc();
    }

    try {
#ifndef CONSUMER
        this->data = this->boost_objs->managed_shm.construct<Data>("e_buffer")();
#else
        this->data = this->boost_objs->managed_shm.find<Data>("e_buffer").first;
        if (this->data = nullptr) {
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

eepromIPC::~eepromIPC() {
    delete this->boost_objs;
}

uint8_t eepromIPC::eeprom_read_byte(const uint8_t p) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->e_mutex));
    int temp = 255;

    temp = this->data->eeprom_buffer[p & E_BUFFER_SIZE];

    return temp;
}

void eepromIPC::eeprom_write_byte(uint8_t p, uint8_t value) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->e_mutex));
    this->data->eeprom_buffer[p & E_BUFFER_SIZE] = value;
}

std::array<uint8_t, E_BUFFER_SIZE> eepromIPC::getEEPROM() {
    return data->eeprom_buffer;
}