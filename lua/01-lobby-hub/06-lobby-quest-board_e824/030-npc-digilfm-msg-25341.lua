mswk25341 = "TALKFONT02/font00/I<658>"
mswk25342 = "TALKFONT02/font00/I<659>"
mswk25343 = "TALKFONT02/font00/I<660>"
mswk25344 = "TALKFONT01/font00/I<661>"
mswk25345 = "TALKFONT01/font00/I<662>"
mswk25346 = "TALKFONT01/font00/I<663>"
mswk25347 = "TALKFONT01/font00/I<664>"
mswk25348 = "TALKFONT01/font00/I<665>"
mswk25349 = "TALKFONT01/font00/I<666>"
mswk25350 = "TALKFONT01/font00/I<667>"
mswk25351 = "TALKFONT01/font00/I<668>"
mswk25352 = "TALKFONT01/font00/I<669>"
mswk25353 = "TALKFONT01/font00/I<670>"
mswk25354 = "TALKFONT01/font00/I<671>"
mswk25355 = "TALKFONT01/font00/I<672>"
mswk25356 = "TALKFONT01/font00/I<673>"
mswk25357 = "TALKFONT01/font00/I<674>"
mswk25358 = "TALKFONT01/font00/I<675>"
mswk25359 = "TALKFONT01/font00/I<676>"
mswk25360 = "TALKFONT02/font00/I<677>"
mswk25361 = "TALKFONT02/font00/I<678>"
funcCloseMessage("talk", "n_digilfm", "fWt", 10, "noturn")
if be:SYSgetDifficulty() == 0 then
    if be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 0 then
        be:FLGset(476, 1)
        if be:SYSgetPlayerName(0) ~= "p_agumon" and be:SYSgetPlayerName(0) ~= "p_hekabut" then
            if be:SYSgetPlayerName(0) == "p_susanoo" then
            end
        end
        if be:SYSgetPlayerNinzu() == 1 then
            be:SYSctlDeviceFolder("SET", 0, "weapon", 0, 666, 0)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25344)
            funcCloseMessage("mess", "n_digilfm", "fWt", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
            be:DMrun()
        elseif be:SYSgetPlayerNinzu() >= 2 then
            be:SYSctlDeviceFolder("SET", 0, "weapon", 0, 666, 0)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25350)
            funcCloseMessage("mess", "n_digilfm", "fWt", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
            be:DMrun()
        else
        end
    elseif be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 1 then
        if be:SYSgetPlayerNinzu() == 1 then
            funcOpenMessage("talk", "n_digilfm", "fWt", 10)
            funcOneMessage(mswk25341)
            funcCloseMessage("talk", "n_digilfm", "fWt", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMrun()
        elseif be:SYSgetPlayerNinzu() >= 2 then
            funcOpenMessage("talk", "n_digilfm", "fWt", 10)
            funcOneMessage(mswk25342)
            funcOneMessage(mswk25343)
            funcCloseMessage("talk", "n_digilfm", "fWt", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMrun()
        end
    end
elseif be:SYSgetDifficulty() == 1 then
    if be:SYSisGetShinkaDigimon(0, 10) == 0 then
        be:FLGset(478, 1)
        if be:SYSgetPlayerNinzu() == 1 then
            be:SYSctlShinka("SETSHINKA", 0, 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25356)
            funcCloseMessage("talk", "n_digilfm", "fWt", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
            be:DMrun()
        elseif be:SYSgetPlayerNinzu() >= 2 then
            be:SYSctlShinka("SETSHINKA", 0, 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25357)
            funcCloseMessage("talk", "n_digilfm", "fWt", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
            be:DMrun()
        end
    elseif be:SYSisGetShinkaDigimon(0, 10) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt", 10)
        funcOneMessage(mswk25360)
        funcOneMessage(mswk25361)
        funcCloseMessage("talk", "n_digilfm", "fWt", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMrun()
    end
elseif be:SYSgetDifficulty() == 2 then
    if be:SYSisGetShinkaDigimon(0, 12) == 0 then
        be:FLGset(480, 1)
        if be:SYSgetPlayerNinzu() == 1 then
            be:SYSctlShinka("SETSHINKA", 0, 12)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25358)
            funcCloseMessage("talk", "n_digilfm", "fWt", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
            be:DMrun()
        elseif be:SYSgetPlayerNinzu() >= 2 then
            be:SYSctlShinka("SETSHINKA", 0, 12)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25359)
            funcCloseMessage("talk", "n_digilfm", "fWt", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
            be:DMrun()
        end
    elseif be:SYSisGetShinkaDigimon(0, 12) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt", 10)
        funcOneMessage(mswk25360)
        funcOneMessage(mswk25361)
        funcCloseMessage("talk", "n_digilfm", "fWt", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMrun()
    end
end
