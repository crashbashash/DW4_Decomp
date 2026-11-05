if be:MATisPlayer() == 1 then
    be:sd("MODELCTRL", "g_conduitz03", 0, "SQ_SWON01")
    be:sd("MODELCTRL", "g_conduitz03", 1, "SQ_SWON01")
    be:sd("MODELCTRL", "g_conduitz03", 2, "SQ_SWON01")
    be:sd("MODELCTRL", "g_conduitz03", 3, "SQ_SWON02")
    be:sd("MODELCTRL", "g_conduitz03", 4, "SQ_SWON02")
    be:sd("MODELCTRL", "g_conduitz03", 5, "SQ_SWON02")
else
    be:sd("MODELCTRL", "g_conduitz03", 0, "SQ_SWOF")
    be:sd("MODELCTRL", "g_conduitz03", 1, "SQ_SWOF")
    be:sd("MODELCTRL", "g_conduitz03", 2, "SQ_SWOF")
    be:sd("MODELCTRL", "g_conduitz03", 3, "SQ_SWOF")
    be:sd("MODELCTRL", "g_conduitz03", 4, "SQ_SWOF")
    be:sd("MODELCTRL", "g_conduitz03", 5, "SQ_SWOF")
end
