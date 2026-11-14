if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    local local_0
    for ramNo = 8, 10 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
    if be:FLGisOn(143) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-05", 1)
    end
end
