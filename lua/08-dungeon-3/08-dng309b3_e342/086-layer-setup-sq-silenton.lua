local local_0
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.0,1.1,1.05>/V<1.0,1.1,1.05>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.2,0.25,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
if be:PLAYERgetPos() == 2 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
end
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<40,65,340>/V<0,0,0>")
be:sd("MODELCTRL", "g_dmpheal", 0, "GENERATE", "V<270,40,-500>/V<0,90,0>")
be:sd("MODELCTRL", "g_dmphealeffect", 0, "GENERATE", "V<270,40,-500>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<-440,40,-140>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<-320,40,-80>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<320,40,-60>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 3, "GENERATE", "V<260,40,-220>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<80,40,700>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<160,40,700>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<-160,40,-20>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 3, "GENERATE", "V<205,40,-380>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<180,40,660>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d3door", 1, "GENERATE", "V<40,65,240>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 2, "GENERATE", "V<140,65,340>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d3door", 3, "GENERATE", "V<300,40,100>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d3door", 4, "GENERATE", "V<-380,40,20>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d3door", 5, "GENERATE", "V<-180,40,-20>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d3door", 6, "GENERATE", "V<-160,40,-35>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 7, "GENERATE", "V<-280,40,-360>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 8, "GENERATE", "V<-40,65,-280>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 9, "GENERATE", "V<225,40,-380>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d3door", 10, "GENERATE", "V<-80,40,-640>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<-160,40,-340>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<120,40,60>/V<0,90,0>")
be:sd("MODELCTRL", "n_recorderdng", 2, "GENERATE", "V<-120,40,180>/V<0,-90,0>")
for i = 1, 23 do
    if be:FLGisOn(i + 182) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", i))
    end
end
if be:FLGisOn(210) ~= 1 then
    be:sd("MODELCTRL", "g_dcellwall", 0, "GENERATE", "V<120,40,-275>/V<0,0,0>")
end
be:sd("MODELCTRL", "g_d3door", 0, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d3door", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 2, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 3, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 4, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 5, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d3door", 6, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d3door", 7, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 8, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 9, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d3door", 10, "SQ_CLEAR")
if be:FLGisOn(206) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
end
if be:FLGisOn(207) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
end
if be:FLGisOn(206) + be:FLGisOn(207) == 2 then
    be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(208) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d3door", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d3door", 6, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
end
if be:FLGisOn(209) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d3door", 9, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
end
if be:FLGisOn(164) == 1 then
    be:sd("MODELCTRL", "g_d3door", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(165) == 1 then
    be:sd("MODELCTRL", "g_d3door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d3door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
    g_security = 1
end
if be:FLGisOn(169) == 1 then
    be:sd("MODELCTRL", "g_d3door", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(177) == 1 then
    be:sd("MODELCTRL", "g_d3door", 8, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
end
if be:FLGisOn(181) == 1 then
    be:sd("MODELCTRL", "g_d3door", 7, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
end
if be:FLGisOn(182) == 1 then
    be:sd("MODELCTRL", "g_d3door", 10, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
end
be:sd("MODELCTRL", "g_dmphealeffect", 0, "SQ_POWERON")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(293) == 1 then
    if be:MDLisLive("j_map309b3", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map309b3", 0, "GENERATE", "SQ_OPEN")
    end
    local local_1
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 and be:MDLisLive("j_mapcur", playerIndex) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", playerIndex, "GENERATE")
        end
    end
end
