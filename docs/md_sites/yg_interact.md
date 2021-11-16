# yg.interact

Functions for adding and reading values from interact GUI items.

## function yg.interact.addNumber()

Adds an interact GUI item for controlling a number (float scalar) value.

> `function yg.interact.addNumber(name, unit, value, min, max)` -> `void`

| Argument | Type   | Info                                 |
| -------- | ------ | ------------------------------------ |
| `name`   | string | Name (label) of the interact item    |
| `unit`   | string | Unit label for the value of the item |
| `value`  | number | Initial value                        |
| `min`    | number | Minimum value                        |
| `max`    | number | Maximum value                        |

## function yg.interact.addInteger()

Adds an interact GUI item for controlling an integer (int scalar) value.

> `function yg.interact.addInteger(name, unit, value, min, max)` -> `void`

| Argument | Type   | Info                                 |
| -------- | ------ | ------------------------------------ |
| `name`   | string | Name (label) of the interact item    |
| `unit`   | string | Unit label for the value of the item |
| `value`  | number | Initial value                        |
| `min`    | number | Minimum value                        |
| `max`    | number | Maximum value                        |

## function yg.interact.addVector2()

Adds an interact GUI item for controlling a 2-component vector.

> `function yg.interact.addVector2(name, x, y)` -> `void`

| Argument | Type   | Info                              |
| -------- | ------ | --------------------------------- |
| `name`   | string | Name (label) of the interact item |
| `x`      | number | Initial x value                   |
| `y`      | number | Initial y value                   |

## function yg.interact.addVector3()

Adds an interact GUI item for controlling a 3-component vector.

> `function yg.interact.addVector3(name, x, y, z)` -> `void`

| Argument | Type   | Info                              |
| -------- | ------ | --------------------------------- |
| `name`   | string | Name (label) of the interact item |
| `x`      | number | Initial x value                   |
| `y`      | number | Initial y value                   |
| `z`      | number | Initial z value                   |

## function yg.interact.addBinary()

Adds an interact GUI item for controlling a boolean.

> `function yg.interact.addBinary(name, unit, value)` -> `void`

| Argument | Type    | Info                                 |
| -------- | ------- | ------------------------------------ |
| `name`   | string  | Name (label) of the interact item    |
| `unit`   | string  | Unit label for the value of the item |
| `value`  | boolean | Initial state                        |

## function yg.interact.addRGB()

Adds an interact GUI item for controlling RGB values (color picker).

> `function yg.interact.addRGB(name, r, g, b)` -> `void`

| Argument | Type   | Info                              |
| -------- | ------ | --------------------------------- |
| `name`   | string | Name (label) of the interact item |
| `r`      | number | Initial red value                 |
| `g`      | number | Initial green value               |
| `b`      | number | Initial blue value                |

## function yg.interact.addRGBA()

Adds an interact GUI item for controlling RGBA values (color picker).

> `function yg.interact.addRGBA(name, r, g, b, a)` -> `void`

| Argument | Type   | Info                              |
| -------- | ------ | --------------------------------- |
| `name`   | string | Name (label) of the interact item |
| `r`      | number | Initial red value                 |
| `g`      | number | Initial green value               |
| `b`      | number | Initial blue value                |
| `a`      | number | Initial alpha value               |

## function yg.interact.addAction()

Adds an interact GUI item for performing an action (button).

> `function yg.interact.addAction(name, unit)` -> `void`

| Argument | Type   | Info                              |
| -------- | ------ | --------------------------------- |
| `name`   | string | Name (label) of the interact item |
| `unit`   | string | Button label                      |

## function yg.interact.addSelect()

Adds an interact GUI item for picking an item (list box).

> `function yg.interact.addSelect(name, items, value)` -> `void`

| Argument | Type     | Info                                  |
| -------- | -------- | ------------------------------------- |
| `name`   | string   | Name (label) of the interact item     |
| `items`  | {string} | Names of the items (array of strings) |
| `value`  | number   | Index of the initially selected item  |

## function yg.interact.getNumber()

Returns the current value of a number interact GUI item.

> `function yg.interact.getNumber(name)` -> `number`

| Argument | Type   | Info                                       |
| -------- | ------ | ------------------------------------------ |
| `name`   | string | Name of the interact item to get data from |

## function yg.interact.getInteger()

Returns the current value of an integer interact GUI item.

> `function yg.interact.getInteger(name)` -> `number`

| Argument | Type   | Info                                       |
| -------- | ------ | ------------------------------------------ |
| `name`   | string | Name of the interact item to get data from |

## function yg.interact.getVector2()

Returns the current values of a 2-component vector interact GUI item.

> `function yg.interact.getVector2(name)` -> `{number}`

| Argument | Type   | Info                                       |
| -------- | ------ | ------------------------------------------ |
| `name`   | string | Name of the interact item to get data from |

## function yg.interact.getVector3()

Returns the current values of a 3-component vector interact GUI item.

> `function yg.interact.getVector3(name)` -> `{number}`

| Argument | Type   | Info                                       |
| -------- | ------ | ------------------------------------------ |
| `name`   | string | Name of the interact item to get data from |

## function yg.interact.getBinary()

Returns the current value of a boolean interact GUI item.

> `function yg.interact.getBinary(name)` -> `boolean`

| Argument | Type   | Info                                       |
| -------- | ------ | ------------------------------------------ |
| `name`   | string | Name of the interact item to get data from |

## function yg.interact.getRGB()

Returns the current values of a RGB (color picker) interact GUI item.

> `function yg.interact.getRGB(name)` -> `{number}`

| Argument | Type   | Info                                       |
| -------- | ------ | ------------------------------------------ |
| `name`   | string | Name of the interact item to get data from |

## function yg.interact.getRGBA()

Returns the current values of a RGBA (color picker) interact GUI item.

> `function yg.interact.getRGBA(name)` -> `{number}`

| Argument | Type   | Info                                       |
| -------- | ------ | ------------------------------------------ |
| `name`   | string | Name of the interact item to get data from |

## function yg.interact.getAction()

Returns `true` if the action was initiated (button was clicked).

> `function yg.interact.getAction(name)` -> `boolean`

| Argument | Type   | Info                                       |
| -------- | ------ | ------------------------------------------ |
| `name`   | string | Name of the interact item to get data from |

## function yg.interact.getSelect()

Returns the index of the currently selected item of the list box.

> `function yg.interact.getSelect(name)` -> `number`

| Argument | Type   | Info                                       |
| -------- | ------ | ------------------------------------------ |
| `name`   | string | Name of the interact item to get data from |
