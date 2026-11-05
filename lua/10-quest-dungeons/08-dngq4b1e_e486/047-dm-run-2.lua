if be:MDLgetRamNo() == 0 then
    be:DMchkSD("MODELCTRL", "g_dbutton1", 0, "ISSEQNAME", "SQ_WAIT", "!=1")
    be:DMsetSD("MODELCTRL", "g_dbutton1", 0, "SQ_SWHIT")
    be:DMrun()
end
