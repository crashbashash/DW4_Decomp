if be:MDLgetRamNo() == 0 then
    be:sd("MODELCTRL", "g_d1door", 2, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT", 45)
    be:FLGset(100, 1)
    if be:FLGisOn(101) ~= 1 then
        for local_1 = 44, 73 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
    end
end
if be:MDLgetRamNo() == 1 and be:FLGisOn(100) ~= 1 then
    for local_1 = 44, 73 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
