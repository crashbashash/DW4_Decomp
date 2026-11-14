mswk25092 = "TALKFONT02/font00/I<278>"
mswk25093 = "TALKFONT02/font00/I<279>"
mswk25094 = "TALKFONT01/font00/I<280>"
mswk25095 = "TALKFONT01/font00/I<281>"
mswk25096 = "TALKFONT01/font00/I<282>"
mswk25097 = "TALKFONT01/font00/I<283>"
mswk25386 = "TALKFONT01/font00/I<284>"
mswk25387 = "TALKFONT01/font00/I<285>"
mswk25388 = "TALKFONT01/font00/I<286>"
mswk25389 = "TALKFONT01/font00/I<287>"
mswk25390 = "TALKFONT01/font00/I<288>"
mswk25391 = "TALKFONT01/font00/I<289>"
mswk25392 = "TALKFONT01/font00/I<290>"
mswk25393 = "TALKFONT01/font00/I<291>"
mswk25394 = "TALKFONT01/font00/I<292>"
mswk25395 = "TALKFONT01/font00/I<293>"
mswk25396 = "TALKFONT01/font00/I<294>"
mswk25397 = "TALKFONT01/font00/I<295>"
mswk25098 = "TALKFONT01/font00/I<296>"
mswk25099 = "TALKFONT01/font00/I<297>"
mswk25100 = "TALKFONT01/font00/I<298>"
mswk25101 = "TALKFONT01/font00/I<299>"
mswk25102 = "TALKFONT01/font00/I<300>"
mswk25103 = "TALKFONT01/font00/I<301>"
mswk25104 = "TALKFONT01/font00/I<302>"
mswk25105 = "TALKFONT01/font00/I<303>"
mswk25106 = "TALKFONT01/font00/I<304>"
mswk25107 = "TALKFONT01/font00/I<305>"
mswk25108 = "TALKFONT01/font00/I<306>"
mswk25109 = "TALKFONT01/font00/I<307>"
mswk25110 = "TALKFONT01/font00/I<281>"
mswk25111 = "TALKFONT01/font00/I<308>"
mswk25112 = "TALKFONT01/font00/I<309>"
mswk25113 = "TALKFONT01/font00/I<310>"
mswk25114 = "TALKFONT01/font00/I<311>"
mswk25115 = "TALKFONT01/font00/I<312>"
mswk25116 = "TALKFONT01/font00/I<313>"
mswk25117 = "TALKFONT01/font00/I<314>"
mswk25118 = "TALKFONT01/font00/I<315>"
mswk25119 = "TALKFONT01/font00/I<316>"
mswk25120 = "TALKFONT01/font00/I<317>"
mswk25121 = "TALKFONT01/font00/I<318>"
mswk25122 = "TALKFONT01/font00/I<319>"
mswk25123 = "TALKFONT01/font00/I<320>"
mswk25124 = "TALKFONT01/font00/I<321>"
mswk25125 = "TALKFONT01/font00/I<322>"
mswk25126 = "TALKFONT01/font00/I<323>"
mswk25127 = "TALKFONT01/font00/I<324>"
mswk25128 = "TALKFONT01/font00/I<325>"
mswk25129 = "TALKFONT01/font00/I<309>"
mswk25130 = "TALKFONT01/font00/I<326>"
mswk25131 = "TALKFONT01/font00/I<327>"
mswk25132 = "TALKFONT01/font00/I<328>"
mswk25133 = "TALKFONT01/font00/I<329>"
mswk25134 = "TALKFONT01/font00/I<330>"
mswk25135 = "TALKFONT01/font00/I<331>"
mswk25136 = "TALKFONT01/font00/I<332>"
mswk25137 = "TALKFONT01/font00/I<333>"
mswk25138 = "TALKFONT01/font00/I<334>"
mswk25139 = "TALKFONT01/font00/I<335>"
mswk25140 = "TALKFONT01/font00/I<336>"
mswk25141 = "TALKFONT01/font00/I<337>"
mswk25142 = "TALKFONT01/font00/I<338>"
mswk25143 = "TALKFONT01/font00/I<339>"
mswk25144 = "TALKFONT01/font00/I<340>"
mswk25145 = "TALKFONT01/font00/I<341>"
mswk25146 = "TALKFONT02/font00/I<342>"
mswk25147 = "TALKFONT02/font00/I<343>"
mswk25374 = "TALKFONT01/font00/I<344>"
mswk25375 = "TALKFONT01/font00/I<345>"
mswk25376 = "TALKFONT01/font00/I<346>"
mswk25377 = "TALKFONT01/font00/I<347>"
mswk25378 = "TALKFONT01/font00/I<348>"
mswk25379 = "TALKFONT01/font00/I<349>"
mswk25380 = "TALKFONT01/font00/I<350>"
mswk25381 = "TALKFONT01/font00/I<351>"
mswk25382 = "TALKFONT01/font00/I<352>"
mswk25383 = "TALKFONT01/font00/I<353>"
mswk25384 = "TALKFONT01/font00/I<354>"
mswk25385 = "TALKFONT01/font00/I<355>"
be:FLGset(409, 0)
be:FLGset(376, 0)
be:FLGset(384, 0)
be:FLGset(571, 0)
be:FLGset(424, 0)
be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWERON")
funcCloseMessage("talk", "n_digilfm", "fWt", 1, "noturn")
if be:SYSgetDifficulty() == 0 then
    if be:COUNTERget(0) >= 900 then
        be:FLGset(426, 1)
        be:FLGset(416, 0)
        be:FLGset(417, 0)
        be:FLGset(418, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:SYSctlBit("ADD", 0, 100)
        be:SYSctlBit("ADD", 1, 100)
        be:SYSctlBit("ADD", 2, 100)
        be:SYSctlBit("ADD", 3, 100)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25094)
        funcCloseMessage("mess", "n_digilfm", "fWt", 1)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    elseif be:COUNTERget(0) > 600 then
        be:FLGset(426, 1)
        be:FLGset(416, 0)
        be:FLGset(417, 0)
        be:FLGset(418, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:SYSctlBit("ADD", 0, 500)
        be:SYSctlBit("ADD", 1, 500)
        be:SYSctlBit("ADD", 2, 500)
        be:SYSctlBit("ADD", 3, 500)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25095)
        funcCloseMessage("mess", "n_digilfm", "fWt", 1)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    elseif be:COUNTERget(0) >= 0 then
        if be:FLGisOn(509) == 0 then
            if be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 1 then
                g_IFLG08 = 0
                if be:SYSgetPlayerNinzu() == 1 then
                    funcOpenMessage("talk", "n_digilfm", "fWt", 1)
                    funcOneMessage(mswk25092)
                    funcOneMessage(mswk25093)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 1)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:FLGset(409, 1)
                    be:FLGset(376, 1)
                    be:FLGset(384, 1)
                    be:FLGset(571, 1)
                    be:FLGset(415, 0)
                    be:FLGset(424, 1)
                    be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWEROF")
                elseif be:SYSgetPlayerNinzu() >= 2 then
                    funcOpenMessage("talk", "n_digilfm", "fWt", 1)
                    funcOneMessage(mswk25146)
                    funcOneMessage(mswk25147)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 1)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:FLGset(409, 1)
                    be:FLGset(376, 1)
                    be:FLGset(384, 1)
                    be:FLGset(571, 1)
                    be:FLGset(415, 0)
                    be:FLGset(424, 1)
                    be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWEROF")
                end
            elseif be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 0 then
                be:FLGset(416, 0)
                be:FLGset(417, 0)
                be:FLGset(418, 0)
                be:FLGset(419, 0)
                be:FLGset(420, 0)
                be:FLGset(509, 1)
                be:FLGset(426, 1)
                if be:SYSgetPlayerNinzu() == 1 then
                    if be:SYSgetPlayerName(0) ~= "p_agumon" and be:SYSgetPlayerName(0) ~= "p_hekabut" then
                        if be:SYSgetPlayerName(0) == "p_susanoo" then
                        end
                    end
                    be:SYSctlDeviceFolder("SET", 0, "weapon", 0, 20, 1)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25386)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 1)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                elseif be:SYSgetPlayerNinzu() >= 2 then
                    if be:SYSgetPlayerName(0) ~= "p_agumon" and be:SYSgetPlayerName(0) ~= "p_hekabut" then
                        if be:SYSgetPlayerName(0) == "p_susanoo" then
                        end
                    end
                    be:SYSctlDeviceFolder("SET", 0, "weapon", 0, 20, 1)
                    be:SYSctlBit("ADD", 1, 1500)
                    be:SYSctlBit("ADD", 2, 1500)
                    be:SYSctlBit("ADD", 3, 1500)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25392)
                    funcOneMessage(mswk25097)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 1)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                else
                end
            end
        elseif be:FLGisOn(509) == 1 then
            be:SYSctlBit("ADD", 0, 1500)
            be:SYSctlBit("ADD", 1, 1500)
            be:SYSctlBit("ADD", 2, 1500)
            be:SYSctlBit("ADD", 3, 1500)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25096)
            funcCloseMessage("mess", "n_digilfm", "fWt", 1)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
        end
    end
elseif be:SYSgetDifficulty() == 1 then
    if be:COUNTERget(0) >= 900 then
        be:FLGset(416, 0)
        be:FLGset(417, 0)
        be:FLGset(418, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:FLGset(433, 1)
        be:SYSctlBit("ADD", 0, 500)
        be:SYSctlBit("ADD", 1, 500)
        be:SYSctlBit("ADD", 2, 500)
        be:SYSctlBit("ADD", 3, 500)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25110)
        funcCloseMessage("mess", "n_digilfm", "fWt", 1)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    elseif be:COUNTERget(0) > 600 then
        be:FLGset(416, 0)
        be:FLGset(417, 0)
        be:FLGset(418, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:FLGset(433, 1)
        be:SYSctlBit("ADD", 0, 2500)
        be:SYSctlBit("ADD", 1, 2500)
        be:SYSctlBit("ADD", 2, 2500)
        be:SYSctlBit("ADD", 3, 2500)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25111)
        funcCloseMessage("mess", "n_digilfm", "fWt", 1)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    elseif be:COUNTERget(0) == 600 then
        if be:FLGisOn(510) == 0 then
            if be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 1 then
                g_IFLG08 = 0
                if be:SYSgetPlayerNinzu() == 1 then
                    funcOpenMessage("talk", "n_digilfm", "fWt", 1)
                    funcOneMessage(mswk25092)
                    funcOneMessage(mswk25093)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 1)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:FLGset(409, 1)
                    be:FLGset(376, 1)
                    be:FLGset(384, 1)
                    be:FLGset(571, 1)
                    be:FLGset(415, 0)
                    be:FLGset(424, 1)
                    be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWEROF")
                elseif be:SYSgetPlayerNinzu() >= 2 then
                    funcOpenMessage("talk", "n_digilfm", "fWt", 1)
                    funcOneMessage(mswk25146)
                    funcOneMessage(mswk25147)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 1)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:FLGset(409, 1)
                    be:FLGset(376, 1)
                    be:FLGset(384, 1)
                    be:FLGset(571, 1)
                    be:FLGset(415, 0)
                    be:FLGset(424, 1)
                    be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWEROF")
                end
            elseif be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 0 then
                be:FLGset(416, 0)
                be:FLGset(417, 0)
                be:FLGset(418, 0)
                be:FLGset(419, 0)
                be:FLGset(420, 0)
                be:FLGset(510, 1)
                be:FLGset(433, 1)
                if be:SYSgetPlayerNinzu() == 1 then
                    if be:SYSgetPlayerName(0) ~= "p_agumon" and be:SYSgetPlayerName(0) ~= "p_hekabut" then
                        if be:SYSgetPlayerName(0) == "p_susanoo" then
                        end
                    end
                    be:SYSctlDeviceFolder("SET", 0, "weapon", 14, 46, 2)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25098)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 1)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                elseif be:SYSgetPlayerNinzu() >= 2 then
                    if be:SYSgetPlayerName(0) ~= "p_agumon" and be:SYSgetPlayerName(0) ~= "p_hekabut" then
                        if be:SYSgetPlayerName(0) == "p_susanoo" then
                        end
                    end
                    be:SYSctlDeviceFolder("SET", 0, "weapon", 14, 46, 2)
                    be:SYSctlBit("ADD", 1, 10000)
                    be:SYSctlBit("ADD", 2, 10000)
                    be:SYSctlBit("ADD", 3, 10000)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25104)
                    funcOneMessage(mswk25115)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 1)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                else
                end
            end
        elseif be:FLGisOn(510) == 1 then
            be:SYSctlBit("ADD", 0, 10000)
            be:SYSctlBit("ADD", 1, 10000)
            be:SYSctlBit("ADD", 2, 10000)
            be:SYSctlBit("ADD", 3, 10000)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25113)
            funcCloseMessage("mess", "n_digilfm", "fWt", 1)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
        end
    elseif be:COUNTERget(0) >= 0 then
        if be:FLGisOn(511) == 0 then
            if be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 1 then
                g_IFLG08 = 0
                if be:SYSgetPlayerNinzu() == 1 then
                    funcOpenMessage("talk", "n_digilfm", "fWt", 1)
                    funcOneMessage(mswk25092)
                    funcOneMessage(mswk25093)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 1)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:FLGset(409, 1)
                    be:FLGset(376, 1)
                    be:FLGset(384, 1)
                    be:FLGset(571, 1)
                    be:FLGset(415, 0)
                    be:FLGset(424, 1)
                    be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWEROF")
                elseif be:SYSgetPlayerNinzu() >= 2 then
                    funcOpenMessage("talk", "n_digilfm", "fWt", 1)
                    funcOneMessage(mswk25146)
                    funcOneMessage(mswk25147)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 1)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:FLGset(409, 1)
                    be:FLGset(376, 1)
                    be:FLGset(384, 1)
                    be:FLGset(571, 1)
                    be:FLGset(415, 0)
                    be:FLGset(424, 1)
                    be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWEROF")
                end
            elseif be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 0 then
                be:FLGset(416, 0)
                be:FLGset(417, 0)
                be:FLGset(418, 0)
                be:FLGset(419, 0)
                be:FLGset(420, 0)
                be:FLGset(511, 1)
                be:FLGset(433, 1)
                if be:SYSgetPlayerNinzu() == 1 then
                    if be:SYSgetPlayerName(0) ~= "p_agumon" and be:SYSgetPlayerName(0) ~= "p_hekabut" then
                        if be:SYSgetPlayerName(0) == "p_susanoo" then
                        end
                    end
                    be:SYSctlDeviceFolder("SET", 0, "weapon", 12, 20, 2)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25116)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 1)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                elseif be:SYSgetPlayerNinzu() >= 2 then
                    if be:SYSgetPlayerName(0) ~= "p_agumon" and be:SYSgetPlayerName(0) ~= "p_hekabut" then
                        if be:SYSgetPlayerName(0) == "p_susanoo" then
                        end
                    end
                    be:SYSctlDeviceFolder("SET", 0, "weapon", 12, 20, 2)
                    be:SYSctlBit("ADD", 1, 5000)
                    be:SYSctlBit("ADD", 2, 5000)
                    be:SYSctlBit("ADD", 3, 5000)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25122)
                    funcOneMessage(mswk25114)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 1)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                else
                end
            end
        elseif be:FLGisOn(511) == 1 then
            be:SYSctlBit("ADD", 0, 5000)
            be:SYSctlBit("ADD", 1, 5000)
            be:SYSctlBit("ADD", 2, 5000)
            be:SYSctlBit("ADD", 3, 5000)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25112)
            funcCloseMessage("mess", "n_digilfm", "fWt", 1)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
        end
    end
elseif be:SYSgetDifficulty() == 2 then
    if be:COUNTERget(0) >= 900 then
        be:FLGset(416, 0)
        be:FLGset(417, 0)
        be:FLGset(418, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:FLGset(440, 1)
        be:SYSctlBit("ADD", 0, 2000)
        be:SYSctlBit("ADD", 1, 2000)
        be:SYSctlBit("ADD", 2, 2000)
        be:SYSctlBit("ADD", 3, 2000)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25128)
        funcCloseMessage("mess", "n_digilfm", "fWt", 1)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    elseif be:COUNTERget(0) > 600 then
        be:FLGset(416, 0)
        be:FLGset(417, 0)
        be:FLGset(418, 0)
        be:FLGset(419, 0)
        be:FLGset(420, 0)
        be:FLGset(440, 1)
        be:SYSctlBit("ADD", 0, 5000)
        be:SYSctlBit("ADD", 1, 5000)
        be:SYSctlBit("ADD", 2, 5000)
        be:SYSctlBit("ADD", 3, 5000)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
        funcOpenMessage("mess")
        funcOneMessage(mswk25129)
        funcCloseMessage("mess", "n_digilfm", "fWt", 1)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
        be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
    elseif be:COUNTERget(0) == 600 then
        if be:FLGisOn(512) == 0 then
            if be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 1 then
                g_IFLG08 = 0
                if be:SYSgetPlayerNinzu() == 1 then
                    funcOpenMessage("talk", "n_digilfm", "fWt", 1)
                    funcOneMessage(mswk25092)
                    funcOneMessage(mswk25093)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 1)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:FLGset(409, 1)
                    be:FLGset(376, 1)
                    be:FLGset(384, 1)
                    be:FLGset(571, 1)
                    be:FLGset(415, 0)
                    be:FLGset(424, 1)
                    be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWEROF")
                elseif be:SYSgetPlayerNinzu() >= 2 then
                    funcOpenMessage("talk", "n_digilfm", "fWt", 1)
                    funcOneMessage(mswk25146)
                    funcOneMessage(mswk25147)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 1)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:FLGset(409, 1)
                    be:FLGset(376, 1)
                    be:FLGset(384, 1)
                    be:FLGset(571, 1)
                    be:FLGset(415, 0)
                    be:FLGset(424, 1)
                    be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWEROF")
                end
            elseif be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 0 then
                be:FLGset(416, 0)
                be:FLGset(417, 0)
                be:FLGset(418, 0)
                be:FLGset(419, 0)
                be:FLGset(420, 0)
                be:FLGset(512, 1)
                be:FLGset(440, 1)
                if be:SYSgetPlayerNinzu() == 1 then
                    if be:SYSgetPlayerName(0) ~= "p_agumon" and be:SYSgetPlayerName(0) ~= "p_hekabut" then
                        if be:SYSgetPlayerName(0) == "p_susanoo" then
                        end
                    end
                    be:SYSctlDeviceFolder("SET", 0, "weapon", 19, 128, 2)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25374)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 1)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                elseif be:SYSgetPlayerNinzu() >= 2 then
                    if be:SYSgetPlayerName(0) ~= "p_agumon" and be:SYSgetPlayerName(0) ~= "p_hekabut" then
                        if be:SYSgetPlayerName(0) == "p_susanoo" then
                        end
                    end
                    be:SYSctlDeviceFolder("SET", 0, "weapon", 19, 128, 2)
                    be:SYSctlBit("ADD", 1, 20000)
                    be:SYSctlBit("ADD", 2, 20000)
                    be:SYSctlBit("ADD", 3, 20000)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25380)
                    funcOneMessage(mswk25133)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 1)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                else
                end
            end
        elseif be:FLGisOn(512) == 1 then
            be:SYSctlBit("ADD", 0, 20000)
            be:SYSctlBit("ADD", 1, 20000)
            be:SYSctlBit("ADD", 2, 20000)
            be:SYSctlBit("ADD", 3, 20000)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25131)
            funcCloseMessage("mess", "n_digilfm", "fWt", 1)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
        end
    elseif be:COUNTERget(0) >= 0 then
        if be:FLGisOn(513) == 0 then
            if be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 1 then
                g_IFLG08 = 0
                if be:SYSgetPlayerNinzu() == 1 then
                    funcOpenMessage("talk", "n_digilfm", "fWt", 1)
                    funcOneMessage(mswk25092)
                    funcOneMessage(mswk25093)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 1)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:FLGset(409, 1)
                    be:FLGset(376, 1)
                    be:FLGset(384, 1)
                    be:FLGset(571, 1)
                    be:FLGset(415, 0)
                    be:FLGset(424, 1)
                    be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWEROF")
                elseif be:SYSgetPlayerNinzu() >= 2 then
                    funcOpenMessage("talk", "n_digilfm", "fWt", 1)
                    funcOneMessage(mswk25146)
                    funcOneMessage(mswk25147)
                    funcCloseMessage("talk", "n_digilfm", "fWt", 1)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:FLGset(409, 1)
                    be:FLGset(376, 1)
                    be:FLGset(384, 1)
                    be:FLGset(571, 1)
                    be:FLGset(415, 0)
                    be:FLGset(424, 1)
                    be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWEROF")
                end
            elseif be:SYSctlDeviceFolder("ISMAX", 0, 0, 0, 0, 0) == 0 then
                be:FLGset(416, 0)
                be:FLGset(417, 0)
                be:FLGset(418, 0)
                be:FLGset(419, 0)
                be:FLGset(420, 0)
                be:FLGset(513, 1)
                be:FLGset(440, 1)
                if be:SYSgetPlayerNinzu() == 1 then
                    if be:SYSgetPlayerName(0) ~= "p_agumon" and be:SYSgetPlayerName(0) ~= "p_hekabut" then
                        if be:SYSgetPlayerName(0) == "p_susanoo" then
                        end
                    end
                    be:SYSctlDeviceFolder("SET", 0, "weapon", 15, 32, 4)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25134)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 1)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                elseif be:SYSgetPlayerNinzu() >= 2 then
                    if be:SYSgetPlayerName(0) ~= "p_agumon" and be:SYSgetPlayerName(0) ~= "p_hekabut" then
                        if be:SYSgetPlayerName(0) == "p_susanoo" then
                        end
                    end
                    be:SYSctlDeviceFolder("SET", 0, "weapon", 15, 32, 4)
                    be:SYSctlBit("ADD", 1, 15000)
                    be:SYSctlBit("ADD", 2, 15000)
                    be:SYSctlBit("ADD", 3, 15000)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
                    funcOpenMessage("mess")
                    funcOneMessage(mswk25140)
                    funcOneMessage(mswk25132)
                    funcCloseMessage("mess", "n_digilfm", "fWt", 1)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
                    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
                    be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
                else
                end
            end
        elseif be:FLGisOn(513) == 1 then
            be:SYSctlBit("ADD", 0, 15000)
            be:SYSctlBit("ADD", 1, 15000)
            be:SYSctlBit("ADD", 2, 15000)
            be:SYSctlBit("ADD", 3, 15000)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT", 5)
            funcOpenMessage("mess")
            funcOneMessage(mswk25130)
            funcCloseMessage("mess", "n_digilfm", "fWt", 1)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
            be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_LOBBY", 180)
            be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_LOBBY", 180)
        end
    end
end
be:DMrun()
