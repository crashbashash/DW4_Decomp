if be:MATisPlayer() == 1 and be:FLGisOn(343) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 6, "SQ_POWERON")
    be:sd("MODELCTRL", "g_rockdownz01", 6, "SQ_ATCK1", 15)
    be:FLGset(343, 1)
end
