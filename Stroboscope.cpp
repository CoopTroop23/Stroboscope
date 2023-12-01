#include <Wire.h>
#include <Adafruit_SSD1306.h>

//prototypes
struct Button;
struct Knob;

void updateButton(Button&);
void updateKnob(Knob&);
double calculatePeriod(int);
void updateScreen();

bool changed = false;

//structure for button
struct Button{
  int pin;
  unsigned long lastButtonPress = 0;
  int state = 0;
  Button(int p){
    pin = p;
    pinMode(pin,INPUT_PULLUP);
  }
};

//structure for the knob
struct Knob{
  //pins
  int CLK;
  int DT;
  //variables for knob
  double counter = 0;
  double increment = 1;
  int currentStateCLK;
  int lastStateCLK;
  
  Knob(int c, int d){
    CLK = c;
    DT = d;
    pinMode(CLK, INPUT);
    pinMode(DT, INPUT);
    lastStateCLK = digitalRead(CLK);
  }
  
};

void updateButton(Button& btn){
    // Read the button state
    bool btnState = digitalRead(btn.pin);
  
    //If we detect LOW signal, button is pressed
    if (btnState == LOW) {
      //if 50ms have passed since last LOW pulse, it means that the
      //button has been pressed, released and pressed again
      if (millis() - btn.lastButtonPress > 50) {
        btn.state++;
        changed = true;
      }
  
      // Remember last button press event
      btn.lastButtonPress = millis();
    }
  }



void updateKnob(Knob& knob){
  // Read the current state of CLK
  knob.currentStateCLK = digitalRead(knob.CLK);
  if (knob.currentStateCLK != knob.lastStateCLK  && knob.currentStateCLK == 1){
      if (digitalRead(knob.DT) != knob.currentStateCLK) {
        knob.counter -= knob.increment;
      } else {
        // Encoder is rotating CW so increment
        knob.counter += knob.increment;
      }
      changed = true;
    }
  
    // Remember last CLK state
    knob.lastStateCLK = knob.currentStateCLK;
  
    if(knob.counter < 0){
      knob.counter = 0;
    }
  }


// gloabal stuff
Adafruit_SSD1306 oled(128, 32, &Wire, -1);
Knob knob1(6,7);
Button knobButton(9);
Button multiplierButton(4);

unsigned long currentTime = 0;
unsigned long pastTime = 0;
bool ledOff = true;
unsigned long interval = 0;

void setup() {
  
  Serial.begin(9600);
  
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  //setting variables to make the screen look good
  knob1.increment = 100;
  multiplierButton.state = 1;
  //initializing the screen
  oled.setTextSize(1);
  oled.setTextColor(1);
  updateScreen();

  //pin for led
  pinMode(13,OUTPUT);
  digitalWrite(13,0);
}


void loop() {
  // get data from knobs
  updateKnob(knob1);
  updateButton(knobButton);
  updateButton(multiplierButton);
  
  //update the knobs increment
  if(knobButton.state > 4){
    knobButton.state = 0;
  }
  if(knobButton.state <= 4){
    knob1.increment = pow(10, 2-knobButton.state);
  }

  //limit the multipliers state
  if(multiplierButton.state > 10){
    multiplierButton.state = 1;
  }
  
  //draw on the screen
  if(changed == true ){
    changed = false;
    updateScreen();
  }
  
  //flashing the led
  if(ledOff == false){
    interval = calculatePeriod(knob1.counter)/multiplierButton.state;
  }else{
    interval = calculatePeriod(knob1.counter)/360;
  }
  currentTime = micros();
  if(currentTime-pastTime > interval){
    pastTime = currentTime;
    if(interval == 0){
      digitalWrite(13,0);
    }else{
      digitalWrite(13,!ledOff);
    }
    ledOff = !ledOff;
  }
  
}

double calculatePeriod(double c){
  double x = pow(c,-1);
  x = x * 1000000;
  return x;
}

void updateScreen(){
  //each character is 7 pixels tall
  String str;
  oled.clearDisplay();
  
  str = "Hz:";
  str += knob1.counter;
  oled.setCursor(0,0);
  oled.print(str);
  
  str = "Increment: ";
  str+= knob1.increment;
  oled.setCursor(0,11);
  oled.print(str);

  str = "Multiplier: ";
  str += multiplierButton.state;
  oled.setCursor(0,22);
  oled.print(str);

  str = "           :";
  str += (knob1.counter*multiplierButton.state);
  oled.setCursor(0,0);
  oled.print(str);
  
  oled.display();

}
