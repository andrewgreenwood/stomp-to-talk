# Stomp-to-Talk

This is a small program that translates MIDI foot-pedal messages into key presses/releases. It's intended usage is
as an alternative method of triggering "push-to-talk" in programs/games. If you happen to use your gaming rig to make
music as well, you'll probably find this useful.

To compile with GCC on Windows:

    gcc midi2key.c -lwinmm

There is no configuration or UI for the program - you'll need to set the options in the source code before compiling
it. In particular you will need to know the MIDI input device number (or just try incrementing from 0 each time until
you find it) and the keyboard scan code (hardware-dependent, though you can probably find this out on the Internet).

There are probably many improvements that could be made - it was written as a quick hack in 2014 though :)

Once running, to terminate the program press CTRL+C.


# Licence

Public domain
Use this code for whatever you like
