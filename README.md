godot-gdnative-fluidsynth
=========================

Godot gdnative fluidsynth library to allow playing music using fluidsynth.

How to Install
--------------

Install system dependencies for Ubuntu:

    apt install libfluidsynth-dev abcmidi

Build
-----

Initialize git submodules:

    git submodule update --init --recursive

Create assets:

    make assets

Compile godot-cpp library:

    make godot-cpp

Compile gdnative library:

    make
