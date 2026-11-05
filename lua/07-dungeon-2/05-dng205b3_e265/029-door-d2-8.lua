be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(206) == 0 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:sd("MODELCTRL", "g_d2door", 3, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 45)
    be:FLGset(206, 1)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(207) == 0 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:sd("MODELCTRL", "g_d2door", 5, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
    be:FLGset(207, 1)
elseif be:MDLgetRamNo() == 2 and be:FLGisOn(210) == 0 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:sd("MODELCTRL", "g_d2door", 8, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT", 45)
    be:FLGset(210, 1)
elseif be:MDLgetRamNo() == 3 and be:FLGisOn(211) == 0 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:sd("MODELCTRL", "g_d2door", 10, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT", 45)
    be:FLGset(211, 1)
elseif be:MDLgetRamNo() == 4 and be:FLGisOn(212) == 0 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:sd("MODELCTRL", "g_d2door", 12, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall13", 0, "OFFHIT", 45)
    be:FLGset(212, 1)
elseif be:MDLgetRamNo() == 5 and be:FLGisOn(213) == 0 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:sd("MODELCTRL", "g_d2door", 14, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall15", 0, "OFFHIT", 45)
    be:FLGset(213, 1)
end
