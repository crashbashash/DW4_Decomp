funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.2,1.0,1.1>/V<1.2,1.0,1.1>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.2,0.16,0.18>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
be:sd("MATCTRL", nil, -1, "PAUSE")
funcPlayerSet()
if be:PLAYERgetPos() == 2 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT", 1)
end
be:sd("MODELCTRL", "g_atcksabtnz02", 0, "GENERATE", "V<-525,200,425>/V<0,90,0>")
be:sd("MODELCTRL", "g_atcksabtnz02", 1, "GENERATE", "V<-525,200,395>/V<0,90,0>")
be:sd("MODELCTRL", "g_atcksabtnz02", 2, "GENERATE", "V<455,60,-155>/V<0,90,0>")
be:sd("MODELCTRL", "g_atcksabtnz02", 3, "GENERATE", "V<165,100,125>/V<0,0,0>")
be:sd("MODELCTRL", "g_bossymbolz02", 0, "GENERATE", "V<-485,170,315>/V<0,90,0>")
be:sd("MODELCTRL", "g_bossymbolz02", 1, "GENERATE", "V<-155,160,265>/V<0,0,0>")
be:sd("MODELCTRL", "g_bossymbolz02", 2, "GENERATE", "V<-25,160,265>/V<0,0,0>")
be:sd("MODELCTRL", "g_bossymbolz02", 3, "GENERATE", "V<395,120,195>/V<0,-130,0>")
be:sd("MODELCTRL", "g_bossymbolz02", 4, "GENERATE", "V<625,60,-375>/V<0,0,0>")
be:sd("MODELCTRL", "g_bossymbolz02", 5, "GENERATE", "V<575,60,-375>/V<0,0,0>")
be:sd("MODELCTRL", "g_bush01z02", 0, "GENERATE", "V<-585,200,295>/V<0,90,0>")
be:sd("MODELCTRL", "g_bush01z02", 1, "GENERATE", "V<-585,200,365>/V<0,180,0>")
be:sd("MODELCTRL", "g_bush01z02", 2, "GENERATE", "V<-575,200,365>/V<0,2,0>")
be:sd("MODELCTRL", "g_bush01z02", 3, "GENERATE", "V<-535,200,385>/V<0,270,0>")
be:sd("MODELCTRL", "g_bush01z02", 4, "GENERATE", "V<-535,200,435>/V<0,90,0>")
be:sd("MODELCTRL", "g_bush01z02", 5, "GENERATE", "V<-365,180,415>/V<0,180,0>")
be:sd("MODELCTRL", "g_bush01z02", 6, "GENERATE", "V<-225,160,355>/V<0,90,0>")
be:sd("MODELCTRL", "g_bush01z02", 7, "GENERATE", "V<-5,160,335>/V<0,270,0>")
be:sd("MODELCTRL", "g_bush01z02", 8, "GENERATE", "V<305,120,-5>/V<0,8,0>")
be:sd("MODELCTRL", "g_bush01z02", 9, "GENERATE", "V<-605,170,85>/V<0,270,0>")
be:sd("MODELCTRL", "g_bush02z02", 0, "GENERATE", "V<-585,200,315>/V<0,0,0>")
be:sd("MODELCTRL", "g_bush02z02", 1, "GENERATE", "V<-545,200,385>/V<0,90,0>")
be:sd("MODELCTRL", "g_bush02z02", 2, "GENERATE", "V<135,120,235>/V<0,180,0>")
be:sd("MODELCTRL", "g_cannon01", 0, "GENERATE", "V<605,60,-185>/V<0,0,0>")
be:sd("MODELCTRL", "g_cannon01", 1, "GENERATE", "V<595,60,-185>/V<0,0,0>")
be:sd("MODELCTRL", "g_cannon01", 2, "GENERATE", "V<-575,170,165>/V<0,90,0>")
be:sd("MODELCTRL", "g_cannon01", 3, "GENERATE", "V<-575,170,175>/V<0,90,0>")
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<80,110,210>/V<0,180,0>")
be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_lever01z02", 0, "GENERATE", "V<300,120,285>/V<0,180,0>")
be:sd("MODELCTRL", "g_lift01z02", 0, "GENERATE", "V<-380,140,150>/V<0,0,0>")
be:sd("MODELCTRL", "g_lift01z02", 1, "GENERATE", "V<-380,120,-20>/V<0,0,0>")
be:sd("MODELCTRL", "g_lift01z02", 2, "GENERATE", "V<-190,100,-100>/V<0,-90,0>")
be:sd("MODELCTRL", "g_lift01z02", 3, "GENERATE", "V<-20,80,-100>/V<0,-90,0>")
be:sd("MODELCTRL", "g_lift01z02", 4, "GENERATE", "V<150,60,-100>/V<0,-90,0>")
be:sd("MODELCTRL", "g_lift02z02", 0, "GENERATE", "V<-380,160,320>/V<0,0,0>")
be:sd("MODELCTRL", "g_lift03z02", 0, "GENERATE", "V<-250,100,-310>/V<0,0,0>")
be:sd("MODELCTRL", "g_lift03az02", 0, "GENERATE", "V<-250,100,-310>/V<0,0,0>")
be:sd("MODELCTRL", "g_lift03bz02", 0, "GENERATE", "V<-250,100,-310>/V<0,0,0>")
be:sd("MODELCTRL", "g_lift04z02", 0, "GENERATE", "V<-250,100,-310>/V<0,0,0>")
be:sd("MODELCTRL", "g_rock01z02", 0, "GENERATE", "V<-595,200.5,315>/V<0,0,0>")
be:sd("MODELCTRL", "g_rock01z02", 1, "GENERATE", "V<-545,200.5,435>/V<0,90,0>")
be:sd("MODELCTRL", "g_rock01z02", 2, "GENERATE", "V<-445,180.5,355>/V<0,180,0>")
be:sd("MODELCTRL", "g_rock01z02", 3, "GENERATE", "V<-365,180.5,425>/V<0,180,0>")
be:sd("MODELCTRL", "g_rock01z02", 4, "GENERATE", "V<-195,160.5,345>/V<0,0,0>")
be:sd("MODELCTRL", "g_rock01z02", 5, "GENERATE", "V<-95,160.5,395>/V<0,270,0>")
be:sd("MODELCTRL", "g_rock01z02", 6, "GENERATE", "V<-85,160,395>/V<0,180,0>")
be:sd("MODELCTRL", "g_rock01z02", 7, "GENERATE", "V<-15,160.5,305>/V<0,180,0>")
be:sd("MODELCTRL", "g_rock01z02", 8, "GENERATE", "V<-45,160.5,325>/V<0,0,0>")
be:sd("MODELCTRL", "g_rock01z02", 9, "GENERATE", "V<165,120,245>/V<0,18.062,0>")
be:sd("MODELCTRL", "g_rock01z02", 10, "GENERATE", "V<365,120,45>/V<0,-73.121,0>")
be:sd("MODELCTRL", "g_rock02z02", 0, "GENERATE", "V<380,120,40>/V<0,0,0>")
be:sd("MODELCTRL", "g_rock02z02", 2, "GENERATE", "V<-540,200,420>/V<0,90,0>")
be:sd("MODELCTRL", "g_rock02z02", 3, "GENERATE", "V<-540,200,400>/V<0,0,0>")
be:sd("MODELCTRL", "g_rock02z02", 4, "GENERATE", "V<-590,170,170>/V<0,0,0>")
be:sd("MODELCTRL", "g_sbutton", 0, "GENERATE", "V<600.240,59.913,-325.173>/V<0,0,0>")
be:sd("MODELCTRL", "g_sbutton", 1, "GENERATE", "V<600.240,59.913,-345.674>/V<0,60,0>")
be:sd("MODELCTRL", "g_sbutton", 2, "GENERATE", "V<615.365,59.913,-335.219>/V<0,-30,0>")
be:sd("MODELCTRL", "g_sbutton", 3, "GENERATE", "V<584.670,59.913,-335.219>/V<0,30,0>")
be:sd("MODELCTRL", "g_torchz02", 0, "GENERATE", "V<-105,160,355>/V<0,180,0>")
be:sd("MODELCTRL", "g_torchz02", 1, "GENERATE", "V<-75,160,355>/V<0,0,0>")
be:sd("MODELCTRL", "g_tunnel02z02", 0, "GENERATE", "V<600,60,-410>/V<0,180,0>")
be:FLGset(0, 1)
be:DMsetLua("startnpc.lua")
be:DMrun()
if be:FLGisOn(45) == 1 then
    be:sd("MODELCTRL", "g_sbutton", 0, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_sbutton", 1, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_sbutton", 2, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_sbutton", 3, "SQ_ONLOOP")
end
if be:FLGisOn(45) == 1 then
    be:sd("MODELCTRL", "g_tunnel02z02", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "hittunnel02z02", 0, "OFFHIT")
end
be:FLGset(47, 1)
if be:FLGisOn(499) == 0 then
    be:sd("MODELCTRL", "g_darktower", 0, "GENERATE", "V<450,120,200>/V<0,90,0>")
else
end
if be:FLGisOn(500) == 0 then
    be:sd("MODELCTRL", "g_darktower", 1, "GENERATE", "V<-40,160,390>/V<0,-90,0>")
else
end
be:sd("MODELCTRL", "g_atcksabtnz02", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_atcksabtnz02", 1, "SQ_POWERON")
be:sd("MODELCTRL", "g_atcksabtnz02", 2, "SQ_POWERON")
be:sd("MODELCTRL", "g_atcksabtnz02", 3, "SQ_POWERON")
be:sd("MODELCTRL", "g_cannon01", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_cannon01", 1, "SQ_POWERON")
be:sd("MODELCTRL", "g_cannon01", 2, "SQ_POWERON")
be:sd("MODELCTRL", "g_cannon01", 3, "SQ_POWERON")
be:FLGset(901, 0)
if be:SYSctlFlagFolder("IS", 4) == 1 and be:SYSctlFlagFolder("IS", 5) == 1 then
    be:FLGset(901, 1)
end
if be:FLGisOn(901) == 1 and be:FLGisOn(45) == 0 then
    local count = 0
    local local_1
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 then
            count = count + 1
        end
    end
    if count == 4 then
        be:sd("MODELCTRL", "g_sbutton", 0, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 1, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 2, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 3, "SQ_POWERON")
    elseif count == 3 then
        be:sd("MODELCTRL", "g_sbutton", 0, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 1, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 2, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 3, "SQ_ONLOOP")
        g_sbutton03 = 1
    elseif count == 2 then
        be:sd("MODELCTRL", "g_sbutton", 0, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 1, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 2, "SQ_ONLOOP")
        g_sbutton02 = 1
        be:sd("MODELCTRL", "g_sbutton", 3, "SQ_ONLOOP")
        g_sbutton03 = 1
    elseif count == 1 then
        be:sd("MODELCTRL", "g_sbutton", 0, "SQ_POWERON")
        be:sd("MODELCTRL", "g_sbutton", 1, "SQ_ONLOOP")
        g_sbutton01 = 1
        be:sd("MODELCTRL", "g_sbutton", 2, "SQ_ONLOOP")
        g_sbutton02 = 1
        be:sd("MODELCTRL", "g_sbutton", 3, "SQ_ONLOOP")
        g_sbutton03 = 1
    end
end
be:sd("SOUND", nil, -1, "PLAY", "ST_DRYLA")
be:sd("SOUND", nil, -1, "PLAY", "AM_DESER")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
