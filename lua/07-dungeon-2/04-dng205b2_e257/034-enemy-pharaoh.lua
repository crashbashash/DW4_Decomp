if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    if be:FLGisOn(138) ~= 1 and be:FLGisOn(302) == 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-06")
    elseif be:FLGisOn(138) ~= 1 and be:FLGisOn(302) ~= 1 then
        be:FLGset(302, 1)
        be:DMsetSD("ENEMY", nil, -1, "ONFREEZE")
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "Ddc205b2a", 30)
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR", 30)
        be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
        be:DMsetSD("GENERATER", nil, -1, "START", "GENE-06", 30)
        be:DMchkSD("MODELCTRL", "e_pharaoh", -1, "ISRUN", "==0")
        be:DMsetSD("ENEMY", "e_pharaoh", -1, "OFCTRL")
        mswk63088 = "DMINFOFONT01/font00/I<10>"
        mswk63089 = "DMINFOFONT02/font00/I<11>"
        mswk63090 = "DMINFOFONT02/font01/I<12>"
        mswk63091 = "DMINFOFONT02/font02/I<13>"
        funcOpenDigimonInfoWin(mswk63088, mswk63089, mswk63090, mswk63091, 30)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "==0")
        be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA", 225)
        be:DMchkSD("MODELCTRL", "i_dminfown", 0, "ISRUN", "!=0")
        be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN01/SET")
        be:DMsetSD("PLAYER", nil, -1, "ONCTRL")
        be:DMsetSD("ENEMY", "e_pharaoh", -1, "ONCTRL")
        be:DMsetSD("ENEMY", nil, -1, "OFFREEZE")
        be:DMrun()
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-06")
end
