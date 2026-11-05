if not g_arm then
    g_arm = 1
end
if not g_DRILLchk then
    g_DRILLchk = 0
end
if local_0 == 0 and g_arm == 0 and be:MDLisLive("f_devl24", 0) == 1 and be:MDLisLive("f_devl24", 1) == 1 then
    if g_DRILLchk >= 1 then
        be:sd("MODELCTRL", "f_devl24", 0, "SQ_EXIT")
        be:sd("MODELCTRL", "f_devl24", 1, "SQ_EXIT")
        g_arm = 1
        be:sd("MODELCTRL", "f_devl23", 0, "SQ_ENTR")
    else
        g_DRILLchk = g_DRILLchk + 1
        be:sd("MODELCTRL", "f_devl24", 0, "SQ_SWON", 0)
        be:sd("MODELCTRL", "f_devl24", 1, "SQ_SWON", 0)
    end
end
