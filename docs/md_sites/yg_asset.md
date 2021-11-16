# yg.asset

Functions for loading assets into the asset manager.

## function yg.asset.clear()

Clears and deletes all previously loaded assets.

> `yg.asset.clear()` -> `void`

## function yg.asset.loadTexture()

Loads a texture or texture atlas (sprite sheet).

> `yg.asset.loadTexture(name, imgFilename, atlasFilename, unit, filter, wrapmode, mipmap)` -> `boolean` (`false` on error)

| Argument        | Type    | Info                                                                                |
| --------------- | ------- | ----------------------------------------------------------------------------------- |
| `name`          | string  | Name of the texture to register it in the asset manager                             |
| `imgFilename`   | string  | Filename of the image to load                                                       |
| `atlasFilename` | string  | Filename of the atlas file (.json) to load. May be `""`                             |
| `unit`          | string  | GL texture unit. Options: `"diffuse"`                                               |
| `filter`        | string  | Texture filter mode. Options: `"linear"`, `"nearest"`                               |
| `wrapmode`      | string  | Texture wrap mode.<br />Options: `"repeat"`, `"mirrored_repeat"`, `"clamp_to_edge"` |
| `mipmap`        | boolean | Enable mipmapping. Options: `true`, `false`                                         |

## function yg.asset.loadVertFragShader()

Loads a GL shader program consisting of a vertex and a fragment shader.

> `yg.asset.loadVertFragShader(name, vertFilename, fragFilename)` -> `boolean` (`false` on error)

| Argument       | Type   | Info                                                           |
| -------------- | ------ | -------------------------------------------------------------- |
| `name`         | string | Name of the shader program to register it in the asset manager |
| `vertFilename` | string | Filename of the vertex shader code                             |
| `fragFilename` | string | Filename of the fragment shader code                           |

## function yg.asset.loadGeometry()

Loads a geometry file (.obj) with optional material library (.mtl).

> `yg.asset.loadGeometry(name, objFilename, mtlFilename)` -> `boolean` (`false` on error)

| Argument      | Type   | Info                                                           |
| ------------- | ------ | -------------------------------------------------------------- |
| `name`        | string | Name of the shader program to register it in the asset manager |
| `objFilename` | string | Filename of the geometry file (.obj)                           |
| `mtlFilename` | string | Filename of the material library file (.mtl). May be `""`      |

## function yg.asset.getTexture()

Retrieves a previously loaded Texture from the asset manager.

> `yg.asset.getTexture(name)` -> `Texture` (`nil` on error)

| Argument | Type   | Info                            |
| -------- | ------ | ------------------------------- |
| `name`   | string | Name of the Texture to retrieve |

## function yg.asset.getShader()

Retrieves a previously loaded Shader program from the asset manager.

> `yg.asset.getShader(name)` -> `Shader` (`nil` on error)

| Argument | Type   | Info                                   |
| -------- | ------ | -------------------------------------- |
| `name`   | string | Name of the Shader program to retrieve |

## function yg.asset.getGeometry()

Retrieves a previously loaded Geometry from the asset manager.

> `yg.asset.getGeometry(name)` -> `Geometry` (`nil` on error)

| Argument | Type   | Info                             |
| -------- | ------ | -------------------------------- |
| `name`   | string | Name of the Geometry to retrieve |

## function yg.asset.destroyTexture()

Destroys a Texture and deletes reference from the asset manager.

> `yg.asset.destroyTexture(name)` -> `void`

| Argument | Type   | Info                           |
| -------- | ------ | ------------------------------ |
| `name`   | string | Name of the Texture to destroy |

## function yg.asset.destroyShader()

Destroys a Shader program and deletes reference from the asset manager.

> `yg.asset.destroyShader(name)` -> `void`

| Argument | Type   | Info                                  |
| -------- | ------ | ------------------------------------- |
| `name`   | string | Name of the Shader program to destroy |

## function yg.asset.destroyGeometry()

Destroys a Geometry and deletes reference from the asset manager.

> `yg.asset.destroyGeometry(name)` -> `void`

| Argument | Type   | Info                            |
| -------- | ------ | ------------------------------- |
| `name`   | string | Name of the Geometry to destroy |

## function yg.asset.numOfTexture()

Retrieves the number of Textures currently registered in the asset manager.

> `yg.asset.numOfTexture()` -> `number`

## function yg.asset.numOfShader()

Retrieves the number of Shader programs currently registered in the asset manager.

> `yg.asset.numOfShader()` -> `number`

## function yg.asset.numOfGeometry()

Retrieves the number of Geometries currently registered in the asset manager.

> `yg.asset.numOfGeometry()` -> `number`
