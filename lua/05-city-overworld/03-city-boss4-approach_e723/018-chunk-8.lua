if g_lFLG05 ~= 1 then
    g_lFLG05 = 1
else
    be:sd("MODELCTRL", "g_sbutton", 4, "SQ_POWERON")
end
