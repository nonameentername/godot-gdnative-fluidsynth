tool
class_name SoundFontDataLoader
extends ResourceFormatLoader

const SoundFontFileReader = preload("res://bin/soundfont_file_reader.gdns")

func get_recognized_extensions():
    return PoolStringArray(["sf2str"])

func get_resource_type(path):
    var ext = path.get_extension().to_lower()
    if ext == "sf2str":
        return "SoundFontFileReader"
    return ""

func handles_type(typename):
    return typename == "SoundFontFileReader"

func load(path, original_path):
    var f = File.new()

    var err = f.open(path, File.READ)
    if err != OK:
        return err

    var res = SoundFontFileReader.new()
    var data = f.get_buffer(f.get_len())
    res.set_data(data)
    f.close()

    return res