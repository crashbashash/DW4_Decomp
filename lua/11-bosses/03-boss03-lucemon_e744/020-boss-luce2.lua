if be:MDLisCallName("chack") == 1 then
    if g_dmgf == 0 then
        be:MDLsetSeq("SQ_WAIT")
    else
        g_dmgf = 0
        be:MDLsetSeq("SQ_SWITCH7")
        be:sd("MODELCTRL", "f_luce2", 0, "SQ_SWOF")
    end
end
if be:MDLisCallName("chack1") == 1 then
    if g_dmgf == 0 then
        be:MDLsetSeq("SQ_SWITCH7")
        be:sd("MODELCTRL", "f_luce2", 0, "SQ_SWOF")
    else
        g_dmgf = 0
        be:MDLsetSeq("SQ_SWITCH7")
        be:sd("MODELCTRL", "f_luce2", 0, "SQ_SWOF")
    end
end
