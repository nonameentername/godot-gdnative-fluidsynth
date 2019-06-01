#ifndef SOUNDFONTFILEREADER_H
#define	SOUNDFONTFILEREADER_H

#include <Godot.hpp>
#include <Resource.hpp>
#include <Variant.hpp>

namespace godot {

class SoundFontFileReader : public Resource {
	GODOT_CLASS(SoundFontFileReader, Resource)

private:
	String file;

    long array_size;
    char *array_data;
	void clear_data();
public:
	SoundFontFileReader();
	~SoundFontFileReader();

    void _init();

	void set_data(PoolByteArray data);
	PoolByteArray get_data();
    char *get_array_data();
    long get_array_size();
    String get_extension();

	static void _register_methods();
};

}

#endif
