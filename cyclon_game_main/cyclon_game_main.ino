#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
    #include <avr/power.h>
#endif

int previous_button_state = 0;
int player_score = 0;
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

void reset_players_scores() {
    player_score = 0;
}
void show_palyers_colors() {
    pixels.setBrightness(12);
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

void start_blink_pixels(int fistPixel, int lastPixel){
  
    for (int i =0 ; i < 10; i++) {
        switch_off_pixels(fistPixel,lastPixel);
        delay(200);
        pixels.fill(setBlueColor(), fistPixel, lastPixel);
        pixels.show();
        delay(250);
    }
}

long choose_first_player() {
    return random(1,3);
}

void set_player_score() {
    player_score += 2;
}

void check_hit() {
     if (236 == pixels.getPixelColor(0)) {
        set_player_score();
     }
}

void show_players_scores() {
    if (player_score > 0) {
        start_blink_pixels(1,player_score);
    }
}

bool check_no_winner() {
  Serial.println(player_score);
  if (player_score == 8) {
    start_blink_pixels(0,16);
    reset_players_scores();
    return false;
  }
  else {
    return true;
  }
}
void start_running_light() {
    int onPixelIndex = 0;
    int offPixelIndex = 0;
    bool round = true;
    
    while (round) {
        if (onPixelIndex == 16) {
          onPixelIndex = 0;
      }
      switch_off_pixels(offPixelIndex,offPixelIndex);
      pixels.setPixelColor(0, setGreenColor());
      pixels.setPixelColor(onPixelIndex, setBlueColor());
      pixels.show();
      delay(35);
      round = stop_running_light();
      onPixelIndex += 1;
      offPixelIndex = onPixelIndex-1; 
   }
   delay(1000);
   check_hit();
}
    
bool stop_running_light() {
      int button_state = read_button_state();
      if (is_button_latched()) {  // Button state is different compared to last run
          update_previous_button_state(button_state);
          if (is_button_released()) {
              return false;
              delay(1000);
          }
      }
      return true;
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
    int player_number = choose_first_player();
    start_blink_pixels(1,7); //First player color blinks
    delay(10);
    while (check_no_winner()) {
        switch_off_pixels(0,16);
        start_running_light();
        show_players_scores();
    }
    
}
