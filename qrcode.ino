#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

// These pins will also work for the 1.8" TFT shield ESP32-WROOM
#define TFT_DC 12         //A0
#define TFT_CS 13        //CS
#define TFT_MOSI 14     //SDA
#define TFT_CLK 27     //SCK
#define TFT_RST 0  
#define TFT_MISO 0 
#define TFT_WIDTH 128
#define TFT_HEIGHT 160

// Leds
#define LED_BLUE 25
#define LED_GREEN 33
#define LED_YELLOW 32

// Buttons
#define BUTTON_BLUE 18
#define BUTTON_GREEN 19
#define BUTTON_YELLOW 21

// TFT display object instance 
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST);

// state machine
unsigned char current_menu = 0;
unsigned char item_selected = 0;
unsigned char quantity_selected = 0;

void setup(void) {    
    pinMode(BUTTON_BLUE, INPUT);
    pinMode(BUTTON_GREEN, INPUT);
    pinMode(BUTTON_YELLOW, INPUT);

    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);

    Serial.begin(9600);
    Serial.print("Booting ST7735 TFT 1.8 128x160 Test");

    tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
    Serial.println("Initialized");
}

void loop(void) {
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextWrap(true);
    tft.setTextSize(1);
    tft.println("Hello, world!");
    delay(500);
    
    tft.fillScreen(ST77XX_RED);
    delay(500);
    tft.fillScreen(ST77XX_GREEN);
    delay(500);
    tft.fillScreen(ST77XX_BLUE);
    delay(500);
    tft.fillScreen(ST77XX_BLACK);
    delay(500);

    if (digitalRead(BUTTON_BLUE) == HIGH) {
        digitalWrite(LED_BLUE, HIGH);
    } else {
        digitalWrite(LED_BLUE, LOW);
    }

    if (digitalRead(BUTTON_GREEN) == HIGH) {
        digitalWrite(LED_GREEN, HIGH);
    } else {
        digitalWrite(LED_GREEN, LOW);
    }

    if (digitalRead(BUTTON_YELLOW) == HIGH) {
        digitalWrite(LED_YELLOW, HIGH);
    } else {
        digitalWrite(LED_YELLOW, LOW);
    }
}

void renderListMenu() {}

void renderAmountMenu() {}

void renderQrCodeMenu () {}