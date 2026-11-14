local local_0
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<0.9,1.0,0.9>/V<1.0,0.9,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.18,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
if be:PLAYERgetPos() == 2 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
end
be:sd("MODELCTRL", "g_d4door", 0, "GENERATE", "V<-460,40,-400>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 1, "GENERATE", "V<360,65,-540>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d4door", 2, "GENERATE", "V<260,65,-440>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 3, "GENERATE", "V<500,40,-360>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 4, "GENERATE", "V<440,40,-300>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 5, "GENERATE", "V<0,40,-380>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 6, "GENERATE", "V<-240,65,20>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 7, "GENERATE", "V<-140,65,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 8, "GENERATE", "V<0,40,220>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 9, "GENERATE", "V<200,40,180>/V<0,90,0>")
be:sd("MODELCTRL", "g_d4door", 10, "GENERATE", "V<140,40,280>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 11, "GENERATE", "V<560,65,420>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d4door", 12, "GENERATE", "V<580,40,760>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-500,40,-380>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<-420,40,-380>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<-500,40,-300>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 3, "GENERATE", "V<-420,40,-300>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 4, "GENERATE", "V<655,40,635>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 5, "GENERATE", "V<545,40,685>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<-140,40,-580>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<-140,40,-500>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<-20,40,-580>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 3, "GENERATE", "V<-20,40,-500>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 4, "GENERATE", "V<540,40,630>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 5, "GENERATE", "V<610,40,630>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 6, "GENERATE", "V<610,40,650>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 7, "GENERATE", "V<590,40,670>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 8, "GENERATE", "V<590,40,690>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 9, "GENERATE", "V<660,40,690>/V<0,-90,0>")
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<260,65,-540>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 0, "GENERATE", "V<-125,40,-585>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 1, "GENERATE", "V<-125,40,-520>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 2, "GENERATE", "V<-80,40,-570>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 3, "GENERATE", "V<-80,40,-520>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 4, "GENERATE", "V<-35,40,-585>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 5, "GENERATE", "V<-35,40,-520>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbarrierp", 6, "GENERATE", "V<-225,40,720>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 7, "GENERATE", "V<-135,40,720>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbarrierp", 8, "GENERATE", "V<585,40,615>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 9, "GENERATE", "V<665,40,615>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbarrierp", 10, "GENERATE", "V<535,40,705>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierp", 11, "GENERATE", "V<615,40,705>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbarrierw2", 0, "GENERATE", "V<-80,40,-556>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierw2", 1, "GENERATE", "V<-211,40,720>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw2", 2, "GENERATE", "V<599,40,615>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw2", 3, "GENERATE", "V<549,40,705>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw1", 0, "GENERATE", "V<-180,40,720>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw3", 0, "GENERATE", "V<-80,40,-534>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierw3", 1, "GENERATE", "V<-149,40,720>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw3", 2, "GENERATE", "V<651,40,615>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw3", 3, "GENERATE", "V<601,40,705>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw4", 0, "GENERATE", "V<625,40,615>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw4", 1, "GENERATE", "V<575,40,705>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbarrierw7", 0, "GENERATE", "V<-125,40,-552.5>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbarrierw7", 1, "GENERATE", "V<-35,40,-552.5>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dtrailmon", 0, "GENERATE", "V<-150,0,350>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtrailmon", 1, "GENERATE", "V<-150,0,350>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtrailmon", 2, "GENERATE", "V<-150,0,350>/V<0,0,0>")
be:sd("MODELCTRL", "g_dtrailmon", 3, "GENERATE", "V<-150,0,350>/V<0,0,0>")
be:sd("MODELCTRL", "r_drail01", 0, "GENERATE", "V<-494.96,0,-340>/V<0,0,0>")
be:sd("MODELCTRL", "r_drail01", 1, "GENERATE", "V<-705,0,-700>/V<0,0,0>")
be:sd("MODELCTRL", "r_drail01", 2, "GENERATE", "V<-20.29,0,-140>/V<0,0,0>")
be:sd("MODELCTRL", "r_drail01", 3, "GENERATE", "V<-545,0,580>/V<0,0,0>")
if be:FLGisOn(160) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<-740,30,-860>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<-700,30,-860>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<-660,30,-860>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<-740,30,-820>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<-700,30,-820>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<-660,30,-820>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<-700,30,-780>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<-740,30,-740>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<-700,30,-740>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<-660,30,-740>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<-780,30,-700>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 11, "GENERATE", "V<-740,30,-700>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 12, "GENERATE", "V<-700,30,-700>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 13, "GENERATE", "V<-660,30,-700>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 14, "GENERATE", "V<-620,30,-700>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 15, "GENERATE", "V<-740,30,-660>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 16, "GENERATE", "V<-700,30,-660>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 17, "GENERATE", "V<-660,30,-660>/V<0,0,0>")
end
if be:FLGisOn(161) ~= 1 and be:FLGisOn(152) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 18, "GENERATE", "V<620,30,-300>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 19, "GENERATE", "V<660,30,-300>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 20, "GENERATE", "V<700,30,-300>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 21, "GENERATE", "V<620,30,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 22, "GENERATE", "V<660,30,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 23, "GENERATE", "V<700,30,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 24, "GENERATE", "V<660,30,-220>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 25, "GENERATE", "V<620,30,-180>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 26, "GENERATE", "V<660,30,-180>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 27, "GENERATE", "V<700,30,-180>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 28, "GENERATE", "V<580,30,-140>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 29, "GENERATE", "V<620,30,-140>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 30, "GENERATE", "V<660,30,-140>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 31, "GENERATE", "V<700,30,-140>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 32, "GENERATE", "V<740,30,-140>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 33, "GENERATE", "V<620,30,-100>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 34, "GENERATE", "V<660,30,-100>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 35, "GENERATE", "V<700,30,-100>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 36, "GENERATE", "V<660,30,-60>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 37, "GENERATE", "V<660,30,-20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 38, "GENERATE", "V<260,30,20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 39, "GENERATE", "V<300,30,20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 40, "GENERATE", "V<340,30,20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 41, "GENERATE", "V<380,30,20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 42, "GENERATE", "V<420,30,20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 43, "GENERATE", "V<460,30,20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 44, "GENERATE", "V<500,30,20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 45, "GENERATE", "V<540,30,20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 46, "GENERATE", "V<580,30,20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 47, "GENERATE", "V<620,30,20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 48, "GENERATE", "V<660,30,20>/V<0,0,0>")
end
if be:FLGisOn(162) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 49, "GENERATE", "V<-580,30,420>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 50, "GENERATE", "V<-540,30,420>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 51, "GENERATE", "V<-500,30,420>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 52, "GENERATE", "V<-580,30,460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 53, "GENERATE", "V<-540,30,460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 54, "GENERATE", "V<-500,30,460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 55, "GENERATE", "V<-540,30,500>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 56, "GENERATE", "V<-580,30,540>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 57, "GENERATE", "V<-540,30,540>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 58, "GENERATE", "V<-500,30,540>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 59, "GENERATE", "V<-620,30,580>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 60, "GENERATE", "V<-580,30,580>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 61, "GENERATE", "V<-540,30,580>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 62, "GENERATE", "V<-500,30,580>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 63, "GENERATE", "V<-460,30,580>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 64, "GENERATE", "V<-580,30,620>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 65, "GENERATE", "V<-540,30,620>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 66, "GENERATE", "V<-500,30,620>/V<0,0,0>")
end
if be:FLGisOn(153) ~= 1 and be:FLGisOn(155) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 67, "GENERATE", "V<-180,30,620>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 68, "GENERATE", "V<-180,30,660>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 69, "GENERATE", "V<-220,30,700>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 70, "GENERATE", "V<-180,30,700>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 71, "GENERATE", "V<-140,30,700>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 72, "GENERATE", "V<-220,30,740>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 73, "GENERATE", "V<-180,30,740>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 74, "GENERATE", "V<-140,30,740>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 75, "GENERATE", "V<-100,30,740>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 76, "GENERATE", "V<-60,30,740>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 77, "GENERATE", "V<-20,30,740>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 78, "GENERATE", "V<20,30,740>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 79, "GENERATE", "V<20,30,780>/V<0,0,0>")
end
if be:FLGisOn(154) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 80, "GENERATE", "V<220,30,500>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 81, "GENERATE", "V<220,30,540>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 82, "GENERATE", "V<180,30,580>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 83, "GENERATE", "V<220,30,580>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 84, "GENERATE", "V<260,30,580>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 85, "GENERATE", "V<180,30,620>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 86, "GENERATE", "V<220,30,620>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 87, "GENERATE", "V<260,30,620>/V<0,0,0>")
end
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<220,40,-105>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<-300,40,615>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 2, "GENERATE", "V<620,65,420>/V<0,0,0>")
for ramNo = 1, 20 do
    if be:FLGisOn(ramNo + 125) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", ramNo))
    end
end
if be:FLGisOn(152) ~= 1 then
    be:sd("MODELCTRL", "g_d4bkwall", 0, "GENERATE", "V<235,40,20>/V<0,-90,0>")
end
if be:FLGisOn(153) ~= 1 then
    be:sd("MODELCTRL", "g_d4bkwall", 1, "GENERATE", "V<-180,40,595>/V<0,180,0>")
end
if be:FLGisOn(154) ~= 1 then
    be:sd("MODELCTRL", "g_d4bkwall", 2, "GENERATE", "V<220,40,475>/V<0,180,0>")
end
if be:FLGisOn(155) ~= 1 then
    be:sd("MODELCTRL", "g_d4bkwall", 3, "GENERATE", "V<20,40,805>/V<0,0,0>")
end
if be:FLGisOn(156) ~= 1 then
    be:sd("MODELCTRL", "g_dscrap", 0, "GENERATE", "V<500,40,-540>/V<0,0,0>")
end
if be:FLGisOn(157) ~= 1 then
    be:sd("MODELCTRL", "g_dscrap", 1, "GENERATE", "V<-60,40,-280>/V<0,90,0>")
end
if be:FLGisOn(158) ~= 1 then
    be:sd("MODELCTRL", "g_dscrap", 2, "GENERATE", "V<-300,40,520>/V<0,180,0>")
end
if be:FLGisOn(159) ~= 1 then
    be:sd("MODELCTRL", "g_dscrap", 3, "GENERATE", "V<220,40,560>/V<0,180,0>")
end
be:sd("MODELCTRL", "g_d4door", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 2, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 3, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 4, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 5, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 6, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 7, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 8, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 9, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 10, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 11, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 12, "SQ_BUTTON")
if be:FLGisOn(146) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
end
if be:FLGisOn(147) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
end
if be:FLGisOn(148) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_SILENTON")
end
if be:FLGisOn(149) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_SILENTON")
end
if be:FLGisOn(146) + be:FLGisOn(147) + be:FLGisOn(148) + be:FLGisOn(149) == 4 then
    be:sd("MODELCTRL", "g_d4door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(150) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 4, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 4, "SQ_SILENTON")
end
if be:FLGisOn(151) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 5, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 5, "SQ_SILENTON")
end
if be:FLGisOn(150) + be:FLGisOn(151) == 2 then
    be:sd("MODELCTRL", "g_d4door", 12, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall13", 0, "OFFHIT")
end
if be:FLGisOn(103) == 1 then
    be:sd("MODELCTRL", "g_d4door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
    g_security = 1
end
if be:FLGisOn(106) == 1 then
    be:sd("MODELCTRL", "g_d4door", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(110) == 1 then
    be:sd("MODELCTRL", "g_d4door", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
if be:FLGisOn(114) == 1 then
    be:sd("MODELCTRL", "g_d4door", 6, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 7, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
end
if be:FLGisOn(118) == 1 then
    be:sd("MODELCTRL", "g_d4door", 8, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 10, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
end
if be:FLGisOn(122) == 1 then
    be:sd("MODELCTRL", "g_d4door", 11, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT")
end
be:sd("MODELCTRL", "g_dbarrierw1", 0, "SQ_POWERON")
for ramNo = 0, 3 do
    be:sd("MODELCTRL", "g_dbarrierw2", ramNo, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw3", ramNo, "SQ_POWERON")
end
for ramNo = 0, 1 do
    be:sd("MODELCTRL", "g_dbarrierw4", ramNo, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbarrierw7", ramNo, "SQ_POWERON")
end
for ramNo = 0, 11 do
    be:sd("MODELCTRL", "g_dbarrierp", ramNo, "SQ_POWERON")
end
be:sd("MODELCTRL", "g_d4door", 3, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
be:sd("MODELCTRL", "g_d4door", 4, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
be:sd("MODELCTRL", "g_d4door", 8, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
be:sd("MODELCTRL", "g_d4door", 9, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(293) == 1 then
    if be:MDLisLive("j_map412b3", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map412b3", 0, "GENERATE", "SQ_OPEN")
    end
    local local_1
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 and be:MDLisLive("j_mapcur", playerIndex) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", playerIndex, "GENERATE")
        end
    end
end
be:sd("MODELCTRL", "g_dtrailmon", 0, "SQ_HIDE")
be:sd("MODELCTRL", "g_dtrailmon", 1, "SQ_HIDE")
be:sd("MODELCTRL", "g_dtrailmon", 2, "SQ_HIDE")
be:sd("MODELCTRL", "g_dtrailmon", 3, "SQ_HIDE")
