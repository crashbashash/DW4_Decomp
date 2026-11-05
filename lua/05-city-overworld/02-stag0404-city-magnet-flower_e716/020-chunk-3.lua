be:MDLsetDMGTurn(0)
if g_IFLG10 ~= 1 then
    be:sd("MODELCTRL", "g_hideliftz04", 0, "SQ_SWON")
    be:sd("HITLANDMODEL", "hithideliftz04", 0, "OFFHIT", 30)
    be:sd("MODELCTRL", "g_sbutton", 0, "SQ_ONLOOP")
    g_IFLG10 = 1
end
