tool
class_name SoundFontDataSaver
extends ResourceFormatSaver

const SoundFontFileReader = preload("res://bin/soundfont_file_reader.gdns")

func get_recognized_extensions(res):
	if res.has_method("get_extension"):
		return PoolStringArray([res.get_extension()])
	else:
		return PoolStringArray()

func recognize(res):
	return res.has_method("get_extension")

func save(path, resource, flags):
	var f = File.new()

	var err = f.open(path, File.WRITE)
	if err != OK:
		return err

	f.store_buffer(resource.get_data())
	f.close()
