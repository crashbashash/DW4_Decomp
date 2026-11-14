if be:MATisPlayer() == 1 then
    local local_0
    if be:FLGisOn(186) ~= 1 then
        be:FLGset(186, 1)
        if be:FLGisOn(178) ~= 1 then
            for ramNo = 8, 12 do
                be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
            end
        end
        if be:FLGisOn(179) ~= 1 then
            for ramNo = 13, 18 do
                be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
            end
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
