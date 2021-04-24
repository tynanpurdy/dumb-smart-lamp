#include <Adafruit_NeoPixel.h> // Drive LED strip

// LED object and pot control

#define LED_PIN    21
#define LED_COUNT  60
#define POT_PIN    A0

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

int hue;
int potVal;
int oldPotVal;
int timeOfDay;
int brightness = 0;
const int MAX_DIF        =  1;
const int CYCLE_MAX      = 4;
const int CYCLE_DURATION =  CYCLE_MAX / 4;

void setup() {
  Serial.begin(9600);
  // ss.begin(GPSBaud);
  strip.begin();
  strip.show();
  strip.setBrightness(200);
  potVal, oldPotVal = analogRead(POT_PIN);
  //  startRoutine(potVal);
}

void loop() {
  //  if (getPot()) {
  //    delay(1000);
  //    getPot();
  //    // reset time to potVal
  //    startRoutine(potVal);
  //  }
  getPot();
  //  Serial.println(potVal);
  timeOfDay = map(potVal, 0, 4095, 0, CYCLE_MAX);
//  Serial.println(timeOfDay);
//  hue = map(potVal, 0, 4095, 0, 2000);
//  brightness = map(potVal, 0, 4095, 0, 255);
//  strip.fill(strip.ColorHSV(hue, 255 - brightness, brightness));
  //  strip.setBrightness(brightness);
  //  strip.fill(strip.Color(255, 255, 255, 255));
  //  strip.fill(strip.ColorHSV(brightness));
  
  //  if (timeOfDay < CYCLE_DURATION) {
  //    morningRoutine(0);
  //  } else if (timeOfDay >= CYCLE_DURATION and timeOfDay < (CYCLE_MAX - CYCLE_DURATION)) {
  ////    strip.fill(strip.Color(255, 255, 255, 255));
  ////    strip.show();
  //    dayRoutine(0);
  //  } else if (timeOfDay > (CYCLE_MAX - CYCLE_DURATION)) {
  //    eveningRoutine(0);
  //  }

  if (potVal < 2048) {
    hue = map(potVal, 0, 4095, 0, 2000);
    brightness = map(potVal, 0, 4095, 0, 255);
    strip.fill(strip.ColorHSV(hue, 255 - brightness, brightness));
  } else if (potVal >= 2048) {
    hue = map(potVal, 0, 4095, 2000, 0);
    brightness = map(potVal, 0, 4095, 255, 0);
    strip.fill(strip.ColorHSV(hue, 255 - brightness, brightness));
  }
  strip.show();
  delay(5);
}

// ------------------------------------------------------------------
// HELPER METHODS
// ------------------------------------------------------------------

/**
   Main LED cycle pattern. Can be interrupted and reset by an adjustment of `potVal`.
   @param currentPotTime sensor position input from Pot indicating desired cycle start point
**/
//void startRoutine(int currentPotTime) {
//  int currentTime = map(currentPotTime, 0, 1023, 0, CYCLE_MAX);
//  // time object = currentTime;
////  (currentTime == 0 or currentTime == CYCLE_MAX)
//  for (int i = currentTime; i < CYCLE_MAX; i++) {
//    if (getPot()) {
//      break;
//    }
//  }
//  // Choose a phase of the day: morning, day, or evening
//  switch (currentTime) {
//    case > 0 and < CYCLE_DURATION:
//      morningRoutine(currentTime);
//      break;
//    case >= CYCLE_DURATION and < CYCLE_MAX - CYCLE_DURATION:
//      dayRoutine(currentTime);
//      break;
//    case >= CYCLE_MAX - CYCLE_DURATION and < CYCLE_MAX:
//      eveningRoutine(currentTime);
//      break;
//    default:
//      dayRoutine(currentTime);
//      break;
//  }
//}

/**
   Check for an adjustment of the pot. Update `potVal` and `oldPotVal`
   @return true if there is a new `potVal`
**/
bool getPot() {
  potVal = analogRead(POT_PIN);
  if (abs(potVal - oldPotVal) > MAX_DIF) {
    oldPotVal = potVal;
    return true;
  } else {
    return false;
  }
}

/**
   Sunrise color cycle at beginning of the day.
   @param currentTime cycle start time position
**/
void morningRoutine(int currentTime) {
  //  for (int i = currentTime; i < CYCLE_DURATION; i++) {
  //    if (getPot()) break;
  ////    strip.fill(strip.Color());
  //    strip.show();
  //  }
  brightness = map(potVal, 0, 1024, 0, 255);
  hue = map(potVal, 0, 1024, 0, 2000);
  strip.fill(strip.ColorHSV(hue));
  strip.setBrightness(brightness);
  strip.show();
}

/**


**/
void dayRoutine(int currentTime) {
  //  for (int i = currentTime; i < (CYCLE_MAX - CYCLE_DURATION); i++) {
  //    if (getPot()) break;
  //    strip.fill(strip.Color(255, 255, 255, 255));
  //    strip.show();
  //  }
  strip.fill(strip.ColorHSV(0, 0, 255));
  strip.show();
}

/**
   Wind down color cycle at end of the day.
   @param currentTime cycle start time position
**/
void eveningRoutine(int currentTime) {
  //  for (int i = currentTime; i < CYCLE_MAX; i++) {
  //    if (getPot()) break;
  ////    strip.fill(strip.Color());
  //    strip.show();
  //  }
  hue = map(potVal, 4095 - 1024, 4095, 2000, 0);
  brightness = map(potVal, 0, 4095 - 1024, 255, 0);
  strip.fill(strip.ColorHSV(hue));
  strip.setBrightness(brightness);
  //  strip.clear();
  strip.show();
}
