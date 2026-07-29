#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <driver/i2s.h>
#include <SD.h>
#include <string>

int xChange = 8;
const int enClk = 25;
const int enDt = 26;
const int enSw = 27;
const int redLed = 35;
const int greenLed = 34;
const int sd_cs = 15;
const int sd_sck = 14;
const int sd_mosi = 13;
const int sd_miso = 4;
const int ws = 19;
const int sd = 23;
const int sck = 18;
int num_file = 0;
int choice = 0;
int lastChoice = -1;
int selectt = 0;
int lastselectt = -1;
int enClkCurrent;
int enClkLast;
int enDtCurrent;
int enDtLast;
int enSwLast;
int enSwCurrent;
int item = 0;
int lastItem = -1;
int prev_item;
int next_item;
bool isRecording = false;

#define I2S_PORT I2S_NUM_0
SPIClass customSPI(VSPI);
File file;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

const unsigned char epd_bitmap__four [] PROGMEM = {
	0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
	0x1f, 0xf8, 0x1f, 0xf8, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18
};

const unsigned char epd_bitmap__three [] PROGMEM = {
	0x00, 0x00, 0x07, 0xe0, 0x0f, 0xf0, 0x1c, 0x38, 0x18, 0x18, 0x00, 0x18, 0x00, 0x38, 0x03, 0xf0, 
	0x03, 0xf0, 0x00, 0x38, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x0c, 0x38, 0x0f, 0xf0, 0x07, 0xe0
};

const unsigned char epd_bitmap__one [] PROGMEM = {
	0x00, 0x00, 0x01, 0x80, 0x03, 0x80, 0x07, 0x80, 0x07, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 
	0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x07, 0xe0, 0x07, 0xe0
};

const unsigned char epd_bitmap__five [] PROGMEM = {
	0x00, 0x00, 0x1f, 0xf8, 0x1f, 0xf8, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x1f, 0xe0, 0x0f, 0xf0, 
	0x00, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1f, 0xf8, 0x0f, 0xf0, 0x00, 0x00
};

const unsigned char epd_bitmap__two [] PROGMEM = {
	0x07, 0xe0, 0x0f, 0xf0, 0x1c, 0x38, 0x18, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x30, 
	0x00, 0x60, 0x00, 0xe0, 0x01, 0xc0, 0x03, 0x80, 0x07, 0x00, 0x0e, 0x00, 0x1f, 0xf8, 0x1f, 0xf8
};

const unsigned char* home_icons[5] = {
	epd_bitmap__one,
	epd_bitmap__two,
	epd_bitmap__three,
	epd_bitmap__four,
	epd_bitmap__five
};

const unsigned char epd_bitmap__scrollbar [] PROGMEM = {
	0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 
	0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 
	0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 
	0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10
};

const int num_icons = 5;

char home_pages[num_icons][20] = {
    {"Room One"},
    {"Room Two"},
    {"Room Three"},
    {"Room Four"},
    {"Room Five"}
};
int box_y[5] {
    5,
    17,
    29,
    41,
    53
};

enum Screen {
    home, RoomOne, RoomTwo, RoomThree, RoomFour, RoomFive, recordingScreen, fullRecording
};

Screen currentScreen = home;
Screen lastScreen = (Screen)-1;

Screen HomeScreenMap[5] {RoomOne, RoomTwo, RoomThree, RoomFour, RoomFive};


void drawBooting() {
    for (int i = 0; i < 15; i++) {
        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_m_c_kids_nes_credits_font_tr);
        u8g2.drawStr(39,33,"TCT");
        u8g2.drawFrame(29,41,68,11);
        u8g2.drawBox(31,43,xChange,7);
        xChange += 4;
        u8g2.sendBuffer();
        delay(350);
        if (i == 14) {
            delay(834);
        }
    }
    xChange = 8;
}

void drawHome() {
    prev_item = item-1;
    if (prev_item < 0) {
        prev_item = num_icons-1;
    }
    next_item = item+1;
    if (next_item >= num_icons) {
        next_item = 0;
    }

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x12_tf);

    u8g2.drawXBMP(120,0,8,64,epd_bitmap__scrollbar);

    u8g2.drawBitmap(4,2,2,16,home_icons[prev_item]);
    u8g2.drawStr(26,14, home_pages[prev_item]);

    u8g2.drawBitmap(4,24,2,16, home_icons[item]);
    u8g2.setFont(u8g2_font_7x14B_tr);
    u8g2.drawStr(26,37, home_pages[item]);
    u8g2.drawFrame(3,23,118,19);

    u8g2.drawBox(123,box_y[item],3,7);

    u8g2.drawBitmap(4,46,2,16, home_icons[next_item]);
    u8g2.setFont(u8g2_font_6x12_tf);
    u8g2.drawStr(26,57, home_pages[next_item]);

    u8g2.sendBuffer();
}

void drawRoom() {

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_7x14B_tr);
    u8g2.drawXBMP(120,0,8,64,epd_bitmap__scrollbar);
    u8g2.drawBitmap(4,2,2,16,home_icons[item]);
    u8g2.drawStr(24,14,home_pages[item]);
    u8g2.drawLine(22,16,87,16);

    if (choice == 0) {
        u8g2.drawTriangle(7,24,7,32,15,28);
        u8g2.setFont(u8g2_font_7x14B_tr);
        u8g2.drawStr(19,33,"Record?");
        u8g2.setFont(u8g2_font_7x14_tf);
        u8g2.drawStr(7,50,"Back");
        u8g2.sendBuffer();
    }
    if (choice == 1) {
        u8g2.drawTriangle(7,40,7,48,15,44);
        u8g2.setFont(u8g2_font_7x14_tr);
        u8g2.drawStr(7,33,"Record?");
        u8g2.setFont(u8g2_font_7x14B_tf);
        u8g2.drawStr(19,50,"Back");
        u8g2.sendBuffer();

    }

}
void drawRecordingScreen() {
    u8g2.clearBuffer();
    u8g2.drawTriangle(7,59,15,55,15,63);
    u8g2.drawTriangle(121,59,113,55,113,63);
    u8g2.setFont(u8g2_font_courB18_tr);
    u8g2.drawStr(11,25,"Record?");
    u8g2.sendBuffer();
}

void startRecording() {
    u8g2.clearBuffer();
    startI2S();
    u8g2.setFont(u8g2_font_courB18_tr);
    u8g2.drawStr(8,21,"Recording!");//
}

void updateLEDs() {
    if (currentScreen != recordingScreen) {
        digitalWrite(greenLed, LOW);
        digitalWrite(redLed, HIGH);
    }
    else {
        digitalWrite(greenLed, LOW);
        digitalWrite(redLed,HIGH);//
    }

}

void startI2S() {
    i2s_config_t config {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = 16000,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
        .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_STAND_I2S),
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 64
    };
    i2s_pin_config_t pins {
        .bck_io_num = sck,
        .ws_io_num = ws,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = sd
    };
    i2s_driver_install(I2S_PORT, &config, 0, NULL);
    i2s_set_pin(I2S_PORT, &pins);
    customSPI.begin(sd_sck, sd_miso, sd_mosi, sd_cs);
    SD.begin(sd_cs, customSPI);
    char buf[12];
    itoa(num_file,buf,10);
    std::string final = "/test" + std::string(buf) + ".txt";
    file = SD.open(final.c_str(), FILE_WRITE);
}

void endI2S() {
    i2s_driver_uninstall(I2S_PORT);
    num_file++;
}



void setup() {
    u8g2.begin();
    Wire.setClock(400000);
    pinMode(enClk, INPUT_PULLUP);
    pinMode(enDt,  INPUT_PULLUP);
    pinMode(enSw, INPUT_PULLUP);
    pinMode(greenLed, OUTPUT);
    pinMode(redLed,OUTPUT);
    //for (int i = 0; i < 2; i++) {
        //drawBooting();
    //}
    delay(700);
    u8g2.clearBuffer();
    u8g2.sendBuffer();
    drawHome();
}

void loop() {
    enClkCurrent = digitalRead(enClk);
    enDtCurrent = digitalRead(enDt);
    enSwCurrent = digitalRead(enSw);

    if (currentScreen == home) {
        if (enClkCurrent == LOW && enClkLast == HIGH) {
            if (enDtCurrent == LOW) {
                item--;
                if (item < 0) {
                    item = num_icons-1;
                }
            }
            else {
                item++;
                if (item >= num_icons) {
                    item = 0;
                }
            }
        }

        if (enSwCurrent == LOW && enSwLast != LOW) {
            currentScreen = HomeScreenMap[item];
            choice = 0;
            enSwLast = enSwCurrent;
            delay(180);
            return;
        }

    }

    if (currentScreen != home && currentScreen != recordingScreen) {
        if (enClkCurrent == LOW && enClkLast != LOW) {
            if (enDtCurrent == LOW) {
                choice++;
                if (choice > 1) {
                    choice = 1;
                }
            }
            else {
                choice--;
                if (choice < 0) {
                    choice = 0;
                }
            }
        }
        if (enSwCurrent == LOW && enSwLast!= LOW) {
            if (choice == 1) {
                currentScreen = home;
            }
            else {
                currentScreen = recordingScreen;
            }
            delay(180);
        }
    }

    if (currentScreen != home && currentScreen == recordingScreen){
        if (enClkCurrent == LOW && enClkLast != LOW) {
            if (enDtCurrent == LOW) {
                selectt++;
                if (selectt > 2) {
                    selectt = 2;
                }
            }
            else {
                selectt--;
                if (selectt < 0) {
                    selectt = 0;
                }
            }
        }

        if (enSwCurrent == LOW && enSwLast!= LOW) {
            if (selectt == 0) {
                currentScreen = HomeScreenMap[item];
            }
            else if (selectt == 1) {
                isRecording = !isRecording;
                if (isRecording) {
                    currentScreen = fullRecording;
                }
                else {
                    currentScreen = recordingScreen;
                }
            }
            else if (selectt == 2) {
                

            }
        }
        
    }

    enClkLast = enClkCurrent;
    enDtLast = enDtCurrent;
    enSwLast = enSwCurrent;

    if (item != lastItem || currentScreen != lastScreen || choice != lastChoice) {
        lastItem = item;
        lastScreen = currentScreen;
        lastChoice = choice;

        if (currentScreen == home) {
            drawHome();
            updateLEDs();
        }
        else if (currentScreen == recordingScreen) {
            drawRecordingScreen();
            updateLEDs();
        }
        else {
            drawRoom();
            updateLEDs();
        }
    }

}