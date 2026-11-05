be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 then
    g_sbutton00 = 1
end
if be:MDLgetRamNo() == 1 then
    g_sbutton01 = 1
end
if be:MDLgetRamNo() == 2 then
    g_sbutton02 = 1
end
if be:MDLgetRamNo() == 3 then
    g_sbutton03 = 1
end
if be:FLGisOn(41) == 0 and g_sbutton00 == 1 and g_sbutton01 == 1 and g_sbutton02 == 1 and g_sbutton03 == 1 then
    be:sd("MODELCTRL", "g_bossgatez01", 0, "SQ_SWON")
    be:sd("HITLANDMODEL", "hitbossgatez01", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_sbutton", 0, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_sbutton", 1, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_sbutton", 2, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_sbutton", 3, "SQ_ONLOOP")
    be:FLGset(41, 1)
end
