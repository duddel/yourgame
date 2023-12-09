# GLSL Shaders

## Attributes Conventions

| Usage     | Type | Location | GLSL Vertex Shader Code                     |
| --------- | ---- | -------- | ------------------------------------------- |
| Position  | vec3 | **0**    | `layout(location = 0) in vec3 inPosition;`  |
| Normal    | vec3 | **1**    | `layout(location = 1) in vec3 inNormal;`    |
| Texcoords | vec2 | **2**    | `layout(location = 2) in vec2 inTexcoords;` |
| Color     | vec3 | **3**    | `layout(location = 3) in vec3 inColor;`     |

## Uniforms Conventions

| Usage                  | Type        | Name                 | GLSL Shader Code                      |
| ---------------------- | ----------- | -------------------- | ------------------------------------- |
| MVP Matrix             | mat4        | **`mvpMat`**         | `uniform mat4        mvpMat;`         |
| VP Matrix              | mat4        | **`vpMat`**          | `uniform mat4        vpMat;`          |
| Model Matrix           | mat4        | **`modelMat`**       | `uniform mat4        modelMat;`       |
| Normal Matrix          | mat3        | **`normalMat`**      | `uniform mat3        normalMat;`      |
| Camera Position        | vec3        | **`camPos`**         | `uniform vec3        camPos;`         |
| Camera Trafo           | mat4        | **`camTrafo`**       | `uniform mat4        camTrafo;`       |
| Sky Rotation Inverse   | mat3        | **`skyRotInv`**      | `uniform mat3        skyRotInv;`      |
| Texture Diffuse        | sampler2D   | **`textureDiffuse`** | `uniform sampler2D   textureDiffuse;` |
| Texture Sky            | samplerCube | **`textureSky`**     | `uniform samplerCube textureSky;`     |
| Light Ambient          | vec3        | **`lightAmbient`**   | `uniform vec3        lightAmbient;`   |
| Light Diffuse          | vec3        | **`lightDiffuse`**   | `uniform vec3        lightDiffuse;`   |
| Light Specular         | vec3        | **`lightSpecular`**  | `uniform vec3        lightSpecular;`  |
| Light Position         | vec3        | **`lightPosition`**  | `uniform vec3        lightPosition;`  |
| Subtexture Coordinates | vec4        | **`subtex`**         | `uniform vec4        subtex;`         |
