funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.2,1.15,1.2>/V<1.2,1.15,1.2>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.2,0.35>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
be:sd("MATCTRL", nil, -1, "PAUSE")
funcPlayerSet()
if be:PLAYERgetPos() == 0 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
elseif be:PLAYERgetPos() == 3 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT", 1)
end
be:sd("MODELCTRL", "g_bossymbolz01", 0, "GENERATE", "V<475,50.1,21.5>/V<0,0,0>")
be:sd("MODELCTRL", "g_bossymbolz01", 1, "GENERATE", "V<445,50.1,21.5>/V<0,0,0>")
be:sd("MODELCTRL", "g_bossymbolz01", 2, "GENERATE", "V<195,66.1,-315>/V<0,0,0>")
be:sd("MODELCTRL", "g_bossymbolz01", 3, "GENERATE", "V<165,66.1,-315>/V<0,0,0>")
be:sd("MODELCTRL", "g_bossymbolz01", 4, "GENERATE", "V<115,50.1,207.5>/V<0,180,0>")
be:sd("MODELCTRL", "g_bossymbolz01", 5, "GENERATE", "V<65,50.1,207.5>/V<0,180,0>")
be:sd("MODELCTRL", "g_bossymbolz01", 6, "GENERATE", "V<-337.5,38.1,205>/V<0,-45,0>")
be:sd("MODELCTRL", "g_bossymbolz01", 7, "GENERATE", "V<-366,38.1,177.5>/V<0,-45,0>")
be:sd("MODELCTRL", "g_bush01z01", 0, "GENERATE", "V<165,58.75,-25>/V<0,0,0>")
be:sd("MODELCTRL", "g_bush01z01", 1, "GENERATE", "V<175,58.75,-15>/V<0,180,0>")
be:sd("MODELCTRL", "g_bush01z01", 2, "GENERATE", "V<165,58.75,35>/V<0,270,0>")
be:sd("MODELCTRL", "g_bush01z01", 3, "GENERATE", "V<175,58.75,45>/V<0,0,0>")
be:sd("MODELCTRL", "g_bush01z01", 4, "GENERATE", "V<-145,57.5,105>/V<0,180,0>")
be:sd("MODELCTRL", "g_bush01z01", 5, "GENERATE", "V<-145,57.5,95>/V<0,0,0>")
be:sd("MODELCTRL", "g_bush01z01", 6, "GENERATE", "V<-237.5,58.75,-125>/V<0,180,0>")
be:sd("MODELCTRL", "g_bush01z01", 7, "GENERATE", "V<-247.5,58.75,-125>/V<0,0,0>")
be:sd("MODELCTRL", "g_bush01z01", 8, "GENERATE", "V<-238.75,58.75,-135>/V<0,270,0>")
be:sd("MODELCTRL", "g_bush01z01", 9, "GENERATE", "V<-248.75,58.75,-135>/V<0,90,0>")
be:sd("MODELCTRL", "g_bush01z01", 10, "GENERATE", "V<-258.75,58.75,-135>/V<0,0,0>")
be:sd("MODELCTRL", "g_bush01z01", 11, "GENERATE", "V<-268.75,58.75,-135>/V<0,180,0>")
be:sd("MODELCTRL", "g_cannon01", 0, "GENERATE", "V<175,68.5,-175>/V<0,0,0>")
be:sd("MODELCTRL", "g_cannon01", 1, "GENERATE", "V<185,68.5,-175>/V<0,0,0>")
be:sd("MODELCTRL", "g_gobgatez01", 0, "GENERATE", "V<180,65,-340>/V<0,0,0>")
be:sd("MODELCTRL", "g_lever01z01", 0, "GENERATE", "V<132.5,50,281.875>/V<0,-135,0>")
be:sd("MODELCTRL", "g_lift01z01", 0, "GENERATE", "V<-190,62.031,-20>/V<0,0,0>")
if be:FLGisOn(349) == 0 then
    be:sd("MODELCTRL", "g_numez01", 0, "GENERATE", "V<120,97.5,-120>/V<0,90,0>")
    if be:FLGisOn(504) == 0 then
        be:sd("MODELCTRL", "i_breakcur", 29, "GENERATE", "V<120,112.5,-120>/V<0,90,0>")
    end
else
end
if be:FLGisOn(350) == 0 then
    be:sd("MODELCTRL", "g_numez01", 1, "GENERATE", "V<120,97.5,-100>/V<0,90,0>")
    if be:FLGisOn(504) == 0 then
        be:sd("MODELCTRL", "i_breakcur", 30, "GENERATE", "V<120,112.5,-100>/V<0,90,0>")
    end
else
end
if be:FLGisOn(351) == 0 then
    be:sd("MODELCTRL", "g_numez01", 2, "GENERATE", "V<120,97.5,-80>/V<0,90,0>")
    if be:FLGisOn(504) == 0 then
        be:sd("MODELCTRL", "i_breakcur", 31, "GENERATE", "V<120,112.5,-80>/V<0,90,0>")
    end
else
end
be:sd("MODELCTRL", "g_rock01z01", 0, "GENERATE", "V<165,57.5,-15>/V<0,0,0>")
be:sd("MODELCTRL", "g_rock01z01", 1, "GENERATE", "V<165,57.5,-5>/V<0,180,0>")
be:sd("MODELCTRL", "g_rock01z01", 2, "GENERATE", "V<175,57.5,-5>/V<0,90,0>")
be:sd("MODELCTRL", "g_rock01z01", 3, "GENERATE", "V<165,57.5,25>/V<0,0,0>")
be:sd("MODELCTRL", "g_rock01z01", 4, "GENERATE", "V<175,57.5,25>/V<0,180,0>")
be:sd("MODELCTRL", "g_rock01z01", 5, "GENERATE", "V<175,57.5,35>/V<0,90,0>")
be:sd("MODELCTRL", "g_rock01z01", 6, "GENERATE", "V<45,49.5,85>/V<0,0,0>")
be:sd("MODELCTRL", "g_rock01z01", 7, "GENERATE", "V<45,49.5,95>/V<0,270,0>")
be:sd("MODELCTRL", "g_rock01z01", 8, "GENERATE", "V<-105,49.5,85>/V<0,0,0>")
be:sd("MODELCTRL", "g_rock01z01", 9, "GENERATE", "V<-105,49.5,95>/V<0,270,0>")
be:sd("MODELCTRL", "g_rock01z01", 10, "GENERATE", "V<-175,57.5,135>/V<0,0,0>")
be:sd("MODELCTRL", "g_rock01z01", 11, "GENERATE", "V<-175,57.5,145>/V<0,180,0>")
be:sd("MODELCTRL", "g_rock01z01", 12, "GENERATE", "V<-240,57.5,-155>/V<0,270,0>")
be:sd("MODELCTRL", "g_rock01z01", 13, "GENERATE", "V<-250,57.5,-155>/V<0,90,0>")
be:sd("MODELCTRL", "g_rock01z01", 14, "GENERATE", "V<-260,57.5,-175>/V<0,0,0>")
be:sd("MODELCTRL", "g_rock01z01", 15, "GENERATE", "V<-270,57.5,-175>/V<0,270,0>")
be:sd("MODELCTRL", "g_rock02z01", 0, "GENERATE", "V<170,58,10>/V<0,0,0>")
be:sd("MODELCTRL", "g_rock02z01", 1, "GENERATE", "V<-30,50,90>/V<0,270,0>")
be:sd("MODELCTRL", "g_rock02z01", 2, "GENERATE", "V<-245,58,-170>/V<0,0,0>")
be:sd("MODELCTRL", "g_rock02z01", 3, "GENERATE", "V<-265,58,-160>/V<0,0,0>")
if be:FLGisOn(337) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 0, "GENERATE", "V<35,86.875,75>/V<0,0,0>")
else
end
if be:FLGisOn(338) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 1, "GENERATE", "V<25,86.875,75>/V<0,0,0>")
else
end
if be:FLGisOn(339) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 2, "GENERATE", "V<15,86.875,75>/V<0,0,0>")
else
end
if be:FLGisOn(340) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 3, "GENERATE", "V<5,86.875,75>/V<0,0,0>")
else
end
if be:FLGisOn(341) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 4, "GENERATE", "V<-5,86.875,75>/V<0,0,0>")
else
end
if be:FLGisOn(342) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 5, "GENERATE", "V<-15,86.875,75>/V<0,0,0>")
else
end
if be:FLGisOn(343) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 6, "GENERATE", "V<-45,86.875,75>/V<0,0,0>")
else
end
if be:FLGisOn(344) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 7, "GENERATE", "V<-55,86.875,75>/V<0,0,0>")
else
end
if be:FLGisOn(345) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 8, "GENERATE", "V<-65,86.875,75>/V<0,0,0>")
else
end
if be:FLGisOn(346) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 9, "GENERATE", "V<-75,86.875,75>/V<0,0,0>")
else
end
if be:FLGisOn(347) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 10, "GENERATE", "V<-85,86.875,75>/V<0,0,0>")
else
end
if be:FLGisOn(348) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 11, "GENERATE", "V<-95,86.875,75>/V<0,0,0>")
else
end
be:sd("MODELCTRL", "g_sbutton", 0, "GENERATE", "V<170,66,-290>/V<0,45,0>")
be:sd("MODELCTRL", "g_sbutton", 1, "GENERATE", "V<190,66,-290>/V<0,-15,0>")
be:sd("MODELCTRL", "g_sbutton", 2, "GENERATE", "V<170,66.4,-270>/V<0,45,0>")
be:sd("MODELCTRL", "g_sbutton", 3, "GENERATE", "V<190,66.3,-270>/V<0,-135,0>")
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "SQ_POWERON/V<-280.625,57.6,-20>/V<0,225,0>")
be:sd("MODELCTRL", "g_torchz01", 0, "GENERATE", "V<75,50,255>/V<0,0,0>")
be:sd("MODELCTRL", "g_wall01z01", 0, "GENERATE", "V<-200,62,-10>/V<0,0,0>")
be:FLGset(0, 1)
be:DMsetLua("startnpc.lua")
be:DMrun()
be:sd("MODELCTRL", "g_numez01", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_numez01", 1, "SQ_POWERON")
be:sd("MODELCTRL", "g_numez01", 2, "SQ_POWERON")
if be:FLGisOn(38) == 0 then
    be:sd("HITLANDMODEL", "hitlift01z01", 0, "ONHIT")
elseif be:FLGisOn(38) == 1 then
    be:sd("MODELCTRL", "g_lift01z01", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "hitlift01z01", 0, "OFFHIT")
    be:sd("GENERATER", nil, -1, "START", "GBOX-01")
end
if be:FLGisOn(38) == 1 then
    be:sd("MODELCTRL", "g_lever01z01", 0, "SQ_SILENTON")
end
if be:FLGisOn(20) ~= 1 then
    if be:FLGisOn(37) == 1 then
    end
end
be:sd("MODELCTRL", "g_gobgatez01", 0, "SQ_SILENTON")
be:sd("HITLANDMODEL", "hitgobgatez01", 0, "OFFHIT")
be:sd("MODELCTRL", "g_cannon01", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_cannon01", 1, "SQ_POWERON")
be:FLGset(900, 0)
if be:SYSctlFlagFolder("IS", 0) == 1 and be:SYSctlFlagFolder("IS", 1) == 1 then
    be:FLGset(900, 1)
end
if be:FLGisOn(900) == 1 then
    if be:FLGisOn(20) ~= 0 then
        if be:FLGisOn(37) == 0 then
        end
    end
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
if be:FLGisOn(20) ~= 1 then
    if be:FLGisOn(37) == 1 then
    end
end
be:sd("MODELCTRL", "g_sbutton", 0, "SQ_ONLOOP")
be:sd("MODELCTRL", "g_sbutton", 1, "SQ_ONLOOP")
be:sd("MODELCTRL", "g_sbutton", 2, "SQ_ONLOOP")
be:sd("MODELCTRL", "g_sbutton", 3, "SQ_ONLOOP")
be:sd("SOUND", nil, -1, "PLAY", "ST_DEATH")
be:sd("SOUND", nil, -1, "PLAY", "AM_VALLE")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
