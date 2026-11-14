if be:SYSgetPlayerNinzu() ~= 1 then
    if be:SYSgetPlayerNinzu() == 2 then
    end
end
if g_IFLG20 ~= 1 then
    g_IFLG20 = 1
    if be:MDLgetRamNo() == 0 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-54")
    elseif be:MDLgetRamNo() == 1 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-16")
    elseif be:MDLgetRamNo() == 2 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-19")
    end
elseif g_IFLG20 == 1 and g_IFLG21 ~= 1 then
    g_IFLG21 = 1
    if be:MDLgetRamNo() == 0 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-54")
    elseif be:MDLgetRamNo() == 1 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-16")
    elseif be:MDLgetRamNo() == 2 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-19")
    end
elseif g_IFLG20 == 1 and g_IFLG21 == 1 and g_IFLG22 ~= 1 then
    g_IFLG22 = 1
    if be:MDLgetRamNo() == 0 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-54")
    elseif be:MDLgetRamNo() == 1 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-16")
    elseif be:MDLgetRamNo() == 2 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-19")
    end
elseif g_IFLG20 == 1 and g_IFLG21 == 1 and g_IFLG22 == 1 and g_IFLG23 ~= 1 then
    g_IFLG23 = 1
    if be:MDLgetRamNo() == 0 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-54")
    elseif be:MDLgetRamNo() == 1 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-16")
    elseif be:MDLgetRamNo() == 2 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-19")
    end
elseif g_IFLG20 == 1 and g_IFLG21 == 1 and g_IFLG22 == 1 and g_IFLG23 == 1 and g_IFLG24 ~= 1 then
    g_IFLG24 = 1
    if be:MDLgetRamNo() == 0 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-54")
    elseif be:MDLgetRamNo() == 1 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-16")
    elseif be:MDLgetRamNo() == 2 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-19")
    end
elseif g_IFLG20 == 1 and g_IFLG21 == 1 and g_IFLG22 == 1 and g_IFLG23 == 1 and g_IFLG24 == 1 and g_IFLG25 ~= 1 then
    g_IFLG25 = 1
    if be:MDLgetRamNo() == 0 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-54")
    elseif be:MDLgetRamNo() == 1 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-16")
    elseif be:MDLgetRamNo() == 2 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-19")
    end
elseif g_IFLG20 == 1 and g_IFLG21 == 1 and g_IFLG22 == 1 and g_IFLG23 == 1 and g_IFLG24 == 1 and g_IFLG25 == 1 and g_IFLG26 ~= 1 then
    g_IFLG26 = 1
    if be:MDLgetRamNo() == 0 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-54")
    elseif be:MDLgetRamNo() == 1 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-16")
    elseif be:MDLgetRamNo() == 2 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-19")
    end
elseif g_IFLG20 == 1 and g_IFLG21 == 1 and g_IFLG22 == 1 and g_IFLG23 == 1 and g_IFLG24 == 1 and g_IFLG25 == 1 and g_IFLG26 == 1 and g_IFLG27 ~= 1 then
    g_IFLG27 = 1
    be:sd("MODELCTRL", "g_numez01", 0, "SQ_POWEROF", 75)
    be:sd("MODELCTRL", "g_numez01", 1, "SQ_POWEROF", 75)
    be:sd("MODELCTRL", "g_numez01", 2, "SQ_POWEROF", 75)
    if be:MDLgetRamNo() == 0 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-54")
    elseif be:MDLgetRamNo() == 1 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-16")
    elseif be:MDLgetRamNo() == 2 then
        be:sd("GENERATER", nil, -1, "RESTART", "GENE-19")
    else
    end
end
