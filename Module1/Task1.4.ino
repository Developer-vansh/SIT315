void setup() {
  // Set PIR sensor pins as inputs
  DDRD &= ~(1 << DDD2); // pir3
  DDRD &= ~(1 << DDD3); // pir2
  DDRD &= ~(1 << DDD4); // pir1

  // Set buzzer and LEDs pins as outputs
  DDRB |= (1 << DDB4); // buzzer
  DDRD |= (1 << DDD5); // timerLed
  DDRB |= (1 << DDB3); // rLed
  DDRB |= (1 << DDB2); // bLed
  DDRB |= (1 << DDB1); // gLed

  // Enable Pin Change Interrupts (PCINT) for PIR sensors
  PCMSK2 |= (1 << PCINT18); // PCINT for pin 2 (pir1)
  PCMSK2 |= (1 << PCINT19); // PCINT for pin 3 (pir2)
  PCMSK2 |= (1 << PCINT20); // PCINT for pin 4 (pir3)
  PCICR |= (1 << PCIE2);    // Enable PortD PCINT

  // Disable interrupts during setup
  cli();

  // Timer1 setup for 1 second interval
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 15624;
  TCCR1B |= (1 << WGM12) | (1 << CS12); // Configure for CTC mode with prescaler 256
  TIMSK1 |= (1 << OCIE1A);  // Enable Timer1 compare match A interrupt

  // Enable interrupts
  sei();

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Delay added for stability
  _delay_ms(500);
}

// Interrupt Service Routine for Pin Change Interrupts (PCINT)
ISR(PCINT2_vect) {
  // Check PIR sensors states and control LEDs and buzzer accordingly
  if (PIND & (1 << PIND4)) {
    PORTB |= (1 << PORTB4); // Buzzer on
    PORTB |= (1 << PORTB3); // Green LED on
  } 
  else if (PIND & (1 << PIND3)) {
    PORTB |= (1 << PORTB4); // Buzzer on
    PORTB |= (1 << PORTB2); // Blue LED on
  }
  else if (PIND & (1 << PIND2)) {
    PORTB |= (1 << PORTB4); // Buzzer on
    PORTB |= (1 << PORTB1); // Red LED on
  } 
  else {
    // Turn off all LEDs and buzzer if no PIR sensors are triggered
    PORTB &= ~(1 << PORTB4);
    PORTB &= ~(1 << PORTB3);
    PORTB &= ~(1 << PORTB2);
    PORTB &= ~(1 << PORTB1);
  }
}

// Interrupt Service Routine for Timer1 compare match A
ISR(TIMER1_COMPA_vect) {
  // Toggle the state of the timer LED using bitwise XOR
  PORTD ^= (1 << PORTD5);
}
