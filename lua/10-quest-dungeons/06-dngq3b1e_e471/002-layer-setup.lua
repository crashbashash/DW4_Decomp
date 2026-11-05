mswk61016 = "TALKFONT01/font00/I<0>"
mswk61061 = "TALKFONT01/font00/I<1>"
mswk61062 = "TALKFONT01/font00/I<2>"
mswk61063 = "TALKFONT01/font00/I<3>"
mswk61064 = "TALKFONT01/font00/I<4>"
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.0,1.1,1.05>/V<1.0,1.1,1.05>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.2,0.25,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
if be:COUNTERget(2) ~= local_1 then
    be:COUNTERset(2, local_1)
    for local_2 = 100, 299 do
        be:FLGset(local_2, 0)
    end
    g_intro = 1
end
if be:SYSgetDifficulty() == 0 then
    be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<100,40,720>/V<0,0,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 1, "GENERATE", "V<140,40,600>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 2, "GENERATE", "V<140,40,240>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 3, "GENERATE", "V<-20,40,20>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 4, "GENERATE", "V<20,40,-280>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 5, "GENERATE", "V<20,40,-480>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 6, "GENERATE", "V<-60,40,-640>/V<0,0,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 7, "GENERATE", "V<100,40,-760>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<160,40,40>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<-135,65,-20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<-100,40,-620>/V<0,0,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<140,40,-420>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<140,40,-400>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<140,40,-380>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 3, "GENERATE", "V<140,40,-360>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 4, "GENERATE", "V<140,40,-340>/V<0,-90,0>")
    if be:FLGisOn(119) ~= 1 then
        be:sd("MODELCTRL", "g_dcellwall", 0, "GENERATE", "V<140,40,280>/V<0,0,0>")
    end
    if be:FLGisOn(120) ~= 1 then
        be:sd("MODELCTRL", "g_dcellwall", 1, "GENERATE", "V<140,40,200>/V<0,0,0>")
    end
    if be:FLGisOn(114) == 1 then
        be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
        be:sd("MODELCTRL", "g_d3door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    else
        be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
    end
    if be:FLGisOn(115) == 1 then
        be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
        be:sd("MODELCTRL", "g_d3door", 3, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    else
        be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
    end
    if be:FLGisOn(116) == 1 then
        be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_SILENTON")
        if be:FLGisOn(141) ~= 1 then
            be:sd("MODELCTRL", "g_d3door", 6, "SQ_SILENTON", 1)
            be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
        else
        end
    end
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_POWERON")
    if be:FLGisOn(138) == 1 then
        if be:FLGisOn(101) == 1 then
            be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON", 1)
            be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
        end
    end
    be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    if be:FLGisOn(139) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    end
    if be:FLGisOn(140) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 5, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
    end
    if be:FLGisOn(100) == 1 then
        be:sd("MODELCTRL", "g_d3door", 1, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    end
    be:sd("MODELCTRL", "g_d3door", 7, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
elseif be:SYSgetDifficulty() == 1 then
    be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<100,40,720>/V<0,0,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 1, "GENERATE", "V<140,40,600>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 2, "GENERATE", "V<140,40,240>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 3, "GENERATE", "V<-20,40,20>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 4, "GENERATE", "V<20,40,-280>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 5, "GENERATE", "V<20,40,-480>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 6, "GENERATE", "V<-60,40,-640>/V<0,0,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 7, "GENERATE", "V<100,40,-760>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<160,40,40>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<-135,65,-20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<-100,40,-620>/V<0,0,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<140,40,-420>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<140,40,-400>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<140,40,-380>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 3, "GENERATE", "V<140,40,-360>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 4, "GENERATE", "V<140,40,-340>/V<0,-90,0>")
    if be:FLGisOn(119) ~= 1 then
        be:sd("MODELCTRL", "g_dcellwall", 0, "GENERATE", "V<140,40,280>/V<0,0,0>")
    end
    if be:FLGisOn(120) ~= 1 then
        be:sd("MODELCTRL", "g_dcellwall", 1, "GENERATE", "V<140,40,200>/V<0,0,0>")
    end
    if be:FLGisOn(114) == 1 then
        be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
        be:sd("MODELCTRL", "g_d3door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    else
        be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
    end
    if be:FLGisOn(115) == 1 then
        be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
        be:sd("MODELCTRL", "g_d3door", 3, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    else
        be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
    end
    if be:FLGisOn(116) == 1 then
        be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_SILENTON")
        if be:FLGisOn(141) ~= 1 then
            be:sd("MODELCTRL", "g_d3door", 6, "SQ_SILENTON", 1)
            be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
        else
        end
    end
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_POWERON")
    if be:FLGisOn(138) == 1 then
        if be:FLGisOn(101) == 1 then
            be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON", 1)
            be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
        end
    end
    be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    if be:FLGisOn(139) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    end
    if be:FLGisOn(140) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 5, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
    end
    if be:FLGisOn(100) == 1 then
        be:sd("MODELCTRL", "g_d3door", 1, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    end
    be:sd("MODELCTRL", "g_d3door", 7, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
elseif be:SYSgetDifficulty() == 2 then
    be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<100,40,720>/V<0,0,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 1, "GENERATE", "V<140,40,600>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 2, "GENERATE", "V<140,40,240>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 3, "GENERATE", "V<-20,40,20>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 4, "GENERATE", "V<20,40,-280>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 5, "GENERATE", "V<20,40,-480>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 6, "GENERATE", "V<-60,40,-640>/V<0,0,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 7, "GENERATE", "V<100,40,-760>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 8, "GENERATE", "V<140,40,315>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 9, "GENERATE", "V<140,40,365>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 10, "GENERATE", "V<200,40,-620>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<160,40,40>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<-135,65,-20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<-100,40,-620>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 3, "GENERATE", "V<180,40,340>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 4, "GENERATE", "V<100,40,-730>/V<0,0,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<140,40,-420>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<140,40,-400>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<140,40,-380>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 3, "GENERATE", "V<140,40,-360>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 4, "GENERATE", "V<140,40,-340>/V<0,-90,0>")
    if be:FLGisOn(119) ~= 1 then
        be:sd("MODELCTRL", "g_dcellwall", 0, "GENERATE", "V<140,40,280>/V<0,0,0>")
    end
    if be:FLGisOn(120) ~= 1 then
        be:sd("MODELCTRL", "g_dcellwall", 1, "GENERATE", "V<140,40,200>/V<0,0,0>")
    end
    if be:FLGisOn(114) == 1 then
        be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
        be:sd("MODELCTRL", "g_d3door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    else
        be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
    end
    if be:FLGisOn(115) == 1 then
        be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
        be:sd("MODELCTRL", "g_d3door", 3, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    else
        be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
    end
    if be:FLGisOn(116) == 1 then
        be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_SILENTON")
        if be:FLGisOn(141) ~= 1 then
            be:sd("MODELCTRL", "g_d3door", 6, "SQ_SILENTON", 1)
            be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
        else
        end
    end
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_POWERON")
    if be:FLGisOn(138) == 1 then
        if be:FLGisOn(101) == 1 then
            be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON", 1)
            be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
        end
    end
    be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    if be:FLGisOn(139) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    end
    if be:FLGisOn(140) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 5, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
    end
    if be:FLGisOn(100) == 1 then
        be:sd("MODELCTRL", "g_d3door", 1, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    end
    be:sd("MODELCTRL", "g_d3door", 7, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
    if be:FLGisOn(117) ~= 1 then
        if be:FLGisOn(121) ~= 1 then
            be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_SILENTON")
            be:sd("MODELCTRL", "g_d3door", 8, "SQ_SILENTON", 1)
            be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
            be:sd("MODELCTRL", "g_d3door", 9, "SQ_SILENTON", 1)
            be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
        else
            be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_POWERON")
        end
    end
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d3door", 8, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d3door", 9, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
else
end
if be:FLGisOn(118) == 1 then
    be:sd("MODELCTRL", "g_dbutton1", 4, "SQ_SILENTON")
else
    be:sd("MODELCTRL", "g_dbutton1", 4, "SQ_POWERON")
    be:sd("MODELCTRL", "g_d3door", 10, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
