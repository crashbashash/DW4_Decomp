be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(102) == 0 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:sd("MODELCTRL", "g_d1door", 0, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT", 45)
    be:FLGset(102, 1)
    if be:FLGisOn(104) ~= 1 then
        for local_3 = 0, 1 do
            be:sd("MODELCTRL", "g_dcap", local_3, "SQ_DDMG")
        end
    end
end
if be:MDLgetRamNo() == 1 and be:FLGisOn(103) == 0 and be:FLGisOn(105) ~= 1 then
    for local_3 = 2, 3 do
        be:sd("MODELCTRL", "g_dcap", local_3, "SQ_DDMG")
    end
end
