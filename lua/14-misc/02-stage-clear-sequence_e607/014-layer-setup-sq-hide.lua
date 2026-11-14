funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.2,1.15,1.2>/V<1.2,1.15,1.2>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.2,0.35>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
be:sd("MATCTRL", nil, -1, "PAUSE")
funcPlayerSet()
if be:PLAYERgetPos() == 0 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
elseif be:PLAYERgetPos() == 3 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
end
be:sd("MODELCTRL", "g_cytelep1", 0, "GENERATE", "V<0,10,165>/V<0,0,0>/SQ_POWERON")
be:sd("MODELCTRL", "g_hideliftz00", 0, "GENERATE", "V<0,10,105>/V<0,90,0>")
be:sd("SOUND", nil, -1, "PLAY", "ST_COMMA")
be:sd("SOUND", nil, -1, "PLAY", "AM_LOBBY")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
