#include "lcdipc.hpp"
#include <cstdint>

#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

namespace bip = boost::interprocess;

/**
data structure for LCD
*/
struct LcdIPC::lcdData {
   public:
    std::array<char_map, 80> lcd_disp;
    std::vector<char_map> cust_chars;
    uint8_t curs_pos;
    bool disp;
    bool curs_enabled;
    bool curs_blink;
    /**
    true is right
    false is left
    */
    bool dir;
    uint8_t back_light;
    uint8_t disp_pos;

   public:
    lcdData() {
        char_map temp;
        temp.fill(0);
        std::array<char_map, 80> temp_2;
        temp_2.fill(temp);
        this->lcd_disp = temp_2;
        this->cust_chars = std::vector<char_map>();
        this->curs_pos = 0;
        this->disp = true;
        this->curs_blink = false;
        this->curs_enabled = false;
        this->dir = true;
        this->back_light = 0;
        this->disp_pos = 0;
    }
};

struct LcdIPC::other {
   public:
    bip::named_mutex mutex;
    bip::managed_shared_memory managed_shm;

   public:
    other() : mutex(bip::create_only, "arduino_mutex"), managed_shm{bip::create_only, "arduino_sm", 1048576} {
    }
    ~other() {
#ifndef CONSUMER
        bip::named_mutex::remove("arduino_mutex");
#endif
    }
};


LcdIPC::LcdIPC() {

#ifndef CONSUMER
    //clears any existing shared memory
    bip::shared_memory_object::remove("arduino_sm");
#endif  

    this->lock = new other();

    try {
        this->data = this->lock->managed_shm.construct<lcdData>("data_obj")();
    } catch (boost::interprocess::bad_alloc &e) {
        throw std::bad_alloc();
    }
}

LcdIPC::~LcdIPC() {
#ifndef CONSUMER
    bip::shared_memory_object::remove("arduino_sm");
    
#endif
    delete this->lock;
}


char_map LcdIPC::getLcdDisp(uint8_t loc) {
    bip::scoped_lock<bip::named_mutex> lock((this->lock->mutex));
    return this->data->lcd_disp[loc % 80];
}

void LcdIPC::setLcdDisp(uint8_t loc, char_map character) {
    bip::scoped_lock<bip::named_mutex> lock((this->lock->mutex));
    this->data->lcd_disp[loc % 80] = character;
}

char_map LcdIPC::getCustChars(uint8_t loc) {
    bip::scoped_lock<bip::named_mutex> lock((this->lock->mutex));
    return this->data->cust_chars[loc % 8];
}

void LcdIPC::setCustChars(uint8_t loc, char_map character) {
    bip::scoped_lock<bip::named_mutex> lock((this->lock->mutex));
    this->data->cust_chars[loc % 8] = character;
}

uint8_t LcdIPC::getCursorPos() {
    bip::scoped_lock<bip::named_mutex> lock((this->lock->mutex));
    return this->data->curs_pos;
}

void LcdIPC::setCursorPos(bool value) {
    bip::scoped_lock<bip::named_mutex> lock((this->lock->mutex));
    this->data->curs_pos = value;
}

bool LcdIPC::getDisp() {
    bip::scoped_lock<bip::named_mutex> lock((this->lock->mutex));
    return this->data->disp;
}

void LcdIPC::setDisp(bool value) {
    bip::scoped_lock<bip::named_mutex> lock((this->lock->mutex));
    this->data->disp = value;
}

bool LcdIPC::getCursEnabled() {
    bip::scoped_lock<bip::named_mutex> lock((this->lock->mutex));
    return this->data->curs_enabled;
}

void LcdIPC::setCursEnabled(bool value) {
    bip::scoped_lock<bip::named_mutex> lock((this->lock->mutex));
    this->data->curs_enabled = value;
}

bool LcdIPC::getCursBlink() {
    bip::scoped_lock<bip::named_mutex> lock((this->lock->mutex));
    return this->data->curs_blink;
}

void LcdIPC::setCursBlink(bool value) {
    bip::scoped_lock<bip::named_mutex> lock((this->lock->mutex));
    this->data->curs_blink = value;
}

bool LcdIPC::getDir() {
    bip::scoped_lock<bip::named_mutex> lock((this->lock->mutex));
    return this->data->dir;
}

void LcdIPC::setDir(bool value) {
    bip::scoped_lock<bip::named_mutex> lock((this->lock->mutex));
    this->data->dir = value;
}

uint8_t LcdIPC::getBackLight() {
    bip::scoped_lock<bip::named_mutex> lock((this->lock->mutex));
    return this->data->back_light;
    
}

void LcdIPC::setBackLight(uint8_t value) {
    bip::scoped_lock<bip::named_mutex> lock((this->lock->mutex));
    this->data->back_light = value;
}

uint8_t LcdIPC::getDispPos() {
    bip::scoped_lock<bip::named_mutex> lock((this->lock->mutex));
    return this->data->disp_pos;
}

void LcdIPC::setDispPos(uint8_t value) {
    bip::scoped_lock<bip::named_mutex> lock((this->lock->mutex));
    this->data->disp_pos = value;
}
