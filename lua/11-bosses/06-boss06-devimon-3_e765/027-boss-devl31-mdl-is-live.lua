if be:MDLisCallName("BALL") == 1 then
    if be:MDLisLive("f_devl31", 0) == 0 and be:MDLisLive("f_devl31", 1) == 0 then
        be:sd("MODELCTRL", "f_devl31", 0, "GENERATE", "f_devl3/I<0>/" .. be:MDLgetPosStr(-30, 30, 100) .. "/V<0.0,0.0,0.0>/SQ_ENTR", 86)
        be:sd("MODELCTRL", "f_devl31", 1, "GENERATE", "f_devl3/I<0>/" .. be:MDLgetPosStr(30, 30, 100) .. "/V<0.0,0.0,0.0>/SQ_ENTR", 106)
    else
        be:sd("MODELCTRL", "f_devl3", 0, "SQ_WAIT")
    end
elseif be:MDLisCallName("WALLBK") == 1 then
    if be:MDLisLive("x_042fmagc01a", 0) == 1 and be:MDLisLive("x_042fmagc01a", 1) == 1 then
        be:sd("MODELCTRL", "f_devl3", 0, "SQ_WAIT")
    else
        be:sd("MODELCTRL", "f_devl3", 0, "SQ_BARRIERBK1")
    end
elseif be:MDLisCallName("WALLFR") == 1 then
    if be:MDLisLive("x_042fmagc01a", 0) == 1 and be:MDLisLive("x_042fmagc01a", 1) == 1 then
        be:sd("MODELCTRL", "f_devl3", 0, "SQ_WAIT")
    else
        be:sd("MODELCTRL", "f_devl3", 0, "SQ_BARRIERFR1")
    end
elseif be:MDLisCallName("BWALL") == 1 then
    if be:MDLisLive("x_042fmagc01a", 0) == 1 and be:MDLisLive("x_042fmagc01a", 1) == 1 then
        be:sd("MODELCTRL", "f_devl3", 0, "SQ_WAIT")
    else
        be:sd("MODELCTRL", "f_devl3", 0, "SQ_BARRIER1")
    end
end
