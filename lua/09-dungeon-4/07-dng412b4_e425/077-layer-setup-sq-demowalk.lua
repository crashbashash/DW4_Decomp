funcPlayerStatusSet()
be:sd("SOUND", nil, -1, "PLAY", "AM_DUNGE")
be:sd("SOUND", nil, -1, "PLAY", "DG_CAVE4")
if be:PLAYERgetPos() == 5 then
    funcStageIn("trans")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWALK", 15)
    be:sd("PLAYER", nil, -1, "SQ_WAIT", 60)
end
g_fall0 = 0
g_fall1 = 0
g_fall2 = 0
g_fall3 = 0
g_fallPos = 41
g_posTbl41 = {"V<-120,100,825>/V<0,90,0>", "V<-120,100,835>/V<0,90,0>", "V<-120,100,845>/V<0,90,0>", "V<-120,100,855>/V<0,90,0>"}
g_posTbl42 = {"V<-320,100,825>/V<0,-90,0>", "V<-320,100,835>/V<0,-90,0>", "V<-320,100,845>/V<0,-90,0>", "V<-320,100,855>/V<0,-90,0>"}
g_posTbl43 = {"V<-200,100,-345>/V<0,180,0>", "V<-200,100,-325>/V<0,180,0>", "V<-190,100,-335>/V<0,180,0>", "V<-210,100,-335>/V<0,180,0>"}
g_posTbl44 = {"V<-200,100,-575>/V<0,180,0>", "V<-200,100,-595>/V<0,180,0>", "V<-210,100,-585>/V<0,180,0>", "V<-190,100,-585>/V<0,180,0>"}
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 5)
