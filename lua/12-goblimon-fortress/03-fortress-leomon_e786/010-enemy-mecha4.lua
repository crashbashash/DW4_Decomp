if be:FLGisOn(20) == 0 and be:FLGisOn(383) == 0 and g_IFLG00 ~= 1 and be:MATisAllPlayer() == 1 and be:DMgetCount() == 0 then
    g_messPlayerNo = 0
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
    be:DMsetSD("NDMWPANEL", nil, -1, "NOGATEDISK", "I<1>")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:DMsetSD("PLAYER", nil, -1, "SQ_WAIT")
    be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "MRogue1", 30)
    be:DMsetSD("MODELCTRL", "g_energyfieldz05", 0, "SQ_SWON", 100)
    be:DMchkSD("MODELCTRL", "g_energyfieldz05", 0, "ISSEQNAME", "SQ_SWON", "==0")
    be:DMchkSD("MODELCTRL", "g_energyfieldz05", 0, "ISSEQNAME", "SQ_SWON", "!=0")
    be:DMsetSD("HITLANDMODEL", "hitenergyfieldz050", 0, "OFFHIT")
    be:DMsetSD("MODELCTRL", "e_mecha4", -1, "SQ_DMENTR", 180)
    g_IFLG00 = 1
    be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 180)
    be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 190)
    be:DMsetSD("MODELCTRL", "i_bosshp18", 0, "GENERATE", "V<0,205,0>/SQ_OPEN", 180)
    be:DMsetSD("METERCTRL", "bshp18", 0, "SETMODELHP", "e_mecha4/I<0>", 180)
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET", 180)
    be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/SET", 180)
    be:DMrun()
else
end
