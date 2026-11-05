funcPlayerStatusSet()
be:sd("SOUND", nil, -1, "PLAY", "DG_TOWER")
if be:PLAYERgetPos() == 3 then
    funcStageIn("trans")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWALK", 15)
    be:sd("PLAYER", nil, -1, "SQ_WAIT", 60)
end
g_fall0 = 0
g_fall1 = 0
g_fall2 = 0
g_fall3 = 0
g_fallPos = 11
g_posTbl11 = {???, ???, ???, ???}
g_posTbl12 = {???, ???, ???, ???}
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 5)
