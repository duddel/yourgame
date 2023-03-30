function init()
    math.randomseed(os.time())
    yg.control.enableVSync(true)
    yg.gl.depthTest(true)

    -- register interact values
    yg.interact.addNumber("gravity", "m/s^2", -9.81, -20, 20)
    yg.interact.addBinary("wiper", "move on/off", true)

    -- make Motion
    motBounce = yg.util.Motion("REPEAT")
    motBounce:addRamp(3.0, -9, 9, "SMOOTH2")
    motBounce:addIdle(0.2, 9)
    motBounce:addRamp(1.5, 9, -9, "CUBEDOWN")
    motBounce:addIdle(0.2, -9)

    -- light and color
    yg.gl.clearColor(0.212, 0.235, 0.270, 1.000)
    lightAmbient = {0.05, 0.05, 0.175}
    lightDiffuse = {1.0, 0.9, 0.7}
    lightPosition = {20, 10, 0}

    -- load assets
    yg.asset.loadTexture("world", "a//ball.png", "", "DIFFUSE", "NEAREST", "REPEAT", true)
    yg.asset.loadTexture("cylinder", "a//cylinder.png", "", "DIFFUSE", "NEAREST", "REPEAT", true)
    yg.asset.loadVertFragShader("diff", "a//yg_default.vert", "a//yg_diffusecolor.frag")
    yg.asset.loadVertFragShader("simple", "a//yg_default.vert", "a//yg_simplecolor.frag")
    yg.asset.loadVertFragShader("tex", "a//yg_default.vert", "a//yg_diffusetex.frag")
    yg.asset.loadGeometry("cube", "a//box.obj", "a//box.mtl")
    yg.asset.loadGeometry("sphere_outside", "a//sphere.obj")
    yg.asset.loadGeometry("grid", "a//yg_grid.obj")
    yg.asset.loadGeometry("cylinder", "a//cylinder.obj")
    yg.asset.loadGeometry("trafficcone", "a//trafficcone.obj", "a//trafficcone.mtl")
    yg.asset.loadGeometry("fence", "a//fence.obj", "a//fence.mtl")

    -- initialize physics
    physEnv = yg.phys.PhysEnv()

    -- rbInfo and trafo are reused for all rigid bodies
    rbInfo = yg.phys.RigidBodyInfo()
    trafo = yg.math.Trafo()

    -- floor (matches grid geometry)
    physEnv:newBoxShape("floor", 10.0, 0.1, 10.0)
    rbInfo.mass = 0; rbInfo.restitution = 1
    eye = {0, -0.1, 0}; trafo:setTranslation(eye)
    physEnv:newRigidBody("floor", "floor", trafo, rbInfo)

    -- fence
    physEnv:newBoxShape("fenceX", 10.0, 1, 0.25)
    physEnv:newBoxShape("fenceZ", 0.25, 1, 10.0)

    eye[1] = 0; eye[2] = 1; eye[3] = 10.25; trafo:setTranslation(eye)
    physEnv:newRigidBody("fence1", "fenceX", trafo, rbInfo)
    eye[3] = -10.25; trafo:setTranslation(eye)
    physEnv:newRigidBody("fence2", "fenceX", trafo, rbInfo)
    eye[1] = 10.25; eye[2] = 1; eye[3] = 0; trafo:setTranslation(eye)
    physEnv:newRigidBody("fence3", "fenceZ", trafo, rbInfo)
    eye[1] = -10.25; trafo:setTranslation(eye)
    physEnv:newRigidBody("fence4", "fenceZ", trafo, rbInfo)

    -- spawn bodies
    physEnv:newBoxShape("box", 0.5, 0.5, 0.5)
    physEnv:newSphereShape("sphere", 0.75)
    physEnv:newCylinderShape("cylinder", 0.25, 1)
    physEnv:newConeShape("cone", 0.5, 1.25)

    -- player
    do
        physEnv:newBoxShape("playerbox", 0.5, 0.25, 2.5)
        local rbInfo = yg.phys.RigidBodyInfo()
        local trafo = yg.math.Trafo()
        rbInfo.mass = 0; rbInfo.kinematic = true
        physEnv:newRigidBody("player", "playerbox", trafo, rbInfo)
    end

    -- random falling bodies
    for i=1,3 do
        for j=1,3 do
            local trafo = yg.math.Trafo()
            rbInfo.mass = 1
            rbInfo.restitution = 0.5
            rbInfo.friction = 0.4
            rbInfo.rollingFriction = 0.05
            rbInfo.spinningFriction = 0.05
            rbInfo.disableDeactivation = true
            rbInfo.kinematic = false
            local eye = {}

            eye = {math.random()*16-8, math.random()*5+6, math.random()*16-8}
            trafo:setTranslation(eye)
            trafo:rotateLocal(math.random() * 3.14159265359, "Z")
            trafo:rotateGlobal(math.random() * 3.14159265359, "X")
            physEnv:newRigidBody("box_" .. i .. "_" .. j, "box", trafo, rbInfo)

            eye = {math.random()*16-8, math.random()*5+6, math.random()*16-8}
            trafo:setTranslation(eye)
            trafo:rotateLocal(math.random() * 3.14159265359, "Z")
            trafo:rotateGlobal(math.random() * 3.14159265359, "X")
            physEnv:newRigidBody("sphere_" .. i .. "_" .. j, "sphere", trafo, rbInfo)

            eye = {math.random()*16-8, math.random()*5+6, math.random()*16-8}
            trafo:setTranslation(eye)
            trafo:rotateLocal(math.random() * 3.14159265359, "Z")
            trafo:rotateGlobal(math.random() * 3.14159265359, "X")
            physEnv:newRigidBody("cylinder_" .. i .. "_" .. j, "cylinder", trafo, rbInfo)
        end
    end

    rbInfo.mass = 0.5
    rbInfo.friction = 0.75
    for i=1,5 do
        for j=1,5 do
            local trafo = yg.math.Trafo()
            local eye = {math.random()*18-9, 0.75, math.random()*18-9}
            trafo:setTranslation(eye)
            physEnv:newRigidBody("cone_" .. i .. "_" .. j, "cone", trafo, rbInfo)
        end
    end

    -- make camera
    c = yg.math.Camera()
    eye = {0, 10, 15}
    center = {0, 2.5, 0}
    up = {0, 1, 0}
    c:trafo():lookAt(eye, center, up)

    -- make lightsource
    light = yg.gl.Lightsource()
    light:setAmbient(lightAmbient)
    light:setDiffuse(lightDiffuse)
    light:setPosition(lightPosition)
end

function tick()
    -- update gravity
    physEnv:setGravity(0, yg.interact.getNumber("gravity"), 0)

    -- update camera from input
    c:setPerspective(65, yg.input.get("WINDOW_ASPECT_RATIO"), 0.1, 100)
    c:trafo():rotateGlobal(yg.time.getDelta() * 1.25 * yg.input.get("KEY_LEFT"), "Y")
    c:trafo():rotateGlobal(yg.time.getDelta() * -1.25 * yg.input.get("KEY_RIGHT"), "Y")
    c:trafo():rotateLocal(yg.time.getDelta() * 1.25 * yg.input.get("KEY_UP"), "X")
    c:trafo():rotateLocal(yg.time.getDelta() * -1.25 * yg.input.get("KEY_DOWN"), "X")
    move = {}
    move[1] = yg.time.getDelta() * 7.0 * yg.input.get("KEY_G") - 
              yg.time.getDelta() * 7.0 * yg.input.get("KEY_D")
    move[2] = 0
    move[3] = yg.time.getDelta() * 7.0 * yg.input.get("KEY_F") - 
              yg.time.getDelta() * 7.0 * yg.input.get("KEY_R")
    c:trafo():translateLocal(move)

    -- move kinematic body
    do
        local trafo = yg.math.Trafo()
        local body = physEnv:getRigidBody("player")
        local move = {motBounce:val(), 0, 0}
        trafo:setTranslation(move)
        body:setTrafo(trafo)
    end

    -- update physics
    physEnv:tick(yg.time.getDelta())

    -- update Motion
    if yg.interact.getBinary("wiper") then
        motBounce:tick(yg.time.getDelta())
    end

    -- draw boxes
    renderBoxes = physEnv:getRigidBodiesStartingWith("box")
    for k, body in pairs(renderBoxes) do
        trafo = body:getTrafo()
        yg.gl.draw(yg.asset.getGeometry("cube"), light, yg.asset.getShader("diff"), nil, c, trafo)
    end

    -- draw fence boxes
    -- renderFences = physEnv:getRigidBodiesStartingWith("fence")
    -- for k, body in pairs(renderFences) do
    --     trafo = body:getTrafo()
    --     yg.gl.draw(yg.asset.getGeometry("cube"), light, yg.asset.getShader("diff"), nil, c, trafo)
    -- end

    -- draw spheres
    renderSpheres = physEnv:getRigidBodiesStartingWith("sphere")
    for k, body in pairs(renderSpheres) do
        trafo = body:getTrafo()
        yg.gl.draw(yg.asset.getGeometry("sphere_outside"), light, yg.asset.getShader("tex"), yg.asset.getTexture("world"), c, trafo)
    end

    -- draw cylinders
    renderCylinders = physEnv:getRigidBodiesStartingWith("cylinder")
    for k, body in pairs(renderCylinders) do
        trafo = body:getTrafo()
        yg.gl.draw(yg.asset.getGeometry("cylinder"), light, yg.asset.getShader("tex"), yg.asset.getTexture("cylinder"), c, trafo)
    end

    -- draw cones
    renderCones = physEnv:getRigidBodiesStartingWith("cone")
    for k, body in pairs(renderCones) do
        trafo = body:getTrafo()
        yg.gl.draw(yg.asset.getGeometry("trafficcone"), light, yg.asset.getShader("diff"), nil, c, trafo)
    end

    body = physEnv:getRigidBody("player")
    trafo = body:getTrafo()
    yg.gl.draw(yg.asset.getGeometry("cube"), light, yg.asset.getShader("diff"), nil, c, trafo)

    yg.gl.draw(yg.asset.getGeometry("grid"), nil, yg.asset.getShader("simple"), nil, c, nil)
    yg.gl.draw(yg.asset.getGeometry("fence"), light, yg.asset.getShader("diff"), nil, c, nil)
end

function shutdown()
end

