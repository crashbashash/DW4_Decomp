if be:FLGisOn(333) == 0 then
    be:sd("MODELCTRL", "n_gekoa", 0, "GENERATE", "V<-570,50,-390>/V<0,90,0>")
elseif be:FLGisOn(333) == 1 then
    be:sd("MODELCTRL", "n_gekoa", 0, "GENERATE", "V<-570,50,-410>/V<0,0,0>")
end
