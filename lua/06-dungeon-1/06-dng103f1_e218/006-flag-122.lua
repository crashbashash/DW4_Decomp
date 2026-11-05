if be:MDLgetRamNo() == 0 then
    if g_button02 ~= 1 and g_button03 == 1 then
        be:sd("MODELCTRL", "g_dtdoor", 7, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT", 45)
        be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
        be:FLGset(122, 1)
    end
    g_button02 = 1
elseif be:MDLgetRamNo() == 1 then
    if g_button03 ~= 1 and g_button02 == 1 then
        be:sd("MODELCTRL", "g_dtdoor", 7, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT", 45)
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
        be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
        be:FLGset(122, 1)
    end
    g_button03 = 1
end
