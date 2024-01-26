# yg.gl

Functions and classes for GL drawing.

## function yg.gl.draw()

Performs a GL draw call.

> `yg.gl.draw(geo, light, shader, texture, camera, trafo)` -> `void`

| Argument  | Type                                            | Info                                      |
| --------- | ----------------------------------------------- | ----------------------------------------- |
| `geo`     | [yg.gl.Geometry](#class-ygglgeometry)           | Geometry to draw                          |
| `light`   | [yg.gl.Lightsource](#class-yggllightsource)     | Lightsource to apply. May be `nil`        |
| `shader`  | [yg.gl.Shader](#class-ygglshader)               | Shader to use                             |
| `texture` | [yg.gl.Texture](#class-yggltexture)             | Texture to use. May be `nil`              |
| `camera`  | [yg.math.Camera](yg_math.md#class-ygmathcamera) | Camera to use. May be `nil`               |
| `trafo`   | [yg.math.Trafo](yg_math.md#class-ygmathtrafo)   | Trafo to use as model trafo. May be `nil` |

## function yg.gl.drawSprite()

Draws a 2D sprite in screen space. Screen origin (`x=0, y=0`) in upper left corner.

Returns an array of 4 numbers (`xmin, xmax, ymin, ymax`) denoting the screen space axis aligned bounding box (AABB), the sprite is drawn in, **as if it was not rotated**.

The `coords` argument must be retrieved from `texture` to get valid coordinate information for a sprite from an atlas or grid texture. To draw an entire texture, [yg.gl.Texture.getGridCoords(1, 1, 0)](#function-yggltexturegetgridcoords) can be used. See example:

```lua
-- Example for yg.gl.drawSprite()
function init()
    yg.asset.loadTexture("demo", "a//demo.png", "",
                         "DIFFUSE", "LINEAR", "REPEAT", true)
    -- Get coords for the entire texture, to draw it with drawSprite()
    coordsDemo = yg.asset.getTexture("demo"):getGridCoords(1, 1, 0)
end

function tick()
    -- Use screenPos to detect clicks or collisions
    screenPos = yg.gl.drawSprite(yg.asset.getTexture("demo"),
                                 coordsDemo, 400, 300, 250, 0, 0)
end
```
> `yg.gl.drawSprite(texture, coords, x, y, width, height, angle)` -> `{number}`

| Argument  | Type                                            | Info                                                                                |
| --------- | ----------------------------------------------- | ----------------------------------------------------------------------------------- |
| `texture` | [yg.gl.Texture](#class-yggltexture)             | Texture to draw from                                                                |
| `coords`  | [yg.gl.TextureCoords](#class-yggltexturecoords) | Subtexture coordinate info to pick sprite from atlas/grid                           |
| `x`       | number                                          | X-position (**center of sprite**)                                                   |
| `y`       | number                                          | Y-position (**center of sprite**)                                                   |
| `width`   | number                                          | Width of sprite [pixels]. If `0.0`, width is determined from original sprite size   |
| `height`  | number                                          | Height of sprite [pixels]. If `0.0`, height is determined from original sprite size |
| `angle`   | number                                          | Counter-clockwise rotation of sprite [rad]                                          |

## function yg.gl.drawSky()

Draws sky from image texture.

> `yg.gl.drawSky(texture, camera, tint)` -> `void`

| Argument  | Type                                            | Info                                                                                        |
| --------- | ----------------------------------------------- | ------------------------------------------------------------------------------------------- |
| `texture` | [yg.gl.Texture](#class-yggltexture)             | Sky texture                                                                                 |
| `camera`  | [yg.math.Camera](yg_math.md#class-ygmathcamera) | Camera to use                                                                               |
| `tint`    | {number}                                        | Tint, ends up as ambient color in shader. Default (neutral): `{1,1,1}` (array of 3 numbers) |


## function yg.gl.drawSky2()

Draws sky from image texture, advanced.

> `yg.gl.drawSky2(texture, camera, tint, shader, trafo)` -> `void`

| Argument  | Type                                            | Info                                                                                        |
| --------- | ----------------------------------------------- | ------------------------------------------------------------------------------------------- |
| `texture` | [yg.gl.Texture](#class-yggltexture)             | Sky texture                                                                                 |
| `camera`  | [yg.math.Camera](yg_math.md#class-ygmathcamera) | Camera to use                                                                               |
| `tint`    | {number}                                        | Tint, ends up as ambient color in shader. Default (neutral): `{1,1,1}` (array of 3 numbers) |
| `shader`  | [yg.gl.Shader](#class-ygglshader)               | Shader to use. May be `nil` (for default sky shader)                                        |
| `trafo`   | [yg.math.Trafo](yg_math.md#class-ygmathtrafo)   | Rotation of `trafo` is applied to sky. May be `nil`                                         |

## function yg.gl.depthTest()

Enables/disables depth test via `glEnable(GL_DEPTH_TEST)` / `glDisable(GL_DEPTH_TEST)`.

> `yg.gl.depthTest(enable)` -> `void`

| Argument | Type    | Info                                      |
| -------- | ------- | ----------------------------------------- |
| `enable` | boolean | Options: `true`: enable, `false`: disable |

## function yg.gl.clearColor()

Sets the clear color via `glClearColor()`.

> `yg.gl.clearColor(r, g, b, a)` -> `void`

| Argument | Type   | Info  |
| -------- | ------ | ----- |
| `r`      | number | Red   |
| `g`      | number | Green |
| `b`      | number | Blue  |
| `a`      | number | Alpha |

## class yg.gl.Texture

### function yg.gl.Texture.getCoords()

Returns coordinate information of a sprite called `name`. Typically used with textures loaded together with an atlas file, see [yg.asset.loadTexture()](yg_asset.md#function-ygassetloadtexture). See also [Accessing Sprites and Sequences](Manual.md#accessing-sprites-and-sequences) in the Manual.

> `yg.gl.Texture.getCoords(name)` -> [`yg.gl.TextureCoords`](#class-yggltexturecoords)

| Argument | Type   | Info               |
| -------- | ------ | ------------------ |
| `name`   | string | Name of the sprite |

### function yg.gl.Texture.getFrameCoords()

Returns coordinate information of a sprite which is a frame of a sequence. `frame` is always wrapped into valid range and may be negative. Typically used with textures loaded together with an atlas file, see [yg.asset.loadTexture()](yg_asset.md#function-ygassetloadtexture). See also [Accessing Sprites and Sequences](Manual.md#accessing-sprites-and-sequences) in the Manual.

> `yg.gl.Texture.getFrameCoords(sequenceName, frame)` -> [`yg.gl.TextureCoords`](#class-yggltexturecoords)

| Argument       | Type   | Info                        |
| -------------- | ------ | --------------------------- |
| `sequenceName` | string | Name of the sprite sequence |
| `frame`        | number | Frame index                 |

### function yg.gl.Texture.getGridCoords()

Returns texture coordinates of a grid cell. Any grid size can be used for any texture. To get coordinates for the entire texture, call `yg.gl.Texture.getGridCoords(1, 1, 0)`. 

> `yg.gl.Texture.getGridCoords(gridWidth, gridHeight, index)` -> [`yg.gl.TextureCoords`](#class-yggltexturecoords)

| Argument     | Type   | Info                                                                               |
| ------------ | ------ | ---------------------------------------------------------------------------------- |
| `gridWidth`  | number | Number of grid columns                                                             |
| `gridHeight` | number | Number of grid rows                                                                |
| `index`      | number | Index of the grid cell to return coordinates for, starting top-left with index `0` |

## class yg.gl.Lightsource

Represents a lightsource.

### constructor

> `yg.gl.Lightsource()` -> [`yg.gl.Lightsource`](#class-yggllightsource)

### function yg.gl.lightsource.setAmbient()

Sets ambient light component.

> `yg.gl.lightsource.setAmbient(r, g, b)` -> `void`

| Argument | Type   | Info                  |
| -------- | ------ | --------------------- |
| `r`      | number | Red light component   |
| `g`      | number | Green light component |
| `b`      | number | Blue light component  |

### function yg.gl.lightsource.setDiffuse()

Sets diffuse light component.

> `yg.gl.lightsource.setDiffuse(r, g, b)` -> `void`

| Argument | Type   | Info                  |
| -------- | ------ | --------------------- |
| `r`      | number | Red light component   |
| `g`      | number | Green light component |
| `b`      | number | Blue light component  |

### function yg.gl.lightsource.setSpecular()

Sets specular light component.

> `yg.gl.lightsource.setSpecular(r, g, b)` -> `void`

| Argument | Type   | Info                  |
| -------- | ------ | --------------------- |
| `r`      | number | Red light component   |
| `g`      | number | Green light component |
| `b`      | number | Blue light component  |

### function yg.gl.lightsource.setPosition()

Sets light origin in world.

> `yg.gl.lightsource.setPosition(r, g, b)` -> `void`

| Argument | Type   | Info         |
| -------- | ------ | ------------ |
| `x`      | number | X coordinate |
| `y`      | number | Y coordinate |
| `z`      | number | Z coordinate |

## class yg.gl.Geometry

No functionality accessible. Used to pass around instances, like from [yg.asset.getGeometry()](yg_asset.md#function-ygassetgetgeometry) to [yg.gl.draw()](#function-yggldraw).

## class yg.gl.Shader

No functionality accessible. Used to pass around instances, like from [yg.asset.getShader()](yg_asset.md#function-ygassetgetshader) to [yg.gl.draw()](#function-yggldraw).

## class yg.gl.TextureCoords

No functionality accessible. Used to pass around instances, like from [yg.gl.Texture.getCoords()](#function-yggltexturegetcoords) to [yg.gl.drawSprite()](#function-yggldrawsprite).
