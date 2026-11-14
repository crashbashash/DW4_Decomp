funcPlayerStatusSet()
be:sd("SOUND", nil, -1, "PLAY", "DG_TOWER")
be:sd("PLAYER", nil, -1, "SQ_DEMOWALK", 15)
be:sd("PLAYER", nil, -1, "SQ_WAIT", 60)
g_fall0 = 0
g_fall1 = 0
g_fall2 = 0
g_fall3 = 0
g_fallPos = 35
g_posTbl35 = {"V<-130,100,520>/V<0,-90,0>", "V<-150,100,520>/V<0,-90,0>", "V<-140,100,530>/V<0,-90,0>", "V<-140,100,510>/V<0,-90,0>"}
g_posTbl36 = {"V<135,100,480>/V<0,90,0>", "V<155,100,480>/V<0,90,0>", "V<145,100,490>/V<0,90,0>", "V<145,100,470>/V<0,90,0>"}
g_posTbl37 = {"V<-15,100,-150>/V<0,0,0>", "V<-5,100,-150>/V<0,0,0>", "V<5,100,-150>/V<0,0,0>", "V<15,100,-150>/V<0,0,0>"}
g_posTbl38 = {"V<-15,100,120>/V<0,0,0>", "V<-5,100,120>/V<0,0,0>", "V<5,100,120>/V<0,0,0>", "V<15,100,120>/V<0,0,0>"}
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 5)
