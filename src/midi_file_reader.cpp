#include "midi_file_reader.h"

using namespace godot;

MidiFileReader::MidiFileReader() {
}

MidiFileReader::~MidiFileReader() {
}

void MidiFileReader::_init() {
}

void MidiFileReader::clear_data() {
}

void MidiFileReader::set_data(PoolByteArray data) {
    PoolByteArray in_array = data;
    PoolByteArray out_array;
    for (int i = 0; i < in_array.size(); i++) {
        out_array.append(in_array[i]);
    }
    array_data = out_array;
}

PoolByteArray MidiFileReader::get_data() {
    PoolByteArray out_array;
    for(int i = 0; i < array_data.size(); i++) {
        out_array.append(array_data[i]);
    }
    return out_array;
}

String MidiFileReader::get_extension() {
    return "midstr";
}

void MidiFileReader::_register_methods() {
	register_method("set_data", &MidiFileReader::set_data);
	register_method("get_data", &MidiFileReader::get_data);
    register_method("get_extension", &MidiFileReader::get_extension);
    register_property<MidiFileReader, PoolByteArray>("data", &MidiFileReader::set_data, &MidiFileReader::get_data, PoolByteArray());
}
