#include "gdmidiplayer.h"

using namespace godot;

void GDMidiPlayer::_register_methods() {
    register_method("_process", &GDMidiPlayer::_process);
    register_property<GDMidiPlayer, float>("amplitude", &GDMidiPlayer::amplitude, 10.0);
    register_property<GDMidiPlayer, float>("speed", &GDMidiPlayer::set_speed, &GDMidiPlayer::get_speed, 1.0);

    register_signal<GDMidiPlayer>((char *)"position_changed", "node", GODOT_VARIANT_TYPE_OBJECT, "new_pos", GODOT_VARIANT_TYPE_VECTOR2);
}

GDMidiPlayer::GDMidiPlayer() {
}

GDMidiPlayer::~GDMidiPlayer() {
    // add your cleanup here
}

void GDMidiPlayer::_init() {
    // initialize any variables here
    time_passed = 0.0;
    amplitude = 10.0;
    speed = 1.0;
}

void GDMidiPlayer::_process(float delta) {
    time_passed += speed * delta;

    Vector2 new_position = Vector2(
        amplitude + (10.0 * sin(time_passed * 2.0)),
        amplitude + (10.0 * cos(time_passed * 1.5))
    );

    set_position(new_position);

    time_emit += delta;

    if (time_emit > 1.0) {
        emit_signal("position_changed", this, new_position);
        time_emit = 0.0;
    }
}

void GDMidiPlayer::set_speed(float p_speed) {
    speed = p_speed;
}

float GDMidiPlayer::get_speed() {
    return speed;
}
