#ifndef __lcd_ipc__
#include "lcdipc.hpp"
#endif

#include <cstdint>
#include <iostream>

#ifndef __charMap__
#include "./charSetMap.hpp"
#endif

#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

namespace bip = boost::interprocess;

/**
data structure for LCD
created in shared memory
*/
struct LcdIPC::lcdData {
   public:
    std::array<charBitMap, 80> lcd_disp;
    std::vector<charBitMap> cust_chars;
    uint8_t curs_pos;
    bool disp;
    bool curs_enabled;
    bool curs_blink;
    /**
    true is left to right
    false is right to left
    */
    bool dir;
    uint8_t back_light;
    uint8_t disp_pos;
    bool auto_scroll;

   public:
    lcdData() {
        charBitMap temp;
        temp.fill(0);
        std::array<charBitMap, 80> temp_2;
        temp_2.fill(temp);
        this->lcd_disp = temp_2;
        this->cust_chars = std::vector<charBitMap>();
        this->curs_pos = 0;
        this->disp = true;
        this->curs_blink = false;
        this->curs_enabled = false;
        this->dir = true;
        this->back_light = 0;
        this->disp_pos = 0;
        this->auto_scroll = false;
    }
};

/**
holds the boost specific objects
*/
struct LcdIPC::boost_struct {
   public:
    bip::named_mutex mutex;
    bip::managed_shared_memory managed_shm;

   public:
    /*
    create only for ArdunioWrapper
    open only for test library
    */
#ifndef CONSUMER
    boost_struct() : mutex(bip::create_only, "arduino_mutex"), managed_shm{bip::create_only, "arduino_sm", 1048576} {
    }
#else
    boost_struct() : mutex(bip::open_only, "arduino_mutex"), managed_shm(bip::open_only, "arduino_sm") {
    }
#endif
    ~boost_struct() {
#ifndef CONSUMER
        /*
        Removes boost objects required as shared memory and mutexes are presistent
        Only required by the ArduinoWrapper library not the test library
        */
        bip::named_mutex::remove("arduino_mutex");
        bip::shared_memory_object::remove("arduino_sm");
#endif
    }
};


LcdIPC::LcdIPC() {

#ifndef CONSUMER
    //clears any existing shared memory and removes named mutex
    bip::shared_memory_object::remove("arduino_sm");
    bip::named_mutex::remove("arduino_mutex");
#endif  
       
    try {
        this->boost_objs = new boost_struct();
    } catch (bip::interprocess_exception &e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Cannot find shared memory or named mutex" << "\n";
        throw std::bad_alloc();
    }

    try {
#ifndef CONSUMER
        this->data = this->boost_objs->managed_shm.construct<lcdData>("data_obj")();
#else
        this->data = this->boost_objs->managed_shm.find<lcdData>("data_obj").first;
        if (this->data == 0) {
            throw bip::bad_alloc();
        }
#endif
    }
     catch (bip::bad_alloc &e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Failed to find object in shared memory" << "\n";
        throw std::bad_alloc();
    }
}

LcdIPC::~LcdIPC() {
    delete this->boost_objs;
}


charBitMap LcdIPC::getLcdDisp(uint8_t loc) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    return this->data->lcd_disp[loc % 80];
}

void LcdIPC::setLcdDisp(uint8_t loc, char value) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    charBitMap character = charTocharMap(value);
    this->data->lcd_disp[loc % 80] = character;
}

void LcdIPC::write(uint8_t value) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    charBitMap character = charTocharMap(value);
    this->data->lcd_disp[this->data->curs_pos] = character;
    if (this->data->dir) {
        this->data->curs_pos++;
        this->data->curs_pos = (this->data->curs_pos % 80);
    } else {
        this->data->curs_pos--;
        this->data->curs_pos = abs(this->data->curs_pos);
        this->data->curs_pos = (this->data->curs_pos % 80);
    }
    //TODO AUTOSCROLL
}

charBitMap LcdIPC::getCustChars(uint8_t loc) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    return this->data->cust_chars[loc % 8];
}

void LcdIPC::setCustChars(uint8_t loc, charBitMap character) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    this->data->cust_chars[loc % 8] = character;
}

uint8_t LcdIPC::getCursorPos() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    return this->data->curs_pos;
}

void LcdIPC::setCursorPos(uint8_t value) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    this->data->curs_pos = value;
}

bool LcdIPC::getDisp() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    return this->data->disp;
}

void LcdIPC::setDisp(bool value) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    this->data->disp = value;
}

bool LcdIPC::getCursEnabled() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    return this->data->curs_enabled;
}

void LcdIPC::setCursEnabled(bool value) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    this->data->curs_enabled = value;
}

bool LcdIPC::getCursBlink() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    return this->data->curs_blink;
}

void LcdIPC::setCursBlink(bool value) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    this->data->curs_blink = value;
}

bool LcdIPC::getDir() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    return this->data->dir;
}

void LcdIPC::setDir(bool value) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    this->data->dir = value;
}

uint8_t LcdIPC::getBackLight() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    return this->data->back_light;
    
}

void LcdIPC::setBackLight(uint8_t value) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    this->data->back_light = value;
}

uint8_t LcdIPC::getDispPos() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    return this->data->disp_pos;
}

void LcdIPC::setDispPos(uint8_t value) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    this->data->disp_pos = value;
}

void LcdIPC::clearDisp() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    charBitMap temp;
    temp.fill(0);
    this->data->lcd_disp.fill(temp);
    home();
}

void LcdIPC::shiftLeft() {
    // shift display pointer
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    this->data->disp_pos--;
    this->data->disp_pos = abs(this->data->disp_pos);
    this->data->disp_pos = (this->data->disp_pos % 80);
}

void LcdIPC::shiftRight() {
    // shift display pointer
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    this->data->disp_pos++;
    this->data->disp_pos = (this->data->disp_pos % 80);
}

void LcdIPC::home() {
    //set cursor to pointer to zero
    //set display pointer to zero
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    this->data->curs_pos = 0;
    this->data->disp_pos = 0;
}

void LcdIPC::setAutoScroll(bool value) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    this->data->auto_scroll = value;
}

bool LcdIPC::getAutoScroll() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    return this->data->auto_scroll;
}
