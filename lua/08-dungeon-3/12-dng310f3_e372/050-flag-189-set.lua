if be:MATisAllPlayer() == 1 and g_cellMovable == 2 and be:FLGisOn(189) == 0 then
    be:DMsetSD("ENEMY", nil, -1, "ONFREEZE")
    be:DMsetSD("PLAYER", nil, -1, "ONFREEZE")
    be:DMsetSD("MODELCTRL", "g_d3movecell2", 1, "SQ_SWON")
    be:DMsetSD("MODELCTRL", "g_d3movecell2w", 1, "SQ_SWON")
    be:DMchkSD("MODELCTRL", "g_d3movecell2", 1, "ISSEQNAME", "SQ_SWON", "==0")
    be:DMchkSD("MODELCTRL", "g_d3movecell2", 1, "ISSEQNAME", "SQ_SWON", "!=0")
    be:DMsetSD("CAMERA", nil, -1, "SHAKE", "37/F<0.3>/F<3.0>/F<9.0>")
    be:DMsetSD("HITLANDMODEL", "cell02left", 0, "OFFHIT")
    be:DMsetSD("HITLANDMODEL", "cell02right", 0, "ONHIT")
    be:DMsetSD("ENEMY", nil, -1, "OFFREEZE")
    be:DMsetSD("PLAYER", nil, -1, "OFFREEZE")
    be:DMrun()
    be:FLGset(189, 1)
    g_cellMovable = 0
end
