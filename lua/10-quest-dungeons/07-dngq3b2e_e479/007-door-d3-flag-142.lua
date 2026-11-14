if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    if be:FLGisOn(142) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 5, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall06", 0, "ONHIT")
        be:FLGset(142, 1)
    end
    if be:FLGisOn(129) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-08", 1)
    end
end
if be:SYSgetDifficulty() > 0 then
    if be:MATisPlayer() == 1 then
        if be:FLGisOn(121) == 1 and be:FLGisOn(134) ~= 1 then
            if be:FLGisOn(129) == 1 then
                be:sd("GENERATER", nil, -1, "START", "GENE-13", 1)
            end
            if be:FLGisOn(144) ~= 1 then
                be:sd("MODELCTRL", "g_d3door", 9, "SQ_SWOF")
                be:sd("HITLANDMODEL", "doorwall10", 0, "ONHIT")
                be:FLGset(144, 1)
            end
        end
    else
        be:sd("GENERATER", nil, -1, "STOP", "GENE-13", 1)
    end
end
