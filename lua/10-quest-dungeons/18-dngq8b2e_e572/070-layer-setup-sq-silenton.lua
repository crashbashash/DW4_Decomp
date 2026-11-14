local local_0
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<0.9,1.0,0.9>/V<1.0,0.9,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.18,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
be:sd("MODELCTRL", "g_d4door", 0, "GENERATE", "V<600,40,300>/V<0,0,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 1, "GENERATE", "V<740,40,-40>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 2, "GENERATE", "V<520,40,20>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 3, "GENERATE", "V<500,40,-40>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 4, "GENERATE", "V<580,40,160>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 5, "GENERATE", "V<180,65,-40>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 6, "GENERATE", "V<280,65,-140>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 7, "GENERATE", "V<160,40,260>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 8, "GENERATE", "V<-240,65,-60>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 9, "GENERATE", "V<-260,65,-200>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 10, "GENERATE", "V<-200,65,-260>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 11, "GENERATE", "V<-480,65,-140>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 12, "GENERATE", "V<-600,40,-140>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 13, "GENERATE", "V<-660,40,-80>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<600,40,280>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<680,40,220>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<700,40,200>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<720,40,180>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 3, "GENERATE", "V<700,40,160>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 4, "GENERATE", "V<680,40,140>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 5, "GENERATE", "V<700,40,120>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 6, "GENERATE", "V<720,40,100>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 7, "GENERATE", "V<700,40,80>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 8, "GENERATE", "V<680,40,60>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 9, "GENERATE", "V<700,40,40>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 10, "GENERATE", "V<720,40,20>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 11, "GENERATE", "V<420,40,160>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 12, "GENERATE", "V<400,40,140>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 13, "GENERATE", "V<380,40,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 14, "GENERATE", "V<360,40,140>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 15, "GENERATE", "V<340,40,160>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 16, "GENERATE", "V<320,40,140>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 17, "GENERATE", "V<300,40,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 18, "GENERATE", "V<280,40,140>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 19, "GENERATE", "V<260,40,160>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 20, "GENERATE", "V<240,40,140>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 21, "GENERATE", "V<220,40,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 22, "GENERATE", "V<-60,40,240>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 23, "GENERATE", "V<-80,40,260>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 24, "GENERATE", "V<-100,40,280>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 25, "GENERATE", "V<-120,40,260>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 26, "GENERATE", "V<-140,40,240>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 27, "GENERATE", "V<-160,40,260>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 28, "GENERATE", "V<-180,40,280>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 29, "GENERATE", "V<-200,40,260>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 30, "GENERATE", "V<-220,40,240>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 31, "GENERATE", "V<-240,40,260>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 32, "GENERATE", "V<-260,40,280>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 33, "GENERATE", "V<-480,40,-20>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 34, "GENERATE", "V<-500,40,0>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 35, "GENERATE", "V<-520,40,20>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 36, "GENERATE", "V<-500,40,40>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 37, "GENERATE", "V<-480,40,60>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 38, "GENERATE", "V<-500,40,80>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 39, "GENERATE", "V<-520,40,100>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 40, "GENERATE", "V<-500,40,120>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 41, "GENERATE", "V<-480,40,140>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 42, "GENERATE", "V<-500,40,160>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 43, "GENERATE", "V<-520,40,180>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 44, "GENERATE", "V<-680,40,-20>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 45, "GENERATE", "V<-660,40,0>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 46, "GENERATE", "V<-640,40,20>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 47, "GENERATE", "V<-660,40,40>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 48, "GENERATE", "V<-680,40,60>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 49, "GENERATE", "V<-660,40,80>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 50, "GENERATE", "V<-640,40,100>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 51, "GENERATE", "V<-660,40,120>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 52, "GENERATE", "V<-680,40,140>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 53, "GENERATE", "V<-660,40,160>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 54, "GENERATE", "V<-640,40,180>/V<0,-90,0>")
if be:FLGisOn(177) ~= 1 and be:FLGisOn(180) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<480,30,-80>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<480,30,-120>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<480,30,-160>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<480,30,-200>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<480,30,-240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<440,30,-240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<400,30,-240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<360,30,-240>/V<0,0,0>")
end
if be:FLGisOn(178) ~= 1 and be:FLGisOn(186) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<200,30,-240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<160,30,-240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<120,30,-240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 11, "GENERATE", "V<120,30,-280>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 12, "GENERATE", "V<120,30,-320>/V<0,0,0>")
end
if be:FLGisOn(179) ~= 1 and be:FLGisOn(186) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 13, "GENERATE", "V<280,30,-280>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 14, "GENERATE", "V<280,30,-320>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 15, "GENERATE", "V<280,30,-360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 16, "GENERATE", "V<280,30,-400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 17, "GENERATE", "V<240,30,-400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 18, "GENERATE", "V<200,30,-400>/V<0,0,0>")
end
if be:FLGisOn(177) ~= 1 then
    be:sd("MODELCTRL", "g_d4bkwall", 0, "GENERATE", "V<480,40,-55>/V<0,0,0>")
end
if be:FLGisOn(178) ~= 1 then
    be:sd("MODELCTRL", "g_d4bkwall", 1, "GENERATE", "V<225,40,-240>/V<0,90,0>/SQ_CUTRIGHT")
end
if be:FLGisOn(179) ~= 1 then
    be:sd("MODELCTRL", "g_d4bkwall", 2, "GENERATE", "V<280,40,-255>/V<0,0,0>")
end
if be:FLGisOn(180) ~= 1 then
    be:sd("MODELCTRL", "g_d4bkwall", 3, "GENERATE", "V<335,40,-240>/V<0,-90,0>/SQ_CUTLEFT")
end
if be:FLGisOn(181) ~= 1 then
    be:sd("MODELCTRL", "g_dscrap", 0, "GENERATE", "V<-160,40,160>/V<0,180,0>")
end
if be:FLGisOn(182) ~= 1 then
    be:sd("MODELCTRL", "g_dscrap", 1, "GENERATE", "V<-420,65,-200>/V<0,90,0>")
end
if be:FLGisOn(183) ~= 1 then
    be:sd("MODELCTRL", "g_dscrap", 2, "GENERATE", "V<-460,40,-80>/V<0,0,0>")
end
if be:FLGisOn(184) ~= 1 then
    be:sd("MODELCTRL", "g_dscrap", 3, "GENERATE", "V<-540,40,-80>/V<0,0,0>")
end
if be:FLGisOn(185) ~= 1 then
    be:sd("MODELCTRL", "g_dscrap", 4, "GENERATE", "V<-665,40,240>/V<0,90,0>")
end
if be:SYSgetDifficulty() == 0 then
    for i = 1, 12 do
        if be:FLGisOn(i + 163) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-E%02d", i))
        end
    end
end
if be:SYSgetDifficulty() == 1 then
    for i = 1, 12 do
        if be:FLGisOn(i + 163) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-H%02d", i))
        end
    end
end
if be:SYSgetDifficulty() == 2 then
    for i = 1, 12 do
        if be:FLGisOn(i + 163) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-V%02d", i))
        end
    end
end
be:MsgBox("G[FïÕxªzèOÅ·B")
if be:FLGisOn(147) == 1 then
    be:sd("MODELCTRL", "g_d4door", 2, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 3, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(149) == 1 then
    be:sd("MODELCTRL", "g_d4door", 4, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(151) == 1 then
    be:sd("MODELCTRL", "g_d4door", 5, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 6, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
end
if be:FLGisOn(153) == 1 then
    be:sd("MODELCTRL", "g_d4door", 7, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
end
if be:FLGisOn(157) == 1 then
    be:sd("MODELCTRL", "g_d4door", 8, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
end
if be:FLGisOn(158) == 1 then
    be:sd("MODELCTRL", "g_d4door", 10, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
end
if be:FLGisOn(160) == 1 then
    be:sd("MODELCTRL", "g_d4door", 11, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT")
end
if be:FLGisOn(161) == 1 then
    be:sd("MODELCTRL", "g_d4door", 12, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall13", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 13, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall14", 0, "OFFHIT")
end
if be:FLGisOn(176) == 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d4door", 0, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
end
be:sd("MODELCTRL", "g_d4door", 1, "SQ_SILENTON", 1)
be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
be:sd("MODELCTRL", "g_d4door", 9, "SQ_SILENTON", 1)
be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
g_matt02 = 0
g_matt03 = 0
g_matt06 = 0
g_matt07 = 0
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
