be:MDLsetDMGTurn(0)
if be:SYSgetPlayerNinzu() == 1 then
    local_0 = 160
else
    local_0 = 15
end
if be:MDLgetRamNo() == 0 then
    if g_wbutton01 ~= 1 then
        be:sd("MODELCTRL", local_2, local_1, "SQ_WAIT", 0)
        be:MDLsetSeq("SQ_SWON")
        g_wbutton01 = 1
        if g_wbutton02 == 1 then
            be:sd("MODELCTRL", "g_d2door", 4, "SQ_SWON", 30)
            be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
            be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_ONLOOP")
            be:FLGset(126, 1)
        else
            be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_SWOF", local_0)
        end
    end
end
if be:MDLgetRamNo() == 1 and g_wbutton02 ~= 1 then
    be:sd("MODELCTRL", local_2, local_1, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    g_wbutton02 = 1
    if g_wbutton01 == 1 then
        be:sd("MODELCTRL", "g_d2door", 4, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
        be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_ONLOOP")
        be:FLGset(126, 1)
    else
        be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_SWOF", local_0)
    end
end
