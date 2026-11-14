if not g_FIYCHACK then
    g_FIYCHACK = 0
end
if be:MDLisCallName("CHACK") == 1 then
    if be:MDLisStatus(be:MDLgetInfoName(), be:MDLgetRamNo(), "BIND") == 0 then
        g_FBSwitch = 0
        be:sd("MODELCTRL", "f_devl3", 0, "SQ_BEND", 0)
    else
        be:sd("MODELCTRL", "f_devl3", 0, "SQ_WAIT", 0)
    end
elseif be:MDLisCallName("FLYSET") == 1 then
    g_FIYCHACK = 0
elseif be:MDLisCallName("GROUND") == 1 then
    g_FIYCHACK = 0
elseif be:MDLisCallName("FLY") == 1 then
    g_FIYCHACK = 1
end
