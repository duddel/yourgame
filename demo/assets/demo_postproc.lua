function init()
    yg.control.enableVSync(true)
    yg.gl.depthTest(true)
    yg.gl.clearColor(0.125, 0.225, 0.35, 1.000)

    -- register interact values
    yg.interact.addBinary("Post processing", "active", true)
    postprocShaders = {"null", "invert", "fog"}
    yg.interact.addSelect("Shader", postprocShaders, 1)
    yg.interact.addInteger("Framebuffer width", "[px]", 640, 0, 1024)
    yg.interact.addInteger("Framebuffer height", "[px]", 480, 0, 1024)

    -- make camera
    c = yg.math.Camera()
    eye = {0, 10, 15}
    center = {0, 2.5, 0}
    up = {0, 1, 0}
    c:trafo():lookAt(eye, center, up)

    -- make lightsource
    light = yg.gl.Lightsource()
    lightAmbient = {0.5, 0.5, 0.5}
    lightDiffuse = {0.5, 0.5, 0.5}
    lightPosition = {0, 10, 0}
    light:setAmbient(lightAmbient)
    light:setDiffuse(lightDiffuse)
    light:setPosition(lightPosition)

    -- load assets
    yg.asset.loadGeometry("grid", "a//yg_grid.obj", "")
    yg.asset.loadGeometry("trafficcone", "a//trafficcone.obj", "a//trafficcone.mtl")
    yg.asset.loadVertFragShader("diff", "a//yg_default.vert", "a//yg_diffusecolor.frag")
    yg.asset.loadVertFragShader("simple", "a//yg_default.vert", "a//yg_simplecolor.frag")
    yg.asset.loadVertFragShader("post_invert", "a//yg_post.vert", "a//yg_post_invert.frag")
    yg.asset.loadVertFragShader("post_fog", "a//yg_post.vert", "a//yg_post_fog.frag")
end

function tick()
    -- initialize post processing
    if yg.interact.getBinary("Post processing") and not yg.postproc.isInitialized() then
        yg.postproc.init(yg.interact.getInteger("Framebuffer width"), yg.interact.getInteger("Framebuffer height"))
    end
    -- shutdown post processing
    if not yg.interact.getBinary("Post processing") and yg.postproc.isInitialized() then
        yg.postproc.shutdown()
    end

    -- update post processing framebuffer
    yg.postproc.resize(yg.interact.getInteger("Framebuffer width"),
                       yg.interact.getInteger("Framebuffer height"))

    camAspect = yg.input.get("WINDOW_ASPECT_RATIO")

    if yg.interact.getInteger("Framebuffer width") >= 1 and
       yg.interact.getInteger("Framebuffer height") >= 1 and
       yg.postproc.isInitialized() then
        camAspect = yg.interact.getInteger("Framebuffer width") / yg.interact.getInteger("Framebuffer height")
    end

    -- set post processing shader
    shaderId = yg.interact.getSelect("Shader")
    if shaderId == 1 then
        yg.postproc.use(nil)
    end
    if shaderId == 2 then
        yg.postproc.use(yg.asset.getShader("post_invert"))
    end
    if shaderId == 3 then
        yg.postproc.use(yg.asset.getShader("post_fog"))
    end

    -- update camera from input
    c:setPerspective(90, camAspect, 1, 100)
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

    -- draw scene objects
    yg.gl.draw(yg.asset.getGeometry("grid"), nil, yg.asset.getShader("simple"), nil, c, nil)
    yg.gl.draw(yg.asset.getGeometry("trafficcone"), light, yg.asset.getShader("diff"), nil, c, nil)
end

function shutdown()
end
