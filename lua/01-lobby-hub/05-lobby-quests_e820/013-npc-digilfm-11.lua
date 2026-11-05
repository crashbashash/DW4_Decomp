mswk25204 = "TALKFONT02/font00/I<278>"
mswk25205 = "TALKFONT02/font00/I<343>"
mswk25206 = "TALKFONT02/font00/I<342>"
mswk25207 = "TALKFONT02/font00/I<356>"
mswk25208 = "TALKFONT01/font00/I<380>"
mswk25209 = "TALKFONT01/font00/I<366>"
mswk25210 = "TALKFONT01/font00/I<381>"
mswk25211 = "TALKFONT01/font00/I<281>"
mswk25212 = "TALKFONT01/font00/I<282>"
mswk25213 = "TALKFONT01/font00/I<309>"
mswk25214 = "TALKFONT01/font00/I<382>"
mswk25215 = "TALKFONT01/font00/I<311>"
mswk25216 = "TALKFONT01/font00/I<383>"
mswk25217 = "TALKFONT01/font00/I<384>"
mswk25218 = "TALKFONT01/font00/I<385>"
mswk25219 = "TALKFONT01/font00/I<386>"
mswk25220 = "TALKFONT01/font00/I<387>"
mswk25221 = "TALKFONT01/font00/I<388>"
mswk25222 = "TALKFONT01/font00/I<389>"
mswk25223 = "TALKFONT01/font00/I<325>"
mswk25224 = "TALKFONT01/font00/I<309>"
mswk25225 = "TALKFONT01/font00/I<326>"
mswk25226 = "TALKFONT01/font00/I<310>"
mswk25227 = "TALKFONT01/font00/I<328>"
mswk25228 = "TALKFONT01/font00/I<312>"
mswk25229 = "TALKFONT01/font00/I<376>"
mswk25230 = "TALKFONT01/font00/I<375>"
mswk25231 = "TALKFONT01/font00/I<390>"
mswk25232 = "TALKFONT01/font00/I<391>"
mswk25233 = "TALKFONT01/font00/I<392>"
mswk25234 = "TALKFONT01/font00/I<393>"
mswk25235 = "TALKFONT01/font00/I<394>"
mswk25236 = "TALKFONT01/font00/I<395>"
mswk25237 = "TALKFONT01/font00/I<396>"
mswk25238 = "TALKFONT01/font00/I<397>"
mswk25239 = "TALKFONT01/font00/I<398>"
mswk25240 = "TALKFONT01/font00/I<399>"
mswk25241 = "TALKFONT01/font00/I<400>"
mswk25242 = "TALKFONT01/font00/I<401>"
mswk25243 = "TALKFONT01/font00/I<402>"
mswk25244 = "TALKFONT01/font00/I<403>"
for local_3 = 0, 3 do
    if local_6 > local_1 then
        local_0 = local_3
        local_1 = local_6
    end
end
be:FLGset(409, 0)
be:FLGset(379, 0)
be:FLGset(387, 0)
be:FLGset(571, 0)
be:FLGset(424, 0)
be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWERON")
funcCloseMessage("talk", "n_digilfm", "fWt", 4, "noturn")
if be:SYSgetDifficulty() == 0 then
    if be:FLGisOn(565) == 1 then
        be:FLGset(415, 0)
        be:FLGset(416, 0)
        be:FLGset(417, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:FLGset(429, 1)
        be:SYSctlBit("ADD", 0, 3000)
        be:SYSctlBit("ADD", 1, 3000)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25210)
        funcCloseMessage("mess", "n_digilfm", "fWt", 4)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    elseif be:FLGisOn(564) == 1 then
        be:FLGset(415, 0)
        be:FLGset(416, 0)
        be:FLGset(417, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:FLGset(429, 1)
        be:SYSctlBit("ADD", 0, 1000)
        be:SYSctlBit("ADD", 1, 1000)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25209)
        funcCloseMessage("mess", "n_digilfm", "fWt", 4)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    else
        be:FLGset(415, 0)
        be:FLGset(416, 0)
        be:FLGset(417, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:FLGset(429, 1)
        be:SYSctlBit("ADD", 0, 200)
        be:SYSctlBit("ADD", 1, 200)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25208)
        funcCloseMessage("mess", "n_digilfm", "fWt", 4)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    end
end
if be:SYSgetDifficulty() == 1 then
    if be:FLGisOn(566) == 1 then
        if be:FLGisOn(567) == 0 then
            if be:SYSgetPlayerNinzu() == 1 then
                if local_0 == 0 then
                    be:FLGset(415, 0)
                    be:FLGset(416, 0)
                    be:FLGset(417, 0)
                    be:FLGset(419, 0)
                    be:FLGset(420, 0)
                    be:FLGset(436, 1)
                    if be:SYSisGetShinkaDigimon(0, 9) == 0 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25217)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlShinka("SETSHINKA", 0, 9)
                    elseif be:SYSisGetShinkaDigimon(0, 9) == 1 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25214)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlBit("ADD", 0, 7000)
                    else
                    end
                end
                if local_0 ~= 1 then
                    if local_0 == 2 then
                        be:FLGset(415, 0)
                        be:FLGset(416, 0)
                        be:FLGset(417, 0)
                        be:FLGset(419, 0)
                        be:FLGset(420, 0)
                        be:FLGset(436, 1)
                        if be:SYSisGetShinkaDigimon(0, 8) == 0 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25218)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlShinka("SETSHINKA", 0, 8)
                        elseif be:SYSisGetShinkaDigimon(0, 8) == 1 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25214)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlBit("ADD", 0, 7000)
                        else
                        end
                    end
                end
                be:FLGset(415, 0)
                be:FLGset(416, 0)
                be:FLGset(417, 0)
                be:FLGset(419, 0)
                be:FLGset(420, 0)
                be:FLGset(436, 1)
                if be:SYSisGetShinkaDigimon(0, 8) == 0 then
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25218)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:SYSctlShinka("SETSHINKA", 0, 8)
                elseif be:SYSisGetShinkaDigimon(0, 8) == 1 then
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25214)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:SYSctlBit("ADD", 0, 7000)
                else
                end
            end
            if be:SYSgetPlayerNinzu() >= 2 then
                if local_0 == 0 then
                    be:FLGset(415, 0)
                    be:FLGset(416, 0)
                    be:FLGset(417, 0)
                    be:FLGset(419, 0)
                    be:FLGset(420, 0)
                    be:FLGset(436, 1)
                    if be:SYSisGetShinkaDigimon(0, 9) == 0 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25220)
                        funcOneMessage(mswk25216)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlShinka("SETSHINKA", 0, 9)
                        be:SYSctlBit("ADD", 1, 7000)
                    elseif be:SYSisGetShinkaDigimon(0, 9) == 1 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25214)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlBit("ADD", 0, 7000)
                        be:SYSctlBit("ADD", 1, 7000)
                    else
                    end
                end
                if local_0 ~= 1 then
                    if local_0 == 2 then
                        be:FLGset(415, 0)
                        be:FLGset(416, 0)
                        be:FLGset(417, 0)
                        be:FLGset(419, 0)
                        be:FLGset(420, 0)
                        be:FLGset(436, 1)
                        if be:SYSisGetShinkaDigimon(0, 8) == 0 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25221)
                            funcOneMessage(mswk25216)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlShinka("SETSHINKA", 0, 8)
                            be:SYSctlBit("ADD", 1, 7000)
                        elseif be:SYSisGetShinkaDigimon(0, 8) == 1 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25214)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlBit("ADD", 0, 7000)
                            be:SYSctlBit("ADD", 1, 7000)
                        else
                        end
                    end
                end
                be:FLGset(415, 0)
                be:FLGset(416, 0)
                be:FLGset(417, 0)
                be:FLGset(419, 0)
                be:FLGset(420, 0)
                be:FLGset(436, 1)
                if be:SYSisGetShinkaDigimon(0, 8) == 0 then
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25221)
                    funcOneMessage(mswk25216)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:SYSctlShinka("SETSHINKA", 0, 8)
                    be:SYSctlBit("ADD", 1, 7000)
                elseif be:SYSisGetShinkaDigimon(0, 8) == 1 then
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25214)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:SYSctlBit("ADD", 0, 7000)
                    be:SYSctlBit("ADD", 1, 7000)
                else
                end
            end
        end
        if be:FLGisOn(567) == 1 then
            be:FLGset(415, 0)
            be:FLGset(416, 0)
            be:FLGset(417, 0)
            be:FLGset(419, 0)
            be:FLGset(420, 0)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25214)
            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
            be:SYSctlBit("ADD", 0, 7000)
            be:SYSctlBit("ADD", 1, 7000)
        else
        end
    end
    if be:FLGisOn(565) == 1 then
        if be:FLGisOn(568) == 0 then
            if be:SYSgetPlayerNinzu() == 1 then
                if local_0 == 0 then
                    be:FLGset(415, 0)
                    be:FLGset(416, 0)
                    be:FLGset(417, 0)
                    be:FLGset(419, 0)
                    be:FLGset(420, 0)
                    be:FLGset(436, 1)
                    if be:SYSisGetShinkaDigimon(0, 9) == 0 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25217)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlShinka("SETSHINKA", 0, 9)
                    elseif be:SYSisGetShinkaDigimon(0, 9) == 1 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25213)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlBit("ADD", 0, 5000)
                    else
                    end
                end
                if local_0 ~= 1 then
                    if local_0 == 2 then
                        be:FLGset(415, 0)
                        be:FLGset(416, 0)
                        be:FLGset(417, 0)
                        be:FLGset(419, 0)
                        be:FLGset(420, 0)
                        be:FLGset(436, 1)
                        if be:SYSisGetShinkaDigimon(0, 8) == 0 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25218)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlShinka("SETSHINKA", 0, 8)
                        elseif be:SYSisGetShinkaDigimon(0, 8) == 1 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25213)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlBit("ADD", 0, 5000)
                        else
                        end
                    end
                end
                be:FLGset(415, 0)
                be:FLGset(416, 0)
                be:FLGset(417, 0)
                be:FLGset(419, 0)
                be:FLGset(420, 0)
                be:FLGset(436, 1)
                if be:SYSisGetShinkaDigimon(0, 8) == 0 then
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25218)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:SYSctlShinka("SETSHINKA", 0, 8)
                elseif be:SYSisGetShinkaDigimon(0, 8) == 1 then
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25213)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:SYSctlBit("ADD", 0, 5000)
                else
                end
            end
            if be:SYSgetPlayerNinzu() >= 2 then
                if local_0 == 0 then
                    be:FLGset(415, 0)
                    be:FLGset(416, 0)
                    be:FLGset(417, 0)
                    be:FLGset(419, 0)
                    be:FLGset(420, 0)
                    be:FLGset(436, 1)
                    if be:SYSisGetShinkaDigimon(0, 9) == 0 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25220)
                        funcOneMessage(mswk25215)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlShinka("SETSHINKA", 0, 9)
                        be:SYSctlBit("ADD", 1, 5000)
                    elseif be:SYSisGetShinkaDigimon(0, 9) == 1 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25213)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlBit("ADD", 0, 5000)
                        be:SYSctlBit("ADD", 1, 5000)
                    else
                    end
                end
                if local_0 ~= 1 then
                    if local_0 == 2 then
                        be:FLGset(415, 0)
                        be:FLGset(416, 0)
                        be:FLGset(417, 0)
                        be:FLGset(419, 0)
                        be:FLGset(420, 0)
                        be:FLGset(436, 1)
                        if be:SYSisGetShinkaDigimon(0, 8) == 0 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25221)
                            funcOneMessage(mswk25215)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlShinka("SETSHINKA", 0, 8)
                            be:SYSctlBit("ADD", 1, 5000)
                        elseif be:SYSisGetShinkaDigimon(0, 8) == 1 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25213)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlBit("ADD", 0, 5000)
                            be:SYSctlBit("ADD", 1, 5000)
                        else
                        end
                    end
                end
                be:FLGset(415, 0)
                be:FLGset(416, 0)
                be:FLGset(417, 0)
                be:FLGset(419, 0)
                be:FLGset(420, 0)
                be:FLGset(436, 1)
                if be:SYSisGetShinkaDigimon(0, 8) == 0 then
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25221)
                    funcOneMessage(mswk25215)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:SYSctlShinka("SETSHINKA", 0, 8)
                    be:SYSctlBit("ADD", 1, 5000)
                elseif be:SYSisGetShinkaDigimon(0, 8) == 1 then
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25213)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:SYSctlBit("ADD", 0, 5000)
                    be:SYSctlBit("ADD", 1, 5000)
                else
                end
            end
        end
        if be:FLGisOn(568) == 1 then
            be:FLGset(415, 0)
            be:FLGset(416, 0)
            be:FLGset(417, 0)
            be:FLGset(419, 0)
            be:FLGset(420, 0)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25213)
            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
            be:SYSctlBit("ADD", 0, 5000)
            be:SYSctlBit("ADD", 1, 5000)
        else
        end
    end
    if be:FLGisOn(564) == 1 then
        be:FLGset(415, 0)
        be:FLGset(416, 0)
        be:FLGset(417, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:FLGset(436, 1)
        be:SYSctlBit("ADD", 0, 1500)
        be:SYSctlBit("ADD", 1, 1500)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25212)
        funcCloseMessage("mess", "n_digilfm", "fWt", 4)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    elseif be:FLGisOn(563) == 1 then
        be:FLGset(415, 0)
        be:FLGset(416, 0)
        be:FLGset(417, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:FLGset(436, 1)
        be:SYSctlBit("ADD", 0, 500)
        be:SYSctlBit("ADD", 1, 500)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25211)
        funcCloseMessage("mess", "n_digilfm", "fWt", 4)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    else
    end
end
if be:SYSgetDifficulty() == 2 then
    if be:FLGisOn(566) == 1 then
        if be:FLGisOn(569) == 0 then
            if be:SYSgetPlayerNinzu() == 1 then
                if local_0 ~= 0 then
                    if local_0 == 2 then
                        be:FLGset(415, 0)
                        be:FLGset(416, 0)
                        be:FLGset(417, 0)
                        be:FLGset(419, 0)
                        be:FLGset(420, 0)
                        be:FLGset(443, 1)
                        if be:SYSisGetShinkaDigimon(0, 11) == 0 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25229)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlShinka("SETSHINKA", 0, 11)
                        elseif be:SYSisGetShinkaDigimon(0, 11) == 1 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25226)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlBit("ADD", 0, 10000)
                        else
                        end
                    end
                end
                be:FLGset(415, 0)
                be:FLGset(416, 0)
                be:FLGset(417, 0)
                be:FLGset(419, 0)
                be:FLGset(420, 0)
                be:FLGset(443, 1)
                if be:SYSisGetShinkaDigimon(0, 11) == 0 then
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25229)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:SYSctlShinka("SETSHINKA", 0, 11)
                elseif be:SYSisGetShinkaDigimon(0, 11) == 1 then
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25226)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:SYSctlBit("ADD", 0, 10000)
                else
                end
            end
            if be:SYSgetPlayerNinzu() >= 2 then
                if local_0 ~= 0 then
                    if local_0 == 2 then
                        be:FLGset(415, 0)
                        be:FLGset(416, 0)
                        be:FLGset(417, 0)
                        be:FLGset(419, 0)
                        be:FLGset(420, 0)
                        be:FLGset(443, 1)
                        if be:SYSisGetShinkaDigimon(0, 11) == 0 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25231)
                            funcOneMessage(mswk25228)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlShinka("SETSHINKA", 0, 11)
                            be:SYSctlBit("ADD", 1, 10000)
                        elseif be:SYSisGetShinkaDigimon(0, 11) == 1 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25226)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlBit("ADD", 0, 10000)
                            be:SYSctlBit("ADD", 1, 10000)
                        else
                        end
                    end
                end
                be:FLGset(415, 0)
                be:FLGset(416, 0)
                be:FLGset(417, 0)
                be:FLGset(419, 0)
                be:FLGset(420, 0)
                be:FLGset(443, 1)
                if be:SYSisGetShinkaDigimon(0, 11) == 0 then
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25231)
                    funcOneMessage(mswk25228)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:SYSctlShinka("SETSHINKA", 0, 11)
                    be:SYSctlBit("ADD", 1, 10000)
                elseif be:SYSisGetShinkaDigimon(0, 11) == 1 then
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25226)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:SYSctlBit("ADD", 0, 10000)
                    be:SYSctlBit("ADD", 1, 10000)
                else
                end
            end
        end
        if be:FLGisOn(569) == 1 then
            be:FLGset(415, 0)
            be:FLGset(416, 0)
            be:FLGset(417, 0)
            be:FLGset(419, 0)
            be:FLGset(420, 0)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25226)
            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
            be:SYSctlBit("ADD", 0, 10000)
            be:SYSctlBit("ADD", 1, 10000)
        else
        end
    end
    if be:FLGisOn(565) == 1 then
        if be:FLGisOn(570) == 0 then
            if be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 1 then
                g_IFLG11 = 0
                if be:SYSgetPlayerNinzu() == 1 then
                    funcOpenMessage("talk", "n_digilfm", "fWt", 4)
                    funcOneMessage(mswk25204)
                    funcOneMessage(mswk25205)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 4)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:FLGset(409, 1)
                    be:FLGset(379, 1)
                    be:FLGset(387, 1)
                    be:FLGset(571, 1)
                    be:FLGset(418, 0)
                    be:FLGset(424, 1)
                    be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWEROF")
                elseif be:SYSgetPlayerNinzu() >= 2 then
                    funcOpenMessage("talk", "n_digilfm", "fWt", 4)
                    funcOneMessage(mswk25206)
                    funcOneMessage(mswk25207)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 4)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:FLGset(409, 1)
                    be:FLGset(379, 1)
                    be:FLGset(387, 1)
                    be:FLGset(571, 1)
                    be:FLGset(418, 0)
                    be:FLGset(424, 1)
                    be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWEROF")
                else
                end
            end
            if be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 0 then
                be:FLGset(415, 0)
                be:FLGset(416, 0)
                be:FLGset(417, 0)
                be:FLGset(419, 0)
                be:FLGset(420, 0)
                be:FLGset(570, 1)
                be:FLGset(443, 1)
                if be:SYSgetPlayerNinzu() == 1 then
                    if be:SYSgetPlayerName(0) ~= "p_agumon" and be:SYSgetPlayerName(0) ~= "p_hekabut" then
                        if be:SYSgetPlayerName(0) == "p_susanoo" then
                            be:SYSctlDeviceFolder("SET", 0, "armor2", 29, 256, 0)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25233)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        else
                            if be:SYSgetPlayerName(0) ~= "p_vmon" and be:SYSgetPlayerName(0) ~= "p_angelr" then
                                if be:SYSgetPlayerName(0) == "p_dukecrim" then
                                    be:SYSctlDeviceFolder("SET", 0, "armor2", 32, 256, 0)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                    funcOpenMessage("mess")
                                    funcOneMessage(mswk25234)
                                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                else
                                    if be:SYSgetPlayerName(0) ~= "p_girumon" then
                                        if be:SYSgetPlayerName(0) == "p_weregaru" then
                                            be:SYSctlDeviceFolder("SET", 0, "armor2", 23, 256, 0)
                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                            funcOpenMessage("mess")
                                            funcOneMessage(mswk25235)
                                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                        else
                                            if be:SYSgetPlayerName(0) ~= "p_dorumon" and be:SYSgetPlayerName(0) ~= "p_alpha" then
                                                if be:SYSgetPlayerName(0) == "p_impdrapm" then
                                                    be:SYSctlDeviceFolder("SET", 0, "armor2", 38, 256, 0)
                                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                                    funcOpenMessage("mess")
                                                    funcOneMessage(mswk25236)
                                                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                                else
                                                    if be:SYSgetPlayerName(0) ~= "p_beelzeb" and be:SYSgetPlayerName(0) ~= "p_impdrafm" then
                                                        if be:SYSgetPlayerName(0) == "p_metalgaru" then
                                                            be:SYSctlDeviceFolder("SET", 0, "armor2", 41, 256, 0)
                                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                                            funcOpenMessage("mess")
                                                            funcOneMessage(mswk25237)
                                                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                                                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                                        else
                                                            if be:SYSgetPlayerName(0) ~= "p_wargrey" then
                                                                if be:SYSgetPlayerName(0) == "p_bwargrey" then
                                                                    be:SYSctlDeviceFolder("SET", 0, "armor2", 35, 256, 0)
                                                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                                                    funcOpenMessage("mess")
                                                                    funcOneMessage(mswk25238)
                                                                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                                                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                                                else
                                                                end
                                                            end
                                                            be:SYSctlDeviceFolder("SET", 0, "armor2", 35, 256, 0)
                                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                                            funcOpenMessage("mess")
                                                            funcOneMessage(mswk25238)
                                                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                                                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                                        end
                                                    end
                                                    be:SYSctlDeviceFolder("SET", 0, "armor2", 41, 256, 0)
                                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                                    funcOpenMessage("mess")
                                                    funcOneMessage(mswk25237)
                                                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                                end
                                            end
                                            be:SYSctlDeviceFolder("SET", 0, "armor2", 38, 256, 0)
                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                            funcOpenMessage("mess")
                                            funcOneMessage(mswk25236)
                                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                        end
                                    end
                                    be:SYSctlDeviceFolder("SET", 0, "armor2", 23, 256, 0)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                    funcOpenMessage("mess")
                                    funcOneMessage(mswk25235)
                                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                end
                            end
                            be:SYSctlDeviceFolder("SET", 0, "armor2", 32, 256, 0)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25234)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        end
                    end
                    be:SYSctlDeviceFolder("SET", 0, "armor2", 29, 256, 0)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25233)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                elseif be:SYSgetPlayerNinzu() >= 2 then
                    if be:SYSgetPlayerName(0) ~= "p_agumon" and be:SYSgetPlayerName(0) ~= "p_hekabut" then
                        if be:SYSgetPlayerName(0) == "p_susanoo" then
                            be:SYSctlDeviceFolder("SET", 0, "armor2", 29, 256, 0)
                            be:SYSctlBit("ADD", 1, 15000)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25239)
                            funcOneMessage(mswk25227)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        else
                            if be:SYSgetPlayerName(0) ~= "p_vmon" and be:SYSgetPlayerName(0) ~= "p_angelr" then
                                if be:SYSgetPlayerName(0) == "p_dukecrim" then
                                    be:SYSctlDeviceFolder("SET", 0, "armor2", 32, 256, 0)
                                    be:SYSctlBit("ADD", 1, 15000)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                    funcOpenMessage("mess")
                                    funcOneMessage(mswk25240)
                                    funcOneMessage(mswk25227)
                                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                else
                                    if be:SYSgetPlayerName(0) ~= "p_girumon" then
                                        if be:SYSgetPlayerName(0) == "p_weregaru" then
                                            be:SYSctlDeviceFolder("SET", 0, "armor2", 23, 256, 0)
                                            be:SYSctlBit("ADD", 1, 15000)
                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                            funcOpenMessage("mess")
                                            funcOneMessage(mswk25241)
                                            funcOneMessage(mswk25227)
                                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                        else
                                            if be:SYSgetPlayerName(0) ~= "p_dorumon" and be:SYSgetPlayerName(0) ~= "p_alpha" then
                                                if be:SYSgetPlayerName(0) == "p_impdrapm" then
                                                    be:SYSctlDeviceFolder("SET", 0, "armor2", 38, 256, 0)
                                                    be:SYSctlBit("ADD", 1, 15000)
                                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                                    funcOpenMessage("mess")
                                                    funcOneMessage(mswk25242)
                                                    funcOneMessage(mswk25227)
                                                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                                else
                                                    if be:SYSgetPlayerName(0) ~= "p_beelzeb" and be:SYSgetPlayerName(0) ~= "p_impdrafm" then
                                                        if be:SYSgetPlayerName(0) == "p_metalgaru" then
                                                            be:SYSctlDeviceFolder("SET", 0, "armor2", 41, 256, 0)
                                                            be:SYSctlBit("ADD", 1, 15000)
                                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                                            funcOpenMessage("mess")
                                                            funcOneMessage(mswk25243)
                                                            funcOneMessage(mswk25227)
                                                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                                                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                                        else
                                                            if be:SYSgetPlayerName(0) ~= "p_wargrey" then
                                                                if be:SYSgetPlayerName(0) == "p_bwargrey" then
                                                                    be:SYSctlDeviceFolder("SET", 0, "armor2", 35, 256, 0)
                                                                    be:SYSctlBit("ADD", 1, 15000)
                                                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                                                    funcOpenMessage("mess")
                                                                    funcOneMessage(mswk25244)
                                                                    funcOneMessage(mswk25227)
                                                                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                                                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                                                else
                                                                end
                                                            end
                                                            be:SYSctlDeviceFolder("SET", 0, "armor2", 35, 256, 0)
                                                            be:SYSctlBit("ADD", 1, 15000)
                                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                                            funcOpenMessage("mess")
                                                            funcOneMessage(mswk25244)
                                                            funcOneMessage(mswk25227)
                                                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                                                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                                        end
                                                    end
                                                    be:SYSctlDeviceFolder("SET", 0, "armor2", 41, 256, 0)
                                                    be:SYSctlBit("ADD", 1, 15000)
                                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                                    funcOpenMessage("mess")
                                                    funcOneMessage(mswk25243)
                                                    funcOneMessage(mswk25227)
                                                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                                end
                                            end
                                            be:SYSctlDeviceFolder("SET", 0, "armor2", 38, 256, 0)
                                            be:SYSctlBit("ADD", 1, 15000)
                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                            funcOpenMessage("mess")
                                            funcOneMessage(mswk25242)
                                            funcOneMessage(mswk25227)
                                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                        end
                                    end
                                    be:SYSctlDeviceFolder("SET", 0, "armor2", 23, 256, 0)
                                    be:SYSctlBit("ADD", 1, 15000)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                    funcOpenMessage("mess")
                                    funcOneMessage(mswk25241)
                                    funcOneMessage(mswk25227)
                                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                end
                            end
                            be:SYSctlDeviceFolder("SET", 0, "armor2", 32, 256, 0)
                            be:SYSctlBit("ADD", 1, 15000)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25240)
                            funcOneMessage(mswk25227)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        end
                    end
                    be:SYSctlDeviceFolder("SET", 0, "armor2", 29, 256, 0)
                    be:SYSctlBit("ADD", 1, 15000)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25239)
                    funcOneMessage(mswk25227)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 4)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                else
                end
            end
        end
        if be:FLGisOn(570) == 1 then
            be:SYSctlBit("ADD", 0, 15000)
            be:SYSctlBit("ADD", 1, 15000)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25225)
            funcCloseMessage("mess", "n_digilfm", "fWt", 4)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
        else
        end
    end
    if be:FLGisOn(564) == 1 then
        be:FLGset(415, 0)
        be:FLGset(416, 0)
        be:FLGset(417, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:FLGset(443, 1)
        be:SYSctlBit("ADD", 0, 5000)
        be:SYSctlBit("ADD", 1, 5000)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25224)
        funcCloseMessage("mess", "n_digilfm", "fWt", 4)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    elseif be:FLGisOn(563) == 1 then
        be:FLGset(415, 0)
        be:FLGset(416, 0)
        be:FLGset(417, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:FLGset(443, 1)
        be:SYSctlBit("ADD", 0, 2000)
        be:SYSctlBit("ADD", 1, 2000)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25223)
        funcCloseMessage("mess", "n_digilfm", "fWt", 4)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    end
end
be:DMrun()
