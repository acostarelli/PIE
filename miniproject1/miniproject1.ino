/** These constants are left in the global scope as parameters for this program
 * as a whole.*/
constexpr int led1 = 9;
constexpr int led2 = 10;
constexpr int led3 = 11;
constexpr int button = 8;
constexpr int potent = A5;

/** Convenience function for simultaneous writing. */
void writeall(int a, int b, int c) {
  digitalWrite(led1, a);
  digitalWrite(led2, b);
  digitalWrite(led3, c);
}

/** Read the button's state.
 * Essentially a wrapper for digitalRead(button) that ignores random/unexpected
 * state changes.
 */
bool readbutton() {
  constexpr unsigned long wait = 50;

  static bool real_read = LOW;
  static bool last_read = LOW;
  static unsigned long last_time = 0;

  bool read = digitalRead(button);
  unsigned long time = millis();

  if (time - last_time > wait) {
    real_read = last_read;
    last_time = time;
  }

  if (read != last_read) {
    last_read = read;
    last_time = time;
  }

  return real_read;
}

/** Detects when the button is lifted after depression. */
bool buttonlifted() {
  static bool last = LOW;
  bool now = readbutton();

  bool ret = last == HIGH && now == LOW;

  last = now;
  return ret;
}

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  constexpr int n_modes = 5;
  static int mode_i = 0;

  /** Cycle through the modes each time the button is unpressed. */
  if (buttonlifted()) {
    mode_i = (mode_i + 1) % n_modes;
  }

  static unsigned long t0 = 0;
  const unsigned long t = millis();

  /** Each mode doesn't need to update any earlier than an interval, so don't
   * continue unless enough time has elapsed. The interval time is given by
   * the potentiometer reading. */
  if (t - t0 < analogRead(potent)) {
    return;
  }
  t0 = t;

  /** Every mode tells which LEDs to turn on, but not every mode tells which
   * LEDs to turn off. So, default by turning off all LEDs. The time between
   * this line and the mode code is too short for the user to notice any
   * LEDs flicker off that should have stayed on. */
  writeall(LOW, LOW, LOW);

  switch (mode_i) {
    case 0: /** All off */
      break;
    case 1: /** All on */
      writeall(HIGH, HIGH, HIGH);

      break;
    case 2: /** All flashing */
      static bool on = false;
      writeall(on, on, on);
      on = !on;

      break;
    case 3: /** "Marquee" */
      /** Light one LED at a time.
       * If LED1 is lit, switch to LED2.
       * If LED2 is lit, switch to LED3.
       * If LED3 is lit, switch to LED1. */
      static int active_led = led1;
      digitalWrite(active_led, HIGH);
      active_led = active_led == led1 ? led2 : (active_led == led2 ? led3 : led1);

      break;
    case 4: /** "Wave" */
      /** Cycle between 4 states.
       * LED1 is always on.
       * LED2 is on except during state 0.
       * LED3 is only on during state 3. */
      static int state = 0;
      writeall(HIGH, state ? HIGH : LOW, state == 2 ? HIGH : LOW);
      state = (state + 1) % 4;

      break;
  }
}