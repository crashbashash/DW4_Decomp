if be:SYSgetPlayerNinzu() <= 1 then
    if be:MDLgetRamNo() == 0 then
        if g_button01 ~= 1 and g_button02 == 1 then
            be:sd("MODELCTRL", "g_d2door", 6, "SQ_SWON", 30)
            be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT", 45)
            be:MDLsetSeq("SQ_ONLOOP")
            be:sd("MODELCTRL", "g_dbutton2", 1, "SETLABEL", "SQ_SWOF/OFF")
            be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
            be:FLGset(135, 1)
        elseif g_button01 ~= 1 then
            be:MDLsetSeq("SQ_ONLOOP")
            be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_SWOF", 120)
        end
        g_button01 = 1
    elseif be:MDLgetRamNo() == 1 then
        if g_button02 ~= 1 and g_button01 == 1 then
            be:sd("MODELCTRL", "g_d2door", 6, "SQ_SWON", 30)
            be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT", 45)
            be:MDLsetSeq("SQ_ONLOOP")
            be:sd("MODELCTRL", "g_dbutton2", 0, "SETLABEL", "SQ_SWOF/OFF")
            be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
            be:FLGset(135, 1)
        elseif g_button02 ~= 1 then
            be:MDLsetSeq("SQ_ONLOOP")
            be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_SWOF", 120)
        end
        g_button02 = 1
    end
elseif be:MDLgetRamNo() == 0 then
    if g_button01 ~= 1 and g_button02 == 1 then
        be:sd("MODELCTRL", "g_d2door", 6, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT", 45)
        be:MDLsetSeq("SQ_ONLOOP")
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
        be:FLGset(135, 1)
    end
    g_button01 = 1
elseif be:MDLgetRamNo() == 1 then
    if g_button02 ~= 1 and g_button01 == 1 then
        be:sd("MODELCTRL", "g_d2door", 6, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT", 45)
        be:MDLsetSeq("SQ_ONLOOP")
        be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
        be:FLGset(135, 1)
    end
    g_button02 = 1
end
