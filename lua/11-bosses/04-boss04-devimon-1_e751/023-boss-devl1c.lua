g_UFOPos = be:SYSgetRandom(4)
if not g_DmgChk0 then
    g_DmgChk0 = 0
end
if not g_DmgChk1 then
    g_DmgChk1 = 0
end
if not g_DmgChk2 then
    g_DmgChk2 = 0
end
if g_UFOPos == 0 then
    be:sd("MODELCTRL", "f_devl1c", 0, "GENERATE", "V<40.0,50.0,-40.0>/V<0.0,0.0,0.0>/SQ_ENTR")
elseif g_UFOPos == 1 then
    be:sd("MODELCTRL", "f_devl1c", 0, "GENERATE", "V<40.0,50.0,40.0>/V<0.0,0.0,0.0>/SQ_ENTR")
elseif g_UFOPos == 2 then
    be:sd("MODELCTRL", "f_devl1c", 0, "GENERATE", "V<-40.0,50.0,40.0>/V<0.0,0.0,0.0>/SQ_ENTR")
elseif g_UFOPos == 3 then
    be:sd("MODELCTRL", "f_devl1c", 0, "GENERATE", "V<-40.0,50.0,-40.0>/V<0.0,0.0,0.0>/SQ_ENTR")
end
g_mecha4live = 3
g_DmgChk0 = 0
g_DmgChk1 = 0
g_DmgChk2 = 0
if g_f_devl1Pos ~= 0 and g_f_devl1Pos ~= 2 then
    if g_f_devl1Pos == 4 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-05")
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-07")
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-09")
    else
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-06")
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-08")
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-10")
    end
end
be:sd("GENERATER", nil, -1, "RESTART", "GENE-05")
be:sd("GENERATER", nil, -1, "RESTART", "GENE-07")
be:sd("GENERATER", nil, -1, "RESTART", "GENE-09")
