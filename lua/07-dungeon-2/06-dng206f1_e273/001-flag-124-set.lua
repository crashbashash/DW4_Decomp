be:MDLsetDMGTurn(0)
local local_0 = 0
if be:MDLgetRamNo() == 0 and be:FLGisOn(124) == 0 then
    local_0 = 1
    be:FLGset(124, 1)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(125) == 0 then
    local_0 = 1
    be:FLGset(125, 1)
end
if local_0 + be:FLGisOn(124) + be:FLGisOn(125) == 3 then
    be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_dtdoor", 11, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT", 45)
end
