be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(204) == 0 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:FLGset(204, 1)
    be:sd("MODELCTRL", "g_d4door", 4, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(205) == 0 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:FLGset(205, 1)
    be:sd("MODELCTRL", "g_d4door", 8, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT", 45)
elseif be:MDLgetRamNo() == 2 and be:FLGisOn(206) == 0 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:FLGset(206, 1)
    be:sd("MODELCTRL", "g_d4door", 10, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT", 45)
end
