if be:MATisPlayer() == 1 and be:FLGisOn(347) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 10, "SQ_POWERON")
    be:sd("MODELCTRL", "g_rockdownz01", 10, "SQ_ATCK1", 15)
    be:FLGset(347, 1)
end
