tool
extends EditorImportPlugin

const MidiFileReader = preload("res://bin/midi_file_reader.gdns")

func get_importer_name():
	return "midi"

func get_visible_name():
	return "MIDI"

func get_recognized_extensions():
	return ["mid"]

func get_save_extension():
	return "midstr"

func get_resource_type():
	return "MidiFileReader"

func get_option_visibility(option, options):
	return true

func get_preset_count():
	return 1;

func get_preset_name(preset):
	return "Default"

func get_import_options(preset):
	return []

func import(source_file, save_path, options, r_platform_variants, r_gen_files):
	var file = File.new()
	var err = file.open(source_file, File.READ)
	if err != OK:
		return err

	var data = file.get_buffer(file.get_len())
	var midi_file = MidiFileReader.new()
	midi_file.set_data(data)
	file.close()

	return ResourceSaver.save("%s.%s" % [save_path, get_save_extension()], midi_file)
