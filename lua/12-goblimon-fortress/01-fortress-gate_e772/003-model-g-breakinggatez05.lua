g_lFLG01 = 1
if g_lFLG00 == 1 then
    be:sd("MODELCTRL", "g_breakinggatez05", 0, "SQ_SWON")
    be:sd("MODELCTRL", "g_breakinggatez05", 2, "SQ_SWON")
    be:sd("HITLANDMODEL", "hitbreakinggatez050", 0, "OFFHIT", 75)
    be:sd("HITLANDMODEL", "hitbreakinggatez052", 0, "OFFHIT", 75)
end
