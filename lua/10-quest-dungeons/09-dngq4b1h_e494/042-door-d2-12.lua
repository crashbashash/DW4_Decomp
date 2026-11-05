if be:MDLgetRamNo() == 0 then
    be:DMchkSD("MODELCTRL", "g_dbutton1", 0, "ISSEQNAME", "SQ_WAIT", "!=1")
    be:DMsetSD("MODELCTRL", "g_dbutton1", 0, "SQ_SWHIT")
    be:DMrun()
elseif be:MDLgetRamNo() == 1 then
    be:sd("MODELCTRL", "g_d2door", 14, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall15", 0, "OFFHIT", 45)
    be:FLGset(141, 1)
elseif be:MDLgetRamNo() == 2 then
    be:sd("MODELCTRL", "g_d2door", 15, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall16", 0, "OFFHIT", 45)
    be:FLGset(142, 1)
end
