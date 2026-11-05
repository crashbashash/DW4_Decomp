mswk25316 = "TALKFONT02/font00/I<633>"
mswk25317 = "TALKFONT02/font00/I<634>"
mswk25318 = "TALKFONT02/font00/I<635>"
mswk25319 = "TALKFONT01/font00/I<636>"
mswk25320 = "TALKFONT01/font00/I<637>"
mswk25321 = "TALKFONT01/font00/I<638>"
mswk25322 = "TALKFONT01/font00/I<639>"
mswk25323 = "TALKFONT01/font00/I<640>"
mswk25324 = "TALKFONT01/font00/I<641>"
mswk25325 = "TALKFONT01/font00/I<642>"
mswk25326 = "TALKFONT01/font00/I<643>"
mswk25327 = "TALKFONT01/font00/I<644>"
mswk25328 = "TALKFONT01/font00/I<645>"
mswk25329 = "TALKFONT01/font00/I<646>"
mswk25330 = "TALKFONT01/font00/I<647>"
mswk25331 = "TALKFONT01/font00/I<648>"
mswk25332 = "TALKFONT01/font00/I<649>"
mswk25333 = "TALKFONT01/font00/I<650>"
mswk25334 = "TALKFONT01/font00/I<651>"
mswk25335 = "TALKFONT01/font00/I<652>"
mswk25336 = "TALKFONT01/font00/I<653>"
mswk25337 = "TALKFONT01/font00/I<654>"
mswk25338 = "TALKFONT01/font00/I<655>"
mswk25339 = "TALKFONT02/font00/I<656>"
mswk25340 = "TALKFONT02/font00/I<657>"
for local_3 = 0, 3 do
    if local_6 > local_1 then
        local_0 = local_3
        local_1 = local_6
    end
end
funcCloseMessage("talk", "n_digilfm", "fWt", 9, "noturn")
if be:SYSgetDifficulty() == 0 then
    be:FLGset(475, 1)
    be:FLGset(432, 1)
    if local_0 == 0 then
        if be:SYSisGetShinkaDigimon(0, 5) == 0 then
            if be:SYSgetPlayerNinzu() == 1 then
                be:SYSctlShinka("SETSHINKA", 0, 5)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                funcOpenMessage("mess")
                funcOneMessage(mswk25319)
                funcCloseMessage("mess", "n_digilfm", "fWt", 9)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                be:DMrun()
            elseif be:SYSgetPlayerNinzu() >= 2 then
                be:SYSctlShinka("SETSHINKA", 0, 5)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                funcOpenMessage("mess")
                funcOneMessage(mswk25323)
                funcCloseMessage("mess", "n_digilfm", "fWt", 9)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                be:DMrun()
            else
            end
        end
        if be:SYSisGetShinkaDigimon(0, 5) == 1 then
            funcOpenMessage("talk", "n_digilfm", "fWt", 9)
            funcOneMessage(mswk25339)
            funcOneMessage(mswk25340)
            funcCloseMessage("talk", "n_digilfm", "fWt", 9)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMrun()
        else
        end
    end
    if local_0 == 1 then
        if be:SYSisGetShinkaDigimon(0, 4) == 0 then
            if be:SYSgetPlayerNinzu() == 1 then
                be:SYSctlShinka("SETSHINKA", 0, 4)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                funcOpenMessage("mess")
                funcOneMessage(mswk25320)
                funcCloseMessage("mess", "n_digilfm", "fWt", 9)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                be:DMrun()
            elseif be:SYSgetPlayerNinzu() >= 2 then
                be:SYSctlShinka("SETSHINKA", 0, 4)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                funcOpenMessage("mess")
                funcOneMessage(mswk25324)
                funcCloseMessage("mess", "n_digilfm", "fWt", 9)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                be:DMrun()
            else
            end
        end
        if be:SYSisGetShinkaDigimon(0, 4) == 1 then
            funcOpenMessage("talk", "n_digilfm", "fWt", 9)
            funcOneMessage(mswk25339)
            funcOneMessage(mswk25340)
            funcCloseMessage("talk", "n_digilfm", "fWt", 9)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMrun()
        else
        end
    end
    if local_0 == 2 then
        if be:SYSisGetShinkaDigimon(0, 6) == 0 then
            if be:SYSgetPlayerNinzu() == 1 then
                be:SYSctlShinka("SETSHINKA", 0, 6)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                funcOpenMessage("mess")
                funcOneMessage(mswk25321)
                funcCloseMessage("mess", "n_digilfm", "fWt", 9)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                be:DMrun()
            elseif be:SYSgetPlayerNinzu() >= 2 then
                be:SYSctlShinka("SETSHINKA", 0, 6)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                funcOpenMessage("mess")
                funcOneMessage(mswk25325)
                funcCloseMessage("mess", "n_digilfm", "fWt", 9)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                be:DMrun()
            else
            end
        end
        if be:SYSisGetShinkaDigimon(0, 6) == 1 then
            funcOpenMessage("talk", "n_digilfm", "fWt", 9)
            funcOneMessage(mswk25339)
            funcOneMessage(mswk25340)
            funcCloseMessage("talk", "n_digilfm", "fWt", 9)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMrun()
        else
        end
    end
    if local_0 == 3 then
        if be:SYSisGetShinkaDigimon(0, 7) == 0 then
            if be:SYSgetPlayerNinzu() == 1 then
                be:SYSctlShinka("SETSHINKA", 0, 7)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                funcOpenMessage("mess")
                funcOneMessage(mswk25322)
                funcCloseMessage("mess", "n_digilfm", "fWt", 9)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                be:DMrun()
            elseif be:SYSgetPlayerNinzu() >= 2 then
                be:SYSctlShinka("SETSHINKA", 0, 7)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                funcOpenMessage("mess")
                funcOneMessage(mswk25326)
                funcCloseMessage("mess", "n_digilfm", "fWt", 9)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                be:DMrun()
            else
            end
        end
        if be:SYSisGetShinkaDigimon(0, 7) == 1 then
            funcOpenMessage("talk", "n_digilfm", "fWt", 9)
            funcOneMessage(mswk25339)
            funcOneMessage(mswk25340)
            funcCloseMessage("talk", "n_digilfm", "fWt", 9)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMrun()
        else
        end
    end
end
if be:SYSgetDifficulty() == 1 then
    be:FLGset(477, 1)
    be:FLGset(439, 1)
    if local_0 ~= 0 then
        if local_0 == 3 then
            if be:SYSisGetShinkaDigimon(0, 8) == 0 then
                if be:SYSgetPlayerNinzu() == 1 then
                    be:SYSctlShinka("SETSHINKA", 0, 8)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25327)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 9)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:DMrun()
                elseif be:SYSgetPlayerNinzu() >= 2 then
                    be:SYSctlShinka("SETSHINKA", 0, 8)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25330)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 9)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:DMrun()
                else
                end
            end
            if be:SYSisGetShinkaDigimon(0, 8) == 1 then
                funcOpenMessage("talk", "n_digilfm", "fWt", 9)
                funcOneMessage(mswk25339)
                funcOneMessage(mswk25340)
                funcCloseMessage("talk", "n_digilfm", "fWt", 9)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                be:DMrun()
            else
            end
        end
    end
    if be:SYSisGetShinkaDigimon(0, 8) == 0 then
        if be:SYSgetPlayerNinzu() == 1 then
            be:SYSctlShinka("SETSHINKA", 0, 8)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25327)
            funcCloseMessage("mess", "n_digilfm", "fWt", 9)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
            be:DMrun()
        elseif be:SYSgetPlayerNinzu() >= 2 then
            be:SYSctlShinka("SETSHINKA", 0, 8)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25330)
            funcCloseMessage("mess", "n_digilfm", "fWt", 9)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
            be:DMrun()
        else
        end
    end
    if be:SYSisGetShinkaDigimon(0, 8) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt", 9)
        funcOneMessage(mswk25339)
        funcOneMessage(mswk25340)
        funcCloseMessage("talk", "n_digilfm", "fWt", 9)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMrun()
    else
    end
end
if be:SYSgetDifficulty() == 2 then
    if be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 0 then
        be:FLGset(479, 1)
        be:FLGset(446, 1)
        if be:SYSgetPlayerName(0) ~= "p_agumon" and be:SYSgetPlayerName(0) ~= "p_hekabut" and be:SYSgetPlayerName(0) ~= "p_susanoo" and be:SYSgetPlayerName(0) ~= "p_vmon" and be:SYSgetPlayerName(0) ~= "p_angelr" then
            if be:SYSgetPlayerName(0) == "p_dukecrim" then
                if be:SYSgetPlayerNinzu() == 1 then
                    be:SYSctlDeviceFolder("SET", 0, "armor1", 25, 150, 5)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25333)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 9)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:DMrun()
                elseif be:SYSgetPlayerNinzu() >= 2 then
                    be:SYSctlDeviceFolder("SET", 0, "armor1", 25, 150, 5)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25336)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 9)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:DMrun()
                else
                end
            end
        end
        if be:SYSgetPlayerNinzu() == 1 then
            be:SYSctlDeviceFolder("SET", 0, "armor1", 25, 150, 5)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25333)
            funcCloseMessage("mess", "n_digilfm", "fWt", 9)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
            be:DMrun()
        elseif be:SYSgetPlayerNinzu() >= 2 then
            be:SYSctlDeviceFolder("SET", 0, "armor1", 25, 150, 5)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25336)
            funcCloseMessage("mess", "n_digilfm", "fWt", 9)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
            be:DMrun()
        else
        end
    end
    if be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 1 then
        if be:SYSgetPlayerNinzu() == 1 then
            funcOpenMessage("talk", "n_digilfm", "fWt", 9)
            funcOneMessage(mswk25316)
            funcOneMessage(mswk25317)
            funcCloseMessage("talk", "n_digilfm", "fWt", 9)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMrun()
        elseif be:SYSgetPlayerNinzu() >= 2 then
            funcOpenMessage("talk", "n_digilfm", "fWt", 9)
            funcOneMessage(mswk25318)
            funcCloseMessage("talk", "n_digilfm", "fWt", 9)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMrun()
        end
    end
end
