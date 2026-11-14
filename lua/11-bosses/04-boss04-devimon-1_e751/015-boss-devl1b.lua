local ramNo = be:MDLgetRamNo()
if ramNo == 0 then
    if be:MDLisLive("f_devl1b", ramNo) == 1 and g_bPosCheck0 == 0 then
        be:sd("MODELCTRL", "f_devl1b", ramNo, "SQ_DROUND1")
    end
elseif ramNo == 1 then
    if be:MDLisLive("f_devl1b", ramNo) == 1 and g_bPosCheck1 == 0 then
        be:sd("MODELCTRL", "f_devl1b", ramNo, "SQ_DROUND1")
    end
elseif ramNo == 2 and be:MDLisLive("f_devl1b", ramNo) == 1 and g_bPosCheck2 == 0 then
    be:sd("MODELCTRL", "f_devl1b", ramNo, "SQ_DROUND1")
end
