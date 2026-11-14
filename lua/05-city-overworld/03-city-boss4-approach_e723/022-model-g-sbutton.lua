if g_lFLG01 ~= 1 then
    g_lFLG01 = 1
else
    be:sd("MODELCTRL", "g_sbutton", 0, "SQ_POWERON")
end
