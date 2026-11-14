funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.1,1.1,1.1>/V<1.1,1.1,1.1>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.2,0.2,0.35>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
be:sd("MATCTRL", nil, -1, "PAUSE")
funcPlayerSet()
if be:PLAYERgetPos() == 0 then
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT", 1)
elseif be:PLAYERgetPos() == 1 then
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT", 1)
elseif be:PLAYERgetPos() == 2 then
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT", 1)
elseif be:PLAYERgetPos() == 4 then
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT", 1)
else
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
end
be:sd("MODELCTRL", "g_cytrerp2", 0, "GENERATE", "V<515,47,-340>/V<0,0,0>")
be:sd("MODELCTRL", "g_evenconsz05", 0, "GENERATE", "V<194.060,38,-340>/V<0,-90,0>")
be:sd("MODELCTRL", "g_evenconsz05", 1, "GENERATE", "V<365.994,38,-340>/V<0,90,0>")
be:sd("MODELCTRL", "g_evenconsz05", 2, "GENERATE", "V<440,38,-414.060>/V<0,0,0>")
be:sd("MODELCTRL", "g_evenconsz05", 3, "GENERATE", "V<440,38,-266.127>/V<0,180,0>")
be:sd("MODELCTRL", "g_cydigi", 0, "GENERATE", "V<-455,50,185>/V<0,0,0>")
be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWERON")
if be:FLGisOn(1) ~= 1 and be:FLGisOn(2) ~= 1 then
    if be:FLGisOn(3) == 1 then
    end
end
be:sd("MODELCTRL", "r_hidingboxz05", 0, "GENERATE", "V<0,0,0>/V<0,0,0>")
be:sd("MODELCTRL", "g_hidingboxz05", 0, "GENERATE", "V<280,40,-340>/V<0,90,0>")
if be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "g_evenconsz05", 0, "SQ_WAIT02")
    be:sd("MODELCTRL", "g_evenconsz05", 2, "SQ_WAIT02")
else
end
if be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_seraph", 0, "GENERATE", "SQ_FALL/V<280,60,-340>/V<0,90,0>")
end
if be:FLGisOn(329) == 1 then
    be:sd("MODELCTRL", "g_evenconsz05", 0, "SQ_SILENTON")
end
if be:FLGisOn(330) == 1 then
    be:sd("MODELCTRL", "g_evenconsz05", 1, "SQ_SILENTON")
end
if be:FLGisOn(331) == 1 then
    be:sd("MODELCTRL", "g_evenconsz05", 2, "SQ_SILENTON")
end
if be:FLGisOn(332) == 1 then
    be:sd("MODELCTRL", "g_evenconsz05", 3, "SQ_SILENTON")
end
if be:FLGisOn(3) == 0 then
    be:sd("SOUND", nil, -1, "PLAY", "AM_LOBBY")
elseif be:FLGisOn(3) == 1 then
    be:sd("SOUND", nil, -1, "PLAY", "AM_OFNI2")
end
if be:FLGisOn(3) == 0 then
    be:sd("SOUND", nil, -1, "PLAY", "ST_LOBBY")
elseif be:FLGisOn(3) == 1 then
    be:sd("SOUND", nil, -1, "PLAY", "QS_HURRY")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
local local_0
g_joincount = 0
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        g_joincount = g_joincount + 1
    end
end
if g_joincount == 1 then
    be:sd("MODELCTRL", "i_stpnl06", 4, "GENERATE")
else
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 then
            if playerIndex == 0 then
                be:sd("MODELCTRL", "i_stpnl06", 0, "GENERATE", "V<-260,-160,0>")
            elseif playerIndex == 1 then
                be:sd("MODELCTRL", "i_stpnl06", 1, "GENERATE", "V<-110,-160,0>")
            elseif playerIndex == 2 then
                be:sd("MODELCTRL", "i_stpnl06", 2, "GENERATE", "V<40,-160,0>")
            elseif playerIndex == 3 then
                be:sd("MODELCTRL", "i_stpnl06", 3, "GENERATE", "V<190,-160,0>")
            end
        end
    end
end
be:FLGset(908, 0)
if be:SYSgetPlayerLevel(0) >= 16 then
    be:FLGset(908, 1)
end
be:FLGset(909, 0)
if be:SYSgetPlayerLevel(0) >= 46 then
    be:FLGset(909, 1)
end
be:FLGset(910, 0)
if be:SYSgetPlayerLevel(0) >= 76 then
    be:FLGset(910, 1)
end
be:FLGset(922, 0)
if be:SYSisGetShinkaDigimon(0, 0) + be:SYSisGetShinkaDigimon(0, 1) + be:SYSisGetShinkaDigimon(0, 2) + be:SYSisGetShinkaDigimon(0, 3) + be:SYSisGetShinkaDigimon(0, 4) + be:SYSisGetShinkaDigimon(0, 5) + be:SYSisGetShinkaDigimon(0, 6) + be:SYSisGetShinkaDigimon(0, 7) + be:SYSisGetShinkaDigimon(0, 8) + be:SYSisGetShinkaDigimon(0, 9) + be:SYSisGetShinkaDigimon(0, 10) + be:SYSisGetShinkaDigimon(0, 11) + be:SYSisGetShinkaDigimon(0, 12) + be:SYSisGetShinkaDigimon(0, 13) + be:SYSisGetShinkaDigimon(0, 14) + be:SYSisGetShinkaDigimon(0, 15) >= 2 then
    be:FLGset(922, 1)
end
be:FLGset(923, 0)
if be:SYSisGetShinkaDigimon(0, 0) + be:SYSisGetShinkaDigimon(0, 1) + be:SYSisGetShinkaDigimon(0, 2) + be:SYSisGetShinkaDigimon(0, 3) + be:SYSisGetShinkaDigimon(0, 4) + be:SYSisGetShinkaDigimon(0, 5) + be:SYSisGetShinkaDigimon(0, 6) + be:SYSisGetShinkaDigimon(0, 7) + be:SYSisGetShinkaDigimon(0, 8) + be:SYSisGetShinkaDigimon(0, 9) + be:SYSisGetShinkaDigimon(0, 10) + be:SYSisGetShinkaDigimon(0, 11) + be:SYSisGetShinkaDigimon(0, 12) + be:SYSisGetShinkaDigimon(0, 13) + be:SYSisGetShinkaDigimon(0, 14) + be:SYSisGetShinkaDigimon(0, 15) >= 5 then
    be:FLGset(923, 1)
end
be:FLGset(924, 0)
if be:SYSisGetShinkaDigimon(0, 0) + be:SYSisGetShinkaDigimon(0, 1) + be:SYSisGetShinkaDigimon(0, 2) + be:SYSisGetShinkaDigimon(0, 3) + be:SYSisGetShinkaDigimon(0, 4) + be:SYSisGetShinkaDigimon(0, 5) + be:SYSisGetShinkaDigimon(0, 6) + be:SYSisGetShinkaDigimon(0, 7) + be:SYSisGetShinkaDigimon(0, 8) + be:SYSisGetShinkaDigimon(0, 9) + be:SYSisGetShinkaDigimon(0, 10) + be:SYSisGetShinkaDigimon(0, 11) + be:SYSisGetShinkaDigimon(0, 12) + be:SYSisGetShinkaDigimon(0, 13) + be:SYSisGetShinkaDigimon(0, 14) + be:SYSisGetShinkaDigimon(0, 15) >= 8 then
    be:FLGset(924, 1)
end
be:FLGset(925, 0)
if be:SYSctlCardFolder("KAZU", 0) >= 25 then
    be:FLGset(925, 1)
end
be:FLGset(926, 0)
if be:SYSctlCardFolder("KAZU", 0) >= 35 then
    be:FLGset(926, 1)
end
be:FLGset(927, 0)
if be:SYSctlCardFolder("KAZU", 0) >= 45 then
    be:FLGset(927, 1)
end
if be:FLGisOn(426) == 1 and be:FLGisOn(427) == 1 and be:FLGisOn(428) == 1 and be:FLGisOn(429) == 1 and be:FLGisOn(430) == 1 and be:FLGisOn(431) == 1 and be:FLGisOn(432) == 1 then
    be:FLGset(928, 1)
else
    be:FLGset(928, 0)
end
if be:FLGisOn(433) == 1 and be:FLGisOn(434) == 1 and be:FLGisOn(435) == 1 and be:FLGisOn(436) == 1 and be:FLGisOn(437) == 1 and be:FLGisOn(438) == 1 and be:FLGisOn(439) == 1 then
    be:FLGset(929, 1)
else
    be:FLGset(929, 0)
end
if be:FLGisOn(440) == 1 and be:FLGisOn(441) == 1 and be:FLGisOn(442) == 1 and be:FLGisOn(443) == 1 and be:FLGisOn(444) == 1 and be:FLGisOn(445) == 1 and be:FLGisOn(446) == 1 then
    be:FLGset(930, 1)
else
    be:FLGset(930, 0)
end
be:FLGset(931, 0)
be:FLGset(932, 0)
be:FLGset(933, 0)
if be:SYSgetDifficulty() == 2 then
    be:FLGset(933, 1)
elseif be:SYSgetDifficulty() == 1 then
    be:FLGset(932, 1)
else
    be:FLGset(931, 1)
end
be:FLGset(935, 0)
if be:SYSgetPlayerNinzu() == 1 then
    be:FLGset(935, 1)
end
be:FLGset(936, 0)
if be:SYSgetPlayerNinzu() <= 2 then
    be:FLGset(936, 1)
end
be:FLGset(912, 0)
be:FLGset(913, 0)
be:FLGset(914, 0)
be:FLGset(915, 0)
be:FLGset(916, 0)
be:FLGset(917, 0)
be:FLGset(918, 0)
be:FLGset(919, 0)
be:FLGset(920, 0)
if be:COUNTERget(1) >= 3956000 then
    be:FLGset(920, 1)
elseif be:COUNTERget(1) >= 1956000 then
    be:FLGset(919, 1)
elseif be:COUNTERget(1) >= 956000 then
    be:FLGset(918, 1)
elseif be:COUNTERget(1) >= 456000 then
    be:FLGset(917, 1)
elseif be:COUNTERget(1) >= 206000 then
    be:FLGset(916, 1)
elseif be:COUNTERget(1) >= 86000 then
    be:FLGset(915, 1)
elseif be:COUNTERget(1) >= 26000 then
    be:FLGset(914, 1)
elseif be:COUNTERget(1) >= 6000 then
    be:FLGset(913, 1)
elseif be:COUNTERget(1) >= 1000 then
    be:FLGset(912, 1)
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 0, "GENERATE", "V<-130,40,-40>/V<0,90,0>")
elseif be:FLGisOn(1) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 0, "GENERATE", "V<-130,40,-40>/V<0,90,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 1, "GENERATE", "V<-350,40,-40>/V<0,-90,0>")
elseif be:FLGisOn(1) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 1, "GENERATE", "V<-350,40,-40>/V<0,-90,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 2, "GENERATE", "V<-220,40,240>/V<0,135,0>")
elseif be:FLGisOn(1) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 2, "GENERATE", "V<-220,40,240>/V<0,135,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 3, "GENERATE", "V<78.187,40,-266>/V<0,180,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 3, "GENERATE", "V<78.187,40,-266>/V<0,180,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 3, "GENERATE", "V<78.187,40,-266>/V<0,180,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 3, "GENERATE", "V<78.187,40,-266>/V<0,180,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 3, "GENERATE", "V<78.187,40,-266>/V<0,180,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 3, "GENERATE", "V<78.187,40,-266>/V<0,180,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 3, "GENERATE", "V<78.187,40,-266>/V<0,180,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 4, "GENERATE", "V<94,40,-398.187>/V<0,-90,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 4, "GENERATE", "V<94,40,-398.187>/V<0,-90,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 4, "GENERATE", "V<94,40,-398.187>/V<0,-90,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 4, "GENERATE", "V<94,40,-398.187>/V<0,-90,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 4, "GENERATE", "V<94,40,-398.187>/V<0,-90,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 4, "GENERATE", "V<94,40,-398.187>/V<0,-90,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 4, "GENERATE", "V<94,40,-398.187>/V<0,-90,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 5, "GENERATE", "V<-54,40,-281.812>/V<0,90,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 5, "GENERATE", "V<-54,40,-281.812>/V<0,90,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 5, "GENERATE", "V<-54,40,-281.812>/V<0,90,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 5, "GENERATE", "V<-54,40,-281.812>/V<0,90,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 5, "GENERATE", "V<-54,40,-281.812>/V<0,90,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 5, "GENERATE", "V<-54,40,-281.812>/V<0,90,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 5, "GENERATE", "V<-54,40,-281.812>/V<0,90,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 6, "GENERATE", "V<-38.187,40,-414>/V<0,0,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 6, "GENERATE", "V<-38.187,40,-414>/V<0,0,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 6, "GENERATE", "V<-38.187,40,-414>/V<0,0,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 6, "GENERATE", "V<-38.187,40,-414>/V<0,0,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 6, "GENERATE", "V<-38.187,40,-414>/V<0,0,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 6, "GENERATE", "V<-38.187,40,-414>/V<0,0,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 6, "GENERATE", "V<-38.187,40,-414>/V<0,0,0>")
end
if be:FLGisOn(931) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(396) == 0 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 7, "GENERATE", "V<-130,40,-420>/V<0,-180,0>")
elseif be:FLGisOn(931) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(396) == 1 and be:FLGisOn(935) == 1 and be:FLGisOn(419) == 0 and be:FLGisOn(388) == 0 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 7, "GENERATE", "V<-130,40,-420>/V<0,-180,0>")
elseif be:FLGisOn(931) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(396) == 1 and be:FLGisOn(419) == 1 and be:FLGisOn(388) == 0 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 7, "GENERATE", "V<-130,40,-420>/V<0,-180,0>")
elseif be:FLGisOn(931) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(396) == 1 and be:FLGisOn(419) == 0 and be:FLGisOn(388) == 1 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 7, "GENERATE", "V<-130,40,-420>/V<0,-180,0>")
elseif be:FLGisOn(931) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(396) == 1 and be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 7, "GENERATE", "V<-130,40,-420>/V<0,-180,0>")
elseif be:FLGisOn(932) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(399) == 0 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 7, "GENERATE", "V<-130,40,-420>/V<0,-180,0>")
elseif be:FLGisOn(932) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(399) == 1 and be:FLGisOn(935) == 1 and be:FLGisOn(419) == 0 and be:FLGisOn(388) == 0 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 7, "GENERATE", "V<-130,40,-420>/V<0,-180,0>")
elseif be:FLGisOn(932) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(399) == 1 and be:FLGisOn(419) == 1 and be:FLGisOn(388) == 0 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 7, "GENERATE", "V<-130,40,-420>/V<0,-180,0>")
elseif be:FLGisOn(932) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(399) == 1 and be:FLGisOn(419) == 0 and be:FLGisOn(388) == 1 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 7, "GENERATE", "V<-130,40,-420>/V<0,-180,0>")
elseif be:FLGisOn(932) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(399) == 1 and be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 7, "GENERATE", "V<-130,40,-420>/V<0,-180,0>")
elseif be:FLGisOn(933) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(402) == 0 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 7, "GENERATE", "V<-130,40,-420>/V<0,-180,0>")
elseif be:FLGisOn(933) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(402) == 1 and be:FLGisOn(935) == 1 and be:FLGisOn(419) == 0 and be:FLGisOn(388) == 0 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 7, "GENERATE", "V<-130,40,-420>/V<0,-180,0>")
elseif be:FLGisOn(933) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(402) == 1 and be:FLGisOn(419) == 1 and be:FLGisOn(388) == 0 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 7, "GENERATE", "V<-130,40,-420>/V<0,-180,0>")
elseif be:FLGisOn(933) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(402) == 1 and be:FLGisOn(419) == 0 and be:FLGisOn(388) == 1 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 7, "GENERATE", "V<-130,40,-420>/V<0,-180,0>")
elseif be:FLGisOn(933) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(402) == 1 and be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 7, "GENERATE", "V<-130,40,-420>/V<0,-180,0>")
elseif be:FLGisOn(3) == 1 and be:FLGisOn(93) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 7, "GENERATE", "V<-130,40,-420>/V<0,-180,0>")
end
if be:FLGisOn(931) == 1 and be:FLGisOn(94) == 1 and be:FLGisOn(420) == 0 and be:FLGisOn(389) == 0 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 8, "GENERATE", "V<-170,40,-380>/V<0,-90,0>")
elseif be:FLGisOn(931) == 1 and be:FLGisOn(94) == 1 and be:FLGisOn(420) == 1 and be:FLGisOn(389) == 0 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 8, "GENERATE", "V<-170,40,-380>/V<0,-90,0>")
elseif be:FLGisOn(931) == 1 and be:FLGisOn(94) == 1 and be:FLGisOn(420) == 0 and be:FLGisOn(389) == 1 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 8, "GENERATE", "V<-170,40,-380>/V<0,-90,0>")
elseif be:FLGisOn(932) == 1 and be:FLGisOn(94) == 1 and be:FLGisOn(420) == 0 and be:FLGisOn(389) == 0 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 8, "GENERATE", "V<-170,40,-380>/V<0,-90,0>")
elseif be:FLGisOn(932) == 1 and be:FLGisOn(94) == 1 and be:FLGisOn(420) == 1 and be:FLGisOn(389) == 0 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 8, "GENERATE", "V<-170,40,-380>/V<0,-90,0>")
elseif be:FLGisOn(932) == 1 and be:FLGisOn(94) == 1 and be:FLGisOn(420) == 0 and be:FLGisOn(389) == 1 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 8, "GENERATE", "V<-170,40,-380>/V<0,-90,0>")
elseif be:FLGisOn(933) == 1 and be:FLGisOn(94) == 1 and be:FLGisOn(420) == 0 and be:FLGisOn(389) == 0 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 8, "GENERATE", "V<-170,40,-380>/V<0,-90,0>")
elseif be:FLGisOn(933) == 1 and be:FLGisOn(94) == 1 and be:FLGisOn(420) == 1 and be:FLGisOn(389) == 0 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 8, "GENERATE", "V<-170,40,-380>/V<0,-90,0>")
elseif be:FLGisOn(933) == 1 and be:FLGisOn(94) == 1 and be:FLGisOn(420) == 0 and be:FLGisOn(389) == 1 and be:FLGisOn(3) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 8, "GENERATE", "V<-170,40,-380>/V<0,-90,0>")
elseif be:FLGisOn(3) == 1 and be:FLGisOn(94) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 8, "GENERATE", "V<-170,40,-380>/V<0,-90,0>")
end
if be:FLGisOn(931) == 1 and be:FLGisOn(95) == 1 and be:FLGisOn(70) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 9, "GENERATE", "V<-240,40,-310>/V<0,-180,0>")
elseif be:FLGisOn(931) == 1 and be:FLGisOn(95) == 1 and be:FLGisOn(70) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 9, "GENERATE", "V<-240,40,-310>/V<0,-180,0>")
elseif be:FLGisOn(932) == 1 and be:FLGisOn(95) == 1 and be:FLGisOn(70) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 9, "GENERATE", "V<-240,40,-310>/V<0,-180,0>")
elseif be:FLGisOn(932) == 1 and be:FLGisOn(95) == 1 and be:FLGisOn(70) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 9, "GENERATE", "V<-240,40,-310>/V<0,-180,0>")
elseif be:FLGisOn(933) == 1 and be:FLGisOn(95) == 1 and be:FLGisOn(70) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 9, "GENERATE", "V<-240,40,-310>/V<0,-180,0>")
elseif be:FLGisOn(933) == 1 and be:FLGisOn(95) == 1 and be:FLGisOn(70) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 9, "GENERATE", "V<-240,40,-310>/V<0,-180,0>")
end
if be:FLGisOn(931) == 1 and be:FLGisOn(96) == 1 and be:FLGisOn(928) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 10, "GENERATE", "V<-290,40,-270>/V<0,-90,0>")
elseif be:FLGisOn(931) == 1 and be:FLGisOn(96) == 1 and be:FLGisOn(928) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 10, "GENERATE", "V<-290,40,-270>/V<0,-90,0>")
elseif be:FLGisOn(932) == 1 and be:FLGisOn(96) == 1 and be:FLGisOn(929) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 10, "GENERATE", "V<-290,40,-270>/V<0,-90,0>")
elseif be:FLGisOn(932) == 1 and be:FLGisOn(96) == 1 and be:FLGisOn(929) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 10, "GENERATE", "V<-290,40,-270>/V<0,-90,0>")
elseif be:FLGisOn(933) == 1 and be:FLGisOn(96) == 1 and be:FLGisOn(930) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 10, "GENERATE", "V<-290,40,-270>/V<0,-90,0>")
elseif be:FLGisOn(933) == 1 and be:FLGisOn(96) == 1 and be:FLGisOn(930) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 10, "GENERATE", "V<-290,40,-270>/V<0,-90,0>")
end
if be:FLGisOn(97) == 1 and be:FLGisOn(908) == 0 and be:FLGisOn(86) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 11, "GENERATE", "V<-430,40,-40>/V<0,-90,0>")
elseif be:FLGisOn(97) == 1 and be:FLGisOn(908) == 1 and be:FLGisOn(909) == 0 and be:FLGisOn(86) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 11, "GENERATE", "V<-430,40,-40>/V<0,-90,0>")
elseif be:FLGisOn(97) == 1 and be:FLGisOn(909) == 1 and be:FLGisOn(910) == 0 and be:FLGisOn(86) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 11, "GENERATE", "V<-430,40,-40>/V<0,-90,0>")
elseif be:FLGisOn(97) == 1 and be:FLGisOn(910) == 1 and be:FLGisOn(86) == 0 and 1 == 1 then
    be:sd("MODELCTRL", "n_digilfm", 11, "GENERATE", "V<-430,40,-40>/V<0,-90,0>")
elseif be:FLGisOn(97) == 1 and be:FLGisOn(910) == 1 and be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 11, "GENERATE", "V<-430,40,-40>/V<0,-90,0>")
elseif be:FLGisOn(97) == 1 and be:FLGisOn(908) == 1 and be:FLGisOn(909) == 0 and be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 11, "GENERATE", "V<-430,40,-40>/V<0,-90,0>")
elseif be:FLGisOn(97) == 1 and be:FLGisOn(909) == 1 and be:FLGisOn(910) == 0 and be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 11, "GENERATE", "V<-430,40,-40>/V<0,-90,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_digilff", 0, "GENERATE", "V<-240,40,70>/V<0,0,0>")
elseif be:FLGisOn(1) == 0 then
    be:sd("MODELCTRL", "n_digilff", 0, "GENERATE", "V<-240,40,70>/V<0,0,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_digilff", 1, "GENERATE", "V<-411,50,98>/V<0,45,0>")
elseif be:FLGisOn(1) == 0 and be:FLGisOn(937) == 0 then
    be:sd("MODELCTRL", "n_digilff", 1, "GENERATE", "V<-411,50,98>/V<0,45,0>")
elseif be:FLGisOn(1) == 0 and be:FLGisOn(937) == 1 then
    be:sd("MODELCTRL", "n_digilff", 1, "GENERATE", "V<-411,50,98>/V<0,45,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_digilff", 2, "GENERATE", "V<-240,40,-150>/V<0,180,0>")
elseif be:FLGisOn(1) == 0 then
    be:sd("MODELCTRL", "n_digilff", 2, "GENERATE", "V<-240,40,-150>/V<0,180,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_digilff", 3, "GENERATE", "V<94,40,-281.407>/V<0,-90,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_digilff", 3, "GENERATE", "V<94,40,-281.407>/V<0,-90,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_digilff", 3, "GENERATE", "V<94,40,-281.407>/V<0,-90,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_digilff", 3, "GENERATE", "V<94,40,-281.407>/V<0,-90,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_digilff", 3, "GENERATE", "V<94,40,-281.407>/V<0,-90,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_digilff", 3, "GENERATE", "V<94,40,-281.407>/V<0,-90,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_digilff", 3, "GENERATE", "V<94,40,-281.407>/V<0,-90,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_digilff", 4, "GENERATE", "V<78.592,40,-414>/V<0,0,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_digilff", 4, "GENERATE", "V<78.592,40,-414>/V<0,0,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_digilff", 4, "GENERATE", "V<78.592,40,-414>/V<0,0,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_digilff", 4, "GENERATE", "V<78.592,40,-414>/V<0,0,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_digilff", 4, "GENERATE", "V<78.592,40,-414>/V<0,0,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_digilff", 4, "GENERATE", "V<78.592,40,-414>/V<0,0,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_digilff", 4, "GENERATE", "V<78.592,40,-414>/V<0,0,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_digilff", 5, "GENERATE", "V<-38.592,40,-266>/V<0,180,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_digilff", 5, "GENERATE", "V<-38.592,40,-266>/V<0,180,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_digilff", 5, "GENERATE", "V<-38.592,40,-266>/V<0,180,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_digilff", 5, "GENERATE", "V<-38.592,40,-266>/V<0,180,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_digilff", 5, "GENERATE", "V<-38.592,40,-266>/V<0,180,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_digilff", 5, "GENERATE", "V<-38.592,40,-266>/V<0,180,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_digilff", 5, "GENERATE", "V<-38.592,40,-266>/V<0,180,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_digilff", 6, "GENERATE", "V<-54,40,-398.592>/V<0,90,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_digilff", 6, "GENERATE", "V<-54,40,-398.592>/V<0,90,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_digilff", 6, "GENERATE", "V<-54,40,-398.592>/V<0,90,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_digilff", 6, "GENERATE", "V<-54,40,-398.592>/V<0,90,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_digilff", 6, "GENERATE", "V<-54,40,-398.592>/V<0,90,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_digilff", 6, "GENERATE", "V<-54,40,-398.592>/V<0,90,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_digilff", 6, "GENERATE", "V<-54,40,-398.592>/V<0,90,0>")
end
if be:FLGisOn(4) == 1 and be:FLGisOn(82) == 1 then
    be:sd("MODELCTRL", "n_leomon", 0, "GENERATE", "V<-290,40,190>/V<0,90,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_leomon", 0, "GENERATE", "V<-290,40,190>/V<0,90,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_leomon", 0, "GENERATE", "V<-290,40,190>/V<0,90,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_leomon", 0, "GENERATE", "V<-290,40,190>/V<0,90,0>")
end
if be:FLGisOn(392) == 0 and 1 == 1 then
    be:sd("MODELCTRL", "n_prmame", 0, "GENERATE", "V<-170,40,310>/V<0,180,0>")
elseif be:FLGisOn(392) == 1 and be:FLGisOn(393) == 0 and 1 == 1 then
    be:sd("MODELCTRL", "n_prmame", 0, "GENERATE", "V<-170,40,310>/V<0,180,0>")
elseif be:FLGisOn(393) == 1 and be:FLGisOn(394) == 0 and 1 == 1 then
    be:sd("MODELCTRL", "n_prmame", 0, "GENERATE", "V<-170,40,310>/V<0,180,0>")
elseif be:FLGisOn(394) == 1 and be:FLGisOn(395) == 0 and 1 == 1 then
    be:sd("MODELCTRL", "n_prmame", 0, "GENERATE", "V<-170,40,310>/V<0,180,0>")
elseif be:FLGisOn(395) == 1 and be:FLGisOn(396) == 0 and 1 == 1 then
    be:sd("MODELCTRL", "n_prmame", 0, "GENERATE", "V<-170,40,310>/V<0,180,0>")
elseif g_lFLG16 == 1 and 1 == 1 then
    be:sd("MODELCTRL", "n_prmame", 0, "GENERATE", "V<-170,40,310>/V<0,180,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_agumon", 0, "GENERATE", "V<-220,40,-190>/V<0,0,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_agumon", 0, "GENERATE", "V<-220,40,-190>/V<0,0,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_agumon", 0, "GENERATE", "V<-220,40,-190>/V<0,0,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_agumon", 0, "GENERATE", "V<-220,40,-190>/V<0,0,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_agumon", 0, "GENERATE", "V<-220,40,-190>/V<0,0,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_agumon", 0, "GENERATE", "V<-220,40,-190>/V<0,0,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_agumon", 0, "GENERATE", "V<-220,40,-190>/V<0,0,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_agumon", 1, "GENERATE", "V<30,40,-280>/V<0,0,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_agumon", 1, "GENERATE", "V<30,40,-280>/V<0,0,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_agumon", 1, "GENERATE", "V<30,40,-280>/V<0,0,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_agumon", 1, "GENERATE", "V<30,40,-280>/V<0,0,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_agumon", 1, "GENERATE", "V<30,40,-280>/V<0,0,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_agumon", 1, "GENERATE", "V<30,40,-280>/V<0,0,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_agumon", 1, "GENERATE", "V<30,40,-280>/V<0,0,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_vmon", 0, "GENERATE", "V<-260,40,-190>/V<0,0,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_vmon", 0, "GENERATE", "V<-260,40,-190>/V<0,0,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_vmon", 0, "GENERATE", "V<-260,40,-190>/V<0,0,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_vmon", 0, "GENERATE", "V<-260,40,-190>/V<0,0,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_vmon", 0, "GENERATE", "V<-260,40,-190>/V<0,0,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_vmon", 0, "GENERATE", "V<-260,40,-190>/V<0,0,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_vmon", 0, "GENERATE", "V<-260,40,-190>/V<0,0,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_vmon", 1, "GENERATE", "V<-238,40,188>/V<0,0,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_vmon", 1, "GENERATE", "V<-238,40,188>/V<0,0,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_vmon", 1, "GENERATE", "V<-238,40,188>/V<0,0,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_vmon", 1, "GENERATE", "V<-238,40,188>/V<0,0,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_vmon", 1, "GENERATE", "V<-238,40,188>/V<0,0,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_vmon", 1, "GENERATE", "V<-238,40,188>/V<0,0,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_vmon", 1, "GENERATE", "V<-238,40,188>/V<0,0,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_vmon", 2, "GENERATE", "V<10,40,-400>/V<0,0,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_vmon", 2, "GENERATE", "V<10,40,-400>/V<0,0,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_vmon", 2, "GENERATE", "V<10,40,-400>/V<0,0,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_vmon", 2, "GENERATE", "V<10,40,-400>/V<0,0,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_vmon", 2, "GENERATE", "V<10,40,-400>/V<0,0,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_vmon", 2, "GENERATE", "V<10,40,-400>/V<0,0,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_vmon", 2, "GENERATE", "V<10,40,-400>/V<0,0,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_girumon", 0, "GENERATE", "V<-260,40,110>/V<0,0,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_girumon", 0, "GENERATE", "V<-260,40,110>/V<0,0,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_girumon", 0, "GENERATE", "V<-260,40,110>/V<0,0,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_girumon", 0, "GENERATE", "V<-260,40,110>/V<0,0,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_girumon", 0, "GENERATE", "V<-260,40,110>/V<0,0,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_girumon", 0, "GENERATE", "V<-260,40,110>/V<0,0,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_girumon", 0, "GENERATE", "V<-260,40,110>/V<0,0,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_girumon", 1, "GENERATE", "V<-163,40,-318>/V<0,0,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_girumon", 1, "GENERATE", "V<-163,40,-318>/V<0,0,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_girumon", 1, "GENERATE", "V<-163,40,-318>/V<0,0,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_girumon", 1, "GENERATE", "V<-163,40,-318>/V<0,0,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_girumon", 1, "GENERATE", "V<-163,40,-318>/V<0,0,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_girumon", 1, "GENERATE", "V<-163,40,-318>/V<0,0,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_girumon", 1, "GENERATE", "V<-163,40,-318>/V<0,0,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_dorumon", 0, "GENERATE", "V<-220,40,110>/V<0,0,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_dorumon", 0, "GENERATE", "V<-220,40,110>/V<0,0,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_dorumon", 0, "GENERATE", "V<-220,40,110>/V<0,0,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_dorumon", 0, "GENERATE", "V<-220,40,110>/V<0,0,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_dorumon", 0, "GENERATE", "V<-220,40,110>/V<0,0,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_dorumon", 0, "GENERATE", "V<-220,40,110>/V<0,0,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_dorumon", 0, "GENERATE", "V<-220,40,110>/V<0,0,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_dorumon", 1, "GENERATE", "V<-240,40,-270>/V<0,0,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_dorumon", 1, "GENERATE", "V<-240,40,-270>/V<0,0,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_dorumon", 1, "GENERATE", "V<-240,40,-270>/V<0,0,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_dorumon", 1, "GENERATE", "V<-240,40,-270>/V<0,0,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_dorumon", 1, "GENERATE", "V<-240,40,-270>/V<0,0,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_dorumon", 1, "GENERATE", "V<-240,40,-270>/V<0,0,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_dorumon", 1, "GENERATE", "V<-240,40,-270>/V<0,0,0>")
end
