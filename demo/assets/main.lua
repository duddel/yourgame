function init()
    yg.control.enableVSync(true)
    yg.gl.clearColor(1, 1, 1, 1)
    yg.asset.loadTexture("splash", "a//demo_splash.png", "a//demo_splash.json",
                         "diffuse", "linear", "repeat", true)
end

function tick()
    -- todo generate default coords for regular 1-sprite textures
    coords = yg.asset.getTexture("splash"):getCoords("demo_splash")

    if yg.input.get("WINDOW_ASPECT_RATIO") > 1 then
        splashWidthFac = 0.5
    else
        splashWidthFac = 0.8
    end

    -- calculate splash position and size
    splashAspectInv = 694 / 1080 -- demo_splash.png pixel size
    splashSim = {} -- xmin, xmax, ymin, ymax
    splashSim[1] = (yg.input.get("WINDOW_WIDTH") - yg.input.get("WINDOW_WIDTH") *
        splashWidthFac) * 0.5
    splashSim[2] = (yg.input.get("WINDOW_WIDTH") + yg.input.get("WINDOW_WIDTH") *
        splashWidthFac) * 0.5
    splashSim[3] = (yg.input.get("WINDOW_HEIGHT") - yg.input.get("WINDOW_WIDTH") *
        splashWidthFac * splashAspectInv) * 0.5
    splashSim[4] = (yg.input.get("WINDOW_HEIGHT") + yg.input.get("WINDOW_WIDTH") *
        splashWidthFac * splashAspectInv) * 0.5

    aabbSprites = {}
    aabbSprites[1] = splashSim[1]
    aabbSprites[2] = splashSim[1] + (yg.input.get("WINDOW_WIDTH") * splashWidthFac * 0.333)
    aabbSprites[3] = splashSim[3]
    aabbSprites[4] = splashSim[3] + (yg.input.get("WINDOW_WIDTH") * splashWidthFac * splashAspectInv * 0.5)

    aabbPhysics = {}
    aabbPhysics[1] = splashSim[1] + (yg.input.get("WINDOW_WIDTH") * splashWidthFac * 0.333)
    aabbPhysics[2] = splashSim[1] + (yg.input.get("WINDOW_WIDTH") * splashWidthFac * 0.666)
    aabbPhysics[3] = splashSim[3]
    aabbPhysics[4] = splashSim[3] + (yg.input.get("WINDOW_WIDTH") * splashWidthFac * splashAspectInv * 0.5)

    -- draw the actual texture
    yg.gl.drawSprite(yg.asset.getTexture("splash"), coords,
                     yg.input.get("WINDOW_WIDTH") * 0.5,
                     yg.input.get("WINDOW_HEIGHT") * 0.5,
                     yg.input.get("WINDOW_WIDTH") * splashWidthFac, 0, 0)

    -- detect clicks
    if yg.input.getDelta("MOUSE_BUTTON_1") > 0 then
        if yg.input.get("MOUSE_X") > aabbSprites[1] and
            yg.input.get("MOUSE_X") < aabbSprites[2] and
            yg.input.get("MOUSE_Y") > aabbSprites[3] and
            yg.input.get("MOUSE_Y") < aabbSprites[4] then
                yg.control.runScript("a//demo_sprites.lua")
        end

        if yg.input.get("MOUSE_X") > aabbPhysics[1] and
            yg.input.get("MOUSE_X") < aabbPhysics[2] and
            yg.input.get("MOUSE_Y") > aabbPhysics[3] and
            yg.input.get("MOUSE_Y") < aabbPhysics[4] then
                yg.control.runScript("a//demo_physics.lua")
        end
    end
end
