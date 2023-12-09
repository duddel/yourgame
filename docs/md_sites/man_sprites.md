# Sprites

## Texture Atlases (Sprite Sheets)

Packed texture atlases created with the tool `Free Texture Packer` (`FTP`) are supported and can be loaded with [yg.asset.loadTexture()](yg_asset.md#function-ygassetloadtexture).

Tested with **Free Texture Packer v0.6.7**.

The following `FTP` settings are required. The rest can be set to users taste.

-   Format: `JSON (hash)` or `JSON (array)`
-   Allow rotation: `No`
-   Allow trim: `No`
-   Padding: `>= 2` (recommended)

## Accessing Sprites and Sequences

To draw a sprite from a texture atlas, the draw function must know where to find the desired sprite in the texture. The following functions can be used on a [yg.gl.Texture](yg_gl.md#class-yggltexture) to retrieve these coordinate information.

-   [yg.gl.Texture.getCoords()](yg_gl.md#function-yggltexturegetcoords): get coordinates  for a sprite that has been listed in the atlas file (`.json`) by it's **name**. This is always possible, even if the sprite is part of a sequence
-   [yg.gl.Texture.getFrameCoords()](yg_gl.md#function-yggltexturegetframecoords): get coordinates from a frame index of a **sequence**

During texture loading, sequences are detected if the sprite names have indexes at the end, separated with `-` or `_`.

**Examples:**

-   `walking_01` -> sequence `walking` detected, [yg.gl.Texture.getFrameCoords()](yg_gl.md#function-yggltexturegetframecoords) can be used
-   `walking-01` -> sequence `walking` detected, [yg.gl.Texture.getFrameCoords()](yg_gl.md#function-yggltexturegetframecoords) can be used
-   `walking01` -> no sequence detected, only [yg.gl.Texture.getCoords()](yg_gl.md#function-yggltexturegetcoords) can be used
