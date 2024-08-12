function init()
    yg.gl.depthTest(true)

    -- register interact values
    yg.interact.addNumber("Sky Rotation", "rad", 0, -3.14159, 3.14159)
    yg.interact.addRGB("Tint", 1, 1, 1)

    -- make camera
    c = yg.math.Camera()
    eye = {-1, 2, 5}
    center = {0, 2, 0}
    up = {0, 1, 0}
    c:trafo():lookAt(eye, center, up)

    -- make lightsource
    light = yg.gl.Lightsource()
    skyAmbient = {1, 0.8, 0.55}
    tintFacAmbient = 0.2
    tintFacDiffuse = 0.7
    lightDist = 10

    -- load assets
    yg.asset.loadTexture("sky", "a//sky.png", "", "DIFFUSE", "LINEAR", "REPEAT", false)
    yg.asset.loadGeometry("object", "a//sphere.obj", "")
    yg.asset.loadGeometry("grid", "a//yg_grid.obj", "")
    yg.asset.loadVertFragShader("diff", "a//yg_default.vert", "a//yg_diffusecolor.frag")
    yg.asset.loadVertFragShader("simple", "a//yg_default.vert", "a//yg_simplecolor.frag")
end

function tick()
    -- update light
    tint = yg.interact.getRGB("Tint")
    ambient = {tint[1] * skyAmbient[1] * tintFacAmbient, tint[2] * skyAmbient[2] * tintFacAmbient, tint[3] * skyAmbient[3] * tintFacAmbient}
    diffuse = {tint[1] * skyAmbient[1] * tintFacDiffuse, tint[2] * skyAmbient[2] * tintFacDiffuse, tint[3] * skyAmbient[3] * tintFacDiffuse}
    light:setAmbient(ambient)
    light:setDiffuse(diffuse)
    rot = yg.interact.getNumber("Sky Rotation") + 1.57079632679
    light:setPosition({lightDist * math.sin(rot), 0, lightDist * math.cos(rot)})

    -- update camera from input
    c:setPerspective(90, yg.input.get("WINDOW_ASPECT_RATIO"), 0.1, 100)
    c:trafo():rotateGlobal(yg.time.getDelta() * 1.25 * yg.input.get("KEY_LEFT"), "Y")
    c:trafo():rotateGlobal(yg.time.getDelta() * -1.25 * yg.input.get("KEY_RIGHT"), "Y")
    c:trafo():rotateLocal(yg.time.getDelta() * 1.25 * yg.input.get("KEY_UP"), "X")
    c:trafo():rotateLocal(yg.time.getDelta() * -1.25 * yg.input.get("KEY_DOWN"), "X")
    move = {}
    move[1] = yg.time.getDelta() * 7.0 * yg.input.get("KEY_D") - 
              yg.time.getDelta() * 7.0 * yg.input.get("KEY_A")
    move[2] = 0
    move[3] = yg.time.getDelta() * 7.0 * yg.input.get("KEY_S") - 
              yg.time.getDelta() * 7.0 * yg.input.get("KEY_W")
    c:trafo():translateLocal(move)

    -- draw sky
    skyT = yg.math.Trafo()
    skyT:rotateGlobal(yg.interact.getNumber("Sky Rotation"), "Y")
    yg.gl.drawSky2(yg.asset.getTexture("sky"), c, yg.interact.getRGB("Tint"), nil, skyT)

    -- draw scene objects
    yg.gl.draw(yg.asset.getGeometry("grid"), nil, yg.asset.getShader("simple"), nil, c, nil)
    yg.gl.draw(yg.asset.getGeometry("object"), light, yg.asset.getShader("diff"), nil, c, nil)
end

function shutdown()
end
