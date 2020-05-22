# Snake-Game Bi-colour led
A snake game on Arduino with LED matrix 8x8 **using 3 pins!**

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
Here we have connected dot matrix display by using Shift Register 74HC595. Here two shift registers are used, one for driving the columns and second for driving the rows.
LatchPin is connected at 10</br>
clockPin is connected at 12</br>
dataPin is connected at 11</br>
button pin</br>
btn_up = 0;</br>
btn_down = 1;</br>
btn_left = 2;</br>
btn_right = 3;</br>

# Shift Register 74HC595 Diagram
![Screenshot 2020-05-22 at 1 44 53 PM](https://user-images.githubusercontent.com/40122399/82646602-7f85e280-9c32-11ea-9314-6aba6032bcc5.png)

# Circuit Diagram
![Screenshot 2020-05-22 at 1 36 04 PM](https://user-images.githubusercontent.com/40122399/82645882-3a14e580-9c31-11ea-8640-e3d78d7f7425.png)

![Screenshot 2020-05-22 at 1 48 47 PM](https://user-images.githubusercontent.com/40122399/82646934-089d1980-9c33-11ea-8f02-dd516c59d526.png)





