local count = 0
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        count = count + 1
    end
end
g_lFLG00 = 1
if g_lFLG01 == 1 and be:FLGisOn(62) == 0 then
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
