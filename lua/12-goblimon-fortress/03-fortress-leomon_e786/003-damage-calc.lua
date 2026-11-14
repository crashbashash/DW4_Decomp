be:MDLsetDMGTurn(0)
local shootRamNo = be:BLTgetShootRamNo()
local playerName = be:SYSgetPlayerName(shootRamNo)
if be:MDLgetHp() > 0 then
    be:MDLaddHp(-100)
    if be:FLGisOn(383) == 0 and be:DMgetCount() == 0 then
        g_messPlayerNo = be:BLTgetShootRamNo()
        be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
        be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
        be:sd("ENEMY", nil, -1, "OFCTRL")
        be:sd("MODELCTRL", playerName, shootRamNo, "SQ_WAIT", 0)
        be:DMchkSD("PLAYER", playerName, shootRamNo, "ISSEQNAME", "SQ_WAIT", "==0")
        be:sd("PLAYER", nil, -1, "OFCTRL")
        be:DMsetSD("MODELCTRL", "g_covercnsz05", 0, "SQ_SWOF")
        funcOpenMessage("mess")
        mswk64006 = "TALKFONT01/font00/I<10>"
        funcOneMessage(mswk64006)
        mswk64007 = "TALKFONT01/font00/I<11>"
        funcOneMessage(mswk64007)
        funcCloseMessage("mess")
        be:DMsetSD("MODELCTRL", "g_covergatez05", 0, "SQ_SWOF")
        be:DMsetSD("HITLANDMODEL", "hitcovergatez05", 0, "OFFHIT")
        be:DMrun()
    end
end
