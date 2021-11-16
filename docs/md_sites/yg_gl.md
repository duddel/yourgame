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

## function yg.gl.gl_drawSprite()

tbc...

## class yg.gl.Geometry

## class yg.gl.Shader

## class yg.gl.Texture

## class yg.gl.Lightsource

Represents a lightsource.

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
