function init()
    yg.control.enableVSync(true)
    yg.gl.depthTest(true)
    yg.gl.clearColor(0.125, 0.225, 0.35, 1.000)

    -- register interact values
    yg.interact.addBinary("camera follow object", "on/off", false)
    yg.interact.addNumber("camera field of view", "deg", 50, 10, 170)
    yg.interact.addBinary("object hectic movement", "on/off", false)

    -- load assets
    yg.asset.loadGeometry("grid", "a//yg_grid.obj")
    yg.asset.loadGeometry("system", "a//yg_system.obj")
    yg.asset.loadGeometry("trafficcone", "a//trafficcone.obj", "a//trafficcone.mtl")
    yg.asset.loadGeometry("box", "a//box.obj", "a//box.mtl")
    yg.asset.loadVertFragShader("diff", "a//yg_default.vert", "a//yg_diffusecolor.frag")
    yg.asset.loadVertFragShader("simple", "a//yg_default.vert", "a//yg_simplecolor.frag")

    -- make camera
    c = yg.math.Camera()
    eye = {0, 10, 15}
    center = {0, 2.5, 0}
    up = {0, 1, 0}
    c:trafo():lookAt(eye, center, up)

    light = yg.gl.Lightsource()
    lightAmbient = {0.5, 0.5, 0.5}
    lightDiffuse = {0.5, 0.5, 0.5}
    lightPosition = {0, 10, 0}
    light:setAmbient(lightAmbient)
    light:setDiffuse(lightDiffuse)
    light:setPosition(lightPosition)

    -- trafo for the main object
    trafo = yg.math.Trafo()
end

function tick()
    -- update camera from input
    c:setPerspective(yg.interact.getNumber("camera field of view"), yg.input.get("WINDOW_ASPECT_RATIO"), 0.1, 100)
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

    -- move object and point it to origin
    if yg.interact.getBinary("object hectic movement") then
        eye = {math.sin(yg.time.getTime() * 1.25 + 2.5) * 5,
                math.sin(yg.time.getTime() * 1.25) * 2.5 + 2,
                math.cos(yg.time.getTime() * 1.25 + 2.5) * 5}
    else
        eye = {7,
                math.sin(yg.time.getTime() * 1.25) * 0.5 + 1,
                math.sin(yg.time.getTime() * 0.75) * 0.75}
    end
    center = {0, 0, 0}
    up = {0, 1, 0}
    trafo:lookAt(eye, center, up)

    if yg.interact.getBinary("camera follow object") then
        cam_trafo = yg.math.Trafo()
        eye_cam = {eye[1], eye[2], eye[3]}
        cam_trafo:lookAt(eye_cam, center, up)
        eye_cam_off = {-2.0 + math.sin(yg.time.getTime() * 1.5) * 0.5,
                        1.5 + math.sin(yg.time.getTime() * 1.1) * 0.75,
                        6}
        cam_trafo:translateLocal(eye_cam_off)
        c:trafo():lookAt(cam_trafo:getEye(), center, up)
    end

    -- draw objects
    yg.gl.draw(yg.asset.getGeometry("trafficcone"), light, yg.asset.getShader("diff"), nil, c, trafo)
    yg.gl.draw(yg.asset.getGeometry("system"), light, yg.asset.getShader("simple"), nil, c, trafo)
    yg.gl.draw(yg.asset.getGeometry("grid"), nil, yg.asset.getShader("simple"), nil, c, nil)
    yg.gl.draw(yg.asset.getGeometry("box"), light, yg.asset.getShader("diff"), nil, c, nil)
end
