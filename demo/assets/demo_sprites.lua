function init()
    yg.control.enableVSync(true)
    yg.gl.clearColor(0.137, 0.255, 0.615, 1.000)

    -- register interact values
    yg.interact.addNumber("frame rate", "Hz", 10, 0, 60)
    yg.interact.addBinary("Framebuffer", "active", false)

    -- load sprite sheet
    yg.asset.loadTexture("sprites", "a//sprites.png", "a//sprites.json", "DIFFUSE", "NEAREST", "REPEAT", true)

    timer = 0
end

function tick()
    -- calc frame index
    timer = timer + (yg.time.getDelta() * yg.interact.getNumber("frame rate"))
    frameIdx = math.floor(timer)

    -- initialize post processing
    if yg.interact.getBinary("Framebuffer") and not yg.postproc.isInitialized() then
        yg.postproc.init(32, 32)
    end
    -- shutdown post processing
    if not yg.interact.getBinary("Framebuffer") and yg.postproc.isInitialized() then
        yg.postproc.shutdown()
    end

    -- draw sprites
    if yg.postproc.isInitialized() then
        coords = yg.asset.getTexture("sprites"):getFrameCoords("heart", frameIdx)
        yg.gl.drawSprite(yg.asset.getTexture("sprites"), coords, 6, 6, 0, 0, 0);

        coords = yg.asset.getTexture("sprites"):getFrameCoords("flame", frameIdx)
        yg.gl.drawSprite(yg.asset.getTexture("sprites"), coords, 16, 16, 0, 0, 0);

        coords = yg.asset.getTexture("sprites"):getFrameCoords("flame2", frameIdx)
        yg.gl.drawSprite(yg.asset.getTexture("sprites"), coords, 26, 26, 0, 0, 0);
    else
        coords = yg.asset.getTexture("sprites"):getFrameCoords("heart", frameIdx)
        yg.gl.drawSprite(yg.asset.getTexture("sprites"), coords, 150, 150, 100, 100, 0);
        
        coords = yg.asset.getTexture("sprites"):getFrameCoords("flame", frameIdx)
        yg.gl.drawSprite(yg.asset.getTexture("sprites"), coords, 300, 150, 100, 100, 0);

        coords = yg.asset.getTexture("sprites"):getFrameCoords("flame2", frameIdx)
        yg.gl.drawSprite(yg.asset.getTexture("sprites"), coords, 450, 150, 100, 100, 0);
    end
end

function shutdown()
end
