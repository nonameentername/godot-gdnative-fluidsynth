#ifndef GDMIDIAUDIOSTREAMPLAYER_H
#define GDMIDIAUDIOSTREAMPLAYER_H

#include <Godot.hpp>
#include <AudioStream.hpp>
#include <AudioStreamPlayer.hpp>
#include <AudioStreamGeneratorPlayback.hpp>
#include <ProjectSettings.hpp>
#include <fluidsynth.h>


namespace godot {

class GDMidiAudioStreamPlayer : public AudioStreamPlayer {
    GODOT_CLASS(GDMidiAudioStreamPlayer, AudioStream)

private:
    float time_emit;
    String soundfont;
    float* buffer;

    fluid_settings_t *settings;
    fluid_synth_t *synth;
    fluid_audio_driver_t *adriver;
    Ref<AudioStreamGeneratorPlayback> stream_playback;

    void fill_buffer();

public:
    static void _register_methods();

    GDMidiAudioStreamPlayer();
    ~GDMidiAudioStreamPlayer();

    void _init(); // our initializer called by Godot

    void _process(float delta);
    void set_soundfont(String p_soundfont);
    String get_soundfont();
};

}

#endif
