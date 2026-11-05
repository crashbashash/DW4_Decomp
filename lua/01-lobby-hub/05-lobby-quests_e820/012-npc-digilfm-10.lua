mswk25176 = "TALKFONT02/font00/I<278>"
mswk25177 = "TALKFONT02/font00/I<343>"
mswk25178 = "TALKFONT01/font00/I<280>"
mswk25179 = "TALKFONT01/font00/I<281>"
mswk25180 = "TALKFONT01/font00/I<325>"
mswk25181 = "TALKFONT01/font00/I<372>"
mswk25182 = "TALKFONT01/font00/I<373>"
mswk25183 = "TALKFONT01/font00/I<374>"
mswk25184 = "TALKFONT01/font00/I<281>"
mswk25185 = "TALKFONT01/font00/I<282>"
mswk25186 = "TALKFONT01/font00/I<309>"
mswk25187 = "TALKFONT01/font00/I<374>"
mswk25188 = "TALKFONT01/font00/I<372>"
mswk25189 = "TALKFONT01/font00/I<373>"
mswk25190 = "TALKFONT01/font00/I<361>"
mswk25191 = "TALKFONT01/font00/I<360>"
mswk25192 = "TALKFONT01/font00/I<359>"
mswk25193 = "TALKFONT01/font00/I<358>"
mswk25194 = "TALKFONT01/font00/I<325>"
mswk25195 = "TALKFONT01/font00/I<309>"
mswk25196 = "TALKFONT01/font00/I<310>"
mswk25197 = "TALKFONT01/font00/I<326>"
mswk25198 = "TALKFONT01/font00/I<375>"
mswk25199 = "TALKFONT01/font00/I<376>"
mswk25200 = "TALKFONT01/font00/I<377>"
mswk25201 = "TALKFONT01/font00/I<378>"
mswk25202 = "TALKFONT01/font00/I<379>"
for local_3 = 0, 3 do
    if local_6 > local_1 then
        local_0 = local_3
        local_1 = local_6
    end
end
be:FLGset(409, 0)
be:FLGset(378, 0)
be:FLGset(386, 0)
be:FLGset(571, 0)
be:FLGset(424, 0)
be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWERON")
funcCloseMessage("talk", "n_digilfm", "fWt", 3, "noturn")
if be:SYSgetDifficulty() == 0 then
    if be:COUNTERget(0) >= 600 then
        if be:FLGisOn(557) == 0 then
            if be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 1 then
                g_IFLG10 = 0
                funcOpenMessage("talk", "n_digilfm", "fWt", 3)
                funcOneMessage(mswk25176)
                funcOneMessage(mswk25177)
                funcCloseMessage("talk", "n_digilfm", "fWt", 3)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                be:FLGset(409, 1)
                be:FLGset(378, 1)
                be:FLGset(386, 1)
                be:FLGset(571, 1)
                be:FLGset(417, 0)
                be:FLGset(424, 1)
                be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWEROF")
            elseif be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 0 then
                be:FLGset(415, 0)
                be:FLGset(416, 0)
                be:FLGset(418, 0)
                be:FLGset(419, 0)
                be:FLGset(420, 0)
                be:FLGset(557, 1)
                be:FLGset(428, 1)
                if be:SYSgetPlayerName(0) ~= "p_agumon" and be:SYSgetPlayerName(0) ~= "p_hekabut" and be:SYSgetPlayerName(0) ~= "p_susanoo" and be:SYSgetPlayerName(0) ~= "p_dorumon" and be:SYSgetPlayerName(0) ~= "p_alpha" then
                    if be:SYSgetPlayerName(0) == "p_impdrapm" then
                        be:SYSctlDeviceFolder("SET", 0, "armor1", 2, 17, 1)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25181)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    else
                        if be:SYSgetPlayerName(0) ~= "p_vmon" and be:SYSgetPlayerName(0) ~= "p_angelr" and be:SYSgetPlayerName(0) ~= "p_dukecrim" and be:SYSgetPlayerName(0) ~= "p_beelzeb" and be:SYSgetPlayerName(0) ~= "p_impdrafm" then
                            if be:SYSgetPlayerName(0) == "p_metalgaru" then
                                be:SYSctlDeviceFolder("SET", 0, "armor1", 11, 17, 1)
                                be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                funcOpenMessage("mess")
                                funcOneMessage(mswk25182)
                                funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            else
                                if be:SYSgetPlayerName(0) ~= "p_girumon" and be:SYSgetPlayerName(0) ~= "p_weregaru" and be:SYSgetPlayerName(0) ~= "p_wargrey" then
                                    if be:SYSgetPlayerName(0) == "p_bwargrey" then
                                        be:SYSctlDeviceFolder("SET", 0, "armor1", 20, 17, 1)
                                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                        funcOpenMessage("mess")
                                        funcOneMessage(mswk25183)
                                        funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                    else
                                    end
                                end
                                be:SYSctlDeviceFolder("SET", 0, "armor1", 20, 17, 1)
                                be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                funcOpenMessage("mess")
                                funcOneMessage(mswk25183)
                                funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            end
                        end
                        be:SYSctlDeviceFolder("SET", 0, "armor1", 11, 17, 1)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25182)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    end
                end
                be:SYSctlDeviceFolder("SET", 0, "armor1", 2, 17, 1)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                funcOpenMessage("mess")
                funcOneMessage(mswk25181)
                funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
            else
            end
        end
        if be:FLGisOn(557) == 1 then
            be:SYSctlBit("ADD", 0, 2000)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25180)
            funcCloseMessage("mess", "n_digilfm", "fWt", 3)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
        else
        end
    end
    if be:COUNTERget(0) >= 420 then
        be:FLGset(415, 0)
        be:FLGset(416, 0)
        be:FLGset(418, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:FLGset(428, 1)
        be:SYSctlBit("ADD", 0, 500)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25179)
        funcCloseMessage("mess", "n_digilfm", "fWt", 3)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    else
        be:FLGset(415, 0)
        be:FLGset(416, 0)
        be:FLGset(418, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:FLGset(428, 1)
        be:SYSctlBit("ADD", 0, 100)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25178)
        funcCloseMessage("mess", "n_digilfm", "fWt", 3)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    end
end
if be:SYSgetDifficulty() == 1 then
    if be:COUNTERget(0) >= 600 then
        if be:FLGisOn(562) == 1 then
            if be:FLGisOn(558) == 0 then
                if be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 1 then
                    g_IFLG10 = 0
                    funcOpenMessage("talk", "n_digilfm", "fWt", 3)
                    funcOneMessage(mswk25176)
                    funcOneMessage(mswk25177)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 3)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:FLGset(409, 1)
                    be:FLGset(378, 1)
                    be:FLGset(386, 1)
                    be:FLGset(571, 1)
                    be:FLGset(417, 0)
                    be:FLGset(424, 1)
                    be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWEROF")
                elseif be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 0 then
                    be:FLGset(415, 0)
                    be:FLGset(416, 0)
                    be:FLGset(418, 0)
                    be:FLGset(419, 0)
                    be:FLGset(420, 0)
                    be:FLGset(558, 1)
                    be:FLGset(435, 1)
                    if be:SYSgetPlayerName(0) ~= "p_agumon" and be:SYSgetPlayerName(0) ~= "p_hekabut" and be:SYSgetPlayerName(0) ~= "p_susanoo" and be:SYSgetPlayerName(0) ~= "p_dorumon" and be:SYSgetPlayerName(0) ~= "p_alpha" then
                        if be:SYSgetPlayerName(0) == "p_impdrapm" then
                            be:SYSctlDeviceFolder("SET", 0, "armor1", 2, 48, 2)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25188)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        else
                            if be:SYSgetPlayerName(0) ~= "p_vmon" and be:SYSgetPlayerName(0) ~= "p_angelr" and be:SYSgetPlayerName(0) ~= "p_dukecrim" and be:SYSgetPlayerName(0) ~= "p_beelzeb" and be:SYSgetPlayerName(0) ~= "p_impdrafm" then
                                if be:SYSgetPlayerName(0) == "p_metalgaru" then
                                    be:SYSctlDeviceFolder("SET", 0, "armor1", 11, 48, 2)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                    funcOpenMessage("mess")
                                    funcOneMessage(mswk25189)
                                    funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                else
                                    if be:SYSgetPlayerName(0) ~= "p_girumon" and be:SYSgetPlayerName(0) ~= "p_weregaru" and be:SYSgetPlayerName(0) ~= "p_wargrey" then
                                        if be:SYSgetPlayerName(0) == "p_bwargrey" then
                                            be:SYSctlDeviceFolder("SET", 0, "armor1", 20, 48, 2)
                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                            funcOpenMessage("mess")
                                            funcOneMessage(mswk25187)
                                            funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                        else
                                        end
                                    end
                                    be:SYSctlDeviceFolder("SET", 0, "armor1", 20, 48, 2)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                    funcOpenMessage("mess")
                                    funcOneMessage(mswk25187)
                                    funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                end
                            end
                            be:SYSctlDeviceFolder("SET", 0, "armor1", 11, 48, 2)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25189)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        end
                    end
                    be:SYSctlDeviceFolder("SET", 0, "armor1", 2, 48, 2)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25188)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                else
                end
            end
            if be:FLGisOn(558) == 1 then
                be:FLGset(415, 0)
                be:FLGset(416, 0)
                be:FLGset(418, 0)
                be:FLGset(419, 0)
                be:FLGset(420, 0)
                be:SYSctlBit("ADD", 0, 5000)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                funcOpenMessage("mess")
                funcOneMessage(mswk25186)
                funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
            else
            end
        end
        if be:FLGisOn(562) == 0 then
            if be:FLGisOn(559) == 0 then
                if local_0 == 0 then
                    be:FLGset(415, 0)
                    be:FLGset(416, 0)
                    be:FLGset(418, 0)
                    be:FLGset(419, 0)
                    be:FLGset(420, 0)
                    be:FLGset(435, 1)
                    if be:SYSisGetShinkaDigimon(0, 4) == 0 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25190)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlShinka("SETSHINKA", 0, 4)
                    elseif be:SYSisGetShinkaDigimon(0, 4) == 1 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25186)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlBit("ADD", 0, 5000)
                    else
                    end
                end
                if local_0 == 1 then
                    be:FLGset(415, 0)
                    be:FLGset(416, 0)
                    be:FLGset(418, 0)
                    be:FLGset(419, 0)
                    be:FLGset(420, 0)
                    be:FLGset(435, 1)
                    if be:SYSisGetShinkaDigimon(0, 5) == 0 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25191)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlShinka("SETSHINKA", 0, 5)
                    elseif be:SYSisGetShinkaDigimon(0, 5) == 1 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25186)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlBit("ADD", 0, 5000)
                    else
                    end
                end
                if local_0 == 2 then
                    be:FLGset(415, 0)
                    be:FLGset(416, 0)
                    be:FLGset(418, 0)
                    be:FLGset(419, 0)
                    be:FLGset(420, 0)
                    be:FLGset(435, 1)
                    if be:SYSisGetShinkaDigimon(0, 7) == 0 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25192)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlShinka("SETSHINKA", 0, 7)
                    elseif be:SYSisGetShinkaDigimon(0, 7) == 1 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25186)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlBit("ADD", 0, 5000)
                    else
                    end
                end
                if local_0 == 3 then
                    be:FLGset(415, 0)
                    be:FLGset(416, 0)
                    be:FLGset(418, 0)
                    be:FLGset(419, 0)
                    be:FLGset(420, 0)
                    be:FLGset(435, 1)
                    if be:SYSisGetShinkaDigimon(0, 6) == 0 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25193)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlShinka("SETSHINKA", 0, 6)
                    elseif be:SYSisGetShinkaDigimon(0, 6) == 1 then
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                        funcOpenMessage("mess")
                        funcOneMessage(mswk25186)
                        funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        be:SYSctlBit("ADD", 0, 5000)
                    else
                    end
                end
            end
            if be:FLGisOn(559) == 1 then
                be:FLGset(415, 0)
                be:FLGset(416, 0)
                be:FLGset(418, 0)
                be:FLGset(419, 0)
                be:FLGset(420, 0)
                be:SYSctlBit("ADD", 0, 5000)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                funcOpenMessage("mess")
                funcOneMessage(mswk25186)
                funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
            else
            end
        end
    end
    if be:COUNTERget(0) >= 420 then
        be:FLGset(415, 0)
        be:FLGset(416, 0)
        be:FLGset(418, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:FLGset(435, 1)
        be:SYSctlBit("ADD", 0, 1500)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25185)
        funcCloseMessage("mess", "n_digilfm", "fWt", 3)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    else
        be:FLGset(415, 0)
        be:FLGset(416, 0)
        be:FLGset(418, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:FLGset(435, 1)
        be:SYSctlBit("ADD", 0, 500)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25184)
        funcCloseMessage("mess", "n_digilfm", "fWt", 3)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    end
end
if be:SYSgetDifficulty() == 2 then
    if be:COUNTERget(0) >= 600 then
        if be:FLGisOn(562) == 1 then
            if be:FLGisOn(560) == 0 then
                if local_0 ~= 0 then
                    if local_0 == 2 then
                        be:FLGset(415, 0)
                        be:FLGset(416, 0)
                        be:FLGset(418, 0)
                        be:FLGset(419, 0)
                        be:FLGset(420, 0)
                        be:FLGset(442, 1)
                        if be:SYSisGetShinkaDigimon(0, 15) == 0 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25198)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:SYSctlShinka("SETSHINKA", 0, 15)
                        elseif be:SYSisGetShinkaDigimon(0, 15) == 1 then
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25196)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 3)
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
                be:FLGset(418, 0)
                be:FLGset(419, 0)
                be:FLGset(420, 0)
                be:FLGset(442, 1)
                if be:SYSisGetShinkaDigimon(0, 15) == 0 then
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25198)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:SYSctlShinka("SETSHINKA", 0, 15)
                elseif be:SYSisGetShinkaDigimon(0, 15) == 1 then
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25196)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:SYSctlBit("ADD", 0, 10000)
                else
                end
            end
            if be:FLGisOn(560) == 1 then
                be:FLGset(415, 0)
                be:FLGset(416, 0)
                be:FLGset(418, 0)
                be:FLGset(419, 0)
                be:FLGset(420, 0)
                be:SYSctlBit("ADD", 0, 10000)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                funcOpenMessage("mess")
                funcOneMessage(mswk25196)
                funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
            else
            end
        end
        if be:FLGisOn(562) == 0 then
            if be:FLGisOn(561) == 0 then
                if be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 1 then
                    g_IFLG10 = 0
                    funcOpenMessage("talk", "n_digilfm", "fWt", 3)
                    funcOneMessage(mswk25176)
                    funcOneMessage(mswk25177)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 3)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:FLGset(409, 1)
                    be:FLGset(378, 1)
                    be:FLGset(386, 1)
                    be:FLGset(571, 1)
                    be:FLGset(417, 0)
                    be:FLGset(424, 1)
                    be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWEROF")
                elseif be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 0 then
                    be:FLGset(415, 0)
                    be:FLGset(416, 0)
                    be:FLGset(418, 0)
                    be:FLGset(419, 0)
                    be:FLGset(420, 0)
                    be:FLGset(561, 1)
                    be:FLGset(442, 1)
                    if be:SYSgetPlayerName(0) ~= "p_agumon" and be:SYSgetPlayerName(0) ~= "p_hekabut" and be:SYSgetPlayerName(0) ~= "p_susanoo" and be:SYSgetPlayerName(0) ~= "p_dorumon" and be:SYSgetPlayerName(0) ~= "p_alpha" then
                        if be:SYSgetPlayerName(0) == "p_impdrapm" then
                            be:SYSctlDeviceFolder("SET", 0, "armor1", 5, 108, 3)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25200)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        else
                            if be:SYSgetPlayerName(0) ~= "p_vmon" and be:SYSgetPlayerName(0) ~= "p_angelr" and be:SYSgetPlayerName(0) ~= "p_dukecrim" and be:SYSgetPlayerName(0) ~= "p_beelzeb" and be:SYSgetPlayerName(0) ~= "p_impdrafm" then
                                if be:SYSgetPlayerName(0) == "p_metalgaru" then
                                    be:SYSctlDeviceFolder("SET", 0, "armor1", 14, 108, 3)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                    funcOpenMessage("mess")
                                    funcOneMessage(mswk25201)
                                    funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                else
                                    if be:SYSgetPlayerName(0) ~= "p_girumon" and be:SYSgetPlayerName(0) ~= "p_weregaru" and be:SYSgetPlayerName(0) ~= "p_wargrey" then
                                        if be:SYSgetPlayerName(0) == "p_bwargrey" then
                                            be:SYSctlDeviceFolder("SET", 0, "armor1", 23, 108, 3)
                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                            funcOpenMessage("mess")
                                            funcOneMessage(mswk25202)
                                            funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                        else
                                        end
                                    end
                                    be:SYSctlDeviceFolder("SET", 0, "armor1", 23, 108, 3)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                                    funcOpenMessage("mess")
                                    funcOneMessage(mswk25202)
                                    funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                                end
                            end
                            be:SYSctlDeviceFolder("SET", 0, "armor1", 14, 108, 3)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25201)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                        end
                    end
                    be:SYSctlDeviceFolder("SET", 0, "armor1", 5, 108, 3)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25200)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                else
                end
            end
            if be:FLGisOn(561) == 1 then
                be:FLGset(415, 0)
                be:FLGset(416, 0)
                be:FLGset(418, 0)
                be:FLGset(419, 0)
                be:FLGset(420, 0)
                be:SYSctlBit("ADD", 0, 15000)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                funcOpenMessage("mess")
                funcOneMessage(mswk25197)
                funcCloseMessage("mess", "n_digilfm", "fWt", 3)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
            else
            end
        end
    end
    if be:COUNTERget(0) >= 420 then
        be:FLGset(415, 0)
        be:FLGset(416, 0)
        be:FLGset(418, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:FLGset(442, 1)
        be:SYSctlBit("ADD", 0, 5000)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25195)
        funcCloseMessage("mess", "n_digilfm", "fWt", 3)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    else
        be:FLGset(415, 0)
        be:FLGset(416, 0)
        be:FLGset(418, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:FLGset(442, 1)
        be:SYSctlBit("ADD", 0, 2000)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25194)
        funcCloseMessage("mess", "n_digilfm", "fWt", 3)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    end
end
be:DMrun()
