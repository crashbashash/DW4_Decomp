be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 then
    be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_POWEROF")
    be:MDLsetSeq("SQ_ONLOOP")
    if be:FLGisOn(125) == 1 then
        be:sd("MODELCTRL", "g_d3door", 5, "SQ_SWOF", 30)
        be:sd("HITLANDMODEL", "doorwall06", 0, "ONHIT", 0)
        be:FLGset(125, 0)
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_POWERON", 120)
    else
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_POWERON", 30)
    end
end
if be:MDLgetRamNo() == 1 then
    be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_POWEROF")
    be:MDLsetSeq("SQ_ONLOOP")
    be:sd("MODELCTRL", "g_d3door", 5, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
    be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_POWERON", 120)
    be:FLGset(125, 1)
end
