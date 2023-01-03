#include <Arduino.h>
#include <USB-MIDI.h>

#define BTN0 6
#define BTN1 7
#define BTN2 8
#define BTN3 9
#define BTN4 10
#define BTN5 11
#define BTN6 12
#define BTN7 13

USBMIDI_CREATE_DEFAULT_INSTANCE();

int noteKnob = 0;
int baseNote = 21;
int note0 = 36;
int note1 = 38;
int note2 = 42;
int note3 = 36;
int note4 = 38;
int note5 = 42;
int note6 = 36;
int note7 = 36;

int btn0LastState = HIGH;
int btn1LastState = HIGH;
int btn2LastState = HIGH;
int btn3LastState = HIGH;
int btn4LastState = HIGH;
int btn5LastState = HIGH;
int btn6LastState = HIGH;
int btn7LastState = HIGH;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BTN0, INPUT_PULLUP);
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);
  pinMode(BTN4, INPUT_PULLUP);
  pinMode(BTN5, INPUT_PULLUP);
  pinMode(BTN6, INPUT_PULLUP);
  pinMode(BTN7, INPUT_PULLUP);
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
  noteKnob = analogRead(A0);
  baseNote = map(noteKnob, 0, 1023, 21, 32);
  note0 = baseNote;
  note1 = baseNote + 11;
  note2 = baseNote + 22;
  note3 = baseNote + 33;
  note4 = baseNote + 44;
  note5 = baseNote + 55;
  note6 = baseNote + 66;
  note7 = baseNote + 77;

  checkBtn(BTN0, note0, btn0LastState);
  checkBtn(BTN1, note1, btn1LastState);
  checkBtn(BTN2, note2, btn2LastState);
  checkBtn(BTN3, note3, btn3LastState);
  checkBtn(BTN4, note4, btn4LastState);
  checkBtn(BTN5, note5, btn5LastState);
  checkBtn(BTN6, note6, btn6LastState);
  checkBtn(BTN7, note7, btn7LastState);
}
