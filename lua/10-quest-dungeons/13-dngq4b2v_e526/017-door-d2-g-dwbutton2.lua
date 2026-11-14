be:MDLsetDMGTurn(0)
local shootRamNo = be:BLTgetShootRamNo()
local playerName = be:SYSgetPlayerName(shootRamNo)
local local_2 = 0
if be:SYSgetPlayerNinzu() <= 1 then
    local_2 = 180
else
    local_2 = 15
end
if be:MDLgetRamNo() == 0 then
    if g_dwbutton01 ~= 1 then
        be:sd("MODELCTRL", playerName, shootRamNo, "SQ_WAIT", 0)
        be:MDLsetSeq("SQ_SWON")
        g_dwbutton01 = 1
        if g_dwbutton02 == 1 then
            be:sd("MODELCTRL", "g_d2door", 8, "SQ_SWON", 30)
            be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT", 45)
            be:FLGset(136, 1)
            be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_ONLOOP")
        else
            be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_SWOF", local_2)
        end
    end
elseif be:MDLgetRamNo() == 1 and g_dwbutton02 ~= 1 then
    be:sd("MODELCTRL", playerName, shootRamNo, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    g_dwbutton02 = 1
    if g_dwbutton01 == 1 then
        be:sd("MODELCTRL", "g_d2door", 8, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT", 45)
        be:FLGset(136, 1)
        be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_ONLOOP")
    else
        be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_SWOF", local_2)
    end
end
