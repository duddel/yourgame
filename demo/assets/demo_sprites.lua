function init()
    yg.control.enableVSync(true)
    yg.gl.clearColor(0.137, 0.255, 0.615, 1.000)

    -- register interact values
    yg.interact.addNumber("frame rate", "Hz", 10, 0, 60)

    -- load sprite sheet
    yg.asset.loadTexture("sprites", "a//sprites.png", "a//sprites.json", "diffuse", "nearest", "repeat", true)

    timer = 0
end

function tick()
    -- calc frame index
    timer = timer + (yg.time.getDelta() * yg.interact.getNumber("frame rate"))
    frameIdx = math.floor(timer)

    -- draw sprites
    coords = yg.asset.getTexture("sprites"):getFrameCoords("heart", frameIdx)
    yg.gl.drawSprite(yg.asset.getTexture("sprites"), coords, 150, 150, 100, 100, 0);
    
    coords = yg.asset.getTexture("sprites"):getFrameCoords("flame", frameIdx)
    yg.gl.drawSprite(yg.asset.getTexture("sprites"), coords, 300, 150, 100, 100, 0);

    coords = yg.asset.getTexture("sprites"):getFrameCoords("flame2", frameIdx)
    yg.gl.drawSprite(yg.asset.getTexture("sprites"), coords, 450, 150, 100, 100, 0);
end

function shutdown()
end
