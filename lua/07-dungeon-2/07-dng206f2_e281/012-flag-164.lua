be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(164) == 0 then
    if be:FLGisOn(165) == 1 then
        be:sd("MODELCTRL", "g_dtdoor", 0, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT", 45)
    end
    be:FLGset(164, 1)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(165) == 0 then
    if be:FLGisOn(164) == 1 then
        be:sd("MODELCTRL", "g_dtdoor", 0, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT", 45)
    end
    be:FLGset(165, 1)
end
