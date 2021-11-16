# yg.control

Functions for controlling the framework.

## function yg.control.exit()

Notifies the application to exit (shut down).

> `yg.control.exit()` -> `void`

## function yg.control.enableFullscreen()

Enables/disables fullscreen mode.

> `yg.control.enableFullscreen(enable)` -> `void`

| Argument | Type    | Info                                        |
| -------- | ------- | ------------------------------------------- |
| `enable` | boolean | Enable fullscreen. Options: `true`, `false` |

## function yg.control.enableVSync()

Enables/disables vertical sync.

> `yg.control.enableVSync(enable)` -> `void`

| Argument | Type    | Info                                           |
| -------- | ------- | ---------------------------------------------- |
| `enable` | boolean | Enable vertical sync. Options: `true`, `false` |

## function yg.control.catchMouse()

Enables/disables catched mouse.

> `yg.control.catchMouse(enable)` -> `void`

| Argument | Type    | Info                                           |
| -------- | ------- | ---------------------------------------------- |
| `enable` | boolean | Enable catched mouse. Options: `true`, `false` |

## function yg.control.enableAudio()

Enables audio module.

> `yg.control.catchMouse()` -> `void`

## function yg.control.runScript()

Starts execution of another Lua script after shutting down current script.

> `yg.control.runScript(filename)` -> `void`

| Argument   | Type   | Info                              |
| ---------- | ------ | --------------------------------- |
| `filename` | string | Filename of the Lua script to run |

## function yg.control.loadScript()

Loads and executes another Lua script while current script runs. Can be used to import additional code.

> `yg.control.loadScript(filename)` -> `void`

| Argument   | Type   | Info                               |
| ---------- | ------ | ---------------------------------- |
| `filename` | string | Filename of the Lua script to load |
