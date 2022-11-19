#ifndef __lcd_ipc__
#include "lcdipc.hpp"
#endif

#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>
#include <vector>

namespace bip = boost::interprocess;

/**
data structure for LCD
created in shared memory
*/
struct LcdIPC::lcdData {
   public:
    std::array<charBitMap, 80> lcd_disp;
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
    uint8_t buttons;

   private:
    uint8_t charset[256][7] = {
        {0},                           // 0
        {0},                           // 1
        {0},                           // 2
        {0},                           // 3
        {0},                           // 4
        {0},                           // 5
        {0},                           // 6
        {0},                           // 7
        {0},                           // 8
        {0},                           // 9
        {0},                           // 10
        {0},                           // 11
        {0},                           // 12
        {0},                           // 13
        {0},                           // 14
        {0},                           // 15
        {0},                           // 16
        {0},                           // 17
        {0},                           // 18
        {0},                           // 19
        {0},                           // 20
        {0},                           // 21
        {0},                           // 22
        {0},                           // 23
        {0},                           // 24
        {0},                           // 25
        {0},                           // 26
        {0},                           // 27
        {0},                           // 28
        {0},                           // 29
        {0},                           // 30
        {0},                           // 31
        {0},                           // 32
        {4, 4, 4, 4, 0, 0, 4},         // 33 !
        {10, 10, 10},                  // 34 "
        {10, 10, 31, 10, 31, 10, 10},  // 35 #
        {4, 15, 20, 14, 5, 30, 4},     // 36 $
        {24, 25, 2, 4, 8, 19, 3},      // 37 %
        {12, 18, 20, 8, 21, 18, 13},   // 38 &
        {12, 4, 8},                    // 39 '
        {2, 4, 8, 8, 8, 4, 2},         // 40 (
        {8, 4, 2, 2, 2, 4, 8},         // 41 )
        {0, 4, 21, 14, 21, 4},         // 42 *
        {0, 4, 4, 31, 4, 4},           // 43 +
        {0, 0, 0, 0, 12, 4, 8},        // 44 ,
        {0, 0, 0, 31},                 // 45 -
        {0, 0, 0, 0, 0, 12, 12},       // 46 .
        {0, 1, 2, 4, 8, 16},           // 47 /
        {14, 17, 19, 21, 25, 17, 14},  // 48 0
        {4, 12, 4, 4, 4, 4, 14},       // 49 1
        {14, 17, 1, 2, 4, 8, 31},      // 50 2
        {31, 2, 4, 2, 1, 17, 14},      // 51 3
        {2, 6, 10, 18, 31, 2, 2},      // 52 4
        {31, 16, 30, 1, 1, 17, 14},    // 53 5
        {6, 8, 16, 30, 17, 17, 14},    // 54 6
        {31, 1, 2, 4, 8, 8, 8},        // 55 7
        {14, 17, 17, 14, 17, 17, 14},  // 56 8
        {14, 17, 17, 15, 1, 2, 12},    // 57 9
        {0, 12, 12, 0, 12, 12},        // 58 :
        {0, 12, 12, 0, 12, 4, 8},      // 59 ;
        {2, 4, 8, 16, 8, 4, 2},        // 60 <
        {0, 0, 31, 0, 31},             // 61 =
        {8, 4, 2, 1, 2, 4, 8},         // 62 >
        {14, 17, 1, 2, 4, 0, 4},       // 63 ?
        {14, 17, 1, 13, 21, 21, 14},   // 64 @
        {14, 17, 17, 31, 17, 17, 17},  // 65 A
        {30, 17, 17, 30, 17, 17, 30},  // 66 B
        {14, 17, 16, 16, 16, 17, 14},  // 67 C
        {28, 18, 17, 17, 17, 18, 28},  // 68 D
        {31, 16, 16, 30, 16, 16, 31},  // 69 E
        {31, 16, 16, 30, 16, 16, 16},  // 70 F
        {14, 17, 16, 23, 17, 17, 15},  // 71 G
        {17, 17, 17, 31, 17, 17, 17},  // 72 H
        {14, 4, 4, 4, 4, 4, 14},       // 73 I
        {14, 2, 2, 2, 2, 18, 12},      // 74 J
        {17, 18, 20, 24, 20, 18, 17},  // 75 K
        {16, 16, 16, 16, 16, 16, 31},  // 76 L
        {17, 27, 21, 21, 17, 17, 17},  // 77 M
        {17, 17, 25, 21, 19, 17, 17},  // 78 N
        {14, 17, 17, 17, 17, 17, 14},  // 79 O
        {30, 17, 17, 30, 16, 16, 16},  // 80 P
        {14, 17, 17, 17, 21, 18, 13},  // 81 Q
        {30, 17, 17, 30, 20, 18, 17},  // 82 R
        {15, 16, 16, 14, 1, 1, 30},    // 83 S
        {31, 4, 4, 4, 4, 4, 4},        // 84 T
        {17, 17, 17, 17, 17, 17, 14},  // 85 U
        {17, 17, 17, 17, 17, 10, 4},   // 86 V
        {17, 17, 17, 21, 21, 21, 10},  // 87 W
        {17, 17, 10, 4, 10, 17, 17},   // 88 X
        {17, 17, 17, 10, 4, 4, 4},     // 89 Y
        {31, 1, 2, 4, 8, 16, 31},      // 90 Z
        {24, 16, 16, 16, 16, 16, 24},  // 91 [
        {17, 10, 31, 4, 31, 4, 4},     // 92 Yen
        {3, 1, 1, 1, 1, 1, 3},         // 93 ]
        {4, 10, 17},                   // 94 ^
        {0, 0, 0, 0, 0, 0, 31},        // 95 _
        {8, 4, 2},                     // 96 `
        {0, 0, 14, 1, 15, 17, 15},     // 97 a
        {16, 16, 22, 25, 17, 17, 30},  // 98 b
        {0, 0, 14, 16, 16, 17, 14},    // 99 c
        {1, 1, 13, 19, 17, 17, 15},    // 100 d
        {0, 0, 14, 17, 31, 16, 14},    // 101 e
        {6, 9, 8, 28, 8, 8, 8},        // 102 f
        {0, 15, 17, 17, 15, 1, 14},    // 103 g
        {16, 16, 22, 25, 17, 17, 17},  // 104 h
        {4, 0, 12, 4, 4, 4, 14},       // 105 i
        {2, 0, 6, 2, 2, 18, 12},       // 106 j
        {16, 16, 18, 20, 24, 20, 18},  // 107 k
        {12, 4, 4, 4, 4, 4, 31},       // 108 l
        {0, 0, 26, 21, 21, 17, 17},    // 109 m
        {0, 0, 22, 25, 17, 17, 17},    // 110 n
        {0, 0, 14, 17, 17, 17, 14},    // 111 o
        {0, 0, 30, 17, 30, 16, 16},    // 112 p
        {0, 0, 13, 19, 15, 1, 1},      // 113 q
        {0, 0, 22, 25, 16, 16, 16},    // 114 r
        {0, 0, 14, 16, 14, 1, 30},     // 115 s
        {8, 8, 28, 8, 8, 9, 6},        // 116 t
        {0, 0, 17, 17, 17, 19, 13},    // 117 u
        {0, 0, 17, 17, 17, 10, 4},     // 118 v
        {0, 0, 17, 17, 21, 21, 10},    // 119 w
        {0, 0, 17, 10, 4, 10, 17},     // 120 x
        {0, 0, 17, 17, 15, 1, 14},     // 121 y
        {0, 0, 31, 2, 4, 8, 31},       // 122 z
        {2, 4, 4, 8, 4, 4, 2},         // 123 {
        {4, 4, 4, 4, 4, 4, 4},         // 124 |
        {8, 4, 4, 2, 4, 4, 8},         // 125 }
        {0, 4, 2, 31, 2, 4},           // 126 ->
        {0, 4, 8, 31, 8, 4},           // 127 <-
        {0},                           // 128
        {0},                           // 129
        {0},                           // 130
        {0},                           // 131
        {0},                           // 132
        {0},                           // 133
        {0},                           // 134
        {0},                           // 135
        {0},                           // 136
        {0},                           // 137
        {0},                           // 138
        {0},                           // 139
        {0},                           // 140
        {0},                           // 141
        {0},                           // 142
        {0},                           // 143
        {0},                           // 144
        {0},                           // 145
        {0},                           // 146
        {0},                           // 147
        {0},                           // 148
        {0},                           // 149
        {0},                           // 150
        {0},                           // 151
        {0},                           // 152
        {0},                           // 153
        {0},                           // 154
        {0},                           // 155
        {0},                           // 156
        {0},                           // 157
        {0},                           // 158
        {0},                           // 159
        {0},                           // 160
        {0, 0, 0, 0, 28, 20, 28},      // 161
        {7, 4, 4, 4},                  // 162
        {0, 0, 0, 4, 4, 4, 28},        // 163
        {0, 0, 0, 0, 16, 8, 4},        // 164
        {0, 0, 0, 12, 12},             // 165
        {0, 31, 1, 31, 1, 2, 4},       // 166
        {0, 0, 31, 1, 6, 4, 8},        // 167
        {0, 0, 2, 4, 12, 20, 4},       // 168
        {0, 0, 4, 31, 17, 1, 14},      // 169
        {0, 0, 0, 31, 4, 4, 31},       // 170
        {0, 0, 2, 31, 6, 10, 18},      // 171
        {0, 0, 8, 31, 9, 10, 8},       // 172
        {0, 0, 0, 14, 2, 2, 31},       // 173
        {0, 0, 30, 2, 30, 2, 30},      // 174
        {0, 0, 0, 21, 21, 1, 6},       // 175
        {0, 0, 0, 31},                 // 176
        {31, 1, 5, 6, 4, 4, 8},        // 177
        {1, 2, 4, 12, 20, 4, 4},       // 178
        {4, 31, 17, 17, 1, 2, 4},      // 179
        {0, 31, 4, 4, 4, 4, 31},       // 180
        {2, 31, 2, 6, 10, 18, 2},      // 181
        {8, 31, 9, 9, 9, 9, 18},       // 182
        {4, 31, 4, 31, 4, 4, 4},       // 183
        {0, 15, 9, 17, 1, 2, 12},      // 184
        {8, 15, 18, 2, 2, 2, 4},       // 185
        {0, 31, 1, 1, 1, 1, 31},       // 186
        {10, 31, 10, 10, 2, 4, 8},     // 187
        {0, 24, 1, 25, 1, 2, 28},      // 188
        {0, 31, 1, 2, 4, 10, 17},      // 189
        {8, 31, 9, 10, 8, 8, 7},       // 190
        {0, 17, 17, 9, 1, 2, 12},      // 191
        {0, 15, 9, 21, 3, 2, 12},      // 192
        {2, 28, 4, 31, 4, 4, 8},       // 193
        {0, 21, 21, 21, 1, 2, 4},      // 194
        {14, 0, 31, 4, 4, 4, 8},       // 195
        {8, 8, 8, 12, 10, 8, 8},       // 196
        {4, 4, 31, 4, 4, 8, 16},       // 197
        {0, 14, 0, 0, 0, 0, 31},       // 198
        {0, 31, 1, 10, 4, 10, 16},     // 199
        {4, 31, 2, 4, 14, 21, 4},      // 200
        {2, 2, 2, 2, 2, 4, 8},         // 201
        {0, 4, 2, 17, 17, 17, 17},     // 202
        {16, 16, 31, 16, 16, 16, 15},  // 203
        {0, 31, 1, 1, 1, 2, 12},       // 204
        {0, 8, 20, 2, 1, 1},           // 205
        {4, 31, 4, 4, 21, 21, 4},      // 206
        {0, 31, 1, 1, 10, 4, 2},       // 207
        {0, 14, 0, 14, 0, 14, 1},      // 208
        {0, 4, 8, 16, 17, 31, 1},      // 209
        {0, 1, 1, 10, 4, 10, 16},      // 210
        {0, 31, 8, 31, 8, 8, 7},       // 211
        {8, 8, 31, 9, 10, 8, 8},       // 212
        {0, 14, 2, 2, 2, 2, 31},       // 213
        {0, 31, 1, 31, 1, 1, 31},      // 214
        {14, 0, 31, 1, 1, 2, 4},       // 215
        {18, 18, 18, 18, 2, 4, 8},     // 216
        {0, 4, 20, 20, 21, 21, 22},    // 217
        {0, 16, 16, 17, 18, 20, 24},   // 218
        {0, 31, 17, 17, 17, 17, 31},   // 219
        {0, 31, 17, 17, 1, 2, 4},      // 220
        {0, 24, 0, 1, 1, 2, 28},       // 221
        {4, 18, 8},                    // 222
        {28, 20, 28},                  // 223
        {0, 0, 9, 21, 18, 18, 13},     // 224 alpha
        {10, 0, 14, 1, 15, 17, 15},    // 225 a:
        {14, 17, 30, 17, 30, 16, 16},  // 226 beta
        {0, 0, 14, 16, 12, 17, 14},    // 227 epsilon
        {17, 17, 17, 19, 29, 16, 16},  // 228 mu
        {0, 0, 15, 20, 18, 17, 14},    // 229 sigma
        {6, 9, 17, 17, 30, 16, 16},    // 230 ro
        {15, 17, 17, 17, 15, 1, 1},    // 231
        {0, 0, 7, 4, 4, 20, 8},        // 232 sq root
        {0, 2, 26, 2},                 // 233 -1
        {1, 0, 3, 1, 1, 1, 1},         // 234 j
        {0, 20, 8, 20},                // 235 x
        {0, 4, 14, 20, 21, 14, 4},     // 236 cent
        {8, 8, 28, 8, 28, 8, 15},      // 237 poud
        {14, 0, 22, 25, 17, 17, 17},   // 238 n~
        {10, 0, 14, 17, 17, 17, 14},   // 239 o:
        {22, 25, 17, 17, 30, 16, 16},  // 240 p
        {13, 19, 17, 17, 15, 1, 1},    // 241 q
        {0, 14, 17, 31, 17, 17, 14},   // 242 theta
        {0, 0, 0, 11, 21, 26},         // 243 inf
        {0, 0, 14, 17, 17, 10, 27},    // 244 Omega
        {10, 0, 17, 17, 17, 19, 13},   // 245 u:
        {31, 16, 8, 4, 8, 16, 31},     // 246 Sigma
        {0, 0, 31, 10, 10, 10, 19},    // 247 pi
        {31, 0, 17, 10, 4, 10, 17},    // 248 x-
        {17, 17, 17, 17, 15, 1},       // 249 y
        {1, 30, 4, 31, 4, 4, 0},       // 250
        {0, 31, 8, 31, 9, 17, 0},      // 251
        {0, 31, 21, 31, 17, 17, 0},    // 252
        {0, 4, 0, 31, 0, 4, 0},        // 253 divide
        {0},                           // 254
        {31, 31, 31, 31, 31, 31, 31},  // 255
    };

   public:
    lcdData() {
        charBitMap temp;
        temp.fill(0);
        std::array<charBitMap, 80> temp_2;
        temp_2.fill(temp);
        this->lcd_disp = temp_2;
        this->curs_pos = 0;
        this->disp = true;
        this->curs_blink = false;
        this->curs_enabled = false;
        this->dir = true;
        this->back_light = 0;
        this->disp_pos = 0;
        this->auto_scroll = false;
    }

    /*
    Reads in char value and converts to a bitmap
    */
    charBitMap charTocharMap(uint16_t value) {
        charBitMap out;
        out.fill(*charset[value]);
        return out;
    }

    /*
    Set a custom char
    */
    void setCustomChar(charBitMap value, uint8_t loc) {
        std::copy(value.begin(), value.end(), std::begin(charset[loc % 8]));
    }

    /*
    Reads out a custom char
    */
    charBitMap getCustomChar(uint8_t loc) {
        charBitMap out;
        out.fill(*charset[loc % 8]);
        return out;
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
    // clears any existing shared memory and removes named mutex
    bip::shared_memory_object::remove("arduino_sm");
    bip::named_mutex::remove("arduino_mutex");
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
        this->data = this->boost_objs->managed_shm.construct<lcdData>("data_obj")();
#else
        this->data = this->boost_objs->managed_shm.find<lcdData>("data_obj").first;
        if (this->data == 0) {
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

LcdIPC::~LcdIPC() {
    delete this->boost_objs;
}

charBitMap LcdIPC::getLcdDisp(uint8_t loc) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    return this->data->lcd_disp[loc % 80];
}

void LcdIPC::setLcdDisp(uint8_t loc, char value) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    charBitMap character = this->data->charTocharMap(value);
    this->data->lcd_disp[loc % 80] = character;
}

size_t LcdIPC::write(uint8_t value) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    charBitMap character = this->data->charTocharMap(value);
    this->data->lcd_disp[this->data->curs_pos] = character;
    if (this->data->dir) {
        this->data->curs_pos++;
        this->data->curs_pos = (this->data->curs_pos % 80);
    } else {
        this->data->curs_pos--;
        this->data->curs_pos = (this->data->curs_pos);
        this->data->curs_pos = (this->data->curs_pos % 80);
    }

    if (this->data->auto_scroll) {
        this->data->disp_pos = this->data->curs_pos;
    }

    return 1;
}

charBitMap LcdIPC::getCustChars(uint8_t loc) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    return this->data->getCustomChar(loc);
}

void LcdIPC::setCustChars(uint8_t loc, charBitMap character) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    this->data->setCustomChar(character, loc);
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
    this->data->disp_pos = (this->data->disp_pos % 80);
}

void LcdIPC::shiftRight() {
    // shift display pointer
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    this->data->disp_pos++;
    this->data->disp_pos = (this->data->disp_pos % 80);
}

void LcdIPC::home() {
    // set cursor to pointer to zero
    // set display pointer to zero
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

void LcdIPC::setButton(uint8_t value) {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    this->data->buttons = value;
}

uint8_t LcdIPC::getButton() {
    bip::scoped_lock<bip::named_mutex> lock((this->boost_objs->mutex));
    return this->data->buttons;
}