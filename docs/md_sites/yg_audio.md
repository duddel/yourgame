# yg.audio

Functions for audio playback.

## Example

```lua
function init()
    -- Initialize the audio module with:
    --   5 sources
    --   Default number of channels
    --   Default sample rate
    yg.audio.init(5, 0, 0)
    -- Store a file to play it back
    yg.audio.storeFile("a//noise.ogg")
    -- Play the file looped endless and get the source id
    noiseSource = yg.audio.play("a//noise.ogg", true)
end

function tick()
    -- Manipulate the channel gains to simulate a moving object
    -- (assuming 2 channels)
    gains = {1.0, 0.3}
    yg.audio.setChannelGains(noiseSource, gains)
end
```

## function yg.audio.init()

Enables the audio module.

> `yg.audio.init(numSources, numChannels, sampleRate)` -> `number` (0 if successful)

| Argument      | Type   | Info                                                                         |
| ------------- | ------ | ---------------------------------------------------------------------------- |
| `numSources`  | number | Maximum number of audio sources to be mixed during playback [`integer`]      |
| `numChannels` | number | Number of audio playback channels [`integer`]. **set 0 for device default.** |
| `sampleRate`  | number | Sample rate. **Set 0 for device default.**                                   |

## function yg.audio.shutdown()

Shuts down the audio module.

> `yg.audio.shutdown()` -> `void`

## function yg.audio.isInitialized()

Returns `true` if the audio module is initialized, `false` otherwise.

> `yg.audio.isInitialized()` -> `boolean`

## function yg.audio.storeFile()

Loads a sound file (.ogg) and stores it for being played back.

> `yg.audio.storeFile(filename)` -> `number` (0 if successful)

| Argument   | Type   | Info                         |
| ---------- | ------ | ---------------------------- |
| `filename` | string | Name of the ogg file to load |

## function yg.audio.play()

Starts the playback of a previously stored audio file, **if a free source slot is available**. In this case, the index of the source is returned `[0,numSources-1]`. On error, a negative value is returned. The source index can be used to manipulate the playback once it has started (see [yg.audio.stop()](#function-ygaudiostop), [yg.audio.pause()](#function-ygaudiopause), etc.).

> `yg.audio.play(filename, loop)` -> `number` (Audio source index, or < 0 on error)

| Argument   | Type    | Info                                                     |
| ---------- | ------- | -------------------------------------------------------- |
| `filename` | string  | Name of the ogg file to play                             |
| `loop`     | boolean | If `true`, playback loops endless. Plays once otherwise. |

## function yg.audio.stop()

Stops the playback of a source and clears the slot.

> `yg.audio.stop(sourceId)` -> `number` (0 if successful)

| Argument   | Type   | Info                                                                         |
| ---------- | ------ | ---------------------------------------------------------------------------- |
| `sourceId` | number | Index of the source, retrieved from [yg.audio.play()](#function-ygaudioplay) |

## function yg.audio.pause()

Pauses the playback of a source.

> `yg.audio.pause(sourceId, pause)` -> `number` (0 if successful)

| Argument   | Type    | Info                                                                         |
| ---------- | ------- | ---------------------------------------------------------------------------- |
| `sourceId` | number  | Index of the source, retrieved from [yg.audio.play()](#function-ygaudioplay) |
| `pause`    | boolean | If `true`, playback is paused. Options: `true`, `false`                      |

## function yg.audio.setChannelGains()

Sets the channel gains of a source: array of numbers, typically in `[0,1]` to reduce gain on individual channels. The audio signal of each channel gets multiplied by the appropriate gain value.

> `yg.audio.setChannelGains(sourceId, gains)` -> `number` (0 if successful)

| Argument   | Type     | Info                                                                         |
| ---------- | -------- | ---------------------------------------------------------------------------- |
| `sourceId` | number   | Index of the source, retrieved from [yg.audio.play()](#function-ygaudioplay) |
| `gains`    | {number} | Gain values in `[0,1]` for each channel (array of number)                    |
