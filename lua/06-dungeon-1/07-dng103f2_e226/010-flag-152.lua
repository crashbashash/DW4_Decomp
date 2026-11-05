be:MDLsetDMGTurn(0)
if be:SYSgetPlayerNinzu() == 1 then
    local_2 = 75
else
    local_2 = 15
end
if be:MDLgetRamNo() == 0 then
    if g_wbutton01 ~= 1 then
        be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
        be:MDLsetSeq("SQ_SWON")
        g_wbutton01 = 1
        if g_wbutton02 == 1 then
            be:sd("MODELCTRL", "g_dbarrierw1", 0, "SQ_POWEROF", 30)
            be:sd("MODELCTRL", "g_dbarrierw2", 0, "SQ_POWEROF", 30)
            be:sd("MODELCTRL", "g_dbarrierw3", 0, "SQ_POWEROF", 30)
            be:sd("MODELCTRL", "g_dbarrierp", 0, "SQ_POWEROF", 30)
            be:sd("MODELCTRL", "g_dbarrierp", 1, "SQ_POWEROF", 30)
            be:sd("HITLANDMODEL", "barrierwall01", 0, "OFFHIT", 30)
            be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_ONLOOP")
            be:FLGset(152, 1)
        else
            be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_SWOF", local_2)
        end
    end
end
if be:MDLgetRamNo() == 1 and g_wbutton02 ~= 1 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    g_wbutton02 = 1
    if g_wbutton01 == 1 then
        be:sd("MODELCTRL", "g_dbarrierw1", 0, "SQ_POWEROF", 30)
        be:sd("MODELCTRL", "g_dbarrierw2", 0, "SQ_POWEROF", 30)
        be:sd("MODELCTRL", "g_dbarrierw3", 0, "SQ_POWEROF", 30)
        be:sd("MODELCTRL", "g_dbarrierp", 0, "SQ_POWEROF", 30)
        be:sd("MODELCTRL", "g_dbarrierp", 1, "SQ_POWEROF", 30)
        be:sd("HITLANDMODEL", "barrierwall01", 0, "OFFHIT", 30)
        be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_ONLOOP")
        be:FLGset(152, 1)
    else
        be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_SWOF", local_2)
    end
end
