for local_1 = 0, 3 do
    if be:SYSisJoinPlayer(local_1) == 1 then
        local_0 = local_0 + 1
    end
end
g_lFLG01 = 1
if g_lFLG00 == 1 and be:FLGisOn(41) == 0 then
    if local_0 == 4 then
        be:sd("MODELCTRL", "g_sbutton", 0, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 1, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 2, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 3, "SQ_POWERON")
    elseif local_0 == 3 then
        be:sd("MODELCTRL", "g_sbutton", 0, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 1, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 2, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 3, "SQ_ONLOOP")
        g_sbutton03 = 1
    elseif local_0 == 2 then
        be:sd("MODELCTRL", "g_sbutton", 0, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 1, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 2, "SQ_ONLOOP")
        g_sbutton02 = 1
        be:sd("MODELCTRL", "g_sbutton", 3, "SQ_ONLOOP")
        g_sbutton03 = 1
    elseif local_0 == 1 then
        be:sd("MODELCTRL", "g_sbutton", 0, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 1, "SQ_ONLOOP")
        g_sbutton01 = 1
        be:sd("MODELCTRL", "g_sbutton", 2, "SQ_ONLOOP")
        g_sbutton02 = 1
        be:sd("MODELCTRL", "g_sbutton", 3, "SQ_ONLOOP")
        g_sbutton03 = 1
    end
end
