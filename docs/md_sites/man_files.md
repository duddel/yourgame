# Load Files

Whenever a function takes a filename argument to load a file, `a//` has to be prepended to the actual filename to load it from `assets/`.

**Example:** `"a//sprites.png"`

This is done to distinguish other directories to load from, that might be used in the future.

## Supported Asset File Formats

| Usage         | Supported Formats        | Note                                                                                         |
| ------------- | ------------------------ | -------------------------------------------------------------------------------------------- |
| Code          | **`.lua`**               | The main script (entry point) must be called `main.lua`                                      |
| Texture       | **`.png`**, **`.jpg`**   | Image formats to load with [yg.asset.loadTexture()](yg_asset.md#function-ygassetloadtexture) |
| Texture Atlas | **`.json`**              | See [Texture Atlases (Sprite Sheets)](#texture-atlases-sprite-sheets)                        |
| Audio         | **`.ogg`**               | Audio format to load with [yg.audio.storeFile()](yg_audio.md#function-ygaudiostorefile)      |
| 3D Model      | **`.obj`**               | See [3D Models and Materials](#3d-models-and-materials)                                      |
| Material      | **`.mtl`**               | See [3D Models and Materials](#3d-models-and-materials)                                      |
| GLSL Shaders  | **`.vert`**, **`.frag`** | Naming convention. See [GLSL Shaders](#glsl-shaders)                                         |
