be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(244) ~= 1 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:FLGset(244, 1)
    be:sd("MODELCTRL", "g_dbutton1", 7, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d4door", 13, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall14", 0, "OFFHIT", 45)
end
