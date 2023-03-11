# Manual

## Loading Files

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

## Texture Atlases (Sprite Sheets)

Packed texture atlases created with the tool `Free Texture Packer` (`FTP`) are supported and can be loaded with [yg.asset.loadTexture()](yg_asset.md#function-ygassetloadtexture).

Tested with **Free Texture Packer v0.6.7**.

The following `FTP` settings are required. The rest can be set to users taste.

-   Format: `JSON (hash)` or `JSON (array)`
-   Allow rotation: `No`
-   Allow trim: `No`
-   Padding: `>= 2` (recommended)

### Accessing Sprites and Sequences

To draw a sprite from a texture atlas, the draw function must know where to find the desired sprite in the texture. The following functions can be used on a [yg.gl.Texture](yg_gl.md#class-yggltexture) to retrieve these coordinate information.

-   [yg.gl.Texture.getCoords()](yg_gl.md#function-yggltexturegetcoords): get coordinates  for a sprite that has been listed in the atlas file (`.json`) by it's **name**. This is always possible, even if the sprite is part of a sequence
-   [yg.gl.Texture.getFrameCoords()](yg_gl.md#function-yggltexturegetframecoords): get coordinates from a frame index of a **sequence**

During texture loading, sequences are detected if the sprite names have indexes at the end, separated with `-` or `_`.

**Examples:**

-   `walking_01` -> sequence `walking` detected, [yg.gl.Texture.getFrameCoords()](yg_gl.md#function-yggltexturegetframecoords) can be used
-   `walking-01` -> sequence `walking` detected, [yg.gl.Texture.getFrameCoords()](yg_gl.md#function-yggltexturegetframecoords) can be used
-   `walking01` -> no sequence detected, only [yg.gl.Texture.getCoords()](yg_gl.md#function-yggltexturegetcoords) can be used

## Sky Images

> **Drawing Sky is not yet supported.**

To draw sky in the scene, an image with **equirectangular projection** (aspect ratio 2:1) is used. These are images that typically 360-degree cameras generate.

ToDo: Photo example

ToDo: Gradient/Horizon example

ToDo: Sprite example

This tool can be used to produce compatible sky images from 2D sprites:

<iframe frameborder="0" src="https://itch.io/embed/1120244?bg_color=465360&amp;fg_color=ffffff&amp;link_color=d6e5f5&amp;border_color=515c68" width="552" height="167"><a href="https://didaduddel.itch.io/skytool">Skybox Composing Tool by didaduddel</a></iframe>

## 3D Models and Materials

### Object (.obj) and Material (.mtl) Support

3D models in `.obj` format can be loaded by `yourgame`, optionally together with a material template library `.mtl`.

This is what `yourgame` does:

-   Normals remain unchanged, preserving edges and smooth areas
    -   Note for `Blender`: the options `Shade Smooth` and `Shade Flat` have an impact on the exported `.obj` data
-   The diffuse color `Kd` from materials (`.mtl`) is attached to the `.obj` data during import and provided as `Color` input to the vertex shader
    -   This way, `Vertex Color Shading` can be performed
    -   See [GLSL Shaders](#glsl-shaders) on how to use vertex color in Shaders

### Create with Blender

Geometry can be created and exported with `Blender`, in `.obj` format with limited Material (`.mtl`) support.

Tested with **Blender v3.4.1**.

Here is a basic workflow, some `Blender` knowledge is required.

![blender_001.png](blender_001.png)

Select all desired meshes and export them with the `Wavefront (.obj)` exporter using the recommended settings below.

-   Limit to: Selected Only
-   Forward Axis: `-Z` (maps Blender's Forward axis **Y** to the typical GL Forward **-Z**)
-   Up Axis: `Y` (maps Blender's Up axis **Z** to the typical GL Up **Y**)
-   Objects: Apply Modifiers
-   Geometry: Export `UV Coordinates`, `Normals` and make the Mesh `Triangulated`
-   Materials: Export

![blender_001.png](blender_003.png)

The generic `Principled BSDF` shader has an impact on the exported materials in the `.mtl` file. If you want to use it, apply this shader to your meshes.

-   Principled BSDF `Base Color` is exported as `Kd` (diffuse color) into the materials (`.mtl`) 
    -   The `Base Color` in the example shader below causes this `Kd` entry in the exported material: `Kd 0.102684 0.235477 1.000000`

See [Object (.obj) and Material (.mtl) support](#object-obj-and-material-mtl-support) on how this information can be used in `yourgame`.

![blender_001.png](blender_002.png)

### Other Tools and 3D Assets

Of course, other 3D tools can be used to generate `yourgame` compatible data. Also, some `.obj` based 3D game assets, made by `Kenney`, can be imported directly without modification.

## GLSL Shaders

### Attributes Conventions

| Usage     | Type | Location | GLSL Vertex Shader Code                     |
| --------- | ---- | -------- | ------------------------------------------- |
| Position  | vec3 | **0**    | `layout(location = 0) in vec3 inPosition;`  |
| Normal    | vec3 | **1**    | `layout(location = 1) in vec3 inNormal;`    |
| Texcoords | vec2 | **2**    | `layout(location = 2) in vec2 inTexcoords;` |
| Color     | vec3 | **3**    | `layout(location = 3) in vec3 inColor;`     |

### Uniforms Conventions

| Usage                  | Type        | Name                 | GLSL Shader Code                      |
| ---------------------- | ----------- | -------------------- | ------------------------------------- |
| MVP Matrix             | mat4        | **`mvpMat`**         | `uniform mat4        mvpMat;`         |
| VP Matrix              | mat4        | **`vpMat`**          | `uniform mat4        vpMat;`          |
| Model Matrix           | mat4        | **`modelMat`**       | `uniform mat4        modelMat;`       |
| Normal Matrix          | mat3        | **`normalMat`**      | `uniform mat3        normalMat;`      |
| Camera Position        | vec3        | **`camPos`**         | `uniform vec3        camPos;`         |
| Camera Trafo           | mat4        | **`camTrafo`**       | `uniform mat4        camTrafo;`       |
| Sky Rotation Inverse   | mat3        | **`skyRotInv`**      | `uniform mat3        skyRotInv;`      |
| Texture Diffuse        | sampler2D   | **`textureDiffuse`** | `uniform sampler2D   textureDiffuse;` |
| Texture Sky            | samplerCube | **`textureSky`**     | `uniform samplerCube textureSky;`     |
| Light Ambient          | vec3        | **`lightAmbient`**   | `uniform vec3        lightAmbient;`   |
| Light Diffuse          | vec3        | **`lightDiffuse`**   | `uniform vec3        lightDiffuse;`   |
| Light Specular         | vec3        | **`lightSpecular`**  | `uniform vec3        lightSpecular;`  |
| Light Position         | vec3        | **`lightPosition`**  | `uniform vec3        lightPosition;`  |
| Subtexture Coordinates | vec4        | **`subtex`**         | `uniform vec4        subtex;`         |
