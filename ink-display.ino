#include <vector>
#include <renderer.h>
#include <font.h>
#include <image.h>
#include <table.h>
#include <WiFi.h>
#include <scheduler.h>

#include "screen_manager.h"

#include "assets/montserrat_header_0.c"
#include "assets/montserrat_header.fnt.c"

ScreenManager *manager = nullptr;
Renderer *renderer = nullptr;
Scheduler *scheduler = nullptr;

template<typename T>
std::vector<std::vector<T> > arrToVector(T *data, int rows, int cols) {
    std::vector<std::vector<T> > vec;
    for (int r = 0; r < rows; r++) {
        std::vector<T> row;
        for (int c = 0; c < cols; c++) {
            row.push_back(data[r * cols + c]);
        }
        vec.push_back(row);
    }

    return vec;
}

void setupRenderer() {

    String data[] = {
        "Bolt Size", "Normal Fit", "Close Fit", "Loose Fit",
        "#0",   "0.076",  "0.067",  "3/32",
        "#1",   "0.089",  "0.081",  "0.104",
        "#2",   "0.102",  "3/32",   "0.116",
        "#3",   "0.116",  "0.106",  "0.128",
        "#4",   "0.128",  "0.120",  "0.144",
        "#5",   "5/32",   "9/64",   "11/64",
        "#6",   "0.170",  "0.154",  "0.185",
        "#8",   "0.196",  "0.180",  "0.213",
        "#10",  "0.221",  "0.206",  "0.238",
        "1/4",  "9/32",   "17/64",  "19/64",
        "5/16", "11/32",  "21/64",  "23/64",
        "3/8",  "13/32",  "25/64",  "27/64",
        "7/16", "15/32",  "29/64",  "31/64",
        "1/2",  "9/16",   "17/32",  "39/64",
        "5/8",  "11/16",  "21/32",  "47/64",
        "3/4",  "13/16",  "25/32",  "29/32"
    };

    TableProperties properties;
    properties.rows = 16;
    properties.cols = 4;
    properties.width = 350;
    properties.height = 400;
    float weights[4] = {0.25, 0.25, 0.25, 0.25};
    properties.weights = (float*) malloc(sizeof(float) * 4);
    memcpy(properties.weights, weights, sizeof(float) * 4);
    Table *t = new Table(properties);
    std::vector< std::vector<String> > vec = arrToVector(data, properties.rows + 1, properties.cols);
    t->setHeader(vec[0]);
    for (int i = 0; i < properties.rows; i++) {
        t->addRow(vec[i+1]);
    }


    renderer = new Renderer(880, 528);
    renderer->clearAll();
    Serial.println("Clear");
    renderer->setColor(DisplayColor::RED);
    // renderer->setFont(smallFont);
    renderer->setFont(new Font(Image::asImage(&montserrat_header_0), montserrat_header_fnt));
    t->draw(renderer, 50, 50);
    renderer->render();

    manager = new ScreenManager();


    // renderer->drawLine(10, 0, 100, 300);
    // renderer->drawLine(50, 100, 700, 20);
    // renderer->fillRoundRect(300, 325, 400, 50, 25);
    // renderer->drawLine(400, 400, 700, 500);
    // renderer->setColor(DisplayColor::RED);
    // renderer->fillRect(700, 345, 50, 10);
    // renderer->fillRoundRect(10, 50, 100, 200, 15);
    // renderer->fillRect(10, 10, 20, 20);
    // renderer->drawImage(fontImage, 0, 0);

    // Image a = Image::asImage(&rage_cry);
    // Image b = Image::asImage(&pic);
    // renderer->drawImage(a, 200, 300);
    // renderer->drawImage(b, 500, 300);
    // renderer->setColor(DisplayColor::RED);
    // renderer->drawText(50, 120, "im JOSH and i can't find GF");
    // renderer->drawText(50, 170, "WAHHHH!11!!");
    // renderer->drawText(50, 220, "I HAV NO DIK & NO FUTURE");
    // renderer->drawLine(400, 250, 400, 500);
    // renderer->drawLine(400, 250, 800, 250);

    // renderer->setFont(font);
    // renderer->drawText(20, 300, "abcdefghijklmnopqrstuvwxyz");
    // renderer->drawText(20, 350, "1234567890-=!@#$%^&*()_+/?,.<>");
    // renderer->setColor(DisplayColor::RED);
    // renderer->drawText(400, 150, "-- RED TEXT");


    // renderer->drawText(200, 400, "I need to add text alignment");

    // renderer->setColor(DisplayColor::BLACK);
    // renderer->fillRect(150, 50, 200, 100);

    // renderer->setColor(DisplayColor::RED);
    // renderer->fillRect(50, 150, 25, 100);

    // renderer->render();
}

// Note: consider deep sleep bug (not waking)
// https://www.instructables.com/ESP32-Deep-Sleep-Tutorial/
void deepSleep(uint64_t seconds) {
    esp_sleep_enable_timer_wakeup(1000000UL * seconds); // sec -> us
    esp_deep_sleep_start();
}

void setup() {
    Serial.begin(115200);

    delay(1000);
    Serial.println("Setup");

    setupRenderer();
    // setupWiFi();
    scheduler = new Scheduler();

    scheduler->schedule(0, 3 * 60 * 60 * 1000, [](uint64_t delta){
        Screen *active = manager->get();
        if (active == nullptr) {
          Serial.println("No screen set!");
          return;
        }

        active->update(delta);

        if (active->isDirty()) {
            renderer->begin();

            renderer->clearAll();
            active->clearDirty();
            active->draw(renderer);
            renderer->render();

            renderer->end();
        } 

        Serial.println("Refresh complete - RAM left: " + String(esp_get_free_heap_size()));
    });
    
    Serial.println("Done - RAM left: " + String(esp_get_free_heap_size()));
}

void loop() {
    // put your main code here, to run repeatedly:
    scheduler->loop();
    delay(1000);
}
