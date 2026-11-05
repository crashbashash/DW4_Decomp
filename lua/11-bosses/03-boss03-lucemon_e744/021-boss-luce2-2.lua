if be:MDLisCallName("OFF") == 1 then
    be:sd("MODELCTRL", "f_luce2", 0, "SQ_SWOF", 0)
elseif be:MDLisCallName("ON") == 1 then
    be:sd("MODELCTRL", "f_luce2", 0, "SQ_SWON", 0)
end
