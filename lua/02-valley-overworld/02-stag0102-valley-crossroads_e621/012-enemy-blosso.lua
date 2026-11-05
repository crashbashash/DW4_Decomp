if be:MATisAllPlayer() == 1 and be:FLGisOn(66) == 0 and g_IFLG04 ~= 1 then
    g_IFLG04 = 1
    be:sd("HITLANDMODEL", "hitbrossgatez010", 0, "ONHIT")
    be:sd("MODELCTRL", "g_brossgatez01", 0, "SQ_SWON")
    be:sd("GENERATER", nil, -1, "START", "GENE-38")
    be:sd("MODELCTRL", "i_bosshp10", 0, "GENERATE", "V<0,205,0>/SQ_OPEN")
    be:sd("METERCTRL", "bshp10", 0, "SETMODELHP", "e_blosso/I<0>", 10)
end
