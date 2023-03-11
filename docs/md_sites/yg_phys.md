# yg.phys

Classes for 3-dimensional physics. With Bullet physics library under the hood.

## class yg.phys.PhysEnv

Represents a physics environment. An instance of this class is mandatory to realize a physics simulation.

### constructor

> `yg.phys.PhysEnv()` -> [`yg.phys.PhysEnv`](#class-ygphysphysenv)

### function yg.phys.PhysEnv.setGravity()

Sets the gravity vector of the Physics Environment.

> `yg.phys.PhysEnv.setGravity(x, y, z)` -> `void`

| Argument | Type   | Info                                      |
| -------- | ------ | ----------------------------------------- |
| `x`      | number | X-component of the gravity vector [m/s^2] |
| `y`      | number | Y-component of the gravity vector [m/s^2] |
| `z`      | number | Z-component of the gravity vector [m/s^2] |

### function yg.phys.PhysEnv.newBoxShape()

Creates and stores a new Box Shape in the Physics Environment.

> `yg.phys.PhysEnv.newBoxShape(name, halfX, halfY, halfZ)` -> `boolean` (`true` on success, `false` otherwise)

| Argument | Type   | Info                            |
| -------- | ------ | ------------------------------- |
| `name`   | string | Name of the new Shape           |
| `halfX`  | number | Half extends in X-dimension [m] |
| `halfY`  | number | Half extends in Y-dimension [m] |
| `halfZ`  | number | Half extends in Z-dimension [m] |

### function yg.phys.PhysEnv.newSphereShape()

Creates and stores a new Sphere Shape in the Physics Environment.

> `yg.phys.PhysEnv.newSphereShape(name, radius)` -> `boolean` (`true` on success, `false` otherwise)

| Argument | Type   | Info                  |
| -------- | ------ | --------------------- |
| `name`   | string | Name of the new Shape |
| `radius` | number | Radius [m]            |

### function yg.phys.PhysEnv.newCylinderShape()

Creates and stores a new Cylinder Shape in the Physics Environment.

> `yg.phys.PhysEnv.newCylinderShape(name, radius, height)` -> `boolean` (`true` on success, `false` otherwise)

| Argument | Type   | Info                  |
| -------- | ------ | --------------------- |
| `name`   | string | Name of the new Shape |
| `radius` | number | Radius [m]            |
| `height` | number | Height [m]            |

### function yg.phys.PhysEnv.newConeShape()

Creates and stores a new Cone Shape in the Physics Environment.

> `yg.phys.PhysEnv.newConeShape(name, radius, height)` -> `boolean` (`true` on success, `false` otherwise)

| Argument | Type   | Info                  |
| -------- | ------ | --------------------- |
| `name`   | string | Name of the new Shape |
| `radius` | number | Radius [m]            |
| `height` | number | Height [m]            |

### function yg.phys.PhysEnv.deleteShape()

Deletes the Shape with name `name` from the Physics Environment, if present.

> `yg.phys.PhysEnv.deleteShape(name)` -> `boolean` (`true` on success, `false` otherwise)

| Argument | Type   | Info                        |
| -------- | ------ | --------------------------- |
| `name`   | string | Name of the Shape to delete |

### function yg.phys.PhysEnv.clearShapes()

Deletes all Shapes from the Physics Environment.

> `yg.phys.PhysEnv.clearShapes()` -> `number` (Number of Shapes that have been deleted)

### function yg.phys.PhysEnv.numShapes()

Returns the number of Shapes contained in the Physics Environment.

> `yg.phys.PhysEnv.numShapes()` -> `number`

### function yg.phys.PhysEnv.newRigidBody()

Creates and stores a new Rigid Body in the Physics Environment.

> `yg.phys.PhysEnv.newRigidBody(name, shapeName, trafo, info)` -> `boolean` (`true` on success, `false` otherwise)

| Argument    | Type                                                | Info                       |
| ----------- | --------------------------------------------------- | -------------------------- |
| `name`      | string                                              | Name of the new Rigid Body |
| `shapeName` | string                                              | Name of the Shape to apply |
| `trafo`     | [yg.math.Trafo](yg_math.md#class-ygmathtrafo)       | Initial pose               |
| `info`      | [yg.phys.RigidBodyInfo](#class-ygphysrigidbodyinfo) | Rigid Body Info            |

### function yg.phys.PhysEnv.deleteRigidBody()

Deletes the Rigid Body with name `name` from the Physics Environment, if present.

> `yg.phys.PhysEnv.deleteRigidBody(name)` -> `boolean` (`true` on success, `false` otherwise)

| Argument | Type   | Info                             |
| -------- | ------ | -------------------------------- |
| `name`   | string | Name of the Rigid Body to delete |

### function yg.phys.PhysEnv.clearRigidBodies()

Deletes all Rigid Bodies from the Physics Environment.

> `yg.phys.PhysEnv.clearRigidBodies()` -> `number` (Number of Rigid Bodies that have been deleted)

### function yg.phys.PhysEnv.numRigidBodies()

Returns the number of Rigid Bodies contained in the Physics Environment.

> `yg.phys.PhysEnv.numRigidBodies()` -> `number`

### function yg.phys.PhysEnv.getRigidBody()

Returns the Rigid Body with name `name`, if present. Returns `nil` otherwise.

> `yg.phys.PhysEnv.getRigidBody(name)` -> [`yg.phys.RigidBody`](#class-ygphysrigidbody) (may return nil)

| Argument | Type   | Info                          |
| -------- | ------ | ----------------------------- |
| `name`   | string | Name of the Rigid Body to get |

### function yg.phys.PhysEnv.getRigidBodiesStartingWith()

Returns an array of Rigid Bodies with names starting with `name`.

> `yg.phys.PhysEnv.getRigidBodiesStartingWith(name)` -> {[`yg.phys.RigidBody`](#class-ygphysrigidbody)} (may return empty array)

| Argument | Type   | Info                                   |
| -------- | ------ | -------------------------------------- |
| `name`   | string | Name prefix of the Rigid Bodies to get |

### function yg.phys.PhysEnv.tick()

Advances (ticks) the Physics Environment by a given time delta.

> `yg.phys.PhysEnv.tick(dt)` -> `void`

| Argument | Type   | Info                 |
| -------- | ------ | -------------------- |
| `dt`     | number | Time delta [seconds] |

### function yg.phys.PhysEnv.getCollisions()

Returns an array of Collision information that happened since last frame.

> `yg.phys.PhysEnv.getCollisions()` -> {[`yg.phys.Collision`](#class-ygphyscollision)} (may return empty array)

### function yg.phys.PhysEnv.rayTest()

Casts a ray and tests its collision in the scene.

> `yg.phys.PhysEnv.rayTest(eyeX, eyeY, eyeZ, targetX, targetY, targetZ)` -> [`yg.phys.RayTestResult`](#class-ygphysraytestresult)

| Argument  | Type   | Info                         |
| --------- | ------ | ---------------------------- |
| `eyeX`    | number | X-coordinate of ray origin   |
| `eyeY`    | number | Y-coordinate of ray origin   |
| `eyeZ`    | number | Z-coordinate of ray origin   |
| `targetX` | number | X-coordinate of target point |
| `targetY` | number | Y-coordinate of target point |
| `targetZ` | number | Z-coordinate of target point |

## class yg.phys.RigidBodyInfo

Represents a Rigid Body Info structure to be used for Rigid Body creation, via [`yg.phys.PhysEnv.newRigidBody()`](#function-ygphysphysenvnewrigidbody).

### Example

```lua
-- Create RigidBodyInfo instance and set some properties
rbInfo = yg.phys.RigidBodyInfo()
rbInfo.mass = 2.5
rbInfo.friction = 0.5
rbInfo.restitution = 0.5
```

### constructor

> `yg.phys.RigidBodyInfo()` -> [`yg.phys.RigidBodyInfo`](#class-ygphysrigidbodyinfo)

### Properties

| Property                   | Type    | Default | Info                                                      |
| -------------------------- | ------- | ------- | --------------------------------------------------------- |
| `mass`                     | number  | 1.0     | Mass [kg]                                                 |
| `linearDamping`            | number  | 0.0     | Linear Damping factor in [0,1]                            |
| `angularDamping`           | number  | 0.0     | Angular Damping factor in [0,1]                           |
| `friction`                 | number  | 0.5     | Friction in [0,1]                                         |
| `rollingFriction`          | number  | 0.0     | Rolling Friction in [0,1]                                 |
| `spinningFriction`         | number  | 0.0     | Spinning Friction in [0,1]                                |
| `restitution`              | number  | 0.0     | Restitution in [0,1]                                      |
| `linearSleepingThreshold`  | number  | 0.8     | Linear Sleeping Threshold in [0,1]                        |
| `angularSleepingThreshold` | number  | 1.0     | Angular Sleeping Threshold in [0,1]                       |
| `kinematic`                | boolean | `false` | If `true`, the Rigid Body will be kinematic               |
| `disableDeactivation`      | boolean | `false` | if `true`, the Rigid Body will have disabled deactivation |

## class yg.phys.RigidBody

Represents a Rigid Body.

### function yg.phys.RigidBody.getTrafo()

Returns the current pose (Trafo) of the Rigid Body.

> `yg.phys.RigidBody.getTrafo()` -> [`yg.math.Trafo`](yg_math.md#class-ygmathtrafo)

### function yg.phys.RigidBody.setTrafo()

Sets the Rigid Body to a new pose (Trafo).

> `yg.phys.RigidBody.setTrafo(trafo)` -> `void`

| Argument | Type                                          | Info         |
| -------- | --------------------------------------------- | ------------ |
| `trafo`  | [yg.math.Trafo](yg_math.md#class-ygmathtrafo) | Trafo to set |

### function yg.phys.RigidBody.setRestitution()

Sets the Restitution of the Rigid Body.

> `yg.phys.RigidBody.setRestitution(restitution)` -> `void`

| Argument      | Type   | Info                        |
| ------------- | ------ | --------------------------- |
| `restitution` | number | Restitution to set in [0,1] |

### function yg.phys.RigidBody.setFriction()

Sets the Friction of the Rigid Body.

> `yg.phys.RigidBody.setFriction(friction)` -> `void`

| Argument   | Type   | Info                     |
| ---------- | ------ | ------------------------ |
| `friction` | number | Friction to set in [0,1] |

### function yg.phys.RigidBody.setSleepingThresholds()

Sets the Sleeping Thresholds of the Rigid Body.

> `yg.phys.RigidBody.setSleepingThresholds(linear, angular)` -> `void`

| Argument  | Type   | Info                                       |
| --------- | ------ | ------------------------------------------ |
| `linear`  | number | Linear sleeping threshold to set in [0,1]  |
| `angular` | number | Angular sleeping threshold to set in [0,1] |

### function yg.phys.RigidBody.setLinearFactors()

Sets the Linear Factors of the Rigid Body.

> `yg.phys.RigidBody.setLinearFactors(x, y, z)` -> `void`

| Argument | Type   | Info                                      |
| -------- | ------ | ----------------------------------------- |
| `x`      | number | X-component linear factor to set in [0,1] |
| `y`      | number | Y-component linear factor to set in [0,1] |
| `z`      | number | Z-component linear factor to set in [0,1] |

### function yg.phys.RigidBody.setAngularFactor()

Sets the Angular Factors of the Rigid Body from a single value which is applied to all axes.

> `yg.phys.RigidBody.setAngularFactor(angFac)` -> `void`

| Argument | Type   | Info                           |
| -------- | ------ | ------------------------------ |
| `angFac` | number | Angular factor to set in [0,1] |

### function yg.phys.RigidBody.setAngularFactors()

Sets the Angular Factors of the Rigid Body from individual values for x-,y-,z-components.

> `yg.phys.RigidBody.setAngularFactors(x, y, z)` -> `void`

| Argument | Type   | Info                                       |
| -------- | ------ | ------------------------------------------ |
| `x`      | number | X-component angular factor to set in [0,1] |
| `y`      | number | Y-component angular factor to set in [0,1] |
| `z`      | number | Z-component angular factor to set in [0,1] |

### function yg.phys.RigidBody.applyCentralForce()

Applies a central force to the Rigid Body. The force `F` is applied to the Rigid Body for the time delta `t` of the next simulation step only.

**Example:** Applying a force `F=5N` for `t=1s` changes the velocity of a Rigid Body with mass `m=1kg` like so (damping etc. ignored):

```
dV = F  * t  / m
dV = 5N * 1s / 1kg
dV = 5m/s
```

> `yg.phys.RigidBody.applyCentralForce(x, y, z)` -> `void`

| Argument | Type   | Info                                   |
| -------- | ------ | -------------------------------------- |
| `x`      | number | X-component central force to apply [N] |
| `y`      | number | Y-component central force to apply [N] |
| `z`      | number | Z-component central force to apply [N] |

### function yg.phys.RigidBody.applyCentralImpulse()

Applies a central impulse to the Rigid Body. The impulse is immediately applied to the Rigid Body as if a force `F` was applied for a time `t`. Unit: [N*s] (newton-second).

**Example:** Applying an impulse `J=5Ns` changes the velocity of a Rigid Body with mass `m=1kg` like so (damping etc. ignored):

```
dV = J   / m
dV = 5Ns / 1kg
dV = 5m/s
```

> `yg.phys.RigidBody.applyCentralImpulse(x, y, z)` -> `void`

| Argument | Type   | Info                                       |
| -------- | ------ | ------------------------------------------ |
| `x`      | number | X-component central impulse to apply [N*s] |
| `y`      | number | Y-component central impulse to apply [N*s] |
| `z`      | number | Z-component central impulse to apply [N*s] |

### Properties

| Property | Type   | Info                   |
| -------- | ------ | ---------------------- |
| `name`   | string | Name of the Rigid Body |

## class yg.phys.Collision

Represents a Collision between two Rigid Bodies.

## class yg.phys.RayTestResult

Represents the result of a ray test.
