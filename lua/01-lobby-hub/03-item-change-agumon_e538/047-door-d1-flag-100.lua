local local_0
if be:MDLgetRamNo() == 0 then
    be:sd("MODELCTRL", "g_d1door", 2, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT", 45)
    be:FLGset(100, 1)
    if be:FLGisOn(101) ~= 1 then
        for ramNo = 44, 73 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
elseif be:MDLgetRamNo() == 1 then
    be:sd("MODELCTRL", "g_d1door", 3, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 45)
    be:FLGset(101, 1)
    if be:FLGisOn(100) ~= 1 then
        for ramNo = 44, 73 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
elseif be:MDLgetRamNo() == 2 then
    be:sd("MODELCTRL", "g_d1door", 4, "SQ_SWOF", 15)
    be:sd("HITLANDMODEL", "doorwall05", 0, "ONHIT")
    be:sd("MODELCTRL", "g_d1door", 5, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
    be:FLGset(111, 1)
elseif be:MDLgetRamNo() == 3 then
    be:sd("MODELCTRL", "g_d1door", 6, "SQ_SWOF", 15)
    be:sd("HITLANDMODEL", "doorwall07", 0, "ONHIT")
    be:sd("MODELCTRL", "g_d1door", 7, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT", 45)
    be:FLGset(112, 1)
end
