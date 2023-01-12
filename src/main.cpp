#include <Arduino.h>
#include <USB-MIDI.h>

#define BTN0 4
#define BTN1 5
#define BTN2 6
#define BTN3 7
#define BTN4 8
#define BTN5 9
#define BTN6 10
#define BTN7 11
#define SWITCH0 12
#define SWITCH1 13
#define POT0 A0
#define POT1 A1
#define POT2 A2

USBMIDI_CREATE_DEFAULT_INSTANCE();

int noteKnob = 0;
int velocityKnob = 0;
int velocity = 127;
int baseNote = 21;
int note0 = 36;
int note1 = 38;
int note2 = 42;
int note3 = 36;
int note4 = 38;
int note5 = 42;
int note6 = 36;
int note7 = 36;

int scaleKnob = 0;
int scale = 0;

int btn0LastState = HIGH;
int btn1LastState = HIGH;
int btn2LastState = HIGH;
int btn3LastState = HIGH;
int btn4LastState = HIGH;
int btn5LastState = HIGH;
int btn6LastState = HIGH;
int btn7LastState = HIGH;

void setNotes() {
  if (scale == 0) {
    note0 = baseNote;
    note1 = baseNote + 2;
    note2 = baseNote + 4;
    note3 = baseNote + 5;
    note4 = baseNote + 7;
    note5 = baseNote + 8;
    note6 = baseNote + 11;
    note7 = baseNote + 13;
  } else if (scale == 1) {
    note0 = baseNote;
    note1 = baseNote + 2;
    note2 = baseNote + 3;
    note3 = baseNote + 5;
    note4 = baseNote + 7;
    note5 = baseNote + 8;
    note6 = baseNote + 11;
    note7 = baseNote + 13;
  } else if (scale == 2) {
    note0 = baseNote;
    note1 = baseNote + 2;
    note2 = baseNote + 3;
    note3 = baseNote + 5;
    note4 = baseNote + 7;
    note5 = baseNote + 9;
    note6 = baseNote + 10;
    note7 = baseNote + 13;
  } else if (scale == 3) {
    note0 = baseNote;
    note1 = baseNote + 1;
    note2 = baseNote + 3;
    note3 = baseNote + 5;
    note4 = baseNote + 6;
    note5 = baseNote + 8;
    note6 = baseNote + 10;
    note7 = baseNote + 12;
  }
}

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
  pinMode(SWITCH0, INPUT_PULLUP);
  pinMode(SWITCH1, INPUT_PULLUP);
  MIDI.begin(4);

  noteKnob = analogRead(POT2);
  baseNote = map(noteKnob, 1023, 0, 0, 116);

  scaleKnob = analogRead(POT2);
  scale = map(noteKnob, 1023, 0, 0, 3);

  setNotes();

  // Serial.begin(9600);
}

void checkBtn(int btn, int note, int &lastState) {
  if (digitalRead(btn) == LOW) {
    if(lastState == HIGH) {
      if (digitalRead(SWITCH1) == HIGH) {
        MIDI.sendNoteOn(note, velocity, 1); 
        lastState = LOW;
        // Serial.println(velocityKnob);
      }
    }
  } else {
    MIDI.sendNoteOff(note, 0, 1);
    lastState = HIGH;
  }
}

void loop() {

  if(digitalRead(SWITCH1) == LOW) {
    noteKnob = analogRead(POT2);

    baseNote = map(noteKnob, 1023, 0, 0, 116);
    setNotes();
  }
  
  velocityKnob = analogRead(POT1);
  velocity = map(velocityKnob, 1023, 0, 1, 127);
  
  if(digitalRead(SWITCH0) == LOW) {
    checkBtn(BTN0, note0, btn0LastState);
    checkBtn(BTN1, note1, btn1LastState);
    checkBtn(BTN2, note2, btn2LastState);
    checkBtn(BTN3, note3, btn3LastState);
    checkBtn(BTN4, note4, btn4LastState);
    checkBtn(BTN5, note5, btn5LastState);
    checkBtn(BTN6, note6, btn6LastState);
    checkBtn(BTN7, note7, btn7LastState);
  } else {
    checkBtn(BTN0, 36, btn0LastState);
    checkBtn(BTN1, 38, btn1LastState);
    checkBtn(BTN2, 48, btn2LastState);
    checkBtn(BTN3, 41, btn3LastState);
    checkBtn(BTN4, 45, btn4LastState);
    checkBtn(BTN5, 42, btn5LastState);
    checkBtn(BTN6, 46, btn6LastState);
    checkBtn(BTN7, 55, btn7LastState);
  }
}
