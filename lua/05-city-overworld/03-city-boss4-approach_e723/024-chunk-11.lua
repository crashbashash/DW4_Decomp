if g_lFLG02 ~= 1 then
    g_lFLG02 = 1
else
    be:sd("MODELCTRL", "g_sbutton", 1, "SQ_POWERON")
end
