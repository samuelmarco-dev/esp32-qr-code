#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
#include <SPI.h>

#include "neon.h"        // Rendering Pixel a Pixel
#include "aurora.h"      // Rendering Image RGB

// These pins will also work for the 1.8" TFT shield ESP32-WROOM
#define TFT_DC 12         // A0
#define TFT_CS 13         // CS
#define TFT_MOSI 14       // SDA
#define TFT_CLK 27        // SCK
#define TFT_RST 0         // RST in 3V3
#define TFT_MISO 0        // NC

// Display size definition
#define TFT_WIDTH 128
#define TFT_HEIGHT 160

// Leds
#define LED_BLUE 25
#define LED_GREEN 33
#define LED_YELLOW 32

// Buttons
#define BUTTON_BLUE 18     // Up and Down
#define BUTTON_GREEN 19    // Progress
#define BUTTON_YELLOW 21   // Return

// TFT display object instance 
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST);

// State machine
unsigned char current_menu = 0;
unsigned char item_selected = 0;

const int value = 5.90;
const int NUM_ITEMS = 7;
const char* items[NUM_ITEMS] = {
    "Pêssego", "Melancia", "Figo", "Tropical", 
    "Açaí", "Zero", "Coco", "Normal"
};

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
    Serial.println("Booting ST7735 TFT 1.8 128x160 Test");

    tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip with black tab
    tft.setRotation(0);
    tft.fillScreen(ST77XX_BLACK);
    Serial.println("Initialized");

    renderEachPixel(107, 160);
    renderItem();
}

void loop(void) {
    if(current_menu == 0) {
        if(digitalRead(BUTTON_BLUE)) {
            item_selected = (item_selected + 1) % NUM_ITEMS;
            renderItem();
        }
        if(digitalRead(BUTTON_GREEN)) {
            current_menu++;
        }
    }

    if(current_menu == 1) {
        renderItemSelected();
        if(digitalRead(BUTTON_GREEN)) {
            current_menu++;
        }
        if(digitalRead(BUTTON_YELLOW)) {
            current_menu = 0;
        }
    }

    if(current_menu == 2) {
        renderAllPixels();
        if(digitalRead(BUTTON_GREEN)) {
            current_menu = 0;
        }
    }

    // tft.fillScreen(ST77XX_BLACK);
    // tft.setCursor(0, 0);
    // tft.setTextColor(ST77XX_WHITE);
    // tft.setTextWrap(true);
    // tft.setTextSize(1);
    // tft.println("Hello, world!");
    // delay(500);
    
    // tft.fillScreen(ST77XX_RED);
    // delay(500);
    // tft.fillScreen(ST77XX_GREEN);
    // delay(500);
    // tft.fillScreen(ST77XX_BLUE);
    // delay(500);
    // tft.fillScreen(ST77XX_BLACK);
    // delay(500);

    // if (digitalRead(BUTTON_BLUE) == HIGH) {
    //     digitalWrite(LED_BLUE, HIGH);
    // } else {
    //     digitalWrite(LED_BLUE, LOW);
    // }

    // if (digitalRead(BUTTON_GREEN) == HIGH) {
    //     digitalWrite(LED_GREEN, HIGH);
    // } else {
    //     digitalWrite(LED_GREEN, LOW);
    // }

    // if (digitalRead(BUTTON_YELLOW) == HIGH) {
    //     digitalWrite(LED_YELLOW, HIGH);
    // } else {
    //     digitalWrite(LED_YELLOW, LOW);
    // }
}

// void renderListMenu() {
//     tft.fillScreen(ST7735_BLACK);
//     tft.drawBitmap(0, 0, item_images[item_selected], TFT_WIDTH, TFT_HEIGHT, ST7735_WHITE);
// }

// void renderAmountMenu() {
//     tft.fillScreen(ST7735_BLACK);
//     tft.drawBitmap(0, 0, quantity_images[quantity_selected], TFT_WIDTH, TFT_HEIGHT, ST7735_WHITE);
// }

// void renderQrCodeMenu () {
//     tft.fillScreen(ST7735_BLACK);
//     tft.drawBitmap(0, 0, qr_code_image, TFT_WIDTH, TFT_HEIGHT, ST7735_WHITE);
// }

void renderItem() {
    tft.fillScreen(ST7735_BLACK);        
    tft.setCursor(0, 0);                 
    tft.setTextColor(ST7735_WHITE);      
    tft.setTextSize(2);                   
    tft.println(items[item_selected]);    
}

void renderItemSelected() {
    tft.fillScreen(ST7735_BLACK);        
    tft.setTextColor(ST7735_WHITE);       
    tft.setTextSize(2);                  

    tft.setCursor(20, 10);                 
    tft.println("Item selecionado:");

    tft.set(20, 50);
    tft.println(items[item_selected]);

    tft.setCursor(20, 100);
    tft.println("Quantidade: 1");

    tft.setCursor(20, 150);
    tft.println("Valor: R$" + value);
}

void renderEachPixel(int width, int height) {
    int buffidx = 0;

    //read each line
    for(int row = 0; row < height; row++) {
        //read each pixel
        for(int column = 0; column < width; column++) { 
            //Read from flash memory from microcontroler, for address 16 bits using pgm_read_word
            tft.drawPixel(column, row, pgm_read_word(evive_in_hand + buffidx));
            buffidx++;
        } 
        // end pixel
    }
}

void renderAllPixels() {
    tft.fillScreen(ST7735_BLACK);
    tft.drawRGBBBitmap(0, 0, auroraWallpaper, AURORA_WIDTH, AURORA_HEIGHT);
}