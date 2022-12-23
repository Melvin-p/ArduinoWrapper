/*
    Code taken from Adafruit_RGBLCDShield.h at https://github.com/adafruit/Adafruit-RGB-LCD-Shield-Library
*/

#define BUTTON_UP 0x08      //!< Up button
#define BUTTON_DOWN 0x04    //!< Down button
#define BUTTON_LEFT 0x10    //!< Left button
#define BUTTON_RIGHT 0x02   //!< Right button
#define BUTTON_SELECT 0x01  //!< Select button
#define LCD_5x8DOTS 0x00    //!< 8 pixel high font mode0

#define __lcd__

#ifndef __cus_print__
#include "print.hpp"
#endif

class Adafruit_RGBLCDShield : public Print {
   public:
    void init(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

    Adafruit_RGBLCDShield();

    ~Adafruit_RGBLCDShield();

    void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);

    /*!
     * @brief High-level command to clear the display
     */
    void clear();
    /*!
     * @brief High-level command to set the cursor position to zero
     */
    void home();

    /*!
     * @brief High-level command to turn the display off
     */
    void noDisplay();
    /*!
     * @brief High-level command to turn the display on
     */
    void display();
    /*!
     * @brief High-level command to turn off the blinking cursor off
     */
    void noBlink();
    /*!
     * @brief High-level command to turn on the blinking cursor
     */
    void blink();
    /*!
     * @brief High-level command to turn the underline cursor off
     */
    void noCursor();
    /*!
     * @brief High-level command to turn the underline cursor on
     */
    void cursor();
    /*!
     * @brief High-level command to scroll display left without changing the RAM
     */
    void scrollDisplayLeft();
    /*!
     * @brief High-level command to scroll display right without changing the RAM
     */
    void scrollDisplayRight();
    /*!
     * @brief High-level command to make text flow right to left
     */
    void leftToRight();
    /*!
     * @brief High-level command to make text flow left to right
     */
    void rightToLeft();
    /*!
     * @brief High-level command to 'right justify' text from cursor
     */
    void autoscroll();
    /*!
     * @brief High-level command to 'left justify' text from cursor
     */
    void noAutoscroll();

    /*!
     * @brief High-level command to set the backlight, only if the LCD backpack is
     * used
     * @param status Status to set the backlight
     */
    void setBacklight(uint8_t status);

    /*!
     * @brief High-level command that creates custom characters in CGRAM
     * @param location Location in cgram to fill
     * @param charmap[] Character map to use
     */
    void createChar(uint8_t, uint8_t[]);

    /*!
     * @brief High-level command that sets the location of the cursor
     * @param col Column to put the cursor in
     * @param row Row to put the cursor in
     */
    void setCursor(uint8_t, uint8_t);

    /*!
     * @brief Mid-level command that sends data to the display
     * @param value Data to send to the display
     */
    virtual size_t write(uint8_t);

    /*!
     * @brief reads the buttons from the shield
     * @return Returns what buttons have been pressed
     */
    uint8_t readButtons();
};
