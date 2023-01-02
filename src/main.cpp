#include <Arduino.h>
#include <USB-MIDI.h>

#define BTN0 8
#define BTN1 9
#define BTN2 10

// MIDI_CREATE_DEFAULT_INSTANCE();

USBMIDI_CREATE_DEFAULT_INSTANCE();

// #if defined(ARDUINO_SAM_DUE) || defined(USBCON)
//     // Print through USB and bench with Hardware serial
//     MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiBench);
// #else
//     #include <SoftwareSerial.h>
//     SoftwareSerial midiSerial(2,3);
//     MIDI_CREATE_INSTANCE(SoftwareSerial, midiSerial, midiBench);
// #endif

int note0 = 36;
int note1 = 38;
int note2 = 42;

int btn0LastState = HIGH;
int btn1LastState = HIGH;
int btn2LastState = HIGH;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BTN0, INPUT_PULLUP);
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  MIDI.begin(4);

  // Serial.begin(16000);
}

void checkBtn(int btn, int note, int &lastState) {
  if (digitalRead(btn) == LOW) {
    if(lastState == HIGH) {
      MIDI.sendNoteOn(note, 127, 1); 
      lastState = LOW;
    }
  } else {
    MIDI.sendNoteOff(note, 0, 1); 
    lastState = HIGH;
  }
}

void loop() {

  checkBtn(BTN0, note0, btn0LastState);
  checkBtn(BTN1, note1, btn1LastState);
  checkBtn(BTN2, note2, btn2LastState);


  // if (digitalRead(BTN0) == LOW) {
  //   if(btn0LastState == HIGH) {
  //     MIDI.sendNoteOn(note0, 127, 1); 
  //     btn0LastState = LOW;
  //   }
  // } else {
  //   MIDI.sendNoteOff(note0, 0, 1); 
  //   btn0LastState = HIGH;
  // }

  // if (digitalRead(BTN1) == LOW) {
  //   if(btn1LastState == HIGH) {
  //     MIDI.sendNoteOn(note1, 127, 1); 
  //     btn1LastState = LOW;
  //   }
  // } else {
  //   MIDI.sendNoteOff(note1, 0, 1); 
  //   btn1LastState = HIGH;
  // }

  // if (digitalRead(BTN2) == LOW) {
  //   if(btn2LastState == HIGH) {
  //     MIDI.sendNoteOn(note2, 127, 1); 
  //     btn2LastState = LOW;
  //   }
  // } else {
  //   MIDI.sendNoteOff(note2, 0, 1); 
  //   btn2LastState = HIGH;
  // }
  
}