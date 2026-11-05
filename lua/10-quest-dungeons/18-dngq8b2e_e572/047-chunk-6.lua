if be:MATisPlayer() == 1 then
    if be:FLGisOn(186) ~= 1 and be:FLGisOn(8, be:FLGisOn(), be, 179) ~= 1 then
        for local_1 = 13, 18 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
    end
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    if be:FLGisOn(152) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-09", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-09", 1)
end
