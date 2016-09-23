#!/usr/bin/env python

"""
If running Ubuntu, add this line to the end of your
$HOME/.profile.

/usr/bin/python /home/wware/midisynth.py &

Change "wware" to your own username, and copy this file
into your home directory.
"""

import os
import re
import time

cmd = (
    "fluidsynth --server --no-shell --audio-driver=alsa " +
    "/usr/share/sounds/sf2/FluidR3_GM.sf2 &"
)
print cmd
assert os.system(cmd) == 0

R = os.popen('ps ax | grep fluidsynth | grep -v grep').read()
if not R:
    os.system("ps ax | grep fluidsynth | cut -c -6 | xargs kill -9")
    assert R, R

iters = 0
while True:
    time.sleep(1)
    R = os.popen('aconnect -l').read()
    if "FLUID Synth" in R:
        r2 = re.compile(r"client (\d+): 'FLUID Synth").search(R)
        fluid_num = r2.group(1)
        break
    iters += 1
    assert iters < 15, "Cannot find fluidsynth process"

connected = False
try:
    while True:
        time.sleep(1)
        R = os.popen('aconnect -l').read()
        r1 = re.compile(r"client (\d+): 'Teensy MIDI'").search(R)
        if not r1:
            connected = False
            continue
        if connected:
            continue
        os.system("aconnect %s %s" % (r1.group(1), r2.group(1)))
        connected = True
except KeyboardInterrupt:
    os.system("ps ax | grep fluidsynth | cut -c -6 | xargs kill -9")
