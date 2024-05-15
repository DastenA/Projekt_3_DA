// Define the pins for the RGB LED
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

// Define the pin numbers for the pushbuttons
const int green_button = 6;
const int yellow_button = 5;
const int blue_button = 4;
const int red_button = 3;
const int ledPin = 13;  // The number of the LED pin (not used in the current code)

int previousColor = -1;  // Variable to store the previous color to avoid repetition

// Variables for reading the pushbutton status
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;

unsigned long startTime;  // Variable to store the start time of the game
const int showTime = 1000;  // Time (in milliseconds) to show each color
const int gameLen = 6;  // Length of the color sequence
const unsigned long duration = showTime * gameLen;  // Total duration for showing the LED sequence

int correctOrder[gameLen];  // Array to store the correct order of colors
int playerOrder[] = {9, 9, 9, 9, 9, 9};  // Array to store the player's input (initialized to a default value)

int i = 0;  // Index for correctOrder
int j = 0;  // Index for playerOrder

void setup() {
  // Set the RGB LED pins as output
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Set the pushbutton pins as input
  pinMode(green_button, INPUT);
  pinMode(yellow_button, INPUT);
  pinMode(blue_button, INPUT);
  pinMode(red_button, INPUT);

  // Seed the random number generator
  randomSeed(analogRead(0));

  // Initialize start time
  startTime = millis();
  
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  updatecolor();  // Update the color sequence
  updatebutton();  // Check for button presses and record player's input
  
  if (j == 6) {
    updategame();  // Check the game result if all colors have been inputted by the player
  }
}

void updatecolor() {
  // Check if the time duration for showing colors has not yet elapsed
  if (millis() - startTime < duration) {
    int color;
    do {
      color = random(3);  // Generate a random number (0-3) to represent the color
    } while (color == previousColor);  // Ensure the new color is different from the previous one

    // Set RGB values based on the selected color
    switch (color) {
      case 0:  // Green
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, HIGH);
        digitalWrite(BLUE_PIN, LOW);
        correctOrder[i] = 0;  // Store the correct color in the array
        Serial.println(" - GREEN");
        break;
      case 1:  // Yellow (combination of red and green)
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(GREEN_PIN, HIGH);
        digitalWrite(BLUE_PIN, LOW);
        correctOrder[i] = 1;  // Store the correct color in the array
        Serial.println(" - YELLOW");
        break;
      case 2:  // Blue
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, HIGH);
        correctOrder[i] = 2;  // Store the correct color in the array
        Serial.println(" - BLUE");
        break;
      case 3:  // Red
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, LOW);
        correctOrder[i] = 3;  // Store the correct color in the array
        Serial.println(" - RED");
        break;
    }
    previousColor = color;  // Update the previous color
    i++;  // Increment the index for correctOrder
    delay(showTime);  // Delay before showing the next color
  } else {
    // Turn off the RGB LED after the sequence is shown
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
  }
}

void updatebutton() {
  // Read the state of the pushbuttons
  buttonState1 = digitalRead(green_button);
  buttonState2 = digitalRead(yellow_button);
  buttonState3 = digitalRead(blue_button);
  buttonState4 = digitalRead(red_button);

  // Check if the green button is pressed
  if (buttonState1 == HIGH) {
    digitalWrite(GREEN_PIN, HIGH);  // Turn on the green LED
    Serial.println(" - GREEN");
    delay(500);  // Debounce delay
    playerOrder[j] = 0;  // Record player's input
    j++;  // Increment the index for playerOrder
  } else {
    digitalWrite(GREEN_PIN, LOW);  // Turn off the green LED
  }

  // Check if the yellow button is pressed
  if (buttonState2 == HIGH) {
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(RED_PIN, HIGH);  // Turn on the yellow LED (green + red)
    Serial.println(" - YELLOW");
    delay(500);  // Debounce delay
    playerOrder[j] = 1;  // Record player's input
    j++;
  } else {
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(RED_PIN, LOW);  // Turn off the yellow LED
  }

  // Check if the blue button is pressed
  if (buttonState3 == HIGH) {
    digitalWrite(BLUE_PIN, HIGH);  // Turn on the blue LED
    Serial.println(" - BLUE");
    delay(500);  // Debounce delay
    playerOrder[j] = 2;  // Record player's input
    j++;
  } else {
    digitalWrite(BLUE_PIN, LOW);  // Turn off the blue LED
  }

  // Check if the red button is pressed
  if (buttonState4 == HIGH) {
    digitalWrite(RED_PIN, HIGH);  // Turn on the red LED
    Serial.println(" - RED");
    delay(500);  // Debounce delay
    playerOrder[j] = 3;  // Record player's input
    j++;
  } else {
    digitalWrite(RED_PIN, LOW);  // Turn off the red LED
  }
}

void updategame() {
  // Check the player's input against the correct color sequence
  for (int k = 0; k < 6; k++) {
    if (playerOrder[k] != correctOrder[k]) {
      // If the player's input is incorrect, turn on the red LED for 3 seconds
      digitalWrite(RED_PIN, HIGH);
      delay(3000);
      digitalWrite(RED_PIN, LOW);
    } else {
      // If the player's input is correct, flash the green LED three times
      for (int l = 0; l < 3; l++) {
        digitalWrite(GREEN_PIN, HIGH);
        delay(200);
        digitalWrite(GREEN_PIN, LOW);
        delay(200);
      }
    }
  }
}
