The Megachordotron
====

Printed circuit boards
----

I use Cadsoft Eagle for PCB layout. For these designs you'll need to pick up
some third-party libraries.

* [Teensy 3.0 library](https://forum.pjrc.com/attachment.php?attachmentid=184&d=1358973338)
  - [Discussion of Teensy library](https://www.pjrc.com/teensy/eagle_lib.html)
* [Sparkfun Connector library](https://github.com/sparkfun/SparkFun-Eagle-Libraries)

Errata
----

I laid out the board in haste and made a mistake. One end of the diode D1 does not
connect correctly to the resistor R3. I think it's the cathode. I had to solder a
little jumper.

This board was originally used for a different instrument (hence the filename) and
the audio circuitry is not needed in the current instantiation. There is no need to
populate the TPA3122 (IC6) or the emitter follower to the left, or the parts around
them, and no need to supply +12V or +5V other than what is supplied by the USB
cable. The bypass caps should all be populated, and D1 and R3 must be populated.
