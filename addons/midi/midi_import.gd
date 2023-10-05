tool
extends EditorPlugin

var midi_plugin
var soundfont_plugin

func _enter_tree():
	add_custom_type("MidiFileReader", "Resource", preload("res://bin/midi_file_reader.gdns"), preload("res://icon.png"))
	midi_plugin = preload("import_midi_plugin.gd").new()
	add_import_plugin(midi_plugin)

	soundfont_plugin = preload("import_soundfont_plugin.gd").new()
	add_import_plugin(soundfont_plugin)

func _exit_tree():
	remove_custom_type("MidiFileReader")

	remove_import_plugin(midi_plugin)
	midi_plugin = null

	remove_import_plugin(soundfont_plugin)
	soundfont_plugin = null
