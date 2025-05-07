const int led = LED_BUILTIN;
const int outputPin = 7;

void setup() {
  pinMode(outputPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()){
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    if (command == "AMICONNECTED?"){
      Serial.println("YOURCONNECTED!");
    }
    else if (command == "ON"){
      digitalWrite(outputPin, HIGH);
      Serial.println("ON");
    }
    else if (command == "OFF"){
      digitalWrite(outputPin, LOW);
      Serial.println("OFF");
    }
    else{
      Serial.println("Unknown command.");
    }
  }

}
