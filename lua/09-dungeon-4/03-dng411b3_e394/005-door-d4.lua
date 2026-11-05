if be:MATisAllPlayer() == 1 and be:FLGisOn(155) ~= 1 then
    if g_door16 ~= 1 then
        be:sd("MODELCTRL", "g_d4door", 15, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall16", 0, "ONHIT")
        g_door16 = 1
    end
    be:sd("GENERATER", nil, -1, "START", "GENE-22", 1)
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-20")
end
