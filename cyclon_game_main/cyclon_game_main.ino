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
uint32_t getBlueColor() {  // Return a non-negative int type 
    return pixels.Color(0,0,255);
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

    if (is_button_latched()) {  // Button state is different compared to last run
        update_previous_button_state(button_state);
        
        Serial.println(previous_button_state);
        
        if (is_button_released()) {
            for (int i=0; i<16; i++) {  // Set all pixel to blue and lit them up
                pixels.setPixelColor(i, getBlueColor());
                pixels.show();
                delay(100);
            }
        }
    }
}
