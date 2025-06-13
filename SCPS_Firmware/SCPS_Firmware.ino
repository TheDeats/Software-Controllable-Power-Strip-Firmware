const int ledPin = 3;
const int outputPin = 7;
const int buttonPin = 5;
const String EOM = "SCPS_EOM";
const unsigned long debounceDelay = 50;
String commandReceived = "";
bool buttonLastState = HIGH;  // high = true = 1;
unsigned long lastDebounceTime = 0;
bool isDebouncing = false;
bool powerState = false;

void setup() {
  pinMode(outputPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  bool buttonState = digitalRead(buttonPin);
  if (buttonState != buttonLastState && !isDebouncing){
    isDebouncing = true;
    lastDebounceTime = millis();
  }
  if (isDebouncing && (millis() - lastDebounceTime) > debounceDelay) {
    if (buttonState == LOW && buttonLastState == HIGH) {
      powerState = !powerState;
      digitalWrite(outputPin, powerState);
      digitalWrite(ledPin, powerState);
    }
    isDebouncing = false;
    buttonLastState = buttonState;
  }
  
  if (Serial.available()){
    char c = Serial.read();
    commandReceived += c;
    if (commandReceived.indexOf(EOM) != -1){
      commandReceived.replace(EOM, "");
      commandReceived.trim();
      
      if (commandReceived == "AMICONNECTED"){
        Serial.println("YOURCONNECTED " + EOM);
      }
      else if (commandReceived == "ON"){
        digitalWrite(outputPin, HIGH);
        powerState = true;
        digitalWrite(ledPin, powerState);
        Serial.println("ON " + EOM);
      }
      else if (commandReceived == "OFF"){
        digitalWrite(outputPin, LOW);
        powerState = false;
        digitalWrite(ledPin, powerState);
        Serial.println("OFF " + EOM);
      }
      else if (commandReceived == "GET"){
        String state = powerState ? "true" : "false";
        Serial.println("GET " + state + " " + EOM);
      }
      else{
        Serial.println("Unknown command. " + EOM);
      }
      commandReceived = "";
    }
  }
}
