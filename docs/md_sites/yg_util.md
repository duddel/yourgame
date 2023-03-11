# yg.util

Utility classes.

## class yg.util.Motion

Represents a scalar value that performs a sequence of motion segments over time.

### Example

```lua
function init()
    -- Initialize a Motion object. Make a repeating Motion:
    --   Acting from -9 to 9 in 3 seconds with SMOOTH2 easing
    --   Idling 0.2 seconds at 9
    --   Moving back to -9 in 1.5 seconds with CUBEDOWN easing
    --   Idling 0.2 seconds at -9
    mot = yg.util.Motion("REPEAT")
    mot:addRamp(3.0, -9, 9, "SMOOTH2")
    mot:addIdle(0.2, 9)
    mot:addRamp(1.5, 9, -9, "CUBEDOWN")
    mot:addIdle(0.2, -9)
end

function tick()
    -- Tick the Motion with the time delta of the last frame
    mot:tick(yg.time.getDelta())

    -- Get the current scalar value of the Motion (and do something with it)
    motVal = mot:val()
end
```

### constructor

> `yg.util.Motion(flowType)` -> [`yg.util.Motion`](#class-ygutilmotion)

| Argument   | Type   | Info                                                    |
| ---------- | ------ | ------------------------------------------------------- |
| `flowType` | string | Motion flow type. Options: `"ONCE"`, `"REPEAT"`, `"PINGPONG"` |

### function yg.util.Motion.addIdle()

Adds an idle segment to the Motion.

Todo: check if chaining works and if this function returns a Motion reference.

> `yg.util.Motion.addIdle(dt, val)` -> `void`

| Argument | Type   | Info                                 |
| -------- | ------ | ------------------------------------ |
| `dt`     | number | Duration of the segment [seconds]    |
| `val`    | number | Constant (idle) value of the segment |

### function yg.util.Motion.addRamp()

Adds a ramp segment to the Motion.

Todo: check if chaining works and if this function returns a Motion reference.

> `yg.util.Motion.addRamp(dt, val0, val1, ease)` -> `void`

| Argument | Type   | Info                                                                                                                        |
| -------- | ------ | --------------------------------------------------------------------------------------------------------------------------- |
| `dt`     | number | Duration of the segment [seconds]                                                                                           |
| `val0`   | number | Start value of the segment                                                                                                  |
| `val1`   | number | End value of the segment                                                                                                    |
| `ease`   | string | Easing of the segment. Options: `"NONE"`, `"SQUARE"`, `"SQUAREDOWN"`, `"CUBE"`, `"CUBEDOWN"`, `"SINE"`, `"SINEDOWN"`, `"SMOOTH"`, `"SMOOTH2"` |

### function yg.util.Motion.tick()

Advances (ticks) the motion by a given time delta.

> `yg.util.Motion.tick(dt)` -> `void`

| Argument | Type   | Info                 |
| -------- | ------ | -------------------- |
| `dt`     | number | Time delta [seconds] |

### function yg.util.Motion.val()

Returns the current scalar value of the motion.

> `yg.util.Motion.val()` -> `number`

### function yg.util.Motion.pause()

Enables/disables (pauses) the Motion. During pause, [`tick()`](#function-ygutilmotiontick) has no effect.

> `yg.util.Motion.pause(pause)` -> `void`

| Argument | Type    | Info                                           |
| -------- | ------- | ---------------------------------------------- |
| `pause`  | boolean | Enable/disable pause. Options: `true`, `false` |

### function yg.util.Motion.restart()

Restarts the Motion.

> `yg.util.Motion.restart()` -> `void`

### function yg.util.Motion.setDirection()

Enables/disables forward direction of the Motion.

> `yg.util.Motion.setDirection(forward)` -> `void`

| Argument  | Type    | Info                                                       |
| --------- | ------- | ---------------------------------------------------------- |
| `forward` | boolean | Enable/disable forward direction. Options: `true`, `false` |

### function yg.util.Motion.isFinished()

Returns `true` if the Motion is finished.

> `yg.util.Motion.isFinished()` -> `boolean`

### function yg.util.Motion.isPaused()

Returns `true` if the Motion is paused.

> `yg.util.Motion.isPaused()` -> `boolean`

### function yg.util.Motion.getDirection()

Returns `true` if the Motion is in forward direction.

> `yg.util.Motion.getDirection()` -> `boolean`
