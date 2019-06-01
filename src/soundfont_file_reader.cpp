#include "soundfont_file_reader.h"

using namespace godot;

SoundFontFileReader::SoundFontFileReader() {
    array_data = NULL;
}

SoundFontFileReader::~SoundFontFileReader() {
    if (array_data != NULL) {
        godot::api->godot_free(array_data);
    }
}

void SoundFontFileReader::_init() {
}

void SoundFontFileReader::clear_data() {
}

void SoundFontFileReader::set_data(PoolByteArray data) {
    PoolByteArray in_array = data;

    if (array_data != NULL) {
        godot::api->godot_free(array_data);
    }

    array_size = in_array.size();
    array_data = (char*)godot::api->godot_alloc((array_size + 1) * sizeof(char));

    for (int i = 0; i < array_size; i++) {
        array_data[i] = in_array[i];
    }
    array_data[array_size] = 0;
}

PoolByteArray SoundFontFileReader::get_data() {
    PoolByteArray out_array;
    for(int i = 0; i < array_size; i++) {
        out_array.append(array_data[i]);
    }
    return out_array;
}

char* SoundFontFileReader::get_array_data() {
    return array_data;
}

long SoundFontFileReader::get_array_size() {
    return array_size;
}

String SoundFontFileReader::get_extension() {
    return "sf2str";
}

void SoundFontFileReader::_register_methods() {
	register_method("set_data", &SoundFontFileReader::set_data);
	register_method("get_data", &SoundFontFileReader::get_data);
    register_method("get_extension", &SoundFontFileReader::get_extension);
    register_property<SoundFontFileReader, PoolByteArray>("data", &SoundFontFileReader::set_data, &SoundFontFileReader::get_data, PoolByteArray());
}
