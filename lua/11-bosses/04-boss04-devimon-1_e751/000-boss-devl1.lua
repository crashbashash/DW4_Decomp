if be:MDLisCallName("entr") == 1 then
    be:DMsetSD("MODELCTRL", "f_devl1", 0, "SQ_EXIT")
    be:DMchkSD("MODELCTRL", "f_devl1", 0, "ISRUN", "==1")
    if g_devl1chgCount < 9 then
        g_devl1chgCount = g_devl1chgCount + 1
    end
    if be:SYSgetDifficulty() == 0 then
        be:DMsetSD("MODELCTRL", "f_devl1", 0, "GENERATE", "I<360>/I<2620>/" .. g_devl1b .. "/V<0.0,0.0,0.0>/SQ_NENTR")
    elseif be:SYSgetDifficulty() == 1 then
        be:DMsetSD("MODELCTRL", "f_devl1", 0, "GENERATE", "I<361>/I<14520>/" .. g_devl1b .. "/V<0.0,0.0,0.0>/SQ_NENTR")
    elseif be:SYSgetDifficulty() == 2 then
        be:DMsetSD("MODELCTRL", "f_devl1", 0, "GENERATE", "I<362>/I<26620>/" .. g_devl1b .. "/V<0.0,0.0,0.0>/SQ_NENTR")
    end
    be:DMsetSD("MODELCTRL", "f_devl1b", g_Ramno, "SQ_ERAS")
    g_devl1blive = g_devl1blive + -1
    be:DMrun()
elseif be:MDLisCallName("bexit") == 1 then
    be:MDLaddHp(-(be:MDLgetHp() * 0.1 * g_devl1chgCount))
    if be:MDLisLive("i_bosshp04", 0) == 1 then
        be:sd("METERCTRL", "bshp04", 0, "SETMODELHP", "f_devl1/I<0>", 1)
    else
    end
end
if be:MDLisCallName("exit") == 1 then
    for local_2 = 0, 2 do
        if be:MDLisLive("e_mecha4bs", local_2) == 1 then
            local_1 = 1
        end
    end
    if local_1 == 1 then
        be:sd("MODELCTRL", "e_mecha4bs", -2, "SQ_EXIT")
    end
end
