if be:MATisPlayer() == 1 then
    if be:FLGisOn(159) ~= 1 then
        if g_door10 ~= 1 then
            be:sd("MODELCTRL", "g_d4door", 9, "SQ_SWOF")
            be:sd("HITLANDMODEL", "doorwall10", 0, "ONHIT")
            g_door10 = 1
        end
        be:sd("GENERATER", nil, -1, "START", "GENE-16")
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-16")
end
