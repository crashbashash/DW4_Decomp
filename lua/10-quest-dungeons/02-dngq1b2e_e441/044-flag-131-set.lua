be:MDLsetDMGTurn(0)
local shootRamNo = be:BLTgetShootRamNo()
local playerName = be:SYSgetPlayerName(shootRamNo)
local local_2 = 0
if be:SYSgetPlayerNinzu() == 1 then
    local_2 = 90
else
    local_2 = 15
end
local local_3 = 0
if be:SYSgetDifficulty() == 0 then
    local_3 = 20
else
    local_3 = 15
end
local local_4 = 0
if be:MDLgetRamNo() == 0 then
    if be:FLGisOn(131) == 0 then
        be:sd("MODELCTRL", playerName, shootRamNo, "SQ_WAIT", 0)
        be:MDLsetSeq("SQ_SWON")
        be:FLGset(131, 1)
        if be:FLGisOn(132) == 1 then
            local_4 = 1
            be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_ONLOOP")
        else
            be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_SWOF", local_2)
        end
    end
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(132) == 0 then
    be:sd("MODELCTRL", playerName, shootRamNo, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:FLGset(132, 1)
    if be:FLGisOn(131) == 1 then
        local_4 = 1
        be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_ONLOOP")
    else
        be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_SWOF", local_2)
    end
end
if local_4 == 1 and be:FLGisOn(115) ~= 1 then
    be:COUNTERset(0, be:COUNTERget(0) - local_3)
    g_counter_min = floor(be:COUNTERget(0) / 60)
    g_counter_sec = be:COUNTERget(0) - 60 * g_counter_min
    be:sd("NUMBERCTRL", "timenm0", 0, "SETVALUE", "I<" .. g_counter_min .. ">")
    be:sd("NUMBERCTRL", "timenm1", 0, "SETVALUE", "I<" .. g_counter_sec .. ">")
    be:sd("MODELCTRL", "i_timenm0", 0, "SQ_BLINK")
    local local_5
    for delay = 11, 60, 7 do
        be:sd("SOUND", nil, -1, "PLAY", "z3COUNT1", delay)
    end
    be:sd("MODELCTRL", "i_timenm0", 0, "SQ_WAIT", 60)
end
