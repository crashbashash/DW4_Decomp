be:FLGset(409, 0)
be:FLGset(381, 0)
be:FLGset(424, 0)
be:sd("MODELCTRL", "g_cytrerp2", 0, "SQ_POWERON")
funcCloseMessage("talk", "n_digilfm", "fWt", 8, "noturn")
funcOpenMessage("talk", "n_digilfm", "fWt", 8)
mswk25087 = "TALKFONT02/font00/I<574>"
funcOneMessage(mswk25087)
mswk25088 = "TALKFONT02/font00/I<575>"
funcOneMessage(mswk25088)
funcCloseMessage("talk", "n_digilfm", "fWt", 8)
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
be:DMrun()
