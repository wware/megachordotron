Printed circuit boards
====

I use Cadsoft Eagle for PCB layout. For these designs you'll need to pick up
some third-party libraries.

* [Teensy 3.0 library](https://forum.pjrc.com/attachment.php?attachmentid=184&d=1358973338)
  - [Discussion of Teensy library](https://www.pjrc.com/teensy/eagle_lib.html)
* [Sparkfun Connector library](https://github.com/sparkfun/SparkFun-Eagle-Libraries)

Some notes on the Trivisynth board
----

R1, R2, and R3 should be 10K, 4.7K and 100 ohms respectively. The two caps near
the audio amp should be 10uF, all others should be 0.1uF. The transistor is
generic NPN (e.g. 2N3904) and the diode is generic (e.g. 1N4148).

Pin 6 of IC3 is wired incorrectly. The trace connecting it to pin 6 of IC1 must
be cut, and a wire soldered from IC3-6 to GPIO 5 of the Teensy (what would be
pin 7 if the Teensy were a DIP).
