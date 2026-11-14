if 1 == 1 then
    be:sd("MODELCTRL", "n_recorder", 0, "GENERATE", "SQ_SETREO/V<541.655,50,75>/V<0,45,0>")
end
if 1 == 1 then
    be:sd("MODELCTRL", "n_recorder", 1, "GENERATE", "SQ_SETREO/V<-675,50,-305>/V<0,90,0>")
end
if be:FLGisOn(376) == 1 then
    be:sd("MODELCTRL", "n_recorder", 2, "GENERATE", "SQ_SETAGM/V<-55,20,265>/V<0,180,0>")
elseif be:FLGisOn(379) == 1 then
    be:sd("MODELCTRL", "n_recorder", 2, "GENERATE", "SQ_SETVEE/V<-145,40,-105>/V<0,0,0>")
end
