funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.1,1.1,0.9>/V<1.1,1.1,0.9>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.23,0.2>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
if be:COUNTERget(2) ~= local_1 then
    be:COUNTERset(2, local_1)
    for local_2 = 100, 299 do
        be:FLGset(local_2, 0)
    end
end
be:sd("MODELCTRL", "g_dwbutton2", 0, "GENERATE", "V<-95,40,-195>/V<0,180,0>")
be:sd("MODELCTRL", "g_dwbutton2", 1, "GENERATE", "V<-25,40,-195>/V<0,180,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<-280,40,-100>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<-240,40,-100>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<120,40,-100>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 3, "GENERATE", "V<160,40,-100>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 4, "GENERATE", "V<380,40,-565>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<-375,40,180>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 3, "GENERATE", "V<255,40,180>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 0, "GENERATE", "V<20,40,-585>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2torch", 0, "GENERATE", "V<-85,40,-125>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2torch", 1, "GENERATE", "V<-35,40,-125>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 0, "GENERATE", "V<-60,40,400>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 1, "GENERATE", "V<-120,40,180>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2door", 2, "GENERATE", "V<0,40,180>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2door", 3, "GENERATE", "V<-60,40,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 4, "GENERATE", "V<-60,40,-200>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 5, "GENERATE", "V<-160,40,-100>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2door", 6, "GENERATE", "V<40,40,-100>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2door", 7, "GENERATE", "V<300,40,-200>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 8, "GENERATE", "V<380,40,-720>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<380,40,-815>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<-415,40,-100>/V<0,90,0>")
for local_2 = 1, 8 do
    if be:FLGisOn(local_2 + 113) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", local_2))
    end
end
if be:FLGisOn(127) ~= 1 then
    be:sd("MODELCTRL", "g_d2dktower", 0, "GENERATE", "V<-60,40,-300>/V<0,0,0>")
end
be:sd("MODELCTRL", "g_d2door", 0, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 2, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 3, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 4, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 5, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 6, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 7, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 8, "SQ_CLEAR")
if be:SYSgetPlayerNinzu() == 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-100,40,420>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<-20,40,420>/V<0,0,0>")
    if be:FLGisOn(122) ~= 1 then
        be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
    else
        be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    end
    if be:FLGisOn(123) ~= 1 then
        be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
    else
        be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
    end
end
be:sd("MODELCTRL", "g_dbutton2", 0, "GENERATE", "V<-100,40,420>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton2", 1, "GENERATE", "V<-20,40,420>/V<0,0,0>")
if be:FLGisOn(122) == 1 then
    if be:FLGisOn(123) ~= 1 then
        be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_POWERON")
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_POWERON")
    else
        be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
    end
end
be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_POWERON")
