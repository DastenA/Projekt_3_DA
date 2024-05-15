// Define the pins for the RGB LED
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

// the number of the pushbutton pin
const int green_button = 6;
const int yellow_button = 5;
const int blue_button = 4;
const int red_button = 3;
const int ledPin = 13;    // the number of the LED pin

int previousColor = -1;


// variable for reading the pushbutton status
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;

unsigned long startTime;
const int showTime = 1000;
const int gameLen = 6;
const unsigned long duration = showTime * gameLen; // duration for the LED game

int correctOrder[gameLen];
int playerOrder[] = {9, 9, 9, 9, 9, 9};

int i = 0;
int j = 0;

void setup() {
  // Set the RGB LED pins as output
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  pinMode(green_button, INPUT);
  pinMode(yellow_button, INPUT);
  pinMode(blue_button, INPUT);
  pinMode(red_button, INPUT);

  // Seed the random number generator
  randomSeed(analogRead(0));

  // Initialize start time
  startTime = millis();
  Serial.begin(9600);
}

void loop() {
  if (j == 0){
  updatecolor();
  }
  
  updatebutton();
  
  if (j == 6){
    updategame();
  }
}

void updatecolor() {  // Check if the time duration has not yet elapsed
  if (millis() - startTime < duration) {
    // Generate a random number (0-3) to represent the color
  int color;
  
  do {
    color = random(3);
  } while (color == previousColor);
  
    // Set RGB values based on the selected color
    switch (color) {
      case 0:  // Green
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, HIGH);
        digitalWrite(BLUE_PIN, LOW);
        correctOrder[i] = 0;
        Serial.println(" - GREEN"); // Prints out " - GREEN"
        break;

      case 1: // Yellow (combination of red and green)
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(GREEN_PIN, HIGH);
        digitalWrite(BLUE_PIN, LOW);
        correctOrder[i] = 1;
        Serial.println(" - YELLOW"); // Prints out " - YELLOW"
        break;

      case 2: // Blue
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, HIGH);
        correctOrder[i] = 2;
        Serial.println(" - BLUE"); // Prints out " - BLUE"
        break;
      case 3:  // Red
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, LOW);
        Serial.println(" - RED"); // Prints out " - RED"
        correctOrder[i] = 3;
        break;

    }
  previousColor = color;

    // Delay for a short period before changing color again
    i++;
    delay(showTime); // Adjust the delay time as needed
  } else {
    // Turn off the RGB LED
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);

  }
}

void updatebutton() {
  // read the state of the pushbutton value:
  buttonState1 = digitalRead(green_button);
  buttonState2 = digitalRead(yellow_button);
  buttonState3 = digitalRead(blue_button);
  buttonState4 = digitalRead(red_button);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:

  // GREEN
  if (buttonState1 == HIGH) {
    // turn LED on:
    digitalWrite(GREEN_PIN, HIGH);
    Serial.println(" - GREEN"); // Prints out " - GREEN"
    delay(500);
    playerOrder[j] = 0;
      j++;
  } else {
    // turn LED off:
    digitalWrite(GREEN_PIN, LOW);
  }

  // YELLOW
  if (buttonState2 == HIGH) {
    // turn LED on:
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(RED_PIN, HIGH);
    Serial.println(" - YELLOW"); // Prints out " - YELLOW"
    delay(500);
    playerOrder[j] = 1;
      j++;
  } else {
    // turn LED off:
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(RED_PIN, LOW);

  }

  // BLUE
  if (buttonState3 == HIGH) {
    // turn LED on:
    digitalWrite(BLUE_PIN, HIGH);
    Serial.println(" - BLUE"); // Prints out " - BLUE"
    delay(500);
    playerOrder[j] = 2;
      j++;
  } else {
    // turn LED off:
    digitalWrite(BLUE_PIN, LOW);
  }

  // RED
  if (buttonState4 == HIGH) {
    // turn LED on:
    digitalWrite(RED_PIN, HIGH);
    Serial.println(" - RED"); // Prints out " - RED"
    delay(500);
    playerOrder[j] = 3;
      j++;
  } else {
    // turn LED off:
    digitalWrite(RED_PIN, LOW);

  }
}


void updategame() {
  for (int k = 0; k < 6; k++) {
    if (playerOrder[k]  != correctOrder[k]) {

      digitalWrite(RED_PIN, HIGH);
      delay(1000);
      digitalWrite(RED_PIN, LOW);

    } else {
      digitalWrite(GREEN_PIN, HIGH);
      delay(200);
      digitalWrite(GREEN_PIN, LOW);
      delay(200);
      digitalWrite(GREEN_PIN, HIGH);
      delay(200);
      digitalWrite(GREEN_PIN, LOW);
      delay(200);
      digitalWrite(GREEN_PIN, HIGH);
      delay(200);
      digitalWrite(GREEN_PIN, LOW);
      delay(200);


    }
    
  }


}
