be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(137) == 0 and be:FLGisOn(121) == 1 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:sd("MODELCTRL", "g_d3door", 11, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT", 45)
    be:FLGset(137, 1)
end
