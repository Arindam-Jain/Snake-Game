# Snake-Game Bi-colour led
A snake game on Arduino with LED matrix 8x8

# Components Used:
Arduino UNO</br>
Self made 8x8 LED Dot Matrix Display using 64 Bi-color LED</br>
Shift Register 74HC595</br>
Push Buttons</br>
Connecting wires</br>
Bread Board</br>
Power Supply</br>
2x Seven Segment Display</br>

# Video
https://drive.google.com/open?id=1FGI-Uws5thmpM7iJ8F73kbpuhiqAwAFZ

# Circuit Explanation:
Here we have connected dot matrix display by using Shift Register 74HC595. Here two shift registers are used, one for driving the columns and second for driving the rows.LatchPin is connected at 10,clockPin is connected at 12, dataPin is connected at 11;
button pin
 btn_up = 0;
 btn_down = 1;
 btn_left = 2;
 btn_right = 3;


