tool
class_name MidiDataLoader
extends ResourceFormatLoader

const MidiFileReader = preload("res://bin/midi_file_reader.gdns")

func get_recognized_extensions():
    return PoolStringArray(["midstr"])


func get_resource_type(path):
    var ext = path.get_extension().to_lower()
    if ext == "midstr":
        return "MidiFileReader"
    return ""

func handles_type(typename):
    return typename == "MidiFileReader"

func load(path, original_path):
    var f = File.new()

    var err = f.open(path, File.READ)
    if err != OK:
        return err

    var res = MidiFileReader.new()
    var data = f.get_buffer(f.get_len())
    res.set_data(data)
    f.close()

    return res
