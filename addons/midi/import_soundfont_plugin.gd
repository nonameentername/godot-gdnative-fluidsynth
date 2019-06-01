tool
extends EditorImportPlugin

const SoundFontFileReader = preload("res://bin/soundfont_file_reader.gdns")

func get_importer_name():
    return "soundfont"

func get_visible_name():
    return "SoundFont"

func get_recognized_extensions():
    return ["sf2"]

func get_save_extension():
    return "sf2str"

func get_resource_type():
    return "SoundFontFileReader"

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
    var soundfont_file = SoundFontFileReader.new()
    soundfont_file.set_data(data)
    file.close()

    return ResourceSaver.save("%s.%s" % [save_path, get_save_extension()], soundfont_file)
