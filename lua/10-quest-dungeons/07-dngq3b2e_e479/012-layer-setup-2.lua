mswkNPC031 = "TALKFONT03/font00/I<0>"
funcPlayerStatusSet()
be:sd("SOUND", nil, -1, "PLAY", "AM_DUNGE")
be:sd("NDMWPANEL", nil, -1, "NOGATEDISK", "I<1>")
if be:FLGisOn(121) ~= 1 then
    be:sd("SOUND", nil, -1, "PLAY", "QS_THEME")
    be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 5)
    be:sd("PLAYER", nil, -1, "SQ_DEMOWALK", 15)
    be:sd("PLAYER", nil, -1, "SQ_WAIT", 60)
else
    be:sd("SOUND", nil, -1, "PLAY", "QS_HURRY")
    g_counter_min = floor(be:COUNTERget(0) / 60)
    g_counter_sec = be:COUNTERget(0) - 60 * g_counter_min
    be:sd("NUMBERCTRL", "timenm0", 0, "SETVALUE", "I<" .. g_counter_min .. ">")
    be:sd("NUMBERCTRL", "timenm1", 0, "SETVALUE", "I<" .. g_counter_sec .. ">")
    be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 5)
    be:sd("PLAYER", nil, -1, "SQ_DEMOWALK", 15)
    be:sd("PLAYER", nil, -1, "SQ_WAIT", 60)
    be:sd("MODELCTRL", "i_timenm0", 0, "GENERATE", "V<-290,217,0>/SQ_OPENDOWN", 60)
end
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
