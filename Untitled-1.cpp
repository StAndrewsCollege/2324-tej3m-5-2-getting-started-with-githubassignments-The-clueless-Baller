#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

int speed;
int strength;
double luck;
int attack;
bool food_eaten = false;
bool pan_taken = false;
bool weapon_given = false;
bool boss_ready = false;
int training = 0;
unsigned long randSeed;
bool exists_and_luck_available = false;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);  // Assuming A0 is used for analog input
  randSeed = analogRead(A0);  // Seed the random number generator
}

void loop() {
    int choice_direction;
    lcd.print(F("Pick your character! Pick 1 for Sean, which is the highest difficulty."));
    lcd.print(F("2 is William English, which is medium difficulty."));
    lcd.print(F("3 is Beric, which is an easy game."));
    lcd.print(F("4 is Willer with the best Char_stats, a comically easy game."));
    int character_int = Serial.parseInt();
    if (character_int == 1) {
        speed = 1;
        strength = 1;
        luck = 0.1;
        lcd.print(F("Your character is Sean"));
        exists_and_luck_available = true;
    }
    else if (character_int == 2) {
        speed = 1;
        strength = 3;
        luck = 1;
        lcd.print(F("Your character is William"));
        exists_and_luck_available = true;
    }
    else if (character_int == 3) {
        speed = 2;
        strength = 3;
        luck = 4;
        lcd.print(F("Your character is Beric"));
        exists_and_luck_available = true;
    }
    else if (character_int == 4){
        speed = 3;
        strength = 5;
        luck = 3;
        lcd.print(F("Your character is Willer"));
    }
    // Gives the player stats based on who they choose. 
    Serial.print(F("Speed: "));
    lcd.print(speed);
    Serial.print(F("Strength: "));
    lcd.print(strength);
    Serial.print(F("Luck: "));
    lcd.print(luck);
    // Displays the players stats to them

    lcd.print(F("You wake up in a nice calm field. Suddenly an alien appears from the edge of the field and begins running towards you and looks like it wants to hurt you"));
    lcd.print(F("Press 1 to fight, and 2 to run"));
    int choice = Serial.parseInt();
    if (choice == 1) {
        if (strength < 2) {
            exists_and_luck_available = false;
            if (strength + random(1000) * 0.001 * luck < 2) {
                lcd.print(F("The alien renders you unconscious, and you wake up lying in that same field. You can see the alien is on his way back with more to help him."));
                lcd.print(F("Press 1 to fight, and 2 to run"));
                choice = Serial.parseInt();
                if (choice == 1) {
                    lcd.print(F("You get captured and probably die"));
                }
                if (choice == 2) {
                    if (speed < 3) {
                        lcd.print(F("To the north is a row of houses, East is the city, South is the forest, West is a massive spaceship hovering above the ground quite far away. N = 1, E = 2, S = 3, W = 4."));
                        choice_direction = Serial.parseInt();
                        checkpoint_1(choice_direction);
                    }
                }
            } 
            else {
                lcd.print(F("You escape"));
                lcd.print(F("You feel that you were outmatched in the fight and shouldn't get into that tight of a situation again."));
                lcd.print(F("To the north is a row of houses, East is the city, South is the forest, West is a massive spaceship hovering above the ground quite far away. N = 1, E = 2, S = 3, W = 4."));
                choice_direction = Serial.parseInt();
                checkpoint_1(choice_direction);
            }
        }
        else {
            lcd.print(F("You fight off the alien and manage to escape"));
            lcd.print(F("To the north is a row of houses, South is the forest, East is the city, West is a massive spaceship hovering above the ground quite far away. N = 1, E = 2, S = 3, W = 4."));
            choice_direction = Serial.parseInt();
            checkpoint_1(choice_direction);
        }
    }
    if (choice == 2) {
        if (speed < 3) {
            exists_and_luck_available = false;
            if (speed + (random(luck)) < 2) {
               lcd.print(F("You are captured and have been taken to the leader of the aliens. The game ends."));
            // If you want to exit the Arduino program, you might use:
            // exit(0);
            // However, keep in mind that Arduino doesn't support exit() directly.
            }
        }
        else {
        lcd.print(F("You escape"));
        lcd.print(F("To the north is a row of houses, South is the forest, East is the city, West is a massive spaceship hovering above the ground quite far away. N = 1, E = 2, S = 3, W = 4."));
        choice_direction = Serial.parseInt();
        checkpoint_1(choice_direction);
        }
    }
}
void checkpoint_1(int confusion) {
        if (confusion == 1){
            lcd.print(F("The door to the houses have been destroyed. Inside you can go to the kitchen, living room, or basement or back outside. 1= kitchen, 2= living room 3= basement 4 = back outside"));
            confusion = Serial.parseInt();
            if (confusion == 1) {
                if (food_eaten == false && pan_taken == false) {
                    lcd.print(F("There is a pan, and some food in the fridge, some of which is past its due date. Use 1 to pick up the pan, 2 to eat the food, and 3 to do both, or 4 to leave."));
                    confusion = Serial.parseInt();
                    if (confusion == 1) {
                        pan_taken = true;
                        lcd.print(F("With this pan as an improvised weapon you think you could do better in a fight."));
                        lcd.print(F("Your attack has increased by 2"));
                        lcd.print(F("Your going back outside, you can come back in the house if you want but I'm not coding that as an option since I'm lazy."));
                        lcd.print(F("To the north is a row of houses that you just left, South is the forest, East is the city, West is a massive spaceship hovering above the ground quite far away. N = 1, E = 2, S = 3, W = 4."));
                        attack = attack + 2;
                        Serial.print(F("Your attack is: "));
                        lcd.print(attack);
                        checkpoint_1(confusion);
                    }
                    else if (confusion == 2) {
                        food_eaten = true;
                        if (luck < 3) {
                            lcd.print(F("You die of food poisoning"));
                            // Assuming you have a suitable way to exit the program on Arduino
                            // Replace the following line with an appropriate method to exit the program on Arduino
                            exit(0);
                        }
                        else {
                            lcd.print(F("You feel a little stronger since you've eaten recently."));
                            lcd.print(F("Your attack has increased by 1"));
                            attack = attack + 1;
                            Serial.print(F("Your attack is: "));
                            lcd.print(attack);
                            checkpoint_1(confusion);
                        }
                        lcd.print(F("Your going back outside, you can come back in the house if you want but I'm not coding that as an option since I'm lazy."));
                        lcd.print(F("To the north is a row of houses that you just left, South is the forest, East is the city, West is a massive spaceship hovering above the ground quite far away. N = 1, E = 2, S = 3, W = 4."));
                        confusion = Serial.parseInt();
                        attack = attack + 1;
                        Serial.print(F("Your attack is: "));
                        lcd.print(attack);
                        checkpoint_1(confusion);
                    }
                    else if (confusion == 3) {
                        pan_taken = true;
                        food_eaten = true;
                        if (luck < 3) {
                            lcd.print(F("You die of food poisoning"));
                            // Assuming you have a suitable way to exit the program on Arduino
                            // Replace the following line with an appropriate method to exit the program on Arduino
                            exit(0);
                        }
                        else {
                            lcd.print(F("You feel a little stronger since you've eaten recently."));
                            checkpoint_1(confusion);
                        }
                        lcd.print(F("With the pan as an improvised weapon and having eaten, you feel more prepared for the challenges ahead."));
                        lcd.print(F("Your attack has increased by 3"));
                        attack = attack + 3;
                        lcd.print(F("Your attack is: "));
                        lcd.print( attack);
                        lcd.print(F("You're going back outside; you can come back in the house if you want, but I'm not coding that as an option since I'm lazy."));
                        lcd.print(F("To the north is a row of houses that you just left, East is the city, South is the forest, West is a massive spaceship hovering above the ground quite far away. N = 1, E = 2, S = 3, W = 4."));
                        confusion = Serial.parseInt();
                        checkpoint_1(confusion);
                    } 
                    else if (confusion == 4) {
                        lcd.print(F("You leave the house and explore the surroundings."));
                        lcd.print(F("To the north is a row of houses, East is the city, South is the forest, West is a massive spaceship hovering above the ground quite far away. N = 1, E = 2, S = 3, W = 4."));
                        confusion = Serial.parseInt();
                        checkpoint_1(confusion);
                    }
                if (food_eaten == false && pan_taken == true) {
                    lcd.print(F("There is some food in the fridge, some of which is past its due date. Use 1 to eat the food, or 2 to leave."));
                    confusion = Serial.parseInt();
                    if (confusion == 1) {
                        food_eaten = true;
                        if (luck < 3) {
                            lcd.print(F("You die of food poisoning"));
                            // Assuming you have a suitable way to exit the program on Arduino
                            // Replace the following line with an appropriate method to exit the program on Arduino
                        }
                        else {
                            lcd.print(F("You feel a little stronger since you've eaten recently."));
                            lcd.print(F("Your attack has increased by 1"));
                            attack = attack + 1;
                            Serial.print(F("Your attack is: "));
                            lcd.print(attack);
                            checkpoint_1(confusion);
                        }
                        lcd.print(F("Your going back outside, you can come back in the house if you want but I'm not coding that as an option since I'm lazy."));
                        lcd.print(F("To the north is a row of houses that you just left, South is the forest, East is the city, West is a massive spaceship hovering above the ground quite far away. N = 1, E = 2, S = 3, W = 4."));
                        confusion = Serial.parseInt();
                        attack = attack + 1;
                        Serial.print(F("Your attack is: "));
                        lcd.print(attack);
                        checkpoint_1(confusion);
                    }
                    else if (confusion == 4) {
                        lcd.print(F("Your going back outside, you can come back in the house if you want but I'm not coding that as an option since I'm lazy."));
                        lcd.print(F("To the north is a row of houses that you just left, South is the forest, East is the city, West is a massive spaceship hovering above the ground quite far away. N = 1, E = 2, S = 3, W = 4."));
                        confusion = Serial.parseInt();
                        checkpoint_1(confusion);
                    }
                }
                if (food_eaten == true && pan_taken == false) {
                    lcd.print(F("There is a pan. Use 1 to pick up the pan or 2 to leave."));
                    confusion = Serial.parseInt();

                    if (confusion == 1) {
                        pan_taken = true;
                        lcd.print(F("With this pan as an improvised weapon you think you could do better in a fight."));
                        lcd.print(F("Your attack has increased by 2"));
                        lcd.print(F("Your going back outside, you can come back in the house if you want but I'm not coding that as an option since I'm lazy."));
                        lcd.print(F("To the north is a row of houses that you just left, South is the forest, East is the city, West is a massive spaceship hovering above the ground quite far away. N = 1, E = 2, S = 3, W = 4."));
                        confusion = Serial.parseInt();
                        attack = attack + 2;
                        Serial.print(F("Your attack is: "));
                        lcd.print(attack);
                        checkpoint_1(confusion);
                        }
                    else if (confusion == 4) {
                        lcd.print(F("Your going back outside, you can come back in the house if you want but I'm not coding that as an option since I'm lazy."));
                        lcd.print(F("To the north is a row of houses that you just left, South is the forest, East is the city, West is a massive spaceship hovering above the ground quite far away. N = 1, E = 2, S = 3, W = 4."));
                        confusion = Serial.parseInt();
                        checkpoint_1(confusion);
                    }
                }
            }
        }
    }
}