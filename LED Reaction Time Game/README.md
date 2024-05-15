
# LED Reaction Time Game

![LED Reaction Time Game](game_preview.jpeg)

## Description

This Arduino project implements a reaction time game using LEDs and buttons. The game challenges players to press a button at the right moment to advance through levels as LEDs light up sequentially. The speed of the game increases with each level, testing the player's reaction time and precision.

## Components Used

- Red LED: Used as a game start indicator.
- LEDs: A row of LEDs that light up sequentially.
- Buttons: Two buttons for gameplay interaction and level advancement.

## Gameplay Mechanics

1. Press the first button to start the game. The red LED indicator lights up for 0.5 seconds.
2. After the red LED turns off, LEDs start lighting up sequentially with decreasing delays between each LED.
3. Press the second button at the right time to advance to the next level. Pressing the button when LEDs are at index 0 or 1 advances to the next level.
4. The game speed increases with each level, providing a progressively challenging experience.
5. Press the first button during gameplay to reset the game and turn off the red LED indicator.
6. If the second button is not pressed at the correct time, the game ends, and all LEDs blink three times to indicate game over.


1. Press the first button to start the game. The red LED indicator lights up and remains on throughout the game.
2. LEDs start lighting up sequentially.
3. Press the second button at the right time to advance to the next level. Pressing the button when LEDs are at index 0 or 1 advances to the next level.
4. The game speed increases with each level, providing a progressively challenging experience.
5. Press the first button during gameplay to reset the game.
6. If the second button is not pressed at the correct time, the game ends, and all LEDs blink three times to indicate game over.

## Setup

1. Connect the components to your Arduino board as per the pin assignments in the code.
2. Upload the provided Arduino sketch (`LEDReactionTimeGame.ino`) to your Arduino board using the Arduino IDE or any compatible IDE.
3. Power up your Arduino board and start playing the LED reaction time game!

## Contributors

- [Abdelghani Yacine BARKA](https://github.com/decodevm)
- [Nardjes Sara KHIAT](https://github.com/Nardjes03)


## Contributing

Contributions to this LED reaction time game project are welcome! If you have any ideas for improvements or new features, feel free to open an issue or submit a pull request.

