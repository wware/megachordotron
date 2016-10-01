The Megachordotron
====

The Megachordotron is a
[MIDI controller](https://en.wikipedia.org/wiki/MIDI_controller)
organized around simple
[chords](https://en.wikipedia.org/wiki/Chord_(music)). It's
intended for people (like myself) who are too clumsy to play a guitar.

![A picture of the Megachordotron](/megachordotron_midi_ctrlr.jpg?raw=true "A picture of the Megachordotron")

Since it's just a MIDI controller, it needs a
[MIDI synthesizer](https://en.wikipedia.org/wiki/MIDI#Synthesizers) to work.
The synthesizer is the PC on this little rack, which is a
[Linux Mint](https://www.linuxmint.com/) box running Fluidsynth (here is
[some](https://wiki.archlinux.org/index.php/FluidSynth)
[info](http://tedfelix.com/linux/linux-midi.html) about that).
There is also a guitar amp and a keyboard and monitor.

![The MIDI synth as of 10/1/2016](/midi_synth.jpg?raw=true "The MIDI synth as of 10/1/2016")

After Maker Faire is over, I want to spend some time making the synth much
[less cumbersome](http://www.tomsguide.com/us/best-mini-pcs,review-2760.html).
As it stands it is quite inconvenient.

BTW, the shortened URL for this repository is https://git.io/vPt04.

Printed circuit board
----

![Schematic](/FullInstrument.png?raw=true "Schematic")

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
them, or the last CD4051 (IC5). There is also no need to supply +12V or +5V other
than what is supplied by the USB cable.

The bypass caps should all be populated, and D1 and R3 must be populated.

Programming the Teensy
----

You should use a Teensy 3.1 or 3.2 to build the Megachordotron.

In the Arduino application menu, choose `Tools > USB Type`, and select `MIDI`.

I am running my Teensy at 72 MHz, but that's probably something you can experiment
with. There is only one place in the code where fast timing is really significant,
in the `read_kdy` function in `teensy.ino` which is mostly in assembly language.
Actually now that I think of it, I'll probably switch to 96 MHz, because that
affects keyboard sensitivity.
