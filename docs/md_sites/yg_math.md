# yg.math

Classes for math.

## class yg.math.Trafo

Represents a 3-dimensional homogeneous transform.

### function yg.math.Trafo.rotateLocal()

Rotates the transform around **local axis** `ax` by `angle` radians.

> `yg.math.Trafo.rotateLocal(angle, ax)` -> `void`

| Argument | Type   | Info                                              |
| -------- | ------ | ------------------------------------------------- |
| `angle`  | number | Radians to rotate                                 |
| `ax`     | string | Local rotation axis. Options: `"X"`, `"Y"`, `"Z"` |

### function yg.math.Trafo.rotateGlobal()

Rotates the transform around **global axis** `ax` by `angle` radians.

> `yg.math.Trafo.rotateGlobal(angle, ax)` -> `void`

| Argument | Type   | Info                                               |
| -------- | ------ | -------------------------------------------------- |
| `angle`  | number | Radians to rotate                                  |
| `ax`     | string | Global rotation axis. Options: `"X"`, `"Y"`, `"Z"` |


### function yg.math.Trafo.translateLocal()

Translates the transform by **local vector** `trans`.

> `yg.math.Trafo.translateLocal(trans)` -> `void`

| Argument | Type     | Info                                          |
| -------- | -------- | --------------------------------------------- |
| `trans`  | {number} | Local translation vector (array of 3 numbers) |

### function yg.math.Trafo.translateGlobal()

Translates the transform by **global vector** `trans`.

> `yg.math.Trafo.translateGlobal(trans)` -> `void`

| Argument | Type     | Info                                           |
| -------- | -------- | ---------------------------------------------- |
| `trans`  | {number} | Global translation vector (array of 3 numbers) |

### function yg.math.Trafo.setScaleLocal()

Sets the (local) scale of the transform to `scale` (array of 3 numbers), {x,y,z}-component.

> `yg.math.Trafo.setScaleLocal(scale)` -> `void`

| Argument | Type     | Info                              |
| -------- | -------- | --------------------------------- |
| `scale`  | {number} | Scale to set (array of 3 numbers) |


### function yg.math.Trafo.setRotation()

Sets the rotation of the transform from a quaternion.

> `yg.math.Trafo.setRotation(rot)` -> `void`

| Argument | Type     | Info                                                 |
| -------- | -------- | ---------------------------------------------------- |
| `rot`    | {number} | Quaternion to set rotation from (array of 4 numbers) |

### function yg.math.Trafo.setTranslation()

Sets the translation of the transform.

> `yg.math.Trafo.setTranslation(trans)` -> `void`

| Argument | Type     | Info                                                |
| -------- | -------- | --------------------------------------------------- |
| `trans`  | {number} | Vector to set translation from (array of 3 numbers) |

### function yg.math.Trafo.pointTo()

Points the **positive Z axis (Z+)** of the transform to `center` point, with transform origin `eye`, respecting up vector `up`.

> `yg.math.Trafo.pointTo(eye, center, up)` -> `void`

| Argument | Type     | Info                                     |
| -------- | -------- | ---------------------------------------- |
| `eye`    | {number} | Eye (origin) vector (array of 3 numbers) |
| `center` | {number} | Center vector (array of 3 numbers)       |
| `up`     | {number} | Up vector (array of 3 numbers)           |

### function yg.math.Trafo.lookAt()

Points the **negative Z axis (Z-)** of the transform to `center` point, with transform origin `eye`, respecting up vector `up`. Typically used to create an [extrinsic camera matrix](#function-ygmathcameratrafo) to generate a view matrix during rendering.

> `yg.math.Trafo.lookAt(eye, center, up)` -> `void`

| Argument | Type     | Info                                     |
| -------- | -------- | ---------------------------------------- |
| `eye`    | {number} | Eye (origin) vector (array of 3 numbers) |
| `center` | {number} | Center vector (array of 3 numbers)       |
| `up`     | {number} | Up vector (array of 3 numbers)           |

### function yg.math.Trafo.lerp()

Performs linear interpolation of this transform to `target` transform by using interpolation factor `t` in [0,1].

> `yg.math.Trafo.lerp(t, target, dst)` -> `void`

| Argument | Type                                | Info                               |
| -------- | ----------------------------------- | ---------------------------------- |
| `t`      | number                              | Interpolation factor in [0,1]      |
| `target` | [yg.math.Trafo](#class-ygmathtrafo) | Target transform to interpolate to |
| `dst`    | [yg.math.Trafo](#class-ygmathtrafo) | Destination (output) transform     |

### function yg.math.Trafo.setIdentity()

Resets the transform. Resulting matrix is identity.

> `yg.math.Trafo.setIdentity()` -> `void`

### function yg.math.Trafo.getAxisLocal(ax)

Returns a **local axis** of the transform (array of 3 numbers), expressed in world system. TODO: this function is not wrapped to accept STRINGS. Does it even work?

> `yg.math.Trafo.getAxisLocal(ax)` -> `{number}`

| Argument | Type   | Info                                       |
| -------- | ------ | ------------------------------------------ |
| `ax`     | string | Desired axis. Options: `"X"`, `"Y"`, `"Z"` |

### function yg.math.Trafo.getAxisGlobal(ax)

Returns a **global axis** of the transform (array of 3 numbers).

-   `"X"` -> {1, 0, 0}
-   `"Y"` -> {0, 1, 0}
-   `"Z"` -> {0, 0, 1}

TODO: this function is not wrapped to accept STRINGS. Does it even work?

> `yg.math.Trafo.getAxisGlobal(ax)` -> `{number}`

| Argument | Type   | Info                                       |
| -------- | ------ | ------------------------------------------ |
| `ax`     | string | Desired axis. Options: `"X"`, `"Y"`, `"Z"` |

### function yg.math.Trafo.getEye()

Returns the eye (origin) of the transform (array of 3 numbers).

> `yg.math.Trafo.getEye()` -> `{number}`

### function yg.math.Trafo.getRotation()

Returns the rotation of the transform as a quaternion (array of 4 numbers).

> `yg.math.Trafo.getRotation()` -> `{number}`

### function yg.math.Trafo.getScale()

Returns the scale of the transform (array of 3 numbers).

> `yg.math.Trafo.getScale()` -> `{number}`

## class yg.math.Camera

Represents a camera with extrinsics (pose in world) and intrinsics (projection) in 3-dimensional space.

### function yg.math.Camera.setPerspective()

Sets the camera to `PERSPECTIVE` projection mode.

> `yg.math.Camera.setPerspective(fovy, aspect, zNear, zFar)` -> `void`

| Argument | Type   | Info                                 |
| -------- | ------ | ------------------------------------ |
| `fovy`   | number | Vertical (Y) field of view [degrees] |
| `aspect` | number | Aspect ratio (width/height = X/Y)    |
| `zNear`  | number | Distance of near clipping plane      |
| `zFar`   | number | Distance of far clipping plane       |

### function yg.math.Camera.setOrthographic()

Sets the camera to `ORTHOGRAPHIC` projection mode.

> `yg.math.Camera.setOrthographic(height, aspect, zNear, zFar)` -> `void`

| Argument | Type   | Info                              |
| -------- | ------ | --------------------------------- |
| `height` | number | Height of the view cuboid         |
| `aspect` | number | Aspect ratio (width/height = X/Y) |
| `zNear`  | number | Distance of near clipping plane   |
| `zFar`   | number | Distance of far clipping plane    |

### function yg.math.Camera.setFovy()

Sets the vertical (Y) field of view. Always set but only valid during `PERSPECTIVE` projection mode.

> `yg.math.Camera.setFovy(fovy)` -> `void`

| Argument | Type   | Info                                 |
| -------- | ------ | ------------------------------------ |
| `fovy`   | number | Vertical (Y) field of view [degrees] |

### function yg.math.Camera.setHeight()

Sets the height of the view cuboid. Always set but only valid during `ORTHOGRAPHIC` projection mode.

> `yg.math.Camera.setHeight(height)` -> `void`

| Argument | Type   | Info                      |
| -------- | ------ | ------------------------- |
| `height` | number | Height of the view cuboid |

### function yg.math.Camera.setAspect()

Sets the projection aspect ratio. Valid for both `PERSPECTIVE` and `ORTHOGRAPHIC` projection modes.

> `yg.math.Camera.setAspect(aspect)` -> `void`

| Argument | Type   | Info                              |
| -------- | ------ | --------------------------------- |
| `aspect` | number | Aspect ratio (width/height = X/Y) |

### function yg.math.Camera.setZNear()

Sets the distance of the near clipping plane. Valid for both `PERSPECTIVE` and `ORTHOGRAPHIC` projection modes.

> `yg.math.Camera.setZNear(zNear)` -> `void`

| Argument | Type   | Info                            |
| -------- | ------ | ------------------------------- |
| `zNear`  | number | Distance of near clipping plane |

### function yg.math.Camera.setZFar()

Sets the distance of the far clipping plane. Valid for both `PERSPECTIVE` and `ORTHOGRAPHIC` projection modes.

> `yg.math.Camera.setZFar(zFar)` -> `void`

| Argument | Type   | Info                           |
| -------- | ------ | ------------------------------ |
| `zFar`   | number | Distance of far clipping plane |

### function yg.math.Camera.trafo()

Returns (a reference to) the transform of the camera (extrinsics).

> `yg.math.Camera.trafo()` -> [`yg.math.Trafo`](#class-ygmathtrafo)

### function yg.math.Camera.castRay()

Casts a ray into the scene through viewport coordinates and returns it as an array of 6 numbers, representing the origin and direction of the ray: `{org.x, org.y, org.z, dir.x, dir.y, dir.z}`.

> `yg.math.Camera.castRay(viewportX, viewportY)` -> `{number}`

| Argument    | Type   | Info                                                      |
| ----------- | ------ | --------------------------------------------------------- |
| `viewportX` | number | X-component of viewport coordinates to cast a ray through |
| `viewportY` | number | Y-component of viewport coordinates to cast a ray through |
