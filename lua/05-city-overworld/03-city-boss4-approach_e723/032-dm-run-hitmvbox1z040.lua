if g_lFLG00 ~= 1 then
    g_lFLG00 = 1
else
    be:sd("MODELCTRL", "g_mvbox1z04", 0, "SQ_SWON1")
    be:DMchkSD("MODELCTRL", "g_mvbox1z04", 0, "ISSEQNAME", "SQ_SWON1", "==0")
    be:DMchkSD("MODELCTRL", "g_mvbox1z04", 0, "ISSEQNAME", "SQ_SWON1", "!=0")
    be:DMsetSD("HITLANDMODEL", "hitmvbox1z040", 0, "OFFHIT")
    be:DMrun()
end
