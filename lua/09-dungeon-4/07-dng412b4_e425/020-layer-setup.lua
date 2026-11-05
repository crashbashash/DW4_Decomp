funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<0.9,1.0,0.9>/V<1.0,0.9,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.18,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
if be:PLAYERgetPos() == 5 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
end
be:sd("MODELCTRL", "g_d4door", 0, "GENERATE", "V<260,125,120>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 1, "GENERATE", "V<460,125,120>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 2, "GENERATE", "V<700,100,80>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 3, "GENERATE", "V<340,125,960>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 4, "GENERATE", "V<180,100,840>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 5, "GENERATE", "V<40,100,780>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 6, "GENERATE", "V<-20,100,840>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 7, "GENERATE", "V<-440,125,500>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 8, "GENERATE", "V<160,100,340>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 9, "GENERATE", "V<-440,100,180>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 10, "GENERATE", "V<-560,100,20>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 11, "GENERATE", "V<-600,100,-220>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 12, "GENERATE", "V<-440,125,-380>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 13, "GENERATE", "V<-200,100,-780>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 14, "GENERATE", "V<-200,100,-980>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<-200,100,-720>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<-200,100,-720>/V<0,0,0>")
be:sd("MODELCTRL", "g_dlaserbs", 0, "GENERATE", "V<-200,100,755>/V<0,0,0>")
be:sd("MODELCTRL", "g_dlaserbs", 1, "GENERATE", "V<-155,100,755>/V<0,0,0>")
be:sd("MODELCTRL", "g_dlaserbs", 2, "GENERATE", "V<-285,100,-465>/V<0,90,0>")
be:sd("MODELCTRL", "g_dlaserbs", 3, "GENERATE", "V<-115,100,-525>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dlasergun", 0, "GENERATE", "V<-200,100,755>/V<0,0,0>")
be:sd("MODELCTRL", "g_dlasergun", 1, "GENERATE", "V<-155,100,755>/V<0,0,0>")
be:sd("MODELCTRL", "g_dlasergun", 2, "GENERATE", "V<-285,100,-465>/V<0,90,0>")
be:sd("MODELCTRL", "g_dlasergun", 3, "GENERATE", "V<-115,100,-525>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dmpheal", 0, "GENERATE", "V<-200,100,-200>/V<0,0,0>")
be:sd("MODELCTRL", "g_dmphealeffect", 0, "GENERATE", "V<-200,100,-200>/V<0,0,0>")
be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<-200,100,-1070>/V<0,0,0>")
be:sd("MODELCTRL", "g_dwbutton1", 0, "GENERATE", "V<160,100,825>/V<0,180,0>")
be:sd("MODELCTRL", "g_dwbutton1", 1, "GENERATE", "V<175,100,360>/V<0,90,0>")
be:sd("MODELCTRL", "g_dwbutton1", 2, "GENERATE", "V<-545,100,115>/V<0,90,0>")
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<360,125,120>/V<0,0,0>")
be:sd("MODELCTRL", "r_dmvmark1", 0, "GENERATE", "V<-200,100,840>/V<0,0,0>")
be:sd("MODELCTRL", "r_dmvmark1", 1, "GENERATE", "V<-295,100,875>/V<0,0,0>")
be:sd("MODELCTRL", "r_dmvmark1", 2, "GENERATE", "V<-170,99.9,-435>/V<0,0,0>")
be:sd("MODELCTRL", "g_drailscaffold", 0, "GENERATE", "V<0,0,0>/V<0,0,0>")
be:sd("MODELCTRL", "g_drailscaffold", 1, "GENERATE", "V<0,0,0>/V<0,0,0>")
be:sd("MODELCTRL", "g_drailscaffold", 2, "GENERATE", "V<0,0,0>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtrailmon", 0, "GENERATE", "V<0,0,0>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtrailmon", 1, "GENERATE", "V<0,0,0>/V<0,0,0>")
be:sd("MODELCTRL", "r_drail02", 0, "GENERATE", "V<490,0,480>/V<0,0,0>")
be:sd("MODELCTRL", "r_drail02", 1, "GENERATE", "V<-485,0,80>/V<0,0,0>")
if be:FLGisOn(210) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<-960,90,-80>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<-920,90,-80>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<-880,90,-80>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<-960,90,-40>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<-920,90,-40>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<-880,90,-40>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<-920,90,0>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<-960,90,40>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<-920,90,40>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<-880,90,40>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<-1000,90,80>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 11, "GENERATE", "V<-960,90,80>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 12, "GENERATE", "V<-920,90,80>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 13, "GENERATE", "V<-880,90,80>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 14, "GENERATE", "V<-840,90,80>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 15, "GENERATE", "V<-960,90,120>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 16, "GENERATE", "V<-920,90,120>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 17, "GENERATE", "V<-880,90,120>/V<0,0,0>")
end
if be:FLGisOn(209) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 18, "GENERATE", "V<840,90,320>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 19, "GENERATE", "V<880,90,320>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 20, "GENERATE", "V<920,90,320>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 21, "GENERATE", "V<840,90,360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 22, "GENERATE", "V<880,90,360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 23, "GENERATE", "V<920,90,360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 24, "GENERATE", "V<880,90,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 25, "GENERATE", "V<840,90,440>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 26, "GENERATE", "V<880,90,440>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 27, "GENERATE", "V<920,90,440>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 28, "GENERATE", "V<800,90,480>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 29, "GENERATE", "V<840,90,480>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 30, "GENERATE", "V<880,90,480>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 31, "GENERATE", "V<920,90,480>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 32, "GENERATE", "V<960,90,480>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 33, "GENERATE", "V<840,90,520>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 34, "GENERATE", "V<880,90,520>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 35, "GENERATE", "V<920,90,520>/V<0,0,0>")
end
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<40,100,445>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<-680,100,45>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 2, "GENERATE", "V<795,100,45>/V<0,0,0>")
for local_1 = 1, 20 do
    if be:FLGisOn(local_1 + 183) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", local_1))
    end
end
if be:FLGisOn(207) ~= 1 then
    be:sd("MODELCTRL", "g_dscrap", 0, "GENERATE", "V<880,100,370>/V<0,90,0>")
end
if be:FLGisOn(208) ~= 1 then
    be:sd("MODELCTRL", "g_dscrap", 1, "GENERATE", "V<-920,100,-30>/V<0,90,0>")
end
be:sd("MODELCTRL", "g_d4door", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 2, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 3, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 4, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 5, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 6, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 7, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 8, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 9, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 10, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 11, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 12, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 13, "SQ_BOSS")
be:sd("MODELCTRL", "g_d4door", 14, "SQ_CLEAR")
if be:FLGisOn(204) == 1 then
    be:sd("MODELCTRL", "g_dwbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d4door", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(205) == 1 then
    be:sd("MODELCTRL", "g_dwbutton1", 1, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d4door", 8, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
end
if be:FLGisOn(206) == 1 then
    be:sd("MODELCTRL", "g_dwbutton1", 2, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d4door", 10, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
end
if be:FLGisOn(164) == 1 then
    be:sd("MODELCTRL", "g_d4door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
    g_security = 1
end
if be:FLGisOn(167) == 1 then
    be:sd("MODELCTRL", "g_d4door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(172) == 1 then
    be:sd("MODELCTRL", "g_d4door", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(173) == 1 then
    be:sd("MODELCTRL", "g_d4door", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 6, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
end
if be:FLGisOn(175) == 1 then
    be:sd("MODELCTRL", "g_d4door", 7, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
end
if be:FLGisOn(179) == 1 then
    be:sd("MODELCTRL", "g_d4door", 11, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT")
end
if be:FLGisOn(181) == 1 then
    be:sd("MODELCTRL", "g_d4door", 12, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall13", 0, "OFFHIT")
end
if be:FLGisOn(183) == 1 then
    be:sd("MODELCTRL", "g_d4door", 14, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall15", 0, "OFFHIT")
end
be:sd("MODELCTRL", "g_d4door", 9, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
be:sd("MODELCTRL", "g_d4door", 13, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall14", 0, "OFFHIT")
be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_drailscaffold", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_drailscaffold", 1, "SQ_POWERON")
be:sd("MODELCTRL", "g_drailscaffold", 2, "SQ_POWERON")
be:sd("MODELCTRL", "r_dmvmark1", 0, "SQ_POWERON1")
be:sd("MODELCTRL", "r_dmvmark1", 1, "SQ_POWERON2", 139)
be:sd("MODELCTRL", "r_dmvmark1", 2, "SQ_POWERON3")
be:sd("MODELCTRL", "g_dtrailmon", 0, "SQ_HIDE")
be:sd("MODELCTRL", "g_dtrailmon", 1, "SQ_HIDE")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(294) == 1 then
    if be:MDLisLive("j_map412b4", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map412b4", 0, "GENERATE", "SQ_OPEN")
    end
    for local_2 = 0, 3 do
        if be:SYSisJoinPlayer(local_2) == 1 and be:MDLisLive("j_mapcur", local_2) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", local_2, "GENERATE")
        end
    end
end
