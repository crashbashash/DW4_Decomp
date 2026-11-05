funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.2,1.15,1.2>/V<1.2,1.15,1.2>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.2,0.35>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT", 1)
be:sd("MODELCTRL", "g_numepodz01", 0, "GENERATE", "V<65,21,335>/V<0,0,0>")
be:sd("MODELCTRL", "g_numepodz01", 1, "GENERATE", "V<-225,21,275>/V<0,0,0>")
be:sd("MODELCTRL", "g_numepodz01", 2, "GENERATE", "V<-265,21,215>/V<0,0,0>")
be:sd("MODELCTRL", "g_numeprisonz01", 0, "GENERATE", "V<60,15,415>/V<0,180,0>")
be:sd("MODELCTRL", "g_numeprisonz01", 1, "GENERATE", "V<-125,15,200>/V<0,-45,0>")
be:sd("MODELCTRL", "g_numeprisonz01", 2, "GENERATE", "V<-130,15,320>/V<0,135,0>")
be:sd("MODELCTRL", "r_boatz01", 0, "GENERATE", "V<0.0,0.0,0.0>/V<0,0,0>")
be:sd("MODELCTRL", "g_boatz01", 0, "GENERATE", "V<585.0,15.0,395.0>/V<0,-90,0>")
be:sd("MODELCTRL", "i_digilfbase", 0, "GENERATE", "V<-275,188,0>/V<0,0,0>")
be:sd("MODELCTRL", "i_digilfcount", 0, "GENERATE", "V<-270,174,0>/V<0,0,0>")
be:sd("MODELCTRL", "i_digilfcount", 1, "GENERATE", "V<-280,149,0>/V<0,0,0>")
be:sd("MODELCTRL", "i_digilfcount", 2, "GENERATE", "V<-270,124,0>/V<0,0,0>")
be:sd("MODELCTRL", "i_digilfcount", 3, "GENERATE", "V<-280,99,0>/V<0,0,0>")
be:sd("MODELCTRL", "i_digilfcount", 4, "GENERATE", "V<-270,74,0>/V<0,0,0>")
be:sd("MODELCTRL", "i_digilfcount", 5, "GENERATE", "V<-280,49,0>/V<0,0,0>")
be:sd("MODELCTRL", "i_digilfcount", 6, "GENERATE", "V<-270,24,0>/V<0,0,0>")
be:sd("MODELCTRL", "i_digilfcount", 7, "GENERATE", "V<-280,-1,0>/V<0,0,0>")
be:sd("MODELCTRL", "i_digilfcount", 8, "GENERATE", "V<-270,-26,0>/V<0,0,0>")
be:sd("MODELCTRL", "i_digilfcount", 9, "GENERATE", "V<-280,-51,0>/V<0,0,0>")
if be:FLGisOn(89) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 0, "GENERATE", "V<60,15,413.5>/V<0,180,0>")
    be:sd("MODELCTRL", "n_digilfm", 0, "SQ_HELP")
else
end
if be:FLGisOn(90) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 1, "GENERATE", "V<-126.061,15,201.061>/V<0,-45,0>")
    be:sd("MODELCTRL", "n_digilfm", 1, "SQ_HELP")
else
end
if be:FLGisOn(91) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 2, "GENERATE", "V<-128.939,15,318.939>/V<0,135,0>")
    be:sd("MODELCTRL", "n_digilfm", 2, "SQ_HELP")
else
end
if be:FLGisOn(92) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 3, "GENERATE", "V<-568.939,15,318.939>/V<0,135,0>")
    be:sd("MODELCTRL", "n_digilfm", 3, "SQ_HELP")
else
end
if be:FLGisOn(93) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 4, "GENERATE", "V<-471.061,15,-256.061>/V<0,-135,0>")
    be:sd("MODELCTRL", "n_digilfm", 4, "SQ_HELP")
else
end
if be:FLGisOn(94) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 5, "GENERATE", "V<-96.061,15,-348.939>/V<0,-45,0>")
    be:sd("MODELCTRL", "n_digilfm", 5, "SQ_HELP")
else
end
if be:FLGisOn(95) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 6, "GENERATE", "V<-83.5,15,-210>/V<0,90,0>")
    be:sd("MODELCTRL", "n_digilfm", 6, "SQ_HELP")
else
end
if be:FLGisOn(96) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 7, "GENERATE", "V<18.939,15,-208.939>/V<0,-45,0>")
    be:sd("MODELCTRL", "n_digilfm", 7, "SQ_HELP")
else
end
if be:FLGisOn(97) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 8, "GENERATE", "V<-88.5,15,-125>/V<0,90,0>")
    be:sd("MODELCTRL", "n_digilfm", 8, "SQ_HELP")
else
end
if be:FLGisOn(98) == 0 then
    be:sd("MODELCTRL", "n_digilfm", 9, "GENERATE", "V<-48.939,15,-86.061>/V<0,135,0>")
    be:sd("MODELCTRL", "n_digilfm", 9, "SQ_HELP")
else
end
be:sd("MODELCTRL", "i_stpnlsp04", 0, "GENERATE", "V<-296,225,0>")
be:sd("MODELCTRL", "i_stpnlsp05", 0, "GENERATE", "V<-296,225,0>")
be:sd("SOUND", nil, -1, "PLAY", "AM_VALLE")
be:sd("SOUND", nil, -1, "PLAY", "AM_RIVER")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
be:sd("MODELCTRL", "i_stpnl00", 0, "GENERATE")
for local_1 = 0, 3 do
    if be:SYSisJoinPlayer(local_1) == 1 then
        if local_1 == 0 then
            be:sd("MODELCTRL", "i_stpnlsp01", 0, "GENERATE", "V<-260,-160,0>")
            be:sd("MODELCTRL", "i_stpnl02", 0, "GENERATE", "V<-260,-160,0>")
            be:sd("MODELCTRL", "i_stpnlsp02", 0, "GENERATE", "V<-260,-160,0>")
            be:sd("MODELCTRL", "i_stpnlsp03", 0, "GENERATE", "V<-260,-160,0>")
            be:sd("MODELCTRL", "i_stpnl05", 0, "GENERATE", "V<-260,-160,0>")
        elseif local_1 == 1 then
            be:sd("MODELCTRL", "i_stpnlsp01", 1, "GENERATE", "V<-110,-160,0>")
            be:sd("MODELCTRL", "i_stpnl02", 1, "GENERATE", "V<-110,-160,0>")
            be:sd("MODELCTRL", "i_stpnlsp02", 1, "GENERATE", "V<-110,-160,0>")
            be:sd("MODELCTRL", "i_stpnlsp03", 1, "GENERATE", "V<-110,-160,0>")
            be:sd("MODELCTRL", "i_stpnl05", 1, "GENERATE", "V<-110,-160,0>")
        elseif local_1 == 2 then
            be:sd("MODELCTRL", "i_stpnlsp01", 2, "GENERATE", "V<40,-160,0>")
            be:sd("MODELCTRL", "i_stpnl02", 2, "GENERATE", "V<40,-160,0>")
            be:sd("MODELCTRL", "i_stpnlsp02", 2, "GENERATE", "V<40,-160,0>")
            be:sd("MODELCTRL", "i_stpnlsp03", 2, "GENERATE", "V<40,-160,0>")
            be:sd("MODELCTRL", "i_stpnl05", 2, "GENERATE", "V<40,-160,0>")
        elseif local_1 == 3 then
            be:sd("MODELCTRL", "i_stpnlsp01", 3, "GENERATE", "V<190,-160,0>")
            be:sd("MODELCTRL", "i_stpnl02", 3, "GENERATE", "V<190,-160,0>")
            be:sd("MODELCTRL", "i_stpnlsp02", 3, "GENERATE", "V<190,-160,0>")
            be:sd("MODELCTRL", "i_stpnlsp03", 3, "GENERATE", "V<190,-160,0>")
            be:sd("MODELCTRL", "i_stpnl05", 3, "GENERATE", "V<190,-160,0>")
        end
    end
end
