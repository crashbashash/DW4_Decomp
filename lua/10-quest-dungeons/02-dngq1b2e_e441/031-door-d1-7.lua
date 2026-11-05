be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(130) ~= 1 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:FLGset(130, 1)
    if be:FLGisOn(133) ~= 1 then
        be:sd("MODELCTRL", "g_d1door", 2, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT", 45)
        be:FLGset(133, 1)
    else
        be:sd("MODELCTRL", "g_d1door", 2, "SQ_SWOF", 15)
        be:sd("HITLANDMODEL", "doorwall03", 0, "ONHIT", 30)
        be:FLGset(133, 0)
    end
    if be:FLGisOn(134) ~= 1 then
        be:sd("MODELCTRL", "g_d1door", 3, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 45)
        be:FLGset(134, 1)
    else
        be:sd("MODELCTRL", "g_d1door", 3, "SQ_SWOF", 15)
        be:sd("HITLANDMODEL", "doorwall04", 0, "ONHIT", 30)
        be:FLGset(134, 0)
    end
end
