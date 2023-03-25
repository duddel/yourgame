function init()
    yg.control.enableVSync(true)
    yg.gl.clearColor(1, 1, 1, 1)

    -- load main texture atlas and get coord infos
    yg.asset.loadTexture("main", "a//sprites_main.png", "a//sprites_main.json", "diffuse", "linear", "repeat", true)
    coordsMenu = yg.asset.getTexture("main"):getCoords("menu")
    coordsLoad = yg.asset.getTexture("main"):getCoords("loading")
end

function tick()
    if yg.input.get("WINDOW_ASPECT_RATIO") > 1 then
        splashWidthFac = 0.5
    else
        splashWidthFac = 0.8
    end

    -- draw the menu
    screenPos = yg.gl.drawSprite(yg.asset.getTexture("main"), coordsMenu,
                                    yg.input.get("WINDOW_WIDTH") * 0.5,
                                    yg.input.get("WINDOW_HEIGHT") * 0.5,
                                    yg.input.get("WINDOW_WIDTH") * splashWidthFac, 0, 0)

    aabbSprites = {}
    aabbSprites[1] = screenPos[1]
    aabbSprites[2] = screenPos[1] + ((screenPos[2] - screenPos[1]) * 0.333)
    aabbSprites[3] = screenPos[3]
    aabbSprites[4] = screenPos[3] + ((screenPos[4] - screenPos[3]) * 0.424)

    aabbPhysics = {}
    aabbPhysics[1] = screenPos[1] + ((screenPos[2] - screenPos[1]) * 0.333)
    aabbPhysics[2] = screenPos[1] + ((screenPos[2] - screenPos[1]) * 0.666)
    aabbPhysics[3] = screenPos[3]
    aabbPhysics[4] = screenPos[3] + ((screenPos[4] - screenPos[3]) * 0.424)

    -- detect clicks
    if yg.input.getDelta("MOUSE_BUTTON_1") > 0 then
        if hitAabb2(aabbSprites, yg.input.get("MOUSE_X"), yg.input.get("MOUSE_Y")) then
            runAnotherScript = "a//demo_sprites.lua"
        end
        if hitAabb2(aabbPhysics, yg.input.get("MOUSE_X"), yg.input.get("MOUSE_Y")) then
            runAnotherScript = "a//demo_physics.lua"
        end
    end

    -- render loading sign if running new script in next cycle
    if runAnotherScript then
        yg.gl.drawSprite(yg.asset.getTexture("main"), coordsLoad,
                                        yg.input.get("WINDOW_WIDTH") * 0.5,
                                        yg.input.get("WINDOW_HEIGHT") * 0.5,
                                        yg.input.get("WINDOW_WIDTH") * splashWidthFac * 0.5, 0, 0)

        yg.control.runScript(runAnotherScript)
    end
end

function hitAabb2(aabb, x, y)
    return x >= aabb[1] and x <= aabb[2] and y >= aabb[3] and y <= aabb[4]
end
