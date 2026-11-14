g_lFLG01 = 1
if g_lFLG00 == 1 then
    be:sd("MODELCTRL", "g_breakinggatez05", 0, "SQ_SWON")
    be:sd("HITLANDMODEL", "hitbreakinggatez050", 0, "OFFHIT", 75)
    be:sd("MODELCTRL", "g_breakinggatez05", 1, "SQ_SWON")
    be:sd("HITLANDMODEL", "hitbreakinggatez051", 0, "OFFHIT", 75)
end
