mswkNPC001 = "TALKFONT03/font00/I<9>"
mswkNPC027 = "TALKFONT03/font00/I<10>"
mswkNPC028 = "TALKFONT03/font00/I<11>"
mswkNPC029 = "TALKFONT03/font00/I<12>"
mswkNPC030 = "TALKFONT03/font00/I<13>"
mswkNPC031 = "TALKFONT03/font00/I<14>"
mswkNPC032 = "TALKFONT03/font00/I<15>"
mswkNPC033 = "TALKFONT03/font00/I<16>"
funcPlayerStatusSet()
be:sd("SOUND", nil, -1, "PLAY", "AM_DUNGE")
be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "entry")
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 5)
be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWALK", 15)
be:DMsetSD("PLAYER", nil, -1, "SQ_DEMOWAIT", 60)
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
be:DMsetSD("MODELCTRL", "i_messwn", 0, "GENERATE", "SQ_OPEN")
be:DMsetSD("TEXTCTL", nil, -1, "ALIGN", "TALKFONT01/font00/CENTER")
g_talk = "mess"
g_page = 0
g_messPlayerNo = 0
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "==0")
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_OPEN", "==0")
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
if g_intro == 1 then
    funcOneMessage(mswk61754)
else
    funcOneMessage(mswk61755)
end
be:DMsetSD("MODELCTRL", "i_messwn", 0, "SQ_CLOSE")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 10)
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 10)
be:DMchkSD("MODELCTRL", "i_messwn", 0, "ISRUN", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "startctrl")
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
be:DMsetSD("PLAYER", nil, -1, "SQ_WAIT")
be:DMrun()
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
