constexpr int led1 = 9;
constexpr int led2 = 10;
constexpr int led3 = 11;

constexpr int button = 8;
constexpr int potent = A5;

constexpr int delay_factor = 5;

/** Convenience function for simultaneous writing. */
void writeall(int a, int b, int c) {
  digitalWrite(led1, a);
  digitalWrite(led2, b);
  digitalWrite(led3, c);
}

/** Read the button's state.
 * The button must maintain its state for {wait} ms before it is trusted to have actually changed state.
 */
bool readbutton() {
  constexpr unsigned long wait = 50;

  /** real_read is the trusted state, last_read is the state that must prove itself. */
  static bool real_read = LOW;
  static bool last_read = LOW;
  static unsigned long last_time = 0;

  bool read = digitalRead(button);
  unsigned long time = millis();

  /** State change can be trusted. */
  if (time - last_time > wait) {
    real_read = last_read;
    last_time = time;
  }

  /** Not enough time elapsed but the state changed, so reset the timer. */
  if (read != last_read) {
    last_read = read;
    last_time = time;
  }

  return real_read;
}

/** Button edge detection. */
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

  if (buttonlifted()) {
    mode_i = (mode_i + 1) % n_modes;
  }

  static unsigned long t0 = millis();
  const unsigned long t = millis();

  /** Every mode only needs to be updated once per interval,
   * so don't continue unless enough time has elapsed. */
  if (t - t0 < analogRead(potent)) {
    return;
  }
  t0 = t;

  /** Reset all LEDs to start from scratch for animated modes.
   * User won't notice flicker for LEDs that are turned back on. */
  writeall(LOW, LOW, LOW);

  /** Five modes: all off (0), all on (1), flashing (2), marquee (3), wave (4) */
  switch (mode_i) {
    case 0:
      break;
    case 1:
      writeall(HIGH, HIGH, HIGH);

      break;
    case 2:
      static bool on = false;
      writeall(on, on, on);
      on = !on;

      break;
    case 3:
      /** Light one LED at a time.
       * If LED1 is lit, switch to LED2.
       * If LED2 is lit, switch to LED3.
       * If LED3 is lit, switch to LED1. */
      static int active_led = led1;
      digitalWrite(active_led, HIGH);
      active_led = active_led == led1 ? led2 : (active_led == led2 ? led3 : led1);

      break;
    case 4:
      /** Cycle between 4 states.
       * LED1 is always on.
       * LED2 is on except during during state 0.
       * LED3 is only on during state 3. */
      static int state = 0;
      writeall(HIGH, state ? HIGH : LOW, state == 2 ? HIGH : LOW);
      state = (state + 1) % 4;

      break;
  }
}