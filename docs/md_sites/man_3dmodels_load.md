# Load 3D Models

## Object (.obj) and Material (.mtl) Support

3D models in `.obj` format can be loaded by `yourgame`, optionally together with a material template library `.mtl`.

This is what `yourgame` does:

-   Normals remain unchanged, preserving edges and smooth areas
    -   Note for `Blender`: the options `Shade Smooth` and `Shade Flat` have an impact on the exported `.obj` data
-   The diffuse color `Kd` from materials (`.mtl`) is attached to the `.obj` data during import and provided as `Color` input to the vertex shader
    -   This way, `Vertex Color Shading` can be performed
    -   See [GLSL Shaders](#glsl-shaders) on how to use vertex color in Shaders

## Tools and 3D Assets

These 3D tools can be used to create `yourgame` compatible data:

-   [Blender](man_3dmodels_blender.md)
-   [Blockbench](man_3dmodels_blockbench.md)
-   ... potentially many more

Some ready-to-use game assets can be imported directly without modification:

-   `.obj` based 3D game assets, made by `Kenney`
-   ... potentially many more
