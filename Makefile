all:
	scons platform=linux bits=64

.PHONY: assets
assets:
	cp /usr/share/sounds/sf2/FluidR3_GM.sf2 assets/example.sf2
	abc2midi assets/example.abc -o assets/example.mid
