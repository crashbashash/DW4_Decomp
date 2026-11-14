local infoName = be:MDLgetInfoName()
local ramNo = be:MDLgetRamNo()
if be:MDLisStatus(infoName, ramNo, "BIND") == 0 then
    be:sd("MODELCTRL", infoName, ramNo, "SQ_SWOF", 0)
end
