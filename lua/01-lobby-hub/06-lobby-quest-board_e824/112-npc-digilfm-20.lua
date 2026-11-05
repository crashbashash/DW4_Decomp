mswk25290 = "TALKFONT02/font00/I<607>"
mswk25291 = "TALKFONT02/font00/I<608>"
mswk25292 = "TALKFONT02/font00/I<609>"
mswk25293 = "TALKFONT02/font00/I<610>"
mswk25294 = "TALKFONT02/font00/I<611>"
mswk25295 = "TALKFONT02/font00/I<612>"
mswk25296 = "TALKFONT02/font00/I<613>"
mswk25297 = "TALKFONT01/font00/I<614>"
mswk25298 = "TALKFONT01/font00/I<615>"
mswk25299 = "TALKFONT01/font00/I<616>"
mswk25300 = "TALKFONT01/font00/I<617>"
mswk25301 = "TALKFONT01/font00/I<618>"
mswk25302 = "TALKFONT01/font00/I<619>"
mswk25303 = "TALKFONT01/font00/I<620>"
mswk25304 = "TALKFONT01/font00/I<621>"
mswk25305 = "TALKFONT01/font00/I<622>"
mswk25306 = "TALKFONT01/font00/I<623>"
mswk25307 = "TALKFONT01/font00/I<624>"
mswk25308 = "TALKFONT01/font00/I<625>"
mswk25309 = "TALKFONT01/font00/I<626>"
mswk25310 = "TALKFONT01/font00/I<627>"
mswk25311 = "TALKFONT01/font00/I<628>"
mswk25312 = "TALKFONT01/font00/I<629>"
mswk25313 = "TALKFONT01/font00/I<630>"
mswk25314 = "TALKFONT01/font00/I<631>"
mswk25315 = "TALKFONT02/font00/I<632>"
for local_3 = 0, 3 do
    if local_6 > local_1 then
        local_0 = local_3
        local_1 = local_6
    end
end
be:FLGset(409, 0)
be:FLGset(381, 0)
be:FLGset(389, 0)
be:FLGset(424, 0)
be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWERON")
funcCloseMessage("talk", "n_digilfm", "fWt", 8, "noturn")
if be:SYSgetDifficulty() == 0 then
    if be:FLGisOn(595) == 1 then
        be:FLGset(415, 0)
        be:FLGset(416, 0)
        be:FLGset(417, 0)
        be:FLGset(418, 0)
        be:FLGset(419, 0)
        if be:SYSctlDeviceFolder("IS", 0, "weapon", 200, 0, 0) == 0 then
            funcOpenMessage("talk", "n_digilfm", "fWt", 8)
            funcOneMessage(mswk25290)
            funcOneMessage(mswk25291)
            funcCloseMessage("talk", "n_digilfm", "fWt", 8)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMrun()
        elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 200, 0, 0) == 1 then
            funcOpenMessage("talk", "n_digilfm", "fWt", 8)
            funcOneMessage(mswk25315)
            funcCloseMessage("talk", "n_digilfm", "fWt", 8)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMrun()
        else
        end
    end
    if be:FLGisOn(595) == 0 then
        if be:SYSctlDeviceFolder("IS", 0, "weapon", 200, 0, 0) == 0 then
            be:FLGset(415, 0)
            be:FLGset(416, 0)
            be:FLGset(417, 0)
            be:FLGset(418, 0)
            be:FLGset(419, 0)
            be:FLGset(431, 1)
            funcOpenMessage("talk", "n_digilfm", "fWt", 8)
            funcOneMessage(mswk25290)
            funcOneMessage(mswk25291)
            funcCloseMessage("talk", "n_digilfm", "fWt", 8)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMrun()
        elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 200, 0, 0) == 1 then
            if be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 0 then
                be:FLGset(415, 0)
                be:FLGset(416, 0)
                be:FLGset(417, 0)
                be:FLGset(418, 0)
                be:FLGset(419, 0)
                be:FLGset(595, 1)
                be:FLGset(431, 1)
                if be:SYSgetPlayerName(0) ~= "p_agumon" and be:SYSgetPlayerName(0) ~= "p_hekabut" then
                    if be:SYSgetPlayerName(0) == "p_susanoo" then
                        if be:SYSgetPlayerNinzu() == 1 then
                            be:SYSctlDeviceFolder("SET", 0, "weapon", 103, 32, 3)
                            funcOpenMessage("talk", "n_digilfm", "fWt", 8)
                            funcOneMessage(mswk25292)
                            funcOneMessage(mswk25293)
                            funcOneMessage(mswk25294)
                            funcCloseMessage("talk", "n_digilfm", "fWt", 8, "noturn")
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25297)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 8)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:DMrun()
                        elseif be:SYSgetPlayerNinzu() >= 2 then
                            be:SYSctlDeviceFolder("SET", 0, "weapon", 103, 32, 3)
                            funcOpenMessage("talk", "n_digilfm", "fWt", 8)
                            funcOneMessage(mswk25292)
                            funcOneMessage(mswk25293)
                            funcOneMessage(mswk25294)
                            funcCloseMessage("talk", "n_digilfm", "fWt", 8, "noturn")
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25303)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 8)
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
                    be:SYSctlDeviceFolder("SET", 0, "weapon", 103, 32, 3)
                    funcOpenMessage("talk", "n_digilfm", "fWt", 8)
                    funcOneMessage(mswk25292)
                    funcOneMessage(mswk25293)
                    funcOneMessage(mswk25294)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 8, "noturn")
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25297)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 8)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:DMrun()
                elseif be:SYSgetPlayerNinzu() >= 2 then
                    be:SYSctlDeviceFolder("SET", 0, "weapon", 103, 32, 3)
                    funcOpenMessage("talk", "n_digilfm", "fWt", 8)
                    funcOneMessage(mswk25292)
                    funcOneMessage(mswk25293)
                    funcOneMessage(mswk25294)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 8, "noturn")
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25303)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 8)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:DMrun()
                else
                end
            end
            if be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 1 then
                be:FLGset(409, 1)
                be:FLGset(381, 1)
                be:FLGset(389, 1)
                g_IFLG13 = 0
                be:FLGset(420, 0)
                be:FLGset(424, 1)
                be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWERON")
                if be:SYSgetPlayerNinzu() == 1 then
                    funcOpenMessage("talk", "n_digilfm", "fWt", 8)
                    funcOneMessage(mswk25292)
                    funcOneMessage(mswk25293)
                    funcOneMessage(mswk25294)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 8, "noturn")
                    funcOpenMessage("talk", "n_digilfm", "fWt", 8)
                    funcOneMessage(mswk25295)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 8)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMrun()
                elseif be:SYSgetPlayerNinzu() >= 2 then
                    funcOpenMessage("talk", "n_digilfm", "fWt", 8)
                    funcOneMessage(mswk25292)
                    funcOneMessage(mswk25293)
                    funcOneMessage(mswk25294)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 8, "noturn")
                    funcOpenMessage("talk", "n_digilfm", "fWt", 8)
                    funcOneMessage(mswk25296)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 8)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMrun()
                else
                end
            end
        end
    end
end
if be:SYSgetDifficulty() == 1 then
    if be:FLGisOn(596) == 1 then
        be:FLGset(415, 0)
        be:FLGset(416, 0)
        be:FLGset(417, 0)
        be:FLGset(418, 0)
        be:FLGset(419, 0)
        if be:SYSctlDeviceFolder("IS", 0, "weapon", 208, 0, 0) == 0 then
            funcOpenMessage("talk", "n_digilfm", "fWt", 8)
            funcOneMessage(mswk25290)
            funcOneMessage(mswk25291)
            funcCloseMessage("talk", "n_digilfm", "fWt", 8)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMrun()
        elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 208, 0, 0) == 1 then
            funcOpenMessage("talk", "n_digilfm", "fWt", 8)
            funcOneMessage(mswk25315)
            funcCloseMessage("talk", "n_digilfm", "fWt", 8)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMrun()
        else
        end
    end
    if be:FLGisOn(596) == 0 then
        if be:SYSctlDeviceFolder("IS", 0, "weapon", 208, 0, 0) == 0 then
            be:FLGset(415, 0)
            be:FLGset(416, 0)
            be:FLGset(417, 0)
            be:FLGset(418, 0)
            be:FLGset(419, 0)
            be:FLGset(438, 1)
            funcOpenMessage("talk", "n_digilfm", "fWt", 8)
            funcOneMessage(mswk25290)
            funcOneMessage(mswk25291)
            funcCloseMessage("talk", "n_digilfm", "fWt", 8)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMrun()
        elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 208, 0, 0) == 1 then
            be:FLGset(415, 0)
            be:FLGset(416, 0)
            be:FLGset(417, 0)
            be:FLGset(418, 0)
            be:FLGset(419, 0)
            be:FLGset(438, 1)
            if local_0 ~= 0 then
                if local_0 == 2 then
                    if be:SYSisGetShinkaDigimon(0, 13) == 1 then
                        funcOpenMessage("talk", "n_digilfm", "fWt", 8)
                        funcOneMessage(mswk25290)
                        funcOneMessage(mswk25291)
                        funcCloseMessage("talk", "n_digilfm", "fWt", 8)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                        be:DMrun()
                    elseif be:SYSisGetShinkaDigimon(0, 13) == 0 then
                        if be:SYSgetPlayerNinzu() == 1 then
                            be:SYSctlShinka("SETSHINKA", 0, 13)
                            funcOpenMessage("talk", "n_digilfm", "fWt", 8)
                            funcOneMessage(mswk25292)
                            funcOneMessage(mswk25293)
                            funcOneMessage(mswk25294)
                            funcCloseMessage("talk", "n_digilfm", "fWt", 8, "noturn")
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25309)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 8)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:DMrun()
                        elseif be:SYSgetPlayerNinzu() >= 2 then
                            be:SYSctlShinka("SETSHINKA", 0, 13)
                            funcOpenMessage("talk", "n_digilfm", "fWt", 8)
                            funcOneMessage(mswk25292)
                            funcOneMessage(mswk25293)
                            funcOneMessage(mswk25294)
                            funcCloseMessage("talk", "n_digilfm", "fWt", 8, "noturn")
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                            funcOpenMessage("mess")
                            funcOneMessage(mswk25311)
                            funcCloseMessage("mess", "n_digilfm", "fWt", 8)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                            be:DMrun()
                        else
                        end
                    end
                end
            end
            if be:SYSisGetShinkaDigimon(0, 13) == 1 then
                funcOpenMessage("talk", "n_digilfm", "fWt", 8)
                funcOneMessage(mswk25290)
                funcOneMessage(mswk25291)
                funcCloseMessage("talk", "n_digilfm", "fWt", 8)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                be:DMrun()
            elseif be:SYSisGetShinkaDigimon(0, 13) == 0 then
                if be:SYSgetPlayerNinzu() == 1 then
                    be:SYSctlShinka("SETSHINKA", 0, 13)
                    funcOpenMessage("talk", "n_digilfm", "fWt", 8)
                    funcOneMessage(mswk25292)
                    funcOneMessage(mswk25293)
                    funcOneMessage(mswk25294)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 8, "noturn")
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25309)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 8)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:DMrun()
                elseif be:SYSgetPlayerNinzu() >= 2 then
                    be:SYSctlShinka("SETSHINKA", 0, 13)
                    funcOpenMessage("talk", "n_digilfm", "fWt", 8)
                    funcOneMessage(mswk25292)
                    funcOneMessage(mswk25293)
                    funcOneMessage(mswk25294)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 8, "noturn")
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25311)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 8)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:DMrun()
                else
                end
            end
        end
    end
end
if be:SYSgetDifficulty() == 2 then
    if be:FLGisOn(597) == 1 then
        be:FLGset(415, 0)
        be:FLGset(416, 0)
        be:FLGset(417, 0)
        be:FLGset(418, 0)
        be:FLGset(419, 0)
        if be:SYSctlDeviceFolder("IS", 0, "weapon", 212, 0, 0) == 0 then
            funcOpenMessage("talk", "n_digilfm", "fWt", 8)
            funcOneMessage(mswk25290)
            funcOneMessage(mswk25291)
            funcCloseMessage("talk", "n_digilfm", "fWt", 8)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMrun()
        elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 212, 0, 0) == 1 then
            funcOpenMessage("talk", "n_digilfm", "fWt", 8)
            funcOneMessage(mswk25315)
            funcCloseMessage("talk", "n_digilfm", "fWt", 8)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMrun()
        else
        end
    end
    if be:FLGisOn(597) == 0 then
        if be:SYSctlDeviceFolder("IS", 0, "weapon", 212, 0, 0) == 0 then
            be:FLGset(415, 0)
            be:FLGset(416, 0)
            be:FLGset(417, 0)
            be:FLGset(418, 0)
            be:FLGset(419, 0)
            be:FLGset(445, 1)
            funcOpenMessage("talk", "n_digilfm", "fWt", 8)
            funcOneMessage(mswk25290)
            funcOneMessage(mswk25291)
            funcCloseMessage("talk", "n_digilfm", "fWt", 8)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMrun()
        elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 212, 0, 0) == 1 then
            be:FLGset(415, 0)
            be:FLGset(416, 0)
            be:FLGset(417, 0)
            be:FLGset(418, 0)
            be:FLGset(419, 0)
            be:FLGset(445, 1)
            if be:SYSisGetShinkaDigimon(0, 14) == 1 then
                funcOpenMessage("talk", "n_digilfm", "fWt", 8)
                funcOneMessage(mswk25290)
                funcOneMessage(mswk25291)
                funcCloseMessage("talk", "n_digilfm", "fWt", 8)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                be:DMrun()
            elseif be:SYSisGetShinkaDigimon(0, 14) == 0 then
                if be:SYSgetPlayerNinzu() == 1 then
                    be:SYSctlShinka("SETSHINKA", 0, 14)
                    funcOpenMessage("talk", "n_digilfm", "fWt", 8)
                    funcOneMessage(mswk25292)
                    funcOneMessage(mswk25293)
                    funcOneMessage(mswk25294)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 8, "noturn")
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25313)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 8)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:DMrun()
                elseif be:SYSgetPlayerNinzu() >= 2 then
                    be:SYSctlShinka("SETSHINKA", 0, 14)
                    funcOpenMessage("talk", "n_digilfm", "fWt", 8)
                    funcOneMessage(mswk25292)
                    funcOneMessage(mswk25293)
                    funcOneMessage(mswk25294)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 8, "noturn")
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25314)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 8)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                    be:DMrun()
                end
            end
        end
    end
end
