if be:MATisAllPlayer() == 1 and g_cellMovable == 1 and be:FLGisOn(148) == 1 then
    be:DMsetSD("ENEMY", nil, -1, "ONFREEZE")
    be:DMsetSD("PLAYER", nil, -1, "ONFREEZE")
    be:DMsetSD("MODELCTRL", "g_d3movecell1", 0, "SQ_SWOF")
    be:DMsetSD("MODELCTRL", "g_d3movecell1w", 0, "SQ_SWOF")
    be:DMchkSD("MODELCTRL", "g_d3movecell1", 0, "ISSEQNAME", "SQ_SWOF", "==0")
    be:DMchkSD("MODELCTRL", "g_d3movecell1", 0, "ISSEQNAME", "SQ_SWOF", "!=0")
    be:DMsetSD("CAMERA", nil, -1, "SHAKE", "73/F<0.3>/F<3.0>/F<9.0>")
    be:DMsetSD("HITLANDMODEL", "cell01left", 0, "ONHIT")
    be:DMsetSD("HITLANDMODEL", "cell01right", 0, "OFFHIT")
    be:DMsetSD("ENEMY", nil, -1, "OFFREEZE")
    be:DMsetSD("PLAYER", nil, -1, "OFFREEZE")
    be:DMrun()
    be:FLGset(148, 0)
    g_cellMovable = 0
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    if be:FLGisOn(139) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-09", 1)
    end
end
