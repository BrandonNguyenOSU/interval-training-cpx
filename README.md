# interval-training-cpx

Interval Training:
The switch activates and deactivates the game.
When the game is turned off, the board's lights turn off.
Upon start-up, the bottom 8 lights will turn red and a level will start.

Upon level start, the left-most LED will be highlighted in white and a musical interval will play.
This musical interval is one of eight intervals in a major scale.
The eight red LEDs represent these eight notes in a major scale.
After the interval plays, the right button can be used to move the highlighted LED from left to right (resets to left-most if moved past right-most).
When the left button is pressed, the highlighted LED will be selected.

If the highlighted LED is correct, a green animation will play and the left-most LED will be green instead of red.
As the user passes more levels correctly, the red LEDs will turn green from left to right
If the highlighted LED is incorrect, a red animation will play and the red and green LEDs will not change.
After something is selected, the level start process will reset and another interval will play

The game is won when eight intervals are properly identified and the eight LEDs are green.
When the game is won, a win animation is played with a green lightshow and a song.
Upon winning, the game is reset to start-up


Inputs:
Switch - Turns game on and off. Can also be used to reset game.
Left Button - Selects highlighted LED. Progresses game to next level.
Right Button - Moves highlighted LED from left to right.

Outputs:
LEDs - Represent number of correctly identified intervals
- Represent highlighted interval to select
- Play animations for correct, incorrect, and winning events
Sound - Plays intervals to be identified on each level
- Plays song when the game is won
