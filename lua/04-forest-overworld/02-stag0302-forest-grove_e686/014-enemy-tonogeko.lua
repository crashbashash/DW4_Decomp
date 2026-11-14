local random = be:SYSgetRandom(122)
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
be:sd("MODELCTRL", "i_bosshp14", 0, "GENERATE", "V<0,205,0>/SQ_OPEN")
be:sd("METERCTRL", "bshp14", 0, "SETMODELHP", "e_tonogeko/I<0>", 10)
