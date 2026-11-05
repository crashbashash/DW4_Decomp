if be:MATisPlayer() == 1 and g_lFLG24 ~= 1 then
    g_lFLG24 = 1
    be:sd("MODELCTRL", "g_numeprisonz01", 4, "GENERATE", "V<-470,15,-255>/V<0,-135,0>")
    be:sd("MODELCTRL", "g_numeprisonz01", 5, "GENERATE", "V<-95,15,-350>/V<0,-45,0>")
    be:sd("MODELCTRL", "g_numeprisonz01", 6, "GENERATE", "V<-85,15,-210>/V<0,90,0>")
    be:sd("MODELCTRL", "g_numeprisonz01", 7, "GENERATE", "V<20,15,-210>/V<0,-45,0>")
    be:sd("MODELCTRL", "g_numeprisonz01", 8, "GENERATE", "V<-90,15,-125>/V<0,90,0>")
    be:sd("MODELCTRL", "g_numeprisonz01", 9, "GENERATE", "V<-48.939,15,-86.061>/V<0,135,0>")
    be:sd("MODELCTRL", "g_numepodz01", 3, "GENERATE", "V<-525,21,-325>/V<0,0,0>")
    be:sd("MODELCTRL", "g_numepodz01", 4, "GENERATE", "V<-375,21,-375>/V<0,0,0>")
    be:sd("MODELCTRL", "g_numepodz01", 5, "GENERATE", "V<-335,21,-315>/V<0,0,0>")
    be:sd("MODELCTRL", "g_numepodz01", 6, "GENERATE", "V<-305,21,-375>/V<0,0,0>")
    be:sd("MODELCTRL", "g_numepodz01", 7, "GENERATE", "V<-265,21,-315>/V<0,0,0>")
else
end
