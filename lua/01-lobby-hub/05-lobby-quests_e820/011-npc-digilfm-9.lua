mswk25148 = "TALKFONT02/font00/I<278>"
mswk25149 = "TALKFONT02/font00/I<343>"
mswk25150 = "TALKFONT02/font00/I<342>"
mswk25151 = "TALKFONT02/font00/I<356>"
mswk25152 = "TALKFONT01/font00/I<280>"
mswk25153 = "TALKFONT01/font00/I<281>"
mswk25154 = "TALKFONT01/font00/I<325>"
mswk25155 = "TALKFONT01/font00/I<357>"
mswk25156 = "TALKFONT01/font00/I<358>"
mswk25157 = "TALKFONT01/font00/I<359>"
mswk25158 = "TALKFONT01/font00/I<360>"
mswk25159 = "TALKFONT01/font00/I<361>"
mswk25160 = "TALKFONT01/font00/I<362>"
mswk25161 = "TALKFONT01/font00/I<363>"
mswk25162 = "TALKFONT01/font00/I<364>"
mswk25163 = "TALKFONT01/font00/I<365>"
mswk25164 = "TALKFONT01/font00/I<281>"
mswk25165 = "TALKFONT01/font00/I<366>"
mswk25166 = "TALKFONT01/font00/I<308>"
mswk25167 = "TALKFONT01/font00/I<309>"
mswk25168 = "TALKFONT01/font00/I<311>"
mswk25169 = "TALKFONT01/font00/I<325>"
mswk25170 = "TALKFONT01/font00/I<309>"
mswk25171 = "TALKFONT01/font00/I<367>"
mswk25172 = "TALKFONT01/font00/I<326>"
mswk25173 = "TALKFONT01/font00/I<328>"
mswk25174 = "TALKFONT01/font00/I<368>"
mswk25175 = "TALKFONT01/font00/I<369>"
mswk25371 = "TALKFONT02/font00/I<370>"
mswk25372 = "TALKFONT02/font00/I<371>"
mswk25373 = "TALKFONT01/font00/I<310>"
if be:SYSgetDifficulty() == 0 then
    local_0 = 279
elseif be:SYSgetDifficulty() == 1 then
    local_0 = 302
elseif be:SYSgetDifficulty() == 2 then
    local_0 = 302
end
for local_3 = 0, 3 do
    if be:SYSisJoinPlayer(local_3) == 1 then
        local_1 = local_1 + be:COUNTERget(local_3 + 3)
    end
end
for local_7 = 0, 3 do
    if local_10 > local_5 then
        local_4 = local_7
        local_5 = local_10
    end
end
be:FLGset(409, 0)
be:FLGset(377, 0)
be:FLGset(385, 0)
be:FLGset(571, 0)
be:FLGset(424, 0)
be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWERON")
funcCloseMessage("talk", "n_digilfm", "fWt", 2, "noturn")
if be:SYSgetDifficulty() == 0 then
    if local_3 == 100 then
        if be:FLGisOn(554) == 0 then
            if be:SYSgetPlayerNinzu() == 1 then
                if local_4 == 0 then
                    be:FLGset(415, 0)
                    be:FLGset(417, 0)
                    be:FLGset(418, 0)
                    be:FLGset(419, 0)
                    be:FLGset(420, 0)
                    be:FLGset(427, 1)
                    if be:SYSisGetShinkaDigimon(0, 6) == 0 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25156)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlShinka("SETSHINKA", 0, 6)
                    elseif be:SYSisGetShinkaDigimon(0, 6) == 1 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25154)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlBit("ADD", 0, 2000)
                    else
                    end
                end
                if local_4 == 1 then
                    be:FLGset(415, 0)
                    be:FLGset(417, 0)
                    be:FLGset(418, 0)
                    be:FLGset(419, 0)
                    be:FLGset(420, 0)
                    be:FLGset(427, 1)
                    if be:SYSisGetShinkaDigimon(0, 7) == 0 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25157)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlShinka("SETSHINKA", 0, 7)
                    elseif be:SYSisGetShinkaDigimon(0, 7) == 1 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25154)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlBit("ADD", 0, 2000)
                    else
                    end
                end
                if local_4 == 2 then
                    be:FLGset(415, 0)
                    be:FLGset(417, 0)
                    be:FLGset(418, 0)
                    be:FLGset(419, 0)
                    be:FLGset(420, 0)
                    be:FLGset(427, 1)
                    if be:SYSisGetShinkaDigimon(0, 5) == 0 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25158)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlShinka("SETSHINKA", 0, 5)
                    elseif be:SYSisGetShinkaDigimon(0, 5) == 1 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25154)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlBit("ADD", 0, 2000)
                    else
                    end
                end
                if local_4 == 3 then
                    be:FLGset(415, 0)
                    be:FLGset(417, 0)
                    be:FLGset(418, 0)
                    be:FLGset(419, 0)
                    be:FLGset(420, 0)
                    be:FLGset(427, 1)
                    if be:SYSisGetShinkaDigimon(0, 4) == 0 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25159)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlShinka("SETSHINKA", 0, 4)
                    elseif be:SYSisGetShinkaDigimon(0, 4) == 1 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25154)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlBit("ADD", 0, 2000)
                    else
                    end
                end
            end
            if be:SYSgetPlayerNinzu() >= 2 then
                if local_4 == 0 then
                    be:FLGset(415, 0)
                    be:FLGset(417, 0)
                    be:FLGset(418, 0)
                    be:FLGset(419, 0)
                    be:FLGset(420, 0)
                    be:FLGset(427, 1)
                    if be:SYSisGetShinkaDigimon(0, 6) == 0 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25160)
                        funcOneMessage(mswk25155)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlShinka("SETSHINKA", 0, 6)
                        be:SYSctlBit("ADD", 1, 2000)
                        be:SYSctlBit("ADD", 2, 2000)
                        be:SYSctlBit("ADD", 3, 2000)
                    elseif be:SYSisGetShinkaDigimon(0, 6) == 1 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25154)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlBit("ADD", 0, 2000)
                        be:SYSctlBit("ADD", 1, 2000)
                        be:SYSctlBit("ADD", 2, 2000)
                        be:SYSctlBit("ADD", 3, 2000)
                    else
                    end
                end
                if local_4 == 1 then
                    be:FLGset(415, 0)
                    be:FLGset(417, 0)
                    be:FLGset(418, 0)
                    be:FLGset(419, 0)
                    be:FLGset(420, 0)
                    be:FLGset(427, 1)
                    if be:SYSisGetShinkaDigimon(0, 7) == 0 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25161)
                        funcOneMessage(mswk25155)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlShinka("SETSHINKA", 0, 7)
                        be:SYSctlBit("ADD", 1, 2000)
                        be:SYSctlBit("ADD", 2, 2000)
                        be:SYSctlBit("ADD", 3, 2000)
                    elseif be:SYSisGetShinkaDigimon(0, 7) == 1 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25154)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlBit("ADD", 0, 2000)
                        be:SYSctlBit("ADD", 1, 2000)
                        be:SYSctlBit("ADD", 2, 2000)
                        be:SYSctlBit("ADD", 3, 2000)
                    else
                    end
                end
                if local_4 == 2 then
                    be:FLGset(415, 0)
                    be:FLGset(417, 0)
                    be:FLGset(418, 0)
                    be:FLGset(419, 0)
                    be:FLGset(420, 0)
                    be:FLGset(427, 1)
                    if be:SYSisGetShinkaDigimon(0, 5) == 0 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25162)
                        funcOneMessage(mswk25155)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlShinka("SETSHINKA", 0, 5)
                        be:SYSctlBit("ADD", 1, 2000)
                        be:SYSctlBit("ADD", 2, 2000)
                        be:SYSctlBit("ADD", 3, 2000)
                    elseif be:SYSisGetShinkaDigimon(0, 5) == 1 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25154)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlBit("ADD", 0, 2000)
                        be:SYSctlBit("ADD", 1, 2000)
                        be:SYSctlBit("ADD", 2, 2000)
                        be:SYSctlBit("ADD", 3, 2000)
                    else
                    end
                end
                if local_4 == 3 then
                    be:FLGset(415, 0)
                    be:FLGset(417, 0)
                    be:FLGset(418, 0)
                    be:FLGset(419, 0)
                    be:FLGset(420, 0)
                    if be:SYSisGetShinkaDigimon(0, 4) == 0 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25163)
                        funcOneMessage(mswk25155)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlShinka("SETSHINKA", 0, 4)
                        be:SYSctlBit("ADD", 1, 2000)
                        be:SYSctlBit("ADD", 2, 2000)
                        be:SYSctlBit("ADD", 3, 2000)
                    elseif be:SYSisGetShinkaDigimon(0, 4) == 1 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25154)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlBit("ADD", 0, 2000)
                        be:SYSctlBit("ADD", 1, 2000)
                        be:SYSctlBit("ADD", 2, 2000)
                        be:SYSctlBit("ADD", 3, 2000)
                    else
                    end
                end
            end
        end
        if be:FLGisOn(554) == 1 then
            be:FLGset(415, 0)
            be:FLGset(417, 0)
            be:FLGset(418, 0)
            be:FLGset(419, 0)
            be:FLGset(420, 0)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25154)
            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
            be:SYSctlBit("ADD", 0, 2000)
            be:SYSctlBit("ADD", 1, 2000)
            be:SYSctlBit("ADD", 2, 2000)
            be:SYSctlBit("ADD", 3, 2000)
        else
        end
    end
    if local_3 >= 80 then
        be:FLGset(415, 0)
        be:FLGset(417, 0)
        be:FLGset(418, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:FLGset(427, 1)
        be:SYSctlBit("ADD", 0, 500)
        be:SYSctlBit("ADD", 1, 500)
        be:SYSctlBit("ADD", 2, 500)
        be:SYSctlBit("ADD", 3, 500)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25153)
        funcCloseMessage("mess", "n_digilfm", "fWt", 2)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    elseif local_3 >= 0 then
        be:FLGset(415, 0)
        be:FLGset(417, 0)
        be:FLGset(418, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:FLGset(427, 1)
        be:SYSctlBit("ADD", 0, 100)
        be:SYSctlBit("ADD", 1, 100)
        be:SYSctlBit("ADD", 2, 100)
        be:SYSctlBit("ADD", 3, 100)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25152)
        funcCloseMessage("mess", "n_digilfm", "fWt", 2)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    else
    end
end
if be:SYSgetDifficulty() == 1 then
    if be:COUNTERget(0) >= 600 then
        if local_3 == 100 then
            if be:FLGisOn(555) == 0 then
                if be:SYSgetPlayerNinzu() == 1 then
                    if local_4 == 0 then
                        be:FLGset(415, 0)
                        be:FLGset(417, 0)
                        be:FLGset(418, 0)
                        be:FLGset(419, 0)
                        be:FLGset(420, 0)
                        be:FLGset(434, 1)
                        if be:SYSisGetShinkaDigimon(0, 7) == 0 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25157)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlShinka("SETSHINKA", 0, 7)
                        elseif be:SYSisGetShinkaDigimon(0, 7) == 1 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25167)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlBit("ADD", 0, 5000)
                        else
                        end
                    end
                    if local_4 == 1 then
                        be:FLGset(415, 0)
                        be:FLGset(417, 0)
                        be:FLGset(418, 0)
                        be:FLGset(419, 0)
                        be:FLGset(420, 0)
                        be:FLGset(434, 1)
                        if be:SYSisGetShinkaDigimon(0, 6) == 0 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25156)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlShinka("SETSHINKA", 0, 6)
                        elseif be:SYSisGetShinkaDigimon(0, 6) == 1 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25167)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlBit("ADD", 0, 5000)
                        else
                        end
                    end
                    if local_4 == 2 then
                        be:FLGset(415, 0)
                        be:FLGset(417, 0)
                        be:FLGset(418, 0)
                        be:FLGset(419, 0)
                        be:FLGset(420, 0)
                        be:FLGset(434, 1)
                        if be:SYSisGetShinkaDigimon(0, 4) == 0 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25159)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlShinka("SETSHINKA", 0, 4)
                        elseif be:SYSisGetShinkaDigimon(0, 4) == 1 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25167)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlBit("ADD", 0, 5000)
                        else
                        end
                    end
                    if local_4 == 3 then
                        be:FLGset(415, 0)
                        be:FLGset(417, 0)
                        be:FLGset(418, 0)
                        be:FLGset(419, 0)
                        be:FLGset(420, 0)
                        be:FLGset(434, 1)
                        if be:SYSisGetShinkaDigimon(0, 5) == 0 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25158)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlShinka("SETSHINKA", 0, 5)
                        elseif be:SYSisGetShinkaDigimon(0, 5) == 1 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25167)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlBit("ADD", 0, 5000)
                        else
                        end
                    end
                end
                if be:SYSgetPlayerNinzu() >= 2 then
                    if local_4 == 0 then
                        be:FLGset(415, 0)
                        be:FLGset(417, 0)
                        be:FLGset(418, 0)
                        be:FLGset(419, 0)
                        be:FLGset(420, 0)
                        be:FLGset(434, 1)
                        if be:SYSisGetShinkaDigimon(0, 7) == 0 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25161)
                            funcOneMessage(mswk25168)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlShinka("SETSHINKA", 0, 7)
                            be:SYSctlBit("ADD", 1, 5000)
                            be:SYSctlBit("ADD", 2, 5000)
                            be:SYSctlBit("ADD", 3, 5000)
                        elseif be:SYSisGetShinkaDigimon(0, 7) == 1 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25167)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlBit("ADD", 0, 5000)
                            be:SYSctlBit("ADD", 1, 5000)
                            be:SYSctlBit("ADD", 2, 5000)
                            be:SYSctlBit("ADD", 3, 5000)
                        else
                        end
                    end
                    if local_4 == 1 then
                        be:FLGset(415, 0)
                        be:FLGset(417, 0)
                        be:FLGset(418, 0)
                        be:FLGset(419, 0)
                        be:FLGset(420, 0)
                        be:FLGset(434, 1)
                        if be:SYSisGetShinkaDigimon(0, 6) == 0 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25160)
                            funcOneMessage(mswk25168)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlShinka("SETSHINKA", 0, 6)
                            be:SYSctlBit("ADD", 1, 5000)
                            be:SYSctlBit("ADD", 2, 5000)
                            be:SYSctlBit("ADD", 3, 5000)
                        elseif be:SYSisGetShinkaDigimon(0, 6) == 1 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25167)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlBit("ADD", 0, 5000)
                            be:SYSctlBit("ADD", 1, 5000)
                            be:SYSctlBit("ADD", 2, 5000)
                            be:SYSctlBit("ADD", 3, 5000)
                        else
                        end
                    end
                    if local_4 == 2 then
                        be:FLGset(415, 0)
                        be:FLGset(417, 0)
                        be:FLGset(418, 0)
                        be:FLGset(419, 0)
                        be:FLGset(420, 0)
                        be:FLGset(434, 1)
                        if be:SYSisGetShinkaDigimon(0, 4) == 0 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25163)
                            funcOneMessage(mswk25168)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlShinka("SETSHINKA", 0, 4)
                            be:SYSctlBit("ADD", 1, 5000)
                            be:SYSctlBit("ADD", 2, 5000)
                            be:SYSctlBit("ADD", 3, 5000)
                        elseif be:SYSisGetShinkaDigimon(0, 4) == 1 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25167)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlBit("ADD", 0, 5000)
                            be:SYSctlBit("ADD", 1, 5000)
                            be:SYSctlBit("ADD", 2, 5000)
                            be:SYSctlBit("ADD", 3, 5000)
                        else
                        end
                    end
                    if local_4 == 3 then
                        be:FLGset(415, 0)
                        be:FLGset(417, 0)
                        be:FLGset(418, 0)
                        be:FLGset(419, 0)
                        be:FLGset(420, 0)
                        be:FLGset(434, 1)
                        if be:SYSisGetShinkaDigimon(0, 5) == 0 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25162)
                            funcOneMessage(mswk25168)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlShinka("SETSHINKA", 0, 5)
                            be:SYSctlBit("ADD", 1, 5000)
                            be:SYSctlBit("ADD", 2, 5000)
                            be:SYSctlBit("ADD", 3, 5000)
                        elseif be:SYSisGetShinkaDigimon(0, 5) == 1 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25167)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlBit("ADD", 0, 5000)
                            be:SYSctlBit("ADD", 1, 5000)
                            be:SYSctlBit("ADD", 2, 5000)
                            be:SYSctlBit("ADD", 3, 5000)
                        else
                        end
                    end
                end
            end
            if be:FLGisOn(555) == 1 then
                be:FLGset(415, 0)
                be:FLGset(417, 0)
                be:FLGset(418, 0)
                be:FLGset(419, 0)
                be:FLGset(420, 0)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                funcOpenMessage("mess")
                funcOneMessage(mswk25167)
                funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                be:SYSctlBit("ADD", 0, 5000)
                be:SYSctlBit("ADD", 1, 5000)
                be:SYSctlBit("ADD", 2, 5000)
                be:SYSctlBit("ADD", 3, 5000)
            else
            end
        end
        if local_3 >= 80 then
            be:FLGset(415, 0)
            be:FLGset(417, 0)
            be:FLGset(418, 0)
            be:FLGset(419, 0)
            be:FLGset(420, 0)
            be:FLGset(434, 1)
            be:SYSctlBit("ADD", 0, 1000)
            be:SYSctlBit("ADD", 1, 1000)
            be:SYSctlBit("ADD", 2, 1000)
            be:SYSctlBit("ADD", 3, 1000)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25165)
            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
        elseif local_3 >= 0 then
            be:FLGset(415, 0)
            be:FLGset(417, 0)
            be:FLGset(418, 0)
            be:FLGset(419, 0)
            be:FLGset(420, 0)
            be:FLGset(434, 1)
            be:SYSctlBit("ADD", 0, 500)
            be:SYSctlBit("ADD", 1, 500)
            be:SYSctlBit("ADD", 2, 500)
            be:SYSctlBit("ADD", 3, 500)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25164)
            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
        else
        end
    end
    if be:COUNTERget(0) >= 0 then
        if local_3 == 100 then
            be:FLGset(415, 0)
            be:FLGset(417, 0)
            be:FLGset(418, 0)
            be:FLGset(419, 0)
            be:FLGset(420, 0)
            be:FLGset(434, 1)
            be:SYSctlBit("ADD", 0, 2500)
            be:SYSctlBit("ADD", 1, 2500)
            be:SYSctlBit("ADD", 2, 2500)
            be:SYSctlBit("ADD", 3, 2500)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25166)
            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
        elseif local_3 >= 80 then
            be:FLGset(415, 0)
            be:FLGset(417, 0)
            be:FLGset(418, 0)
            be:FLGset(419, 0)
            be:FLGset(420, 0)
            be:FLGset(434, 1)
            be:SYSctlBit("ADD", 0, 1000)
            be:SYSctlBit("ADD", 1, 1000)
            be:SYSctlBit("ADD", 2, 1000)
            be:SYSctlBit("ADD", 3, 1000)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25165)
            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
        elseif local_3 >= 0 then
            be:FLGset(415, 0)
            be:FLGset(417, 0)
            be:FLGset(418, 0)
            be:FLGset(419, 0)
            be:FLGset(420, 0)
            be:FLGset(434, 1)
            be:SYSctlBit("ADD", 0, 500)
            be:SYSctlBit("ADD", 1, 500)
            be:SYSctlBit("ADD", 2, 500)
            be:SYSctlBit("ADD", 3, 500)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25164)
            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
        else
        end
    end
end
if be:SYSgetDifficulty() == 2 then
    if be:COUNTERget(0) >= 600 then
        if local_3 == 100 then
            if be:FLGisOn(556) == 0 then
                if be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 1 then
                    g_IFLG09 = 0
                    if be:SYSgetPlayerNinzu() == 1 then
                        funcOpenMessage("talk", "n_digilfm", "fWt", 2)
                        funcOneMessage(mswk25148)
                        funcOneMessage(mswk25149)
                        funcCloseMessage("talk", "n_digilfm", "fWt", 2)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:FLGset(409, 1)
                        be:FLGset(377, 1)
                        be:FLGset(385, 1)
                        be:FLGset(571, 1)
                        be:FLGset(416, 0)
                        be:FLGset(424, 1)
                        be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWEROF")
                    elseif be:SYSgetPlayerNinzu() >= 2 then
                        funcOpenMessage("talk", "n_digilfm", "fWt", 2)
                        funcOneMessage(mswk25150)
                        funcOneMessage(mswk25151)
                        funcCloseMessage("talk", "n_digilfm", "fWt", 2)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:FLGset(409, 1)
                        be:FLGset(377, 1)
                        be:FLGset(385, 1)
                        be:FLGset(571, 1)
                        be:FLGset(416, 0)
                        be:FLGset(424, 1)
                        be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWEROF")
                    else
                    end
                end
                if be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 0 then
                    be:FLGset(415, 0)
                    be:FLGset(417, 0)
                    be:FLGset(418, 0)
                    be:FLGset(419, 0)
                    be:FLGset(420, 0)
                    be:FLGset(556, 1)
                    be:FLGset(441, 1)
                    if be:SYSgetPlayerNinzu() == 1 then
                        be:SYSctlDeviceFolder("SET", 0, "abChip", 42, 0, 0)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25174)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    elseif be:SYSgetPlayerNinzu() >= 2 then
                        be:SYSctlDeviceFolder("SET", 0, "abChip", 42, 0, 0)
                        be:SYSctlBit("ADD", 1, 15000)
                        be:SYSctlBit("ADD", 2, 15000)
                        be:SYSctlBit("ADD", 3, 15000)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25175)
                        funcOneMessage(mswk25173)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    else
                    end
                end
            end
            if be:FLGisOn(556) == 1 then
                be:FLGset(415, 0)
                be:FLGset(417, 0)
                be:FLGset(418, 0)
                be:FLGset(419, 0)
                be:FLGset(420, 0)
                be:SYSctlBit("ADD", 0, 15000)
                be:SYSctlBit("ADD", 1, 15000)
                be:SYSctlBit("ADD", 2, 15000)
                be:SYSctlBit("ADD", 3, 15000)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                funcOpenMessage("mess")
                funcOneMessage(mswk25172)
                funcCloseMessage("mess", "n_digilfm", "fWt", 2)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
            else
            end
        end
        if local_3 >= 80 then
            be:FLGset(415, 0)
            be:FLGset(417, 0)
            be:FLGset(418, 0)
            be:FLGset(419, 0)
            be:FLGset(420, 0)
            be:FLGset(441, 1)
            be:SYSctlBit("ADD", 0, 5000)
            be:SYSctlBit("ADD", 1, 5000)
            be:SYSctlBit("ADD", 2, 5000)
            be:SYSctlBit("ADD", 3, 5000)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25170)
            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
        elseif local_3 > 0 then
            be:FLGset(415, 0)
            be:FLGset(417, 0)
            be:FLGset(418, 0)
            be:FLGset(419, 0)
            be:FLGset(420, 0)
            be:FLGset(441, 1)
            be:SYSctlBit("ADD", 0, 2000)
            be:SYSctlBit("ADD", 1, 2000)
            be:SYSctlBit("ADD", 2, 2000)
            be:SYSctlBit("ADD", 3, 2000)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25169)
            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
        else
            be:FLGset(415, 0)
            be:FLGset(417, 0)
            be:FLGset(418, 0)
            be:FLGset(419, 0)
            be:FLGset(420, 0)
            be:FLGset(441, 1)
            be:SYSctlBit("ADD", 0, 10000)
            be:SYSctlBit("ADD", 1, 10000)
            be:SYSctlBit("ADD", 2, 10000)
            be:SYSctlBit("ADD", 3, 10000)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25373)
            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
        end
    end
    if be:COUNTERget(0) >= 0 then
        if local_3 == 100 then
            be:FLGset(415, 0)
            be:FLGset(417, 0)
            be:FLGset(418, 0)
            be:FLGset(419, 0)
            be:FLGset(420, 0)
            be:FLGset(441, 1)
            be:SYSctlBit("ADD", 0, 7500)
            be:SYSctlBit("ADD", 1, 7500)
            be:SYSctlBit("ADD", 2, 7500)
            be:SYSctlBit("ADD", 3, 7500)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25171)
            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
        elseif local_3 >= 80 then
            be:FLGset(415, 0)
            be:FLGset(417, 0)
            be:FLGset(418, 0)
            be:FLGset(419, 0)
            be:FLGset(420, 0)
            be:FLGset(441, 1)
            be:SYSctlBit("ADD", 0, 5000)
            be:SYSctlBit("ADD", 1, 5000)
            be:SYSctlBit("ADD", 2, 5000)
            be:SYSctlBit("ADD", 3, 5000)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25170)
            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
        elseif local_3 > 0 then
            be:FLGset(415, 0)
            be:FLGset(417, 0)
            be:FLGset(418, 0)
            be:FLGset(419, 0)
            be:FLGset(420, 0)
            be:FLGset(441, 1)
            be:SYSctlBit("ADD", 0, 2000)
            be:SYSctlBit("ADD", 1, 2000)
            be:SYSctlBit("ADD", 2, 2000)
            be:SYSctlBit("ADD", 3, 2000)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25169)
            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
        else
            be:FLGset(415, 0)
            be:FLGset(417, 0)
            be:FLGset(418, 0)
            be:FLGset(419, 0)
            be:FLGset(420, 0)
            be:FLGset(441, 1)
            be:SYSctlBit("ADD", 0, 10000)
            be:SYSctlBit("ADD", 1, 10000)
            be:SYSctlBit("ADD", 2, 10000)
            be:SYSctlBit("ADD", 3, 10000)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("talk", "n_digilfm", "fWt", 2)
            funcOneMessage(mswk25371)
            funcOneMessage(mswk25372)
            funcCloseMessage("talk", "n_digilfm", "fWt", 2)
            funcOpenMessage("mess")
            funcOneMessage(mswk25373)
            funcCloseMessage("mess", "n_digilfm", "fWt", 2)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
        end
    end
end
be:DMrun()
