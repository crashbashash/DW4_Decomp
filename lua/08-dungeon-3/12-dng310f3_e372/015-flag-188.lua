if be:MATisAllPlayer() == 1 and g_cellMovable == 1 and be:FLGisOn(188) ~= 1 then
    be:DMsetSD("ENEMY", nil, -1, "ONFREEZE")
    be:DMsetSD("PLAYER", nil, -1, "ONFREEZE")
    be:DMsetSD("MODELCTRL", "g_d3movecell2", 0, "SQ_SWOF")
    be:DMsetSD("MODELCTRL", "g_d3movecell2w", 0, "SQ_SWOF")
    be:DMchkSD("MODELCTRL", "g_d3movecell2", 0, "ISSEQNAME", "SQ_SWOF", "==0")
    be:DMchkSD("MODELCTRL", "g_d3movecell2", 0, "ISSEQNAME", "SQ_SWOF", "!=0")
    be:DMsetSD("CAMERA", nil, -1, "SHAKE", "73/F<0.3>/F<3.0>/F<9.0>")
    be:DMsetSD("HITLANDMODEL", "cell01left", 0, "ONHIT")
    be:DMsetSD("HITLANDMODEL", "cell01right", 0, "OFFHIT")
    be:DMsetSD("ENEMY", nil, -1, "OFFREEZE")
    be:DMsetSD("PLAYER", nil, -1, "OFFREEZE")
    be:DMrun()
    be:FLGset(188, 1)
    g_cellMovable = 0
end
