be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 then
    if be:FLGisOn(122) == 0 and be:FLGisOn(123) == 1 then
        be:sd("MODELCTRL", "g_d2door", 0, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT", 45)
        be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
    end
    be:FLGset(122, 1)
elseif be:MDLgetRamNo() == 1 then
    if be:FLGisOn(123) == 0 and be:FLGisOn(122) == 1 then
        be:sd("MODELCTRL", "g_d2door", 0, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT", 45)
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
        be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
    end
    be:FLGset(123, 1)
end
