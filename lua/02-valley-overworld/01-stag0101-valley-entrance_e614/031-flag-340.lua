if be:MATisPlayer() == 1 and be:FLGisOn(340) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 3, "SQ_POWERON")
    be:sd("MODELCTRL", "g_rockdownz01", 3, "SQ_ATCK1", 15)
    be:FLGset(340, 1)
end
