function init()
    yg.control.enableVSync(true)
    yg.gl.clearColor(1, 1, 1, 1)
    yg.asset.loadTexture("splash", "a//demo_splash.png", "", "diffuse", "linear", "repeat", true)
    -- get coords for the entire texture, to draw it with drawSprite()
    coordsSplash = yg.asset.getTexture("splash"):getGridCoords(1, 1, 0)
end

function tick()
    if yg.input.get("WINDOW_ASPECT_RATIO") > 1 then
        splashWidthFac = 0.5
    else
        splashWidthFac = 0.8
    end

    -- draw the actual texture
    screenPos = yg.gl.drawSprite(yg.asset.getTexture("splash"), coordsSplash,
                                    yg.input.get("WINDOW_WIDTH") * 0.5,
                                    yg.input.get("WINDOW_HEIGHT") * 0.5,
                                    yg.input.get("WINDOW_WIDTH") * splashWidthFac, 0, 0)

    aabbSprites = {}
    aabbSprites[1] = screenPos[1]
    aabbSprites[2] = screenPos[1] + ((screenPos[2] - screenPos[1]) * 0.333)
    aabbSprites[3] = screenPos[3]
    aabbSprites[4] = screenPos[3] + ((screenPos[4] - screenPos[3]) * 0.5)

    aabbPhysics = {}
    aabbPhysics[1] = screenPos[1] + ((screenPos[2] - screenPos[1]) * 0.333)
    aabbPhysics[2] = screenPos[1] + ((screenPos[2] - screenPos[1]) * 0.666)
    aabbPhysics[3] = screenPos[3]
    aabbPhysics[4] = screenPos[3] + ((screenPos[4] - screenPos[3]) * 0.5)

    -- detect clicks
    if yg.input.getDelta("MOUSE_BUTTON_1") > 0 then
        if hitAabb2(aabbSprites, yg.input.get("MOUSE_X"), yg.input.get("MOUSE_Y")) then
            yg.control.runScript("a//demo_sprites.lua")
        end
        if hitAabb2(aabbPhysics, yg.input.get("MOUSE_X"), yg.input.get("MOUSE_Y")) then
            yg.control.runScript("a//demo_physics.lua")
        end
    end
end

function hitAabb2(aabb, x, y)
    return x >= aabb[1] and x <= aabb[2] and y >= aabb[3] and y <= aabb[4]
end
