if local_0 == 0 then
    if be:MDLisLive("f_devl1b", local_0) == 1 and g_bPosCheck0 == 0 then
        be:sd("MODELCTRL", "f_devl1b", local_0, "SQ_DROUND1")
    else
    end
end
if local_0 == 1 then
    if be:MDLisLive("f_devl1b", local_0) == 1 and g_bPosCheck1 == 0 then
        be:sd("MODELCTRL", "f_devl1b", local_0, "SQ_DROUND1")
    else
    end
end
if local_0 == 2 and be:MDLisLive("f_devl1b", local_0) == 1 and g_bPosCheck2 == 0 then
    be:sd("MODELCTRL", "f_devl1b", local_0, "SQ_DROUND1")
end
