# yg.audio

Functions for audio playback.

## function yg.audio.storeFile()

Loads a sound file (.ogg) and stores it for being played back.

> `yg.audio.storeFile(filename)` -> `number` (Status code 0 if successful)

| Argument   | Type   | Info                         |
| ---------- | ------ | ---------------------------- |
| `filename` | string | Name of the ogg file to load |

## function yg.audio.play()

Starts the playback of a previously stored audio file.

> `src_idx = yg.audio.play(filename, loop)` -> `number` (Audio source index)

| Argument   | Type    | Info                                     |
| ---------- | ------- | ---------------------------------------- |
| `filename` | string  | Name of the ogg file to play             |
| `loop`     | boolean | If true, playback loops. Once otherwise. |
