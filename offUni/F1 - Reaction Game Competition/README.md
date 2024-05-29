# Arduino Reaction Game

This project implements a reaction game using an Arduino Uno board. The game requires the player to react quickly to a stimulus by pressing a button. The reaction time is measured and displayed after each round.

## Components Used
- Arduino Uno board
- LEDs (Red, Orange, Green)
- Button
- Buzzer
- Light Sensor (LDR)

## Gameplay
1. The game starts with a countdown sequence, where LEDs simulate the lights of an F1 race.
2. After the countdown, the green LED turns on, signaling the player to react.
3. The player must press the button as quickly as possible.
4. The reaction time is measured and displayed.
5. Depending on the reaction time, a success or failure sound is played through the buzzer.

## Light Sensor Integration
- A light sensor (LDR) is used to simulate different environmental conditions.
- The game starts only when the light level falls below a certain threshold, simulating a transition to a darker environment.
- The threshold value can be adjusted to control when the game starts, allowing for customization of gameplay based on lighting conditions.

## Getting Started
1. Connect the components as per the circuit diagram provided.
2. Upload the Arduino sketch to the Arduino Uno board.
3. Ensure that the environment has varying light conditions to experience the effect of the light sensor.

## Circuit Diagram
![Circuit Diagram](circuit_diagram.png)

## Additional Notes
- Adjust the threshold value in the Arduino sketch to customize gameplay based on lighting conditions.
- Experiment with different combinations of LEDs, sounds, and gameplay elements to enhance the gaming experience.

Have fun playing and improving your reaction time with the Arduino Reaction Game!
