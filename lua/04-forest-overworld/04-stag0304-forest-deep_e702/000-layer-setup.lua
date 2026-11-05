if be:PLAYERgetPos() == 0 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 1 then
    funcStageIn("trans")
elseif be:PLAYERgetPos() == 2 then
    funcStageIn("stay")
end
if be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 27, 0, 0) == 1 then
    if local_0 >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a00")
    elseif local_0 >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a01")
    elseif local_0 >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a02")
    elseif local_0 >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a03")
    elseif local_0 >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a04")
    elseif local_0 >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a05")
    end
elseif be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 28, 0, 0) == 1 then
    if local_0 >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a00")
    elseif local_0 >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a01")
    elseif local_0 >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a02")
    elseif local_0 >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a03")
    elseif local_0 >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a04")
    elseif local_0 >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a05")
    end
elseif be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 29, 0, 0) == 1 then
    if local_0 >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a00")
    elseif local_0 >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a01")
    elseif local_0 >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a02")
    elseif local_0 >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a03")
    elseif local_0 >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a04")
    elseif local_0 >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a05")
    end
elseif be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 29, 0, 0) == 0 and be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 28, 0, 0) == 0 and be:SYSctlDeviceFolder("ISEQUIP", 0, "armor2", 27, 0, 0) == 0 then
    if local_0 >= 61 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a00")
    elseif local_0 >= 41 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a01")
    elseif local_0 >= 25 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a02")
    elseif local_0 >= 13 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a03")
    elseif local_0 >= 5 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a04")
    elseif local_0 >= 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-a05")
    end
end
funcPlayerStatusSet()
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN60", 5)
