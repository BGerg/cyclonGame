#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
    #include <avr/power.h>
#endif

int previous_button_state = 0;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(16, 6, NEO_GRB + NEO_KHZ800);


bool is_button_latched() {
    return previous_button_state != digitalRead(2);
}

bool is_button_released() {
    return previous_button_state == 0;
}

void update_previous_button_state(int update_with) {
    previous_button_state = update_with;
}

int read_button_state() {
    return digitalRead(2);
}

uint32_t setRedColor() {  // Return a non-negative int type 
    return pixels.Color(255,0,0);
}

uint32_t setGreenColor() {  // Return a non-negative int type 
    return pixels.Color(0,255,0);
}

uint32_t setBlueColor() {  // Return a non-negative int type 
    return pixels.Color(0,0,255);
}

uint32_t setOffColor() {
    return pixels.Color(0,0,0);
}
void show_palyers_colors() {
    pixels.setBrightness(20);
    pixels.setPixelColor(0, setGreenColor());
    pixels.setPixelColor(8, setGreenColor());
    pixels.fill(setBlueColor(), 1, 7);
    pixels.fill(setRedColor(), 9, 15);
    pixels.show();
    delay(3000);
}

void switch_off_pixels(int fistPixel, int lastPixel) {
    pixels.fill(setOffColor(), fistPixel, lastPixel);
    pixels.show();
}

void blink_pixels(int fistPixel, int lastPixel){
    for (int i = 0; i < 6; i++) {
        pixels.fill(pixels.getPixelColor(fistPixel), fistPixel, lastPixel);
        pixels.show();
        delay(250);
        switch_off_pixels(fistPixel,lastPixel);
        delay(200);
    }
}

void start_running_light() {
    pixels.setPixelColor(0, setGreenColor());
    int count = 0;
    int clearPixelIndex = 0;
    while (true) {
      if (count == 16) {
        count = 0;
      }
      switch_off_pixels(clearPixelIndex,clearPixelIndex);
      pixels.setPixelColor(count, setBlueColor());
      pixels.show();
      delay(100);
      count += 1;
      clearPixelIndex = count-1;
    }
    
}
void setup() {
    #if defined (__ARVR_ATtiny85__)
        if(F_CPU == 16000000) clock_prescale_set(clock_div_1);
    #endif
  
    pixels.begin();  
    pinMode(2, INPUT_PULLUP);  // enable internal pull-up
    Serial.begin(9600);
}

void loop() {
    int button_state = read_button_state();
    delay(10);  // Wait for debouncing (this is a crude filtering)


    show_palyers_colors();
    blink_pixels(1,7); //First player color blinks
    switch_off_pixels(0,16);
    start_running_light();
    
    if (is_button_latched()) {  // Button state is different compared to last run
        update_previous_button_state(button_state);
        Serial.println(previous_button_state);
        if (is_button_released()) {
            for (int i=0; i<16; i++) {  // Set all pixel to blue and lit them up
                pixels.setPixelColor(i, setBlueColor());
                pixels.setBrightness(1);
                pixels.show();
                delay(100);
            }
        }
    }
}
