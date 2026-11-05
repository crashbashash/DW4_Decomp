if be:MDLisLive("f_bit", 0) == 0 then
    be:sd("MODELCTRL", "f_bit", 0, "GENERATE", "f_apocaly/I<0>/V<0,30,0>/V<0,90,0>/SQ_ENTR")
else
    be:sd("MODELCTRL", "f_apocaly", 0, "SQ_WAIT")
end
