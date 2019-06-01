#include "gdmidiplayer.h"
#include "midi_file_reader.h"
#include "soundfont_file_reader.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);
    godot::register_class<godot::MidiFileReader>();
    godot::register_class<godot::SoundFontFileReader>();
    godot::register_class<godot::GDMidiAudioStreamPlayer>();
}
