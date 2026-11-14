funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.2,1.15,1.2>/V<1.2,1.15,1.2>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.2,0.35>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
be:sd("MATCTRL", nil, -1, "PAUSE")
funcPlayerSet()
if be:PLAYERgetPos() == 0 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
end
be:sd("MODELCTRL", "g_rock01z01", 0, "GENERATE", "V<85,10,-60>/V<0,0,0>")
be:sd("MODELCTRL", "g_rock01z02", 0, "GENERATE", "V<105,10,-40>/V<0,0,0>")
if be:FLGisOn(960) == 0 then
    be:sd("MODELCTRL", "n_leomon", 0, "GENERATE", "V<25,10,-70>/V<0,0,0>")
    be:sd("MODELCTRL", "n_digilff", 0, "GENERATE", "V<55,10,-70>/V<0,0,0>")
    be:sd("MODELCTRL", "n_digilff", 1, "GENERATE", "V<-5,10,-70>/V<0,0,0>")
    be:sd("MODELCTRL", "n_digilfm", 0, "GENERATE", "V<-35,10,-70>/V<0,0,0>")
    be:sd("MODELCTRL", "n_digilfm", 1, "GENERATE", "V<110,10,35>/V<0,-90,0>")
    be:sd("MODELCTRL", "n_digilfm", 2, "GENERATE", "V<115,10,-10>/V<0,-90,0>")
end
be:sd("MODELCTRL", "n_digilfm", 3, "GENERATE", "V<80,10,65>/V<0,-180,0>")
if be:FLGisOn(960) == 0 then
    be:sd("MODELCTRL", "e_goburi", 0, "GENERATE", "I<638>/I<30>/V<-65,10,-70>/V<0,0,0>/SQ_SLEP")
    be:sd("MODELCTRL", "e_goburi", 1, "GENERATE", "I<638>/I<30>/V<-95,10,-60>/V<0,0,0>/SQ_SLEP")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
