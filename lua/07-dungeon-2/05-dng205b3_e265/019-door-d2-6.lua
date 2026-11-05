if be:FLGisOn(220) ~= 1 then
    be:sd("GENERATER", nil, -1, "RESTART", "GENE-03", 1)
else
    be:FLGset(177, 1)
    if be:FLGisOn(190) + be:FLGisOn(191) + be:FLGisOn(192) == 3 then
        be:sd("MODELCTRL", "g_d2door", 4, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
    end
end
