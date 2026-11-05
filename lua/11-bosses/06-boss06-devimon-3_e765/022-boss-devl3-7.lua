if not g_FBSwitch then
    g_FBSwitch = 0
end
g_FBSwitch = 0
be:MDLsetSeq("SQ_BACKOFF")
be:sd("MODELCTRL", "f_devl3", 0, "MOVETRANS", be:MDLgetPosStr(0, 0, 0.3) .. "/" .. be:MDLgetRotStr(0, 0, 0))
