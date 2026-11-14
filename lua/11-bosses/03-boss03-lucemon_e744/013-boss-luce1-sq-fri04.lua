if be:MDLisCallName("bom1") == 1 then
    be:sd("MODELCTRL", "f_luce1", 0, "MOVETRANS", "V<0.0,10.0,30.0>/V<0.0,0.0,0.0>")
    be:sd("MODELCTRL", "f_luce1", 0, "SQ_FRI04")
elseif be:MDLisCallName("bom2") == 1 then
    be:sd("MODELCTRL", "f_luce1", 0, "MOVETRANS", "V<0.0,10.0,0.0>/V<0.0,0,0.0>")
    be:sd("MODELCTRL", "f_luce1", 0, "SQ_FRI04")
elseif be:MDLisCallName("bom3") == 1 then
    be:sd("MODELCTRL", "f_luce1", 0, "MOVETRANS", "V<0.0,10.0,-30.0>/V<0.0,0,0.0>")
    be:sd("MODELCTRL", "f_luce1", 0, "SQ_FRI04")
elseif be:MDLisCallName("bom4") == 1 then
    be:sd("MODELCTRL", "f_luce1", 0, "MOVETRANS", "V<-30.0,10.0,0.0>/V<0.0,0.0,0.0>")
    be:sd("MODELCTRL", "f_luce1", 0, "SQ_FRI03")
elseif be:MDLisCallName("bom5") == 1 then
    be:sd("MODELCTRL", "f_luce1", 0, "MOVETRANS", "V<0.0,10.0,0.0>/V<0.0,0.0,0.0>")
    be:sd("MODELCTRL", "f_luce1", 0, "SQ_FRI03")
elseif be:MDLisCallName("bom6") == 1 then
    be:sd("MODELCTRL", "f_luce1", 0, "MOVETRANS", "V<30.0,10.0,0.0>/V<0.0,0.0,0.0>")
    be:sd("MODELCTRL", "f_luce1", 0, "SQ_FRI03")
end
