funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.1,1.1,0.9>/V<1.1,1.1,0.9>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.23,0.2>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
if be:PLAYERgetPos() == 1 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
end
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<-460,10,280>/V<0,90,0>")
be:sd("MODELCTRL", "g_dwbutton1", 0, "GENERATE", "V<-155,10,-595>/V<0,180,0>")
be:sd("MODELCTRL", "g_dwbutton1", 1, "GENERATE", "V<-575,10,-380>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dwbutton1", 2, "GENERATE", "V<-335,10,540>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dwbutton1", 3, "GENERATE", "V<-335,10,620>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dwbutton1", 4, "GENERATE", "V<-335,10,660>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<710,10,460>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<360,10,460>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<360,10,460>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<-280,10,180>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<-280,10,220>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<-240,10,220>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-320,10,100>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<-240,10,100>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<-80,10,655>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 3, "GENERATE", "V<-40,10,540>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 0, "GENERATE", "V<-525,10,-585>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 1, "GENERATE", "V<-115,10,-585>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 2, "GENERATE", "V<-205,10,-175>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 3, "GENERATE", "V<-365,10,295>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 4, "GENERATE", "V<-195,10,295>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 5, "GENERATE", "V<-365,10,465>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 6, "GENERATE", "V<-195,10,465>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 7, "GENERATE", "V<5,10,505>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 0, "GENERATE", "V<-565,10,-60>/V<0,90,0>")
be:sd("MODELCTRL", "g_dallhealeffect", 0, "GENERATE", "V<-320,10,-380>/V<0,0,0>")
be:sd("MODELCTRL", "g_dallhealbase", 0, "GENERATE", "V<-320,10,-380>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2torch", 0, "GENERATE", "V<-365,10,-425>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2torch", 1, "GENERATE", "V<-275,10,-425>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2torch", 2, "GENERATE", "V<-365,10,-335>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2torch", 3, "GENERATE", "V<-275,10,-335>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 0, "GENERATE", "V<-320,10,-520>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 1, "GENERATE", "V<-440,10,-320>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 2, "GENERATE", "V<-120,10,-160>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 3, "GENERATE", "V<-500,10,100>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2door", 4, "GENERATE", "V<-440,10,160>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 5, "GENERATE", "V<-60,10,100>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2door", 6, "GENERATE", "V<-120,10,160>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 7, "GENERATE", "V<-380,10,380>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2door", 8, "GENERATE", "V<-180,10,380>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2door", 9, "GENERATE", "V<-280,10,480>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 10, "GENERATE", "V<-220,10,580>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2door", 11, "GENERATE", "V<-60,10,580>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2door", 12, "GENERATE", "V<-40,10,520>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 13, "GENERATE", "V<20,10,460>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2door", 14, "GENERATE", "V<420,10,460>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2door", 15, "GENERATE", "V<620,10,460>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2base", 0, "GENERATE", "V<-520,10,-580>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2base", 1, "GENERATE", "V<-120,10,-580>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2base", 2, "GENERATE", "V<-200,10,-180>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2base", 3, "GENERATE", "V<-360,10,300>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2base", 4, "GENERATE", "V<-200,10,300>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2base", 5, "GENERATE", "V<-360,10,460>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2base", 6, "GENERATE", "V<-200,10,460>/V<0,180,0>")
be:sd("MODELCTRL", "g_d2base", 7, "GENERATE", "V<0,10,500>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbasewall", 0, "GENERATE", "V<-520,10,-580>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbasewall", 1, "GENERATE", "V<-120,10,-580>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbasewall", 2, "GENERATE", "V<-200,10,-180>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbasewall", 3, "GENERATE", "V<-360,10,300>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbasewall", 4, "GENERATE", "V<-200,10,300>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbasewall", 5, "GENERATE", "V<-360,10,460>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbasewall", 6, "GENERATE", "V<-200,10,460>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbasewall", 7, "GENERATE", "V<0,10,500>/V<0,180,0>")
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<118,10,578>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<-440,10,-260>/V<0,0,0>")
for local_1 = 1, 13 do
    if be:FLGisOn(local_1 + 146) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", local_1))
    end
end
if be:FLGisOn(169) ~= 1 then
    be:sd("MODELCTRL", "g_d2dktower", 0, "GENERATE", "V<-620,10,100>/V<0,0,0>")
end
if be:FLGisOn(170) ~= 1 then
    be:sd("MODELCTRL", "g_d2dktower", 1, "GENERATE", "V<60,10,100>/V<0,0,0>")
end
be:sd("MODELCTRL", "g_d2door", 0, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 1, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 2, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 3, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 4, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 5, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 6, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 7, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 8, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 9, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 10, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 11, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 12, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 13, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 14, "SQ_BOSS")
be:sd("MODELCTRL", "g_d2door", 15, "SQ_CLEAR")
if be:FLGisOn(160) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d2door", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(161) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d2door", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
if be:FLGisOn(162) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d2door", 11, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT")
end
if be:FLGisOn(163) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d2door", 12, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall13", 0, "OFFHIT")
end
if be:FLGisOn(164) == 1 then
    be:sd("MODELCTRL", "g_dwbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d2door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(165) == 1 then
    be:sd("MODELCTRL", "g_dwbutton1", 1, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d2door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
end
if be:FLGisOn(166) == 1 then
    be:sd("MODELCTRL", "g_dwbutton1", 2, "SQ_SILENTON")
end
if be:FLGisOn(167) == 1 then
    be:sd("MODELCTRL", "g_dwbutton1", 3, "SQ_SILENTON")
end
if be:FLGisOn(166) == 1 then
    be:sd("MODELCTRL", "g_d2door", 10, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
end
if be:FLGisOn(138) ~= 1 then
    be:FLGset(168, 0)
else
    be:sd("MODELCTRL", "g_dwbutton1", 4, "SQ_SILENTON")
end
if be:FLGisOn(131) == 1 then
    be:sd("MODELCTRL", "g_d2door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(133) + be:FLGisOn(141) + be:FLGisOn(142) + be:FLGisOn(143) == 4 then
    be:sd("MODELCTRL", "g_d2door", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(135) + be:FLGisOn(144) + be:FLGisOn(145) + be:FLGisOn(146) == 4 then
    be:sd("MODELCTRL", "g_d2door", 6, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
end
if be:FLGisOn(137) == 1 then
    be:sd("MODELCTRL", "g_d2door", 7, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d2door", 8, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d2door", 9, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
end
if be:FLGisOn(139) == 1 then
    be:sd("MODELCTRL", "g_d2door", 13, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall14", 0, "OFFHIT")
end
if be:FLGisOn(140) == 1 then
    be:sd("MODELCTRL", "g_d2door", 15, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall16", 0, "OFFHIT")
end
be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
g_security = 1
be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_d2door", 14, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall15", 0, "OFFHIT")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(292) == 1 then
    if be:MDLisLive("j_map204b2", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map204b2", 0, "GENERATE", "SQ_OPEN")
    end
    for local_2 = 0, 3 do
        if be:SYSisJoinPlayer(local_2) == 1 and be:MDLisLive("j_mapcur", local_2) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", local_2, "GENERATE")
        end
    end
end
