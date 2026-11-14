local local_0
funcPlayerStatusSet()
be:sd("SOUND", nil, -1, "PLAY", "AM_DUNGE")
be:sd("SOUND", nil, -1, "PLAY", "DG_CAVE2")
g_matRideS0 = 0
g_matRideS1 = 0
g_matRideS2 = 0
g_matRideS3 = 0
g_matRideM0 = 0
g_matRideM1 = 0
g_matRideM2 = 0
g_matRideM3 = 0
g_matRideL0 = 0
g_matRideL1 = 0
g_matRideL2 = 0
g_matRideL3 = 0
g_fall0 = 0
g_fall1 = 0
g_fall2 = 0
g_fall3 = 0
g_fallPos = 51
g_posTbl51 = {"V<-225,35,-195>/V<0,0,0>", "V<-215,35,-195>/V<0,0,0>", "V<-225,35,-205>/V<0,0,0>", "V<-215,35,-205>/V<0,0,0>"}
g_posTbl52 = {"V<105,35,-195>/V<0,0,0>", "V<95,35,-195>/V<0,0,0>", "V<105,35,-205>/V<0,0,0>", "V<95,35,-205>/V<0,0,0>"}
g_posTbl53 = {"V<-105,15,685>/V<0,0,0>", "V<-105,15,675>/V<0,0,0>", "V<-115,10,685>/V<0,0,0>", "V<-115,10,675>/V<0,0,0>"}
if be:PLAYERgetPos() == 1 then
    funcStageIn("trans")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWALK", 15)
    be:sd("PLAYER", nil, -1, "SQ_WAIT", 60)
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 then
            be:sd("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "SETMETAL", 60)
        end
    end
end
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 5)
