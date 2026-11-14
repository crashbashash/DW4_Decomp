local local_0
if be:SYSgetPlayerNinzu() <= 3 then
    if be:MDLgetRamNo() == 0 then
        if g_button01 ~= 1 and g_button04 == 1 then
            be:MDLsetSeq("SQ_ONLOOP")
            be:sd("MODELCTRL", "g_dbutton2", 3, "SETLABEL", "SQ_SWOF/OFF")
            be:sd("MODELCTRL", "g_dbutton2", 3, "SQ_ONLOOP")
        elseif g_button01 ~= 1 and g_button04 ~= 1 then
            be:MDLsetSeq("SQ_ONLOOP")
            be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_SWOF", 90)
        end
        g_button01 = 1
    elseif be:MDLgetRamNo() == 1 then
        if g_button02 ~= 1 and g_button03 == 1 then
            be:MDLsetSeq("SQ_ONLOOP")
            be:sd("MODELCTRL", "g_dbutton2", 2, "SETLABEL", "SQ_SWOF/OFF")
            be:sd("MODELCTRL", "g_dbutton2", 2, "SQ_ONLOOP")
        elseif g_button02 ~= 1 and g_button03 ~= 1 then
            be:MDLsetSeq("SQ_ONLOOP")
            be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_SWOF", 90)
        end
        g_button02 = 1
    elseif be:MDLgetRamNo() == 2 then
        if g_button03 ~= 1 and g_button02 == 1 then
            be:MDLsetSeq("SQ_ONLOOP")
            be:sd("MODELCTRL", "g_dbutton2", 1, "SETLABEL", "SQ_SWOF/OFF")
            be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
        elseif g_button03 ~= 1 and g_button02 ~= 1 then
            be:MDLsetSeq("SQ_ONLOOP")
            be:sd("MODELCTRL", "g_dbutton2", 2, "SQ_SWOF", 90)
        end
        g_button03 = 1
    elseif be:MDLgetRamNo() == 3 then
        if g_button04 ~= 1 and g_button01 == 1 then
            be:MDLsetSeq("SQ_ONLOOP")
            be:sd("MODELCTRL", "g_dbutton2", 0, "SETLABEL", "SQ_SWOF/OFF")
            be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
        elseif g_button04 ~= 1 and g_button01 ~= 1 then
            be:MDLsetSeq("SQ_ONLOOP")
            be:sd("MODELCTRL", "g_dbutton2", 3, "SQ_SWOF", 90)
        end
        g_button04 = 1
    end
elseif be:MDLgetRamNo() == 0 then
    g_button01 = 1
elseif be:MDLgetRamNo() == 1 then
    g_button02 = 1
elseif be:MDLgetRamNo() == 2 then
    g_button03 = 1
elseif be:MDLgetRamNo() == 3 then
    g_button04 = 1
end
local count = 0
if g_button01 == 1 then
    count = count + 1
end
if g_button02 == 1 then
    count = count + 1
end
if g_button03 == 1 then
    count = count + 1
end
if g_button04 == 1 then
    count = count + 1
end
if count == 4 then
    for ramNo = 0, 3 do
        be:sd("MODELCTRL", "g_dbutton2", ramNo, "SQ_ONLOOP")
    end
    be:sd("MODELCTRL", "g_d3door", 4, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
    be:FLGset(161, 1)
end
