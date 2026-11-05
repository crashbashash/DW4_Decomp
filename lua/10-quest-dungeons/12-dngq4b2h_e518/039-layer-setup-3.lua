mswkNPC028 = "TALKFONT03/font00/I<0>"
funcPlayerStatusSet()
be:sd("SOUND", nil, -1, "PLAY", "AM_DUNGE")
be:sd("NDMWPANEL", nil, -1, "NOHEALING", "I<1>")
be:sd("NDMWPANEL", nil, -1, "NOGATEDISK", "I<1>")
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
g_posTbl61 = {???, ???, ???, ???}
be:sd("SOUND", nil, -1, "PLAY", "QS_THEME")
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 5)
be:sd("PLAYER", nil, -1, "SQ_DEMOWALK", 15)
be:sd("PLAYER", nil, -1, "SQ_WAIT", 60)
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
