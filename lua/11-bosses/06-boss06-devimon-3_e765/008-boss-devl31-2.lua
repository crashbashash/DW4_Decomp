if not g_31ram0 then
    g_31ram0 = 0
end
if not g_31ram1 then
    g_31ram1 = 0
end
if be:MDLgetRamNo() == 0 then
    if g_31ram0 == 2 then
        g_31ram0 = 0
        be:sd("MODELCTRL", "f_devl31", 0, "SQ_EXIT")
    else
        g_31ram0 = g_31ram0 + 1
        be:sd("MODELCTRL", "f_devl31", 0, "SQ_WAIT")
    end
end
if be:MDLgetRamNo() == 1 then
    if g_31ram1 == 2 then
        g_31ram1 = 0
        be:sd("MODELCTRL", "f_devl31", 1, "SQ_EXIT")
    else
        g_31ram1 = g_31ram1 + 1
        be:sd("MODELCTRL", "f_devl31", 1, "SQ_WAIT")
    end
end
