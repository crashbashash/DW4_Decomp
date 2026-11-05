if be:MDLgetRamNo() == 0 then
    be:sd("MODELCTRL", "g_d4door", 5, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
end
