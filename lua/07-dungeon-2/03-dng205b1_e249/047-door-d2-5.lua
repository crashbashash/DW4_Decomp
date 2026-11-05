be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 then
    if be:FLGisOn(125) == 0 and be:FLGisOn(126) == 1 then
        be:sd("MODELCTRL", "g_d2door", 7, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT", 45)
        be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
    end
    be:FLGset(125, 1)
elseif be:MDLgetRamNo() == 1 then
    if be:FLGisOn(126) == 0 and be:FLGisOn(125) == 1 then
        be:sd("MODELCTRL", "g_d2door", 7, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT", 45)
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
        be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
    end
    be:FLGset(126, 1)
end
