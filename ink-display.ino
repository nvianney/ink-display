#include <vector>
#include <renderer.h>
#include <font.h>
#include <image.h>
#include <table.h>
#include <WiFi.h>
#include <scheduler.h>

#include "screen_manager.h"
#include "bolt_clearance.h"

#include "assets/montserrat_title_0.c"
#include "assets/montserrat_title.fnt.c"
#include "assets/montserrat_content_0.c"
#include "assets/montserrat_content.fnt.c"

ScreenManager *manager = nullptr;
Renderer *renderer = nullptr;
Scheduler *scheduler = nullptr;
Font *titleFont = nullptr;
Font *contentFont = nullptr;

void setupRenderer() {
    titleFont = new Font(Image::asImage(&montserrat_title_0), montserrat_title_fnt);
    contentFont = new Font(Image::asImage(&montserrat_content_0), montserrat_content_fnt);

    renderer = new Renderer(880, 528);
    renderer->clearAll();
    Serial.println("Clear");
    renderer->setColor(DisplayColor::RED);
    renderer->setFont(contentFont);
    renderer->render();

    manager = new ScreenManager();
    manager->add(new BoltClearance(880, 528));

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

            renderer->setFont(contentFont);
            active->draw(renderer);

            // title
            renderer->setFont(titleFont);
            renderer->drawText(50, 50, active->getTitle().c_str());

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
