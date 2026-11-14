if be:PLAYERgetPos() == 0 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 1 then
    funcStageIn("trans")
elseif be:PLAYERgetPos() == 2 then
    funcStageIn("stay")
end
if be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 27, 0, 0) == 1 then
    local random = be:SYSgetRandom(300)
    if random >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a00")
    elseif random >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a01")
    elseif random >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a02")
    elseif random >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a03")
    elseif random >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a04")
    elseif random >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a05")
    end
elseif be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 28, 0, 0) == 1 then
    local random = be:SYSgetRandom(240)
    if random >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a00")
    elseif random >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a01")
    elseif random >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a02")
    elseif random >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a03")
    elseif random >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a04")
    elseif random >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a05")
    end
elseif be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 29, 0, 0) == 1 then
    local random = be:SYSgetRandom(180)
    if random >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a00")
    elseif random >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a01")
    elseif random >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a02")
    elseif random >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a03")
    elseif random >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a04")
    elseif random >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a05")
    end
elseif be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 29, 0, 0) == 0 and be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 28, 0, 0) == 0 and be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 27, 0, 0) == 0 then
    local random = be:SYSgetRandom(420)
    if random >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a00")
    elseif random >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a01")
    elseif random >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a02")
    elseif random >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a03")
    elseif random >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a04")
    elseif random >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a05")
    end
end
funcPlayerStatusSet()
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN60", 5)
