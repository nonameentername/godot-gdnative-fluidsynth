#include "gdmidiplayer.h"

using namespace godot;

int position = 0;
long fsize = 0;

void *my_open(const char *filename) {
    void *p;
    if(filename[0] != '&') {
        return NULL;
    }
    sscanf(filename, "&%p", &p);
    return p;
}

int my_read(void *buf, int count, void *handle) {
    memcpy(buf, (handle + position), count);
    position = position + count;

    return FLUID_OK;
}

int my_seek(void *handle, long offset, int origin) {
    switch(origin) {
        case SEEK_SET:
            position = offset;
            break;
        case SEEK_CUR:
            position = position + offset;
            break;
        default:
            position = fsize + offset;
            break;
    }

    if (position < 0 || position > fsize) {
        return FLUID_FAILED;
    }

    return FLUID_OK;
}

int my_close(void *handle) {
    return FLUID_OK;
}

long my_tell(void *handle) {
    return position;
}

void GDMidiAudioStreamPlayer::_register_methods() {
    register_method("_process", &GDMidiAudioStreamPlayer::_process);
    register_method("program_select", &GDMidiAudioStreamPlayer::program_select);
    register_method("note_on", &GDMidiAudioStreamPlayer::note_on);
    register_method("note_off", &GDMidiAudioStreamPlayer::note_off);
    register_method("pitch_bend", &GDMidiAudioStreamPlayer::pitch_bend);
    register_property<GDMidiAudioStreamPlayer, String>("soundfont", &GDMidiAudioStreamPlayer::set_soundfont, &GDMidiAudioStreamPlayer::get_soundfont, String("[empty]"));
    register_property<GDMidiAudioStreamPlayer, String>("midi file", &GDMidiAudioStreamPlayer::set_midi_file, &GDMidiAudioStreamPlayer::get_midi_file, String(), GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_RESOURCE_TYPE, String("MidiFileReader"));
}

GDMidiAudioStreamPlayer::GDMidiAudioStreamPlayer() {
    settings = new_fluid_settings();
    fluid_settings_setstr(settings, "audio.driver", "pulseaudio");
    synth = new_fluid_synth(settings);
    player = new_fluid_player(synth);
    fluid_sfloader_t *my_sfloader = new_fluid_defsfloader(settings);
    fluid_sfloader_set_callbacks(my_sfloader,
                                 my_open,
                                 my_read,
                                 my_seek,
                                 my_tell,
                                 my_close);
    fluid_synth_add_sfloader(synth, my_sfloader);
}

GDMidiAudioStreamPlayer::~GDMidiAudioStreamPlayer() {
    delete buffer;
    delete_fluid_player(player);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);
}

void GDMidiAudioStreamPlayer::_init() {
    buffer=new float[44100*2];
    fluidsynth_playing = false;
    stream_playback = get_stream_playback();
}

void GDMidiAudioStreamPlayer::_process(float delta) {
    if (fluid_player_get_status(player) == FLUID_PLAYER_DONE && fluidsynth_playing) {
        fluid_player_stop(player);
        fluid_player_join(player);
        delete_fluid_player(player);
        fluidsynth_playing = false;

        player = new_fluid_player(synth);
    }

    if (is_playing() && !fluidsynth_playing) {
        fluidsynth_play();
    }

    if (is_playing()) {
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

    if(ResourceLoader::get_singleton()->exists(soundfont)) {
        Variant resource = ResourceLoader::get_singleton()->load(soundfont);
        Ref<SoundFontFileReader> soundfont_file = resource;
        char abused_filename[64];
        const void *pointer_to_sf2_in_mem = soundfont_file->get_array_data();
        sprintf(abused_filename, "&%p", pointer_to_sf2_in_mem);
        fsize = soundfont_file->get_array_size();
        sfont_id = fluid_synth_sfload(synth, abused_filename, 1);
    }
}

String GDMidiAudioStreamPlayer::get_soundfont() {
    return soundfont;
}

void GDMidiAudioStreamPlayer::set_midi_file(String p_midi_file) {
    midi_file = p_midi_file;
}

String GDMidiAudioStreamPlayer::get_midi_file() {
    return midi_file;
}

void GDMidiAudioStreamPlayer::fluidsynth_play() {
    if(ResourceLoader::get_singleton()->exists(midi_file)) {
        Variant resource = ResourceLoader::get_singleton()->load(midi_file);

        Ref<MidiFileReader> midi = resource;
        PoolByteArray byte_array = midi->get_data();

        if (byte_array.size() > 0) {
            char midi_file[byte_array.size()];

            for (int i = 0; i < byte_array.size(); i++) {
                midi_file[i] = byte_array[i];
            }

            fluid_player_add_mem(player, midi_file, byte_array.size());
        }

        fluid_player_play(player);
        fluidsynth_playing = true;
    }
}

void GDMidiAudioStreamPlayer::program_select(int chan, int bank_num, int preset_num) {
    fluid_synth_program_select(synth, chan, sfont_id, bank_num, preset_num);
}

void GDMidiAudioStreamPlayer::note_on(int chan, int key, int vel) {
    fluid_synth_noteon(synth, chan, key, vel);
}

void GDMidiAudioStreamPlayer::note_off(int chan, int key) {
    fluid_synth_noteoff(synth, chan, key);
}

void GDMidiAudioStreamPlayer::pitch_bend(int chan, int val) {
    fluid_synth_pitch_bend(synth, chan, val);
}
