if be:MATisPlayer() == 1 then
    if be:FLGisOn(110) ~= 1 then
        be:sd("MODELCTRL", "g_d2door", 5, "SQ_SWON")
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 15)
        be:FLGset(110, 1)
    end
    be:MATsetRun(0)
end
