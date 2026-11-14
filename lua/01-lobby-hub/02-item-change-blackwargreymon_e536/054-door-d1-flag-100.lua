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
end
