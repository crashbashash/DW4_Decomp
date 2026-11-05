be:sd("MODELCTRL", "g_d2door", 2, "SQ_SWON", 30)
be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT", 45)
if be:FLGisOn(143) ~= 1 then
    for local_1 = 42, 46 do
        be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
    end
end
be:FLGset(129, 1)
be:sd("GENERATER", nil, -1, "START", "GENE-11")
