funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.1,1.1,1.1>/V<1.1,1.1,1.1>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.2,0.2,0.35>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
be:sd("MATCTRL", nil, -1, "PAUSE")
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_HIDE")
if be:FLGisOn(2) == 0 and be:FLGisOn(3) == 0 and be:FLGisOn(4) == 0 and be:FLGisOn(5) == 0 and be:FLGisOn(6) == 0 and be:FLGisOn(86) == 0 then
    be:FLGset(1, 1)
else
end
be:sd("MODELCTRL", "g_cytrerp2", 0, "GENERATE", "V<40,17,50>/V<0,0,0>")
be:sd("MODELCTRL", "g_indicatorz05", 0, "GENERATE", "V<140,60,-140>/V<0,0,0>")
be:sd("MODELCTRL", "g_movepass01z05", 0, "GENERATE", "V<100,45,-120>/V<0,0,0>")
be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWERON")
if be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "g_indicatorz05", 0, "SQ_SILENTON")
end
if be:FLGisOn(324) == 1 then
    be:sd("MODELCTRL", "g_movepass01z05", 0, "SQ_SWON")
    be:sd("HITLANDMODEL", "hitmovepass01z05", 0, "OFFHIT")
end
if be:FLGisOn(3) == 0 then
    be:sd("SOUND", nil, -1, "PLAY", "AM_LOBBY")
elseif be:FLGisOn(3) == 1 then
    be:sd("SOUND", nil, -1, "PLAY", "AM_OFNI2")
end
if be:FLGisOn(1) == 1 then
    be:sd("SOUND", nil, -1, "PLAY", "ST_COMMA")
elseif be:FLGisOn(2) == 1 and be:FLGisOn(20) == 0 and be:FLGisOn(322) == 0 then
    be:sd("SOUND", nil, -1, "PLAY", "ST_COMMA")
elseif be:FLGisOn(2) == 1 and be:FLGisOn(20) == 1 and be:FLGisOn(322) == 0 then
    be:sd("SOUND", nil, -1, "PLAY", "DM_LEOMN")
elseif be:FLGisOn(2) == 1 and be:FLGisOn(20) == 1 and be:FLGisOn(322) == 1 then
    be:sd("SOUND", nil, -1, "PLAY", "ST_COMMA")
elseif be:FLGisOn(3) == 1 and be:FLGisOn(324) == 0 then
    be:sd("SOUND", nil, -1, "PLAY", "QS_HURRY")
elseif be:FLGisOn(3) == 1 and be:FLGisOn(324) == 1 then
    be:sd("SOUND", nil, -1, "PLAY", "DM_SERAF")
elseif be:FLGisOn(4) == 1 then
    be:sd("SOUND", nil, -1, "PLAY", "ST_COMMA")
elseif be:FLGisOn(5) == 1 then
    be:sd("SOUND", nil, -1, "PLAY", "ST_COMMA")
elseif be:FLGisOn(6) == 1 then
    be:sd("SOUND", nil, -1, "PLAY", "ST_COMMA")
elseif be:FLGisOn(86) == 1 then
    be:sd("SOUND", nil, -1, "PLAY", "ST_COMMA")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
g_joincount = 0
for local_1 = 0, 3 do
    if be:SYSisJoinPlayer(local_1) == 1 then
        g_joincount = g_joincount + 1
    end
end
if g_joincount == 1 then
    be:sd("MODELCTRL", "i_stpnl06", 4, "GENERATE")
else
    for local_1 = 0, 3 do
        if be:SYSisJoinPlayer(local_1) == 1 then
            if local_1 == 0 then
                be:sd("MODELCTRL", "i_stpnl06", 0, "GENERATE", "V<-260,-160,0>")
            elseif local_1 == 1 then
                be:sd("MODELCTRL", "i_stpnl06", 1, "GENERATE", "V<-110,-160,0>")
            elseif local_1 == 2 then
                be:sd("MODELCTRL", "i_stpnl06", 2, "GENERATE", "V<40,-160,0>")
            elseif local_1 == 3 then
                be:sd("MODELCTRL", "i_stpnl06", 3, "GENERATE", "V<190,-160,0>")
            end
        end
    end
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 0, "GENERATE", "V<-50,10,80>/V<0,180,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 0, "GENERATE", "V<-50,10,80>/V<0,180,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 0, "GENERATE", "V<-50,10,80>/V<0,180,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 0, "GENERATE", "V<-50,10,80>/V<0,180,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 0, "GENERATE", "V<-50,10,80>/V<0,180,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 0, "GENERATE", "V<-50,10,80>/V<0,180,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_digilfm", 0, "GENERATE", "V<-50,10,80>/V<0,180,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_digilfm", 1, "GENERATE", "V<-20,60,-130>/V<0,0,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_digilfm", 2, "GENERATE", "V<-90,60,-130>/V<0,0,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_digilfm", 3, "GENERATE", "V<-230,60,-30>/V<0,90,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_digilfm", 4, "GENERATE", "V<-230,60,40>/V<0,90,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_digilfm", 5, "GENERATE", "V<-230,60,160>/V<0,90,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_digilfm", 6, "GENERATE", "V<-190,60,230>/V<0,180,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_digilfm", 7, "GENERATE", "V<-80,60,230>/V<0,180,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_digilfm", 8, "GENERATE", "V<-10,60,230>/V<0,180,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_digilfm", 9, "GENERATE", "V<130,60,130>/V<0,-90,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_digilfm", 10, "GENERATE", "V<130,60,60>/V<0,-90,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_digilff", 0, "GENERATE", "V<-50,10,110>/V<0,180,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_digilff", 0, "GENERATE", "V<-50,10,110>/V<0,180,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_digilff", 0, "GENERATE", "V<-50,10,110>/V<0,180,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_digilff", 0, "GENERATE", "V<-50,10,110>/V<0,180,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_digilff", 0, "GENERATE", "V<-50,10,110>/V<0,180,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_digilff", 0, "GENERATE", "V<-50,10,110>/V<0,180,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_digilff", 0, "GENERATE", "V<-50,10,110>/V<0,180,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_digilff", 1, "GENERATE", "V<-50,10,-10>/V<0,0,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_digilff", 1, "GENERATE", "V<-50,10,-10>/V<0,0,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_digilff", 1, "GENERATE", "V<-50,10,-10>/V<0,0,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_digilff", 1, "GENERATE", "V<-50,10,-10>/V<0,0,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_digilff", 1, "GENERATE", "V<-50,10,-10>/V<0,0,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_digilff", 1, "GENERATE", "V<-50,10,-10>/V<0,0,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_digilff", 1, "GENERATE", "V<-50,10,-10>/V<0,0,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_digilff", 2, "GENERATE", "V<-60,60,-130>/V<0,0,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_digilff", 3, "GENERATE", "V<-130,60,-130>/V<0,0,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_digilff", 4, "GENERATE", "V<-230,60,10>/V<0,90,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_digilff", 5, "GENERATE", "V<-230,60,80>/V<0,90,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_digilff", 6, "GENERATE", "V<-230,60,190>/V<0,90,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_digilff", 7, "GENERATE", "V<-160,60,230>/V<0,180,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_digilff", 8, "GENERATE", "V<-40,60,230>/V<0,180,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_digilff", 9, "GENERATE", "V<30,60,230>/V<0,180,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_digilff", 10, "GENERATE", "V<130,60,90>/V<0,-90,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_digilff", 11, "GENERATE", "V<130,60,20>/V<0,-90,0>")
end
if be:FLGisOn(1) == 1 then
    be:sd("MODELCTRL", "n_ofanim", 0, "GENERATE", "V<230,60,-100>/V<0,90,0>")
elseif be:FLGisOn(2) == 1 then
    be:sd("MODELCTRL", "n_ofanim", 0, "GENERATE", "V<230,60,-100>/V<0,-90,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_ofanim", 0, "GENERATE", "V<230,60,-100>/V<0,-90,0>")
elseif be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_ofanim", 0, "GENERATE", "V<230,60,-100>/V<0,-90,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_ofanim", 0, "GENERATE", "V<230,60,-100>/V<0,-90,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_ofanim", 0, "GENERATE", "V<230,60,-100>/V<0,-90,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_ofanim", 0, "GENERATE", "V<230,60,-100>/V<0,-90,0>")
end
if be:FLGisOn(4) == 1 then
    be:sd("MODELCTRL", "n_seraph", 0, "GENERATE", "V<100,60,-230>/V<0,0,0>")
elseif be:FLGisOn(5) == 1 then
    be:sd("MODELCTRL", "n_seraph", 0, "GENERATE", "V<100,60,-230>/V<0,0,0>")
elseif be:FLGisOn(6) == 1 then
    be:sd("MODELCTRL", "n_seraph", 0, "GENERATE", "V<100,60,-230>/V<0,0,0>")
elseif be:FLGisOn(86) == 1 then
    be:sd("MODELCTRL", "n_seraph", 0, "GENERATE", "V<100,60,-230>/V<0,0,0>")
elseif be:FLGisOn(3) == 1 then
    be:sd("MODELCTRL", "n_seraph", 0, "GENERATE", "V<100,60,-230>/V<0,0,0>")
end
