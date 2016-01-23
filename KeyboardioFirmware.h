#pragma once

#include <Arduino.h>
//add your includes for the project KeyboardIO here
#include <EEPROM.h>

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project KeyboardIO here


#include <stdio.h>
#include <math.h>
#include <avr/wdt.h>
#include "key_defs.h"
#include "KeyboardConfig.h"

#include "generated/keymaps.h"
#include "debouncing.h"
#include "led_control.h"
#include <Wire.h>
#include "KeyboardioSX1509.h"

//extern int usbMaxPower;

char x;
char y;

byte matrixState[ROWS][COLS];
static const Key keymaps[KEYMAPS][ROWS][COLS] = { KEYMAP_LIST };

long reporting_counter = 0;
byte primary_keymap = 0;
byte temporary_keymap = 0;



byte commandBuffer[32];
int commandBufferSize;
bool commandMode;
bool commandPromptPrinted;


// Console related
void process_command_buffer();

// EEPROM related
void save_primary_keymap(byte keymap);
byte load_primary_keymap();



// Mouse-related methods

double mouse_accel (double cycles);
void handle_mouse_movement( char x, char y);
void begin_warping();
void end_warping();
void warp_mouse(Key key);

// hardware keymap interaction
void setup_pins();
void setup_input_pins();
void setup_output_pins();
void scan_matrix();

// key matrix
void setup_matrix();
void reset_matrix();
void handle_immediate_action_during_matrix_scan(Key keymapEntry, byte matrixStateEntry);

// keymaps
void set_keymap_keymap(Key keymapEntry, byte matrixStateEntry);

// sending events to the computer
void handle_synthetic_key_press(byte switchState, Key mappedKey);
void handle_mouse_key_press(byte switchState, Key mappedKey, char &x, char &y);
void send_key_events();
void send_key_event(byte row, byte col);
void press_key(Key mappedKey);

int setup_sx1509(sx1509Class sx1509, int colpins[], int rowpins[]);

#ifndef VERSION
#define VERSION "locally-built"
#endif

