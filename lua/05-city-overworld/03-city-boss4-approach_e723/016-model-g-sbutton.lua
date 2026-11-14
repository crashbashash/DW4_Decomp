if g_lFLG04 ~= 1 then
    g_lFLG04 = 1
else
    be:sd("MODELCTRL", "g_sbutton", 3, "SQ_POWERON")
end
