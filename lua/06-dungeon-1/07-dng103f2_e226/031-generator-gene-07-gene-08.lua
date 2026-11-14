if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    if be:FLGisOn(129) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-07", 1)
    end
    if be:FLGisOn(130) ~= 1 and g_matg06 == 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-08", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-07", 1)
    be:sd("GENERATER", nil, -1, "STOP", "GENE-08", 1)
end
