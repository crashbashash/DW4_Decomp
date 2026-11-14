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
g_posTbl11 = {"V<-15,100,205>/V<0,180,0>", "V<-5,100,205>/V<0,180,0>", "V<5,100,205>/V<0,180,0>", "V<15,100,205>/V<0,180,0>"}
g_posTbl12 = {"V<-15,100,35>/V<0,180,0>", "V<-5,100,35>/V<0,180,0>", "V<5,100,35>/V<0,180,0>", "V<15,100,35>/V<0,180,0>"}
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 5)
