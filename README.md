Color-Tracking-Robot
====================

Python Scripts and Arduino Sketches for color tracking Car


Uses OpenCV to locate an object and return its coordinates in the camera's field of view

Sends coordinates over serial connection to Arduino

Important: When hooking up GPIO on Raspberry Pi to serial on Arduino make sure to either use a logic level converter
or have a voltage divider on the tx line from the Arduino to the rx line of the Pi to prevent damage to the Raspberry Pi
