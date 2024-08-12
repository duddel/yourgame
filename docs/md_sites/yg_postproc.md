# yg.postproc

Functions for GL post processing.

## function yg.postproc.init()

Initializes the frame buffer for post processing.

-   If both `width` and `height` are `> 0`, this will be the frame buffer size
-   If both `width` and `height` are `0`, the frame buffer size will be synced to the window size
-   If exactly one of `width` and `height` is `0`, this dimensions will be set suitable, maintaining the windows aspect ratio

> `yg.postproc.init(width, height)` -> `void`

| Argument | Type   | Info                                                          |
| -------- | ------ | ------------------------------------------------------------- |
| `width`  | number | Width of the frame buffer. If `0`, will be set automatically  |
| `height` | number | Height of the frame buffer. If `0`, will be set automatically |

## function yg.postproc.shutdown()

Shuts down the post processing frame buffer.

> `yg.postproc.shutdown()` -> `void`

## function yg.postproc.isInitialized()

Returns `true` if post processing is initialized, `false` otherwise.

> `yg.postproc.isInitialized()` -> `boolean`

## function yg.postproc.resize()

Resizes the post processing frame buffer. See [yg.postproc.init()](#function-ygpostprocinit)

> `yg.postproc.resize(width, height)` -> `void`

| Argument | Type   | Info                                                          |
| -------- | ------ | ------------------------------------------------------------- |
| `width`  | number | Width of the frame buffer. If `0`, will be set automatically  |
| `height` | number | Height of the frame buffer. If `0`, will be set automatically |

## function yg.postproc.use()

Sets the post processing shader to use.

> `yg.postproc.use(shader)` -> `void`

| Argument | Type                                      | Info                                                    |
| -------- | ----------------------------------------- | ------------------------------------------------------- |
| `shader` | [yg.gl.Shader](yg_gl.md#class-ygglshader) | Post processing shader to use. `nil` for neutral shader |
