mswk25362 = "TALKFONT02/font00/I<576>"
mswk25363 = "TALKFONT02/font00/I<577>"
mswk25364 = "TALKFONT02/font00/I<578>"
mswk25365 = "TALKFONT01/font00/I<579>"
mswk25366 = "TALKFONT01/font00/I<580>"
mswk25367 = "TALKFONT01/font00/I<581>"
mswk25368 = "TALKFONT01/font00/I<582>"
mswk25369 = "TALKFONT02/font00/I<182>"
mswk25370 = "TALKFONT02/font00/I<186>"
be:sd("PLAYER", nil, -1, "OFCTRL")
be:sd("ENEMY", nil, -1, "OFCTRL")
be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
if be:SYSgetPlayerName(g_messPlayerNo) == "p_agumon" then
    if be:SYSisGetShinkaDigimon(g_messPlayerNo, 3) == 0 then
        be:SYSctlShinka("SETSHINKA", g_messPlayerNo, 3)
        funcOneMessage(mswk25362)
        funcOneMessage(mswk25363)
        local_0("talk", "n_digilff", "fWt", 1, "noturn")
        funcOpenMessage("mess")
        funcOneMessage(mswk25368)
        local_0("mess", "n_digilff", "fWt", 1, "noturn")
        funcOpenMessage("talk", "n_digilff", "fWt", 1)
        funcOneMessage(mswk25364)
        local_0("talk", "n_digilff", "fWt", 1)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMrun()
    elseif be:SYSisGetShinkaDigimon(g_messPlayerNo, 3) == 1 then
        be:DMsetLua("bML01004.lua")
        be:DMrun()
    else
    end
end
if be:SYSgetPlayerName(g_messPlayerNo) == "p_vmon" then
    if be:SYSisGetShinkaDigimon(g_messPlayerNo, 2) == 0 then
        be:SYSctlShinka("SETSHINKA", g_messPlayerNo, 2)
        funcOneMessage(mswk25362)
        funcOneMessage(mswk25363)
        local_0("talk", "n_digilff", "fWt", 1, "noturn")
        funcOpenMessage("mess")
        funcOneMessage(mswk25367)
        local_0("mess", "n_digilff", "fWt", 1, "noturn")
        funcOpenMessage("talk", "n_digilff", "fWt", 1)
        funcOneMessage(mswk25364)
        local_0("talk", "n_digilff", "fWt", 1)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMrun()
    elseif be:SYSisGetShinkaDigimon(g_messPlayerNo, 2) == 1 then
        be:DMsetLua("bML01004.lua")
        be:DMrun()
    else
    end
end
if be:SYSgetPlayerName(g_messPlayerNo) == "p_girumon" then
    if be:SYSisGetShinkaDigimon(g_messPlayerNo, 0) == 0 then
        be:SYSctlShinka("SETSHINKA", g_messPlayerNo, 0)
        funcOneMessage(mswk25362)
        funcOneMessage(mswk25363)
        local_0("talk", "n_digilff", "fWt", 1, "noturn")
        funcOpenMessage("mess")
        funcOneMessage(mswk25365)
        local_0("mess", "n_digilff", "fWt", 1, "noturn")
        funcOpenMessage("talk", "n_digilff", "fWt", 1)
        funcOneMessage(mswk25364)
        local_0("talk", "n_digilff", "fWt", 1)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMrun()
    elseif be:SYSisGetShinkaDigimon(g_messPlayerNo, 0) == 1 then
        be:DMsetLua("bML01004.lua")
        be:DMrun()
    else
    end
end
if be:SYSgetPlayerName(g_messPlayerNo) == "p_dorumon" then
    if be:SYSisGetShinkaDigimon(g_messPlayerNo, 1) == 0 then
        be:SYSctlShinka("SETSHINKA", g_messPlayerNo, 1)
        funcOneMessage(mswk25362)
        funcOneMessage(mswk25363)
        local_0("talk", "n_digilff", "fWt", 1, "noturn")
        funcOpenMessage("mess")
        funcOneMessage(mswk25366)
        local_0("mess", "n_digilff", "fWt", 1, "noturn")
        funcOpenMessage("talk", "n_digilff", "fWt", 1)
        funcOneMessage(mswk25364)
        local_0("talk", "n_digilff", "fWt", 1)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMrun()
    elseif be:SYSisGetShinkaDigimon(g_messPlayerNo, 1) == 1 then
        be:DMsetLua("bML01004.lua")
        be:DMrun()
    else
    end
end
be:DMsetLua("bML01004.lua")
be:DMrun()
