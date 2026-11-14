local random = be:SYSgetRandom(122)
if be:MATisAllPlayer() == 1 and g_IFLG05 ~= 1 and be:FLGisOn(63) == 1 then
    if random >= 49 then
        be:sd("GENERATER", nil, -1, "START", "GENE-s01")
    elseif random >= 27 then
        be:sd("GENERATER", nil, -1, "START", "GENE-s02")
    elseif random >= 11 then
        be:sd("GENERATER", nil, -1, "START", "GENE-s03")
    elseif random >= 3 then
        be:sd("GENERATER", nil, -1, "START", "GENE-s04")
    elseif random <= 2 then
        be:sd("GENERATER", nil, -1, "START", "GENE-s05")
    end
    be:sd("GENERATER", "", -1, "START", "GENE-67", 60)
    be:sd("HITLANDMODEL", "hitlift030", 0, "ONHIT")
    be:sd("MODELCTRL", "g_lift03z02", 0, "SQ_SWOF", 30)
    be:sd("MODELCTRL", "g_lift03az02", 0, "SQ_SWOF")
    be:sd("MODELCTRL", "g_lift03bz02", 0, "SQ_SWOF")
    be:sd("MODELCTRL", "i_bosshp12", 0, "GENERATE", "V<0,205,0>/SQ_OPEN")
    be:sd("METERCTRL", "bshp12", 0, "SETMODELHP", "e_skulgrey/I<0>", 10)
    g_IFLG05 = 1
end
