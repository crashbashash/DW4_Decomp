g_act = 2
if not g_StgPos then
    g_StgPos = 0
elseif g_StgPos == 3 then
    g_StgPos = 0
else
    g_StgPos = g_StgPos + 1
end
if g_StgPos == 0 then
    be:sd("MODELCTRL", "f_devl1", 0, "MOVETRANS", "V<40.0,10.0,-40.0>/V<0.0,0.0,0.0>")
    be:sd("MODELCTRL", "f_devl1", 0, "SQ_SWARPOUT", 10)
elseif g_StgPos == 1 then
    be:sd("MODELCTRL", "f_devl1", 0, "MOVETRANS", "V<40.0,10.0,40.0>/V<0.0,0.0,0.0>")
    be:sd("MODELCTRL", "f_devl1", 0, "SQ_SWARPOUT", 10)
elseif g_StgPos == 2 then
    be:sd("MODELCTRL", "f_devl1", 0, "MOVETRANS", "V<-40.0,10.0,40.0>/V<0.0,0.0,0.0>")
    be:sd("MODELCTRL", "f_devl1", 0, "SQ_SWARPOUT", 10)
elseif g_StgPos == 3 then
    be:sd("MODELCTRL", "f_devl1", 0, "MOVETRANS", "V<-40.0,10.0,-40.0>/V<0.0,0.0,0.0>")
    be:sd("MODELCTRL", "f_devl1", 0, "SQ_SWARPOUT", 10)
end
