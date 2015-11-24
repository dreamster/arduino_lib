Examples
========

line_follower_pid
-----------------

Line follower using a PID control, depends on [PID Library](http://playground.arduino.cc/Code/PIDLibrary).

It has calibration of the infrared sensors and can follow both a white line on 
a black background and a black line on a white background.

The line is read via a weighted average reading of the two sensors, which produces a single number that goes from 0 (line is at the left sensor) to 2048 (line is at the right sensor). This is the input of the PID control.

The output of the PID is clamped between 0 and 200, using from 0 to 100 to control the left motor, and 101 to 200 to control the right motor. 

[Watch a video of it in action](http://webm.host/619ab).


line_follower_pid_1sensor
-------------------------

Very similar to _line_follower_pid_, but with only one sensor instead of two. Uses a slightly different sensor reading method: instead of reading the two sensors to make the weighted average, it reads the same sensor twice and uses the second reading in place of the second sensor. This generates a single number too, only it is using the current reading and the previous reading (from the past) to calculate the weighted average.

[Watch a video of it in action](http://webm.host/37731).