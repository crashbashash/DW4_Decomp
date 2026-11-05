if g_lFLG06 ~= 1 then
    g_lFLG06 = 1
else
    be:sd("MODELCTRL", "g_sbutton", 5, "SQ_POWERON")
end
