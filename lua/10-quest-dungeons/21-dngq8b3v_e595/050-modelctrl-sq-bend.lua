local infoName = be:MDLgetInfoName()
local ramNo = be:MDLgetRamNo()
if be:MDLisStatus(infoName, ramNo, "BIND") == 0 then
    be:sd("MODELCTRL", infoName, ramNo, "SQ_BEND", 0)
end
