local setFileNames = function()
    if be:SYSisJoinPlayer(0) == 1 then
        local local_0
        local count = 0
        for playerIndex = 0, 3 do
            if be:SYSisJoinPlayer(playerIndex) == 1 then
                count = count + 1
            end
        end
        if count <= 2 then
            for playerIndex = 0, 3 do
                if be:SYSisJoinPlayer(playerIndex) == 1 then
                    be:CFLsetName("_common/" .. be:SYSgetPlayerName(playerIndex) .. ".igb")
                end
            end
        end
        for playerIndex = 0, 3 do
            if be:SYSisJoinPlayer(playerIndex) == 1 then
                local playerName = be:SYSgetPlayerName(playerIndex)
                local local_6 = gsub(playerName, "p_", "q_")
                be:CFLsetName("_common/" .. local_6 .. ".igb")
            end
        end
    else
        be:CFLsetName("_common/p_agumon.igb")
        be:CFLsetName("_common/p_alpha.igb")
        be:CFLsetName("_common/p_angelr.igb")
        be:CFLsetName("_common/p_beelzeb.igb")
        be:CFLsetName("_common/p_dorumon.igb")
        be:CFLsetName("_common/p_dukecrim.igb")
        be:CFLsetName("_common/p_girumon.igb")
        be:CFLsetName("_common/p_hekabut.igb")
        be:CFLsetName("_common/p_impdrafm.igb")
        be:CFLsetName("_common/p_vmon.igb")
        be:CFLsetName("_common/p_wargrey.igb")
        be:CFLsetName("_common/p_weregaru.igb")
        be:CFLsetName("_common/p_impdrapm.igb")
        be:CFLsetName("_common/p_susanoo.igb")
        be:CFLsetName("_common/p_metalgaru.igb")
        be:CFLsetName("_common/p_bwargrey.igb")
    end
end
local setFileNames2 = function()
    if be:SYSisJoinPlayer(0) == 1 then
        local local_0
        local local_1
        for playerIndex = 0, 3 do
            if be:SYSisJoinPlayer(playerIndex) == 1 then
                for slot = 0, 2 do
                    local weaponName = be:SYSgetWeaponName(playerIndex, slot)
                    if weaponName then
                        be:CFLsetName("_common/" .. weaponName .. ".igb")
                    end
                end
            end
        end
    else
        be:CFLsetName("_common/w_arm01.igb")
        be:CFLsetName("_common/w_arm02.igb")
        be:CFLsetName("_common/w_arm03.igb")
        be:CFLsetName("_common/w_arm04.igb")
        be:CFLsetName("_common/w_arm05.igb")
        be:CFLsetName("_common/w_arm06.igb")
        be:CFLsetName("_common/w_arm07.igb")
        be:CFLsetName("_common/w_axe01.igb")
        be:CFLsetName("_common/w_axe02.igb")
        be:CFLsetName("_common/w_axe03.igb")
        be:CFLsetName("_common/w_axe04.igb")
        be:CFLsetName("_common/w_axe05.igb")
        be:CFLsetName("_common/w_axe06.igb")
        be:CFLsetName("_common/w_common01.igb")
        be:CFLsetName("_common/w_common02.igb")
        be:CFLsetName("_common/w_common03.igb")
        be:CFLsetName("_common/w_common04.igb")
        be:CFLsetName("_common/w_common05.igb")
        be:CFLsetName("_common/w_common06.igb")
        be:CFLsetName("_common/w_common07.igb")
        be:CFLsetName("_common/w_cutlas01.igb")
        be:CFLsetName("_common/w_cutlas02.igb")
        be:CFLsetName("_common/w_cutlas03.igb")
        be:CFLsetName("_common/w_cutlas04.igb")
        be:CFLsetName("_common/w_cutlas05.igb")
        be:CFLsetName("_common/w_cutlas06.igb")
        be:CFLsetName("_common/w_cutlas07.igb")
        be:CFLsetName("_common/w_dagger01.igb")
        be:CFLsetName("_common/w_dagger02.igb")
        be:CFLsetName("_common/w_dagger03.igb")
        be:CFLsetName("_common/w_dagger04.igb")
        be:CFLsetName("_common/w_dagger05.igb")
        be:CFLsetName("_common/w_dagger06.igb")
        be:CFLsetName("_common/w_glave01.igb")
        be:CFLsetName("_common/w_glave02.igb")
        be:CFLsetName("_common/w_glave03.igb")
        be:CFLsetName("_common/w_glave04.igb")
        be:CFLsetName("_common/w_glave05.igb")
        be:CFLsetName("_common/w_glave06.igb")
        be:CFLsetName("_common/w_gun01.igb")
        be:CFLsetName("_common/w_gun02.igb")
        be:CFLsetName("_common/w_gun03.igb")
        be:CFLsetName("_common/w_gun04.igb")
        be:CFLsetName("_common/w_gun05.igb")
        be:CFLsetName("_common/w_gun06.igb")
        be:CFLsetName("_common/w_gun07.igb")
        be:CFLsetName("_common/w_gun08.igb")
        be:CFLsetName("_common/w_katana01.igb")
        be:CFLsetName("_common/w_katana02.igb")
        be:CFLsetName("_common/w_katana03.igb")
        be:CFLsetName("_common/w_katana04.igb")
        be:CFLsetName("_common/w_katana05.igb")
        be:CFLsetName("_common/w_katana06.igb")
        be:CFLsetName("_common/w_maul01.igb")
        be:CFLsetName("_common/w_maul02.igb")
        be:CFLsetName("_common/w_maul03.igb")
        be:CFLsetName("_common/w_maul04.igb")
        be:CFLsetName("_common/w_maul05.igb")
        be:CFLsetName("_common/w_maul06.igb")
        be:CFLsetName("_common/w_maul07.igb")
        be:CFLsetName("_common/w_saber01.igb")
        be:CFLsetName("_common/w_saber02.igb")
        be:CFLsetName("_common/w_saber03.igb")
        be:CFLsetName("_common/w_saber04.igb")
        be:CFLsetName("_common/w_saber05.igb")
        be:CFLsetName("_common/w_saber06.igb")
        be:CFLsetName("_common/w_saber07.igb")
        be:CFLsetName("_common/w_sword01.igb")
        be:CFLsetName("_common/w_sword02.igb")
        be:CFLsetName("_common/w_sword03.igb")
        be:CFLsetName("_common/w_sword04.igb")
        be:CFLsetName("_common/w_sword05.igb")
        be:CFLsetName("_common/w_sword06.igb")
        be:CFLsetName("_common/w_sp0203.igb")
    end
end
local setFileNames3 = function()
    if be:SYSgetDifficulty() == 0 then
        be:CFLsetName(be:CFLgetFolderName() .. "/separate/generatorN.igb")
    elseif be:SYSgetDifficulty() == 1 then
        be:CFLsetName(be:CFLgetFolderName() .. "/separate/generatorH.igb")
    else
        be:CFLsetName(be:CFLgetFolderName() .. "/separate/generatorV.igb")
    end
end
local setFileNames4 = function(...)
    local local_1 = be:CFLgetFolderName() .. "/separate/"
    if be:SYSgetCameraMode() == 0 then
        be:CFLsetName(local_1 .. "aaaCamera.igb")
    else
        be:CFLsetName(local_1 .. "aaaCameraL.igb")
    end
    if arg.n ~= 0 then
        be:CFLsetName(local_1 .. "ACMR_pack.igb")
        if be:SYSgetIsPackOnly() == 0 then
            local local_2
            for i = 1, arg.n do
                be:CFLsetName(local_1 .. arg[i] .. ".igb")
            end
        end
    end
end
local setFileNames5 = function(...)
    local list = {"AJP_", "AUS_", "AEU_"}
    local local_2 = be:SYSgetArea() + 1
    local local_3 = be:CFLgetFolderName() .. "/separate/" .. list[local_2]
    be:CFLsetName(local_3 .. "pack.igb")
    if be:SYSgetIsPackOnly() == 0 then
        local local_4
        for i = 1, arg.n do
            be:CFLsetName(local_3 .. arg[i] .. ".igb")
        end
    end
end
local setFileNames6 = function(...)
    local list = {"JPN_", "USA_", "ENG_", "FRA_", "ITA_", "GER_", "SPN_"}
    local local_2 = be:SYSgetCountry() + 1
    local local_3 = be:CFLgetFolderName() .. "/separate/" .. list[local_2]
    be:CFLsetName(local_3 .. "pack.igb")
    if be:SYSgetIsPackOnly() == 0 then
        local local_4
        for i = 1, arg.n do
            be:CFLsetName(local_3 .. arg[i] .. ".igb")
        end
    end
end
local setFileNames7 = function(...)
    local local_1 = be:CFLgetFolderName() .. "/separate/"
    if be:SYSgetLightMode() == 0 then
        local_1 = local_1 .. "LS_"
    else
        local_1 = local_1 .. "LH_"
    end
    be:CFLsetName(local_1 .. "pack.igb")
    if be:SYSgetIsPackOnly() == 0 then
        local local_2
        for i = 1, arg.n do
            be:CFLsetName(local_1 .. arg[i] .. ".igb")
        end
    end
end
be:CFLclear()
setFileNames3()
setFileNames()
setFileNames2()
if be:FLGisOn(64) == 0 then
    be:CFLsetName(be:CFLgetFolderName() .. "/separate/e_torta.igb")
else
    be:CFLsetName(be:CFLgetFolderName() .. "/separate/e_tonogeko.igb")
end
setFileNames6("FontTree", "DBBase", "bcnumic", "bitnum", "expnum", "getitempnl01", "getitempnl02", "getitempnl03", "pcnumic", "rareicon01", "stdownic00", "stdownic01", "stdownic02", "stdownic03", "stdownic04", "stdownic05", "stdownic06", "stdownic07", "stdownic08", "stdownic09", "stdownic10", "stpnl05", "zzstchgwb", "zzstchgwn", "stpnl01", "stpnl03", "stpnl04", "healnum", "stbase")
setFileNames7("BGG00n", "BGG00s", "BGJ00n", "BGJ00s", "BGL00n")
