UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
PLATFORM=linux
endif
ifeq ($(UNAME), Darwin)
PLATFORM=osx
endif

all:
	scons platform=$(PLATFORM) bits=64

.PHONY: godot-cpp

godot-cpp:
	(cd godot-cpp && scons platform=$(PLATFORM) bits=64 generate_bindings=yes)

.PHONY: assets
assets:
	cp /usr/share/sounds/sf2/FluidR3_GM.sf2 assets/example.sf2
	abc2midi assets/example.abc -o assets/example.mid
