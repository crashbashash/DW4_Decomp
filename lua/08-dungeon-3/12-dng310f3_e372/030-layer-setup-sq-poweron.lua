local local_0
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.0,0.9,1.0>/V<1.0,0.9,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.2,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
be:sd("MODELCTRL", "g_dbarrierw2", 0, "GENERATE", "V<20,100,-351>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierw2", 1, "GENERATE", "V<-20,100,-351>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierw2", 2, "GENERATE", "V<-471,100,60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw3", 0, "GENERATE", "V<20,100,-329>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierw3", 1, "GENERATE", "V<-20,100,-329>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierw3", 2, "GENERATE", "V<-449,100,60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 0, "GENERATE", "V<20,100,-365>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 1, "GENERATE", "V<20,100,-315>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 2, "GENERATE", "V<-20,100,-365>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 3, "GENERATE", "V<-20,100,-315>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 4, "GENERATE", "V<-485,100,60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 5, "GENERATE", "V<-435,100,60>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbarrierp", 6, "GENERATE", "V<-165,100,500>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 7, "GENERATE", "V<-105,100,500>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbarrierp", 8, "GENERATE", "V<105,100,500>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 9, "GENERATE", "V<165,100,500>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbarrierw5", 0, "GENERATE", "V<-135,100,500>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw5", 1, "GENERATE", "V<135,100,500>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbossgate", 0, "GENERATE", "V<0,100,150>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<240,100,-240>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<160,125,-280>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<-280,100,-200>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 3, "GENERATE", "V<-200,125,-280>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 4, "GENERATE", "V<-460,100,45>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 5, "GENERATE", "V<-460,100,75>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfadescaffold", 0, "GENERATE", "V<-80,100,460>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfadescaffold", 1, "GENERATE", "V<-40,100,460>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfadescaffold", 2, "GENERATE", "V<0,100,460>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfadescaffold", 3, "GENERATE", "V<40,100,460>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfadescaffold", 4, "GENERATE", "V<80,100,460>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfadescaffold", 5, "GENERATE", "V<-80,100,540>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfadescaffold", 6, "GENERATE", "V<-40,100,540>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfadescaffold", 7, "GENERATE", "V<0,100,540>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfadescaffold", 8, "GENERATE", "V<40,100,540>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfadescaffold", 9, "GENERATE", "V<80,100,540>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfadescaffold", 10, "GENERATE", "V<-40,100,-80>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfadescaffold", 11, "GENERATE", "V<40,100,-80>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfadescaffold", 12, "GENERATE", "V<-40,100,-40>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfadescaffold", 13, "GENERATE", "V<40,100,-40>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfadescaffold", 14, "GENERATE", "V<-40,100,0>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfadescaffold", 15, "GENERATE", "V<40,100,0>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfadescaffold", 16, "GENERATE", "V<-40,100,40>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfadescaffold", 17, "GENERATE", "V<40,100,40>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfirefloor", 0, "GENERATE", "V<-400,100,-120>/V<0,0,0>")
be:sd("MODELCTRL", "g_dfirefloor", 1, "GENERATE", "V<240,100,360>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<0,100,-340>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<0,100,-340>/V<0,0,0>")
be:sd("MODELCTRL", "g_drolllaser", 0, "GENERATE", "V<0,100,-240>/V<0,0,0>")
be:sd("MODELCTRL", "g_drolllsbase", 0, "GENERATE", "V<0,100,-240>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 0, "GENERATE", "V<200,125,-240>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 1, "GENERATE", "V<200,125,-280>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 2, "GENERATE", "V<-240,125,-200>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 3, "GENERATE", "V<-240,125,-280>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 4, "GENERATE", "V<-440,100,-20>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 5, "GENERATE", "V<160,125,-20>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 6, "GENERATE", "V<-280,125,100>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 7, "GENERATE", "V<-280,125,300>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtdoor", 8, "GENERATE", "V<300,100,360>/V<0,90,0>")
be:sd("MODELCTRL", "g_dwbutton1", 0, "GENERATE", "V<35,100,-375>/V<0,180,0>")
be:sd("MODELCTRL", "g_dwbutton1", 1, "GENERATE", "V<-35,100,-375>/V<0,180,0>")
be:sd("MODELCTRL", "g_d3movecell2", 0, "GENERATE", "V<160,100,-180>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3movecell2", 1, "GENERATE", "V<-240,100,-100>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3movecell2w", 0, "GENERATE", "V<160,100,-180>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3movecell2w", 1, "GENERATE", "V<-240,100,-100>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<-280,125,80>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<160,125,-40>/V<0,0,0>")
for ramNo = 1, 20 do
    if be:FLGisOn(ramNo + 159) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", ramNo))
    end
end
be:sd("MODELCTRL", "g_dtdoor", 0, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 1, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 2, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 3, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 4, "SQ_BUTTON")
be:sd("MODELCTRL", "g_dtdoor", 5, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 6, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 7, "SQ_CLEAR")
be:sd("MODELCTRL", "g_dtdoor", 8, "SQ_CLEAR")
if be:FLGisOn(151) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 8, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
end
if be:FLGisOn(152) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
if be:FLGisOn(155) == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 6, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dtdoor", 7, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
end
if be:FLGisOn(158) + be:FLGisOn(159) == 2 then
    be:sd("MODELCTRL", "g_dbossgate", 0, "SQ_POWERON")
    g_bossgate = 1
end
if be:FLGisOn(180) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_dtdoor", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(181) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_dtdoor", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
end
if be:FLGisOn(182) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_dtdoor", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(183) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_dtdoor", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(183) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 4, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw2", 2, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw3", 2, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 4, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 5, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "barrierwall03", 0, "OFFHIT")
end
if be:FLGisOn(185) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 5, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 5, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_dtdoor", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(186) ~= 1 then
    be:sd("MODELCTRL", "g_dbarrierw2", 1, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw3", 1, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 2, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 3, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dwbutton1", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "barrierwall02", 0, "OFFHIT")
end
if be:FLGisOn(187) ~= 1 then
    be:sd("MODELCTRL", "g_dbarrierw2", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw3", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierp", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dwbutton1", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "barrierwall01", 0, "OFFHIT")
end
if be:FLGisOn(188) == 1 then
    be:sd("HITLANDMODEL", "cell01right", 0, "OFFHIT")
else
    be:sd("MODELCTRL", "g_d3movecell2", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d3movecell2w", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "cell01left", 0, "OFFHIT")
end
if be:FLGisOn(189) ~= 1 then
    be:sd("HITLANDMODEL", "cell02right", 0, "OFFHIT")
else
    be:sd("MODELCTRL", "g_d3movecell2", 1, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d3movecell2w", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "cell02left", 0, "OFFHIT")
end
be:sd("MODELCTRL", "g_dbarrierw5", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_dbarrierw5", 1, "SQ_POWERON")
for ramNo = 6, 9 do
    be:sd("MODELCTRL", "g_dbarrierp", ramNo, "SQ_POWERON")
end
be:sd("MODELCTRL", "g_dfadescaffold", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_dfadescaffold", 1, "SQ_POWERON")
be:sd("MODELCTRL", "g_dfadescaffold", 2, "SQ_POWERON")
be:sd("MODELCTRL", "g_dfadescaffold", 3, "SQ_POWERON")
be:sd("MODELCTRL", "g_dfadescaffold", 4, "SQ_POWERON")
be:sd("MODELCTRL", "g_dfadescaffold", 5, "SQ_POWERON")
be:sd("MODELCTRL", "g_dfadescaffold", 6, "SQ_POWERON")
be:sd("MODELCTRL", "g_dfadescaffold", 7, "SQ_POWERON")
be:sd("MODELCTRL", "g_dfadescaffold", 8, "SQ_POWERON")
be:sd("MODELCTRL", "g_dfadescaffold", 9, "SQ_POWERON")
be:sd("MODELCTRL", "g_dfadescaffold", 10, "SQ_POWERON")
be:sd("MODELCTRL", "g_dfadescaffold", 11, "SQ_POWERON")
be:sd("MODELCTRL", "g_dfadescaffold", 12, "SQ_POWERON")
be:sd("MODELCTRL", "g_dfadescaffold", 13, "SQ_POWERON")
be:sd("MODELCTRL", "g_dfadescaffold", 14, "SQ_POWERON")
be:sd("MODELCTRL", "g_dfadescaffold", 15, "SQ_POWERON")
be:sd("MODELCTRL", "g_dfadescaffold", 16, "SQ_POWERON")
be:sd("MODELCTRL", "g_dfadescaffold", 17, "SQ_POWERON")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(293) == 1 then
    if be:MDLisLive("j_map310f3", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map310f3", 0, "GENERATE", "SQ_OPEN")
    end
    local local_1
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 and be:MDLisLive("j_mapcur", playerIndex) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", playerIndex, "GENERATE")
        end
    end
end
