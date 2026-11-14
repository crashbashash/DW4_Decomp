if be:MDLgetRamNo() == 0 and be:FLGisOn(121) == 0 then
    be:sd("MODELCTRL", "g_dtdoor", 1, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT", 45)
    be:sd("MODELCTRL", "g_dtdoor", 2, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT", 45)
    be:FLGset(121, 1)
end
