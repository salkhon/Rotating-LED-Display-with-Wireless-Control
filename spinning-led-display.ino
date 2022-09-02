#include "RTClib.h"

RTC_DS1307 rtc;

byte NUMBER9[] = { 0b11110001, 0b10010001, 0b10010001, 0b10010001, 0b11111111 };
byte NUMBER8[] = { 0b01101110, 0b10010001, 0b10010001, 0b10010001, 0b01101110 };
byte NUMBER7[] = { 0b10000000, 0b10001000, 0b10001000, 0b10011111, 0b11101000 };
byte NUMBER6[] = { 0b11111111, 0b10001001, 0b10001001, 0b10001001, 0b10001111 };
byte NUMBER5[] = { 0b11111001, 0b10001001, 0b10001001, 0b10001001, 0b10001111 };
byte NUMBER4[] = { 0b11110000, 0b00010000, 0b00010000, 0b00010000, 0b11111111 };
byte NUMBER3[] = { 0b10010001, 0b10010001, 0b10010001, 0b10010001, 0b11111111 };
byte NUMBER2[] = { 0b10000011, 0b10000101, 0b10001001, 0b10010001, 0b01100001 };
byte NUMBER1[] = { 0b00000000, 0b00000000, 0b11111111, 0b00000000, 0b00000000 };
byte NUMBER0[] = { 0b11111111, 0b10000001, 0b10000001, 0b10000001, 0b11111111 };
byte _[] = { 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000 };

byte A[] = { 0b11111111, 0b10010000, 0b10010000, 0b10010000, 0b11111111 };
byte B[] = { 0b11111111, 0b10010001, 0b10010001, 0b10010001, 0b01101110 };
byte C[] = { 0b00111100, 0b01000010, 0b10000001, 0b10000001, 0b10000001 };
byte D[] = { 0b11111111, 0b10000001, 0b10000001, 0b01000010, 0b00111100 };
byte E[] = { 0b11111111, 0b10010001, 0b10010001, 0b10010001, 0b10010001 };
byte F[] = { 0b11111111, 0b10010000, 0b10010000, 0b10010000, 0b10010000 };
byte G[] = { 0b01111111, 0b10000001, 0b10001001, 0b10001001, 0b10001110 };
byte H[] = { 0b11111111, 0b00001000, 0b00001000, 0b00001000, 0b11111111 };
byte I[] = { 0b10000001, 0b10000001, 0b11111111, 0b10000001, 0b10000001 };
byte J[] = { 0b00000110, 0b00001001, 0b00000001, 0b00000001, 0b11111110 };
byte K[] = { 0b11111111, 0b00011000, 0b00100100, 0b01000010, 0b10000001 };
byte L[] = { 0b11111111, 0b00000001, 0b00000001, 0b00000001, 0b00000001 };
byte M[] = { 0b11111111, 0b01000000, 0b00100000, 0b01000000, 0b11111111 };
byte N[] = { 0b11111111, 0b00100000, 0b00011000, 0b00000100, 0b11111111 };
byte O[] = { 0b01111110, 0b10000001, 0b10000001, 0b10000001, 0b01111110 };
byte P[] = { 0b11111111, 0b10010000, 0b10010000, 0b10010000, 0b01100000 };
byte Q[] = { 0b01111110, 0b10000001, 0b10000101, 0b01111110, 0b00000001 };
byte R[] = { 0b11111111, 0b10011000, 0b10010100, 0b10010010, 0b01100001 };
byte S[] = { 0b01110001, 0b10001001, 0b10001001, 0b10001001, 0b10001110 };
byte T[] = { 0b10000000, 0b10000000, 0b11111111, 0b10000000, 0b10000000 };
byte U[] = { 0b11111110, 0b00000001, 0b00000001, 0b00000001, 0b11111110 };
byte V[] = { 0b11111100, 0b00000010, 0b00000001, 0b00000010, 0b11111100 };
byte W[] = { 0b11111111, 0b00000010, 0b00000100, 0b00000010, 0b11111111 };
byte X[] = { 0b11000011, 0b00100100, 0b00011000, 0b00100100, 0b11000011 };
byte Y[] = { 0b11000000, 0b00100000, 0b00011111, 0b00100000, 0b11000000 };
byte Z[] = { 0b10000111, 0b10001001, 0b10010001, 0b10100001, 0b11000001 };

byte dummy[] = {};
byte* alpha[] = { A, B, C, D, E, F, G, H, NUMBER1, J, K, L, M, N, NUMBER0, P, dummy, R, NUMBER5, T, U, V, W, X, Y, Z };
byte* num[] = { NUMBER0, NUMBER1, NUMBER2, NUMBER3, NUMBER4, NUMBER5, NUMBER6, NUMBER7, NUMBER8, NUMBER9 };

int ledPins[] = { A2, 3, 4, 5, 13, 6, 7, 8, 9, 10, 11, 12 };
const byte NUM_LED_PINS = 12;

int LETTER_SPACE_uS;
int DOT_TIME_uS;
unsigned ANLG_DOT_TIME_uS;
unsigned ANLG_UNIT_SPACE_uS;

String str_from_bt;
String displayStr;

unsigned long prev_rpm_update_ms;
unsigned long rpm;
unsigned long rotations;

bool color;
enum Mode {
    DigitalClock, BluetoothString, AnalogClock, RPMDisplay
};

Mode mode;

unsigned hour;
unsigned minute;
unsigned second;

unsigned propeller_posn;
unsigned n;

void setup() {
    Serial.begin(38400);

    pinMode(2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(2), displayStr_ISR, FALLING);

    // setting the ports of the leds to OUTPUT(SExperiments)
    for (int i = 3; i <= 13; i++) {
        pinMode(i, OUTPUT);
    }

    pinMode(A2, OUTPUT);
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    digitalWrite(A0, HIGH);//yellow
    digitalWrite(A1, LOW);

    displayStr = "123";

    // defining the time dots appear (ms)
    DOT_TIME_uS = 200;
    // defining the space between the letters (ms)
    LETTER_SPACE_uS = 800;

    ANLG_DOT_TIME_uS = 50;
    ANLG_UNIT_SPACE_uS = 200;

    if (!rtc.begin()) {
        while (1) {
            Serial.println("Couldn't find RTC");
        };
    }

    if (!rtc.isrunning()) {
        Serial.println("RTC is NOT running!");
    }
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
    respond_to_bluetooth();

    if (mode == DigitalClock) {
        display_digital_clock();
    } else if (mode == BluetoothString) {
        displayStr = str_from_bt;
    } else if (mode == AnalogClock) {
        display_analog_clock();
    } else if (mode == RPMDisplay) {
        display_rpm();
    }
}

void respond_to_bluetooth() {
    if (Serial.available()) {
        detachInterrupt(digitalPinToInterrupt(2));

        str_from_bt = Serial.readString();
        str_from_bt.trim();
        str_from_bt.toUpperCase();

        if (str_from_bt == "SWITCH 0") {
            mode = DigitalClock;
        } else if (str_from_bt == "SWITCH 1") {
            mode = BluetoothString;
        } else if (str_from_bt == "SWITCH 2") {
            mode = AnalogClock;
        } else if (str_from_bt == "SWITCH 3") {
            mode = RPMDisplay;
        } else if (str_from_bt == "SWITCH 4") {
            color = !color;
            digitalWrite(A0, color);
            digitalWrite(A1, !color);

        }

        Serial.print("recieved: ");
        Serial.println(str_from_bt);

        if (mode == AnalogClock) {
            attachInterrupt(digitalPinToInterrupt(2), analogue_clock_ISR, FALLING);
        } else {
            attachInterrupt(digitalPinToInterrupt(2), displayStr_ISR, FALLING);
        }
    }
}

void display_rpm() {
    if (millis() - prev_rpm_update_ms > 1000) {
        rpm = rotations * 60000 / (millis() - prev_rpm_update_ms);
        prev_rpm_update_ms = millis();
        rotations = 0;
    }

    char rpm_str[15];
    sprintf(rpm_str, "%lu", rpm);
    displayStr = rpm_str;
}

void display_digital_clock() {
    DateTime now = rtc.now();
    char time[6];
    sprintf(time, "%02hhu_%02hhu_%02hhu", now.hour(), now.minute(), now.second());
    displayStr = time;
}

int letter_col_bit(byte letter_col, byte bit_pos_from_msb) {
    return (letter_col & (0b10000000 >> bit_pos_from_msb)) != 0;
}

void printLetterByte(byte letter[]) {
    int y;
    const int COLUMNS = 5;

    for (int i = 0; i < COLUMNS; i++) {
        for (y = 0; y < 8; y++) {
            digitalWrite(ledPins[y], letter_col_bit(letter[i], y));
        }
        delayMicroseconds(DOT_TIME_uS);
    };

    for (y = 0; y < 8; y++) {
        digitalWrite(ledPins[y], 0);
    }
    delayMicroseconds(LETTER_SPACE_uS);
}

bool is_alpha(char c) {
    return c >= 'A' && c <= 'Z';
}

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

void showString(String str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '_') {
            printLetterByte(_);
        } else if (is_alpha(str[i])) {
            printLetterByte(alpha[str[i] - 'A']);
        } else if (is_digit(str[i])) {
            printLetterByte(num[str[i] - '0']);
        }
    }
}

void displayStr_ISR() {
    rotations++;
    showString(displayStr);
}

// analog

void display_analog_clock() {
    DateTime now = rtc.now();
    hour = now.hour();
    minute = now.minute();
    second = now.second();
}

void analogue_clock_ISR() {
    propeller_posn = 0;
    n = 0;

    while (n < 60) {
        if (propeller_posn % 5 == 0) {
            drawHourMarker();
        }
        if (propeller_posn % 15 == 0) {
            drawQuarterMarker();
        }
        if (propeller_posn == hour * 5) {
            drawHoursHand();
        }
        if (propeller_posn == minute) {
            drawMinutesHand();
        }
        if (propeller_posn == second) {
            drawSecondsHand();
        }

        delayMicroseconds(ANLG_DOT_TIME_uS);

        displayClear();

        delayMicroseconds(ANLG_UNIT_SPACE_uS);

        n++;
        propeller_posn++;
        propeller_posn %= 60;
    }
}

void drawHourMarker() {
    digitalWrite(ledPins[0], HIGH);
}

void drawQuarterMarker() {
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[2], HIGH);
}

void drawHoursHand() {
    for (int i = 0; i < 4; i++) {
        digitalWrite(ledPins[NUM_LED_PINS - 1 - i], HIGH);
    }
}

void drawMinutesHand() {
    for (int i = 0; i < 6; i++) {
        digitalWrite(ledPins[NUM_LED_PINS - 1 - i], HIGH);
    }
}

void drawSecondsHand() {
    for (int i = 0; i < 8; i++) {
        digitalWrite(ledPins[NUM_LED_PINS - 1 - i], HIGH);
    }
}

void displayClear() {
    for (int i = 0; i < NUM_LED_PINS; i++) {
        digitalWrite(ledPins[i], LOW);
    }
}
