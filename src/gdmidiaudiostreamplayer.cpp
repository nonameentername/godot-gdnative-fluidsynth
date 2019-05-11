#include "gdmidiaudiostreamplayer.h"

using namespace godot;

void GDMidiAudioStreamPlayer::_register_methods() {
    register_method("_process", &GDMidiAudioStreamPlayer::_process);
    register_property<GDMidiAudioStreamPlayer, String>("soundfont", &GDMidiAudioStreamPlayer::set_soundfont, &GDMidiAudioStreamPlayer::get_soundfont, String("[empty]"));
}

GDMidiAudioStreamPlayer::GDMidiAudioStreamPlayer() {
    // create the settings
    settings = new_fluid_settings();
    fluid_settings_setstr(settings, "audio.driver", "pulseaudio");

    // create the synthesizer
    synth = new_fluid_synth(settings);

    // create the audio driver
    //adriver = new_fluid_audio_driver(settings, synth);
}

GDMidiAudioStreamPlayer::~GDMidiAudioStreamPlayer() {
    // clean up
    delete buffer;
    delete_fluid_audio_driver(adriver);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);
}

void GDMidiAudioStreamPlayer::_init() {
    // initialize any variables here
    buffer=new float[44100*2];
}

void GDMidiAudioStreamPlayer::_process(float delta) {
    time_emit += delta;

    if (time_emit > 1.0) {
        time_emit = 0.0;

        // generate a random key
        int key = 60 + (int)(12.0f * rand() / (float) RAND_MAX);
        fluid_synth_noteon(synth, 0, key, 80);
        //TODO(nonameentername) use timer to turn the note off
        //fluid_synth_noteoff(synth, 0, key);
        fill_buffer();
    }
}

void GDMidiAudioStreamPlayer::fill_buffer() {
    int64_t to_fill = stream_playback->get_frames_available();
    if (to_fill > 44100) {
        to_fill = 44100;
    }
    fluid_synth_write_float(synth, to_fill, buffer, 0, 2, buffer, 1, 2);
    int index = 0;
    while (to_fill > 0) {
        stream_playback->push_frame(Vector2(buffer[index], buffer[index+1]));
        index = index + 2;
        to_fill = to_fill - 1;
    }

}

void GDMidiAudioStreamPlayer::set_soundfont(String p_soundfont) {
    soundfont = p_soundfont;

    // load a soundfont and reset presets
    String path = ProjectSettings::get_singleton()->globalize_path(soundfont.strip_edges());
    //TODO(nonameentername) does alloc need to free the memory
    int sfont_id = fluid_synth_sfload(synth, path.alloc_c_string(), 1);

    stream_playback = get_stream_playback();
    play();
}

String GDMidiAudioStreamPlayer::get_soundfont() {
    return soundfont;
}
