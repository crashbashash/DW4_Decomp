funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.2,1.0,1.1>/V<1.2,1.0,1.1>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.2,0.16,0.18>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
if be:SYSgetPlayerNinzu() == 0 then
    be:sd("PLAYERARMS", "w_sp0203", 0, "GENERATE")
else
    for local_1 = 0, 3 do
        if be:SYSisJoinPlayer(local_1) == 1 then
            be:sd("PLAYERARMS", "w_sp0203", local_1, "GENERATE")
        end
    end
end
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT", 1)
be:sd("MODELCTRL", "g_gatesign", 0, "GENERATE", "V<2045,25,-1300>/V<0,180,0>")
be:sd("MODELCTRL", "g_gatesign", 1, "GENERATE", "V<2655,25,-500>/V<0,0,0>")
be:sd("MODELCTRL", "g_highjumper", 0, "GENERATE", "V<-100,-15,-1600>/V<0,-90,0>")
be:sd("MODELCTRL", "g_highjumper", 1, "GENERATE", "V<600,-15,-1600>/V<0,-90,0>")
be:sd("MODELCTRL", "g_highjumper", 2, "GENERATE", "V<1700,-15,-1600>/V<0,-90,0>")
be:sd("MODELCTRL", "g_lowjumper", 0, "GENERATE", "V<-300,-22,-1600>/V<0,90,0>")
be:sd("MODELCTRL", "g_lowjumper", 1, "GENERATE", "V<900,-22,-1600>/V<0,90,0>")
be:sd("MODELCTRL", "g_sandgate", 0, "GENERATE", "V<2100,27,-500>/V<0,180,0>")
be:sd("MODELCTRL", "g_sandgate", 1, "GENERATE", "V<2600,27,-1300>/V<0,0,0>")
be:sd("MODELCTRL", "g_sidejumper", 0, "GENERATE", "V<-800,-22,-1600>/V<0,-90,0>")
be:sd("MODELCTRL", "g_sidejumper", 1, "GENERATE", "V<-600,-22,-1600>/V<0,90,0>")
be:sd("MODELCTRL", "g_sidejumper", 2, "GENERATE", "V<100,-22,-1600>/V<0,-90,0>")
be:sd("MODELCTRL", "g_sidejumper", 3, "GENERATE", "V<300,-22,-1600>/V<0,90,0>")
be:sd("MODELCTRL", "g_sidejumper", 4, "GENERATE", "V<1200,-22,-1600>/V<0,-90,0>")
be:sd("MODELCTRL", "g_sidejumper", 5, "GENERATE", "V<1400,-22,-1600>/V<0,90,0>")
be:sd("MODELCTRL", "r_trainz02", 0, "GENERATE", "V<0,0,0>/V<0,0,0>")
be:sd("MODELCTRL", "g_soukouz02", 0, "GENERATE", "V<-2300,10,1300>/V<0,180,0>")
be:sd("SOUND", nil, -1, "PLAY", "AM_VALLE")
be:sd("SOUND", nil, -1, "PLAY", "AM_DESER")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
