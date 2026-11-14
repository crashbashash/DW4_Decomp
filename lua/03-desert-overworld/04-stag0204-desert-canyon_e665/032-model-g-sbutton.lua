if be:MATisPlayer() == 1 and be:FLGisOn(55) == 0 and be:FLGisOn(51) == 1 and be:FLGisOn(52) == 1 and be:FLGisOn(53) == 1 and be:FLGisOn(54) == 1 then
    local count = 0
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 then
            count = count + 1
        end
    end
    if count == 4 then
        be:sd("MODELCTRL", "g_sbutton", 0, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 1, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 2, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 3, "SQ_POWERON")
    elseif count == 3 then
        be:sd("MODELCTRL", "g_sbutton", 0, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 1, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 2, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 3, "SQ_ONLOOP")
        g_sbutton03 = 1
    elseif count == 2 then
        be:sd("MODELCTRL", "g_sbutton", 0, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 1, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 2, "SQ_ONLOOP")
        g_sbutton02 = 1
        be:sd("MODELCTRL", "g_sbutton", 3, "SQ_ONLOOP")
        g_sbutton03 = 1
    elseif count == 1 then
        be:sd("MODELCTRL", "g_sbutton", 0, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 1, "SQ_ONLOOP")
        g_sbutton01 = 1
        be:sd("MODELCTRL", "g_sbutton", 2, "SQ_ONLOOP")
        g_sbutton02 = 1
        be:sd("MODELCTRL", "g_sbutton", 3, "SQ_ONLOOP")
        g_sbutton03 = 1
    end
end
