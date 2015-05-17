int ledPin = 13;
int potPin = 7;
int led_state = 0;
char rcv_buf[10];     // Receive command arrays.

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("Hello world");
}
 
void loop() {
  String buf = "";
  while(1) {
    char c;
    while(Serial.available() && buf.length() < 100) {
      c = Serial.read();
      buf.concat(c);
      Serial.println("Got: " + c);
      if(c == '\n')
        break;
    }
    if(buf.indexOf('\n') != -1)
      break;
  }
  if (buf.indexOf("ON") != -1) {      // Open the light L when the command is "ON".
       digitalWrite(ledPin, HIGH);                       // Set D13 pin as high and openg the light L
       Serial.println("LIGHT ON");                      
  } else if (buf.indexOf("OFF") != -1) {  // Close the light L when the command is "OFF".
       digitalWrite(ledPin, LOW);                      // Set D13 pin as low and  the light L
       Serial.println("LIGHT OFF");              
  } else {
       Serial.println("LIGHT ???");
  }
  if(is_button_1_pressed())
    Serial.println("Button 1 pressed");
}

void toggle_led() {
  led_state = ! led_state;
  if(led_state)
    digitalWrite(ledPin, HIGH);
  else
    digitalWrite(ledPin, LOW);
}

unsigned int prevPotVal = 999999;

int is_button_1_pressed() {
  unsigned int potVal = analogRead(potPin);
  if(potVal < 50 && ! prevPotVal < 50 )
    return 1;
  else
    return 0;
  prevPotVal = potVal;
}
