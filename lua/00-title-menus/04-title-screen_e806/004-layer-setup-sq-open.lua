be:DMsetSD("SOUND", nil, -1, "BGMSTOP")
be:DMsetSD("SOUND", nil, -1, "ENVSTOP")
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLIN30")
be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "entry")
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
be:DMsetSD("SOUND", nil, -1, "PLAYatPAUSE", "ST_CHARA")
be:DMsetSD("SOUND", nil, -1, "PAUSEOFF", "ST_CHARA", 240)
if be:SYSgetArea() == 0 then
    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_TITLE")
else
    be:DMsetSD("SOUND", nil, -1, "PLAY", "AM_TITLE2")
end
be:DMsetSD("MODELCTRL", "j_startback", 0, "GENERATE", "SQ_OPEN")
be:DMchkSD("MODELCTRL", "j_startback", 0, "ISSEQNAME", "SQ_OPEN", "==0")
be:DMchkSD("MODELCTRL", "j_startback", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
if be:SYSgetArea() == 0 then
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_WTIN60")
end
be:DMsetSD("TITLE2", nil, 0, "RUN")
be:DMrun()
funcFirstLayerSet()
be:sd("SWITCHCTRL", nil, -1, "ALLON")
be:sd("STAGECTL", nil, -1, "PADINPUT", "ENABLE", 30)
