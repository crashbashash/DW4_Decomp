if not g_arm then
    g_arm = 1
end
if not g_DRILLchk then
    g_DRILLchk = 0
end
if g_arm == 1 and be:MDLisLive("f_devl24", 0) == 0 and be:MDLisLive("f_devl24", 1) == 0 then
    g_arm = 0
    be:sd("MODELCTRL", "f_devl23", 0, "SQ_CHANGE")
    g_DRILLchk = 0
    be:sd("MODELCTRL", "f_devl24", 0, "GENERATE", "V<50.0,40.0,0.0>/V<0.0,-90.0,0.0>/SQ_ENTR", 0)
    be:sd("MODELCTRL", "f_devl24", 1, "GENERATE", "V<-50.0,40.0,0.0>/V<0.0,90.0,0.0>/SQ_ENTR", 0)
end
