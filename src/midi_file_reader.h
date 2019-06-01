#ifndef MIDIFILEREADER_H
#define	MIDIFILEREADER_H

#include <Godot.hpp>
#include <Resource.hpp>
#include <Variant.hpp>

namespace godot {

class MidiFileReader : public Resource {
	GODOT_CLASS(MidiFileReader, Resource)

private:
	String file;

    PoolByteArray array_data;
	void clear_data();
public:
	MidiFileReader();
	~MidiFileReader();

    void _init();

	void set_data(PoolByteArray data);
	PoolByteArray get_data();
    String get_extension();

	static void _register_methods();
};

}

#endif
