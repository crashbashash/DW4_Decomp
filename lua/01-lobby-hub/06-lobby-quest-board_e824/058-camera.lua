be:CFLclear()
if be:SYSisJoinPlayer(0) == 1 then
    for local_8 = 0, 3 do
        if be:SYSisJoinPlayer(local_8) == 1 then
            be:CFLsetName("_common/" .. local_12 .. ".igb")
        end
    end
else
    be:CFLsetName("_common/m_agumon.igb")
    be:CFLsetName("_common/m_alpha.igb")
    be:CFLsetName("_common/m_angelr.igb")
    be:CFLsetName("_common/m_beelzeb.igb")
    be:CFLsetName("_common/m_dorumon.igb")
    be:CFLsetName("_common/m_dukecrim.igb")
    be:CFLsetName("_common/m_girumon.igb")
    be:CFLsetName("_common/m_hekabut.igb")
    be:CFLsetName("_common/m_impdrafm.igb")
    be:CFLsetName("_common/m_vmon.igb")
    be:CFLsetName("_common/m_wargrey.igb")
    be:CFLsetName("_common/m_weregaru.igb")
    be:CFLsetName("_common/m_impdrapm.igb")
    be:CFLsetName("_common/m_susanoo.igb")
    be:CFLsetName("_common/m_metalgaru.igb")
    be:CFLsetName("_common/m_bwargrey.igb")
end
local_1()
local_5("FontTree", "DBBase", "pcnumic", "zzstchgwb", "zzstchgwn", "stpnl01", "stpnl03", "stpnl04", "healnum", "stbase", "shbase")
local_6("BGG00n", "BGG00s", "BGJ00n", "BGJ00s")
PintmessOpen = function() end
