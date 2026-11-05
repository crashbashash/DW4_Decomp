if not g_Ground then
    g_Ground = 0
end
if be:MDLisCallName("FLYSET") == 1 then
    g_Ground = 0
elseif be:MDLisCallName("GROUND") == 1 then
    g_Ground = 1
elseif be:MDLisCallName("FLY") == 1 then
    g_Ground = 0
end
