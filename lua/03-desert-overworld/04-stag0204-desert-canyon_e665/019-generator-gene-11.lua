if be:MATisPlayer() == 1 and be:FLGisOn(49) == 1 then
    be:sd("MODELCTRL", "g_cannon01", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_cannon01", 1, "SQ_POWERON")
    be:sd("MODELCTRL", "g_cannon01", 2, "SQ_POWERON")
    be:sd("MODELCTRL", "g_cannon01", 3, "SQ_POWERON")
end
if be:MATisAllPlayer() == 1 then
    if be:FLGisOn(49) == 0 and be:FLGisOn(50) == 0 and g_IFLG00 ~= 1 then
        g_IFLG00 = 1
        be:sd("MODELCTRL", "g_scorpiongatez02", 0, "SQ_SWOF")
        be:sd("HITLANDMODEL", "hitscorpiongatez020", 0, "ONHIT")
    elseif be:FLGisOn(49) == 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-11")
    end
end
