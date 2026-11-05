if be:MATisPlayer() == 1 then
    if g_dcap ~= 1 then
        for local_1 = 0, 11 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
        g_dcap = 1
    end
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-08")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    if be:FLGisOn(120) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-05", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-05", 1)
