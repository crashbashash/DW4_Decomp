if g_lFLG03 ~= 1 then
    g_lFLG03 = 1
else
    be:sd("MODELCTRL", "g_sbutton", 2, "SQ_POWERON")
end
