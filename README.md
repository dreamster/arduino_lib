Dreamlib
========

This is an Arduino compatible library for Dreamster.

It can also be used as a standalone library without installing it to the Arduino libraries folder (copy the .h file into your project folder and include it in your .ino file.)


How to use
==========

Installing
----------

Copy `Dreamlib.h` and `Dreamlib.cpp` to a folder inside your Arduino `libraries` folder, and then include it:
 
    #include <Dreamlib.h>

Alternatively, copy only the `Dreamlib.h` file into your project folder, and then include it with `#include "Dreamlib.h"` (using quotes).


Using
-----

Instanciate features without any parameters to use them.

    Motors motors;
    InfraredSensors ir_sensors;
    UltrasonicSensors us_sensors;
    Leds leds;


Motors
------

Used simply with `.go(left_speed, right_speed)`, where positive speeds (in percentage) make the motor go forward, and negative speeds make the motor go backwards.

    motors.go(100, -25) // make the robot turn to the right

Can also use the individual methods for changing speed or direction of each motor:

    motors.setLeftSpeed(100);
    motors.setRightSpeed(25);
    motors.setLeftDirection(FORWARD);
    motors.setRightDirection(BACKWARD);


Infrared Sensors
----------------

Called with `.left()` or `.right()`, returns distance in cm (typically `0` to `400`).

    left_sensor_value = ir_sensors.left();

Can specify a maximum distance to speed up sensing with `.setMaximumSensingDistance(distance_in_cm)`.


Ultrasonic sensors
------------------

Called with `.a()` (front sensor), `.b()` or `.c()` (the sensors from the side), returns `0` to `1023`.

    distance_from_front_sensor = us_sensors.a();


Leds
----

Turn on, turn off, or toggle the red, blue and green leds individually.

    leds.redOn();
    leds.blueOff();
    leds.greenToggle();



Folder structure
================

examples
--------

Real examples of the Dreamlib go in this folder.


test_programs
-------------

Some programs used to test both the software and the hardware of the Dreamster 
robot go here. 

None of these use the Dreamster library.