g_SItemDB = 0
funcOpenMessage("talk", "n_vmon", "uC")
if be:SYSctlFlagFolder("IS", 11) == 1 then
    mswk61556 = "TALKFONT02/font00/I<400>"
    funcOneMessage(mswk61556)
    mswk61557 = "TALKFONT02/font00/I<442>"
    funcOneMessage(mswk61557)
    g_SItemDB = "impItem"
    g_SItemID = 11
    g_TItemDB = "weapon"
    g_TItemID = 50
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 175, 0, 0) == 1 then
    mswk61558 = "TALKFONT02/font00/I<443>"
    funcOneMessage(mswk61558)
    mswk61559 = "TALKFONT02/font00/I<444>"
    funcOneMessage(mswk61559)
    g_SItemDB = "weapon"
    g_SItemID = 175
    g_TItemDB = "weapon"
    g_TItemID = 235
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 0, 0, 0) == 1 then
    mswk61560 = "TALKFONT02/font00/I<445>"
    funcOneMessage(mswk61560)
    mswk61561 = "TALKFONT02/font00/I<424>"
    funcOneMessage(mswk61561)
    g_SItemDB = "weapon"
    g_SItemID = 0
    g_TItemDB = "weapon"
    g_TItemID = 227
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 25, 0, 0) == 1 then
    mswk61562 = "TALKFONT02/font00/I<446>"
    funcOneMessage(mswk61562)
    mswk61563 = "TALKFONT02/font00/I<447>"
    funcOneMessage(mswk61563)
    g_SItemDB = "weapon"
    g_SItemID = 25
    g_TItemDB = "weapon"
    g_TItemID = 177
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 35, 0, 0) == 1 then
    mswk61564 = "TALKFONT02/font00/I<448>"
    funcOneMessage(mswk61564)
    mswk61565 = "TALKFONT02/font00/I<449>"
    funcOneMessage(mswk61565)
    g_SItemDB = "weapon"
    g_SItemID = 35
    g_TItemDB = "weapon"
    g_TItemID = 34
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 110, 0, 0) == 1 then
    mswk61566 = "TALKFONT02/font00/I<406>"
    funcOneMessage(mswk61566)
    mswk61567 = "TALKFONT02/font00/I<449>"
    funcOneMessage(mswk61567)
    g_SItemDB = "weapon"
    g_SItemID = 110
    g_TItemDB = "weapon"
    g_TItemID = 34
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 27, 0, 0) == 1 then
    mswk61568 = "TALKFONT02/font00/I<450>"
    funcOneMessage(mswk61568)
    mswk61569 = "TALKFONT02/font00/I<451>"
    funcOneMessage(mswk61569)
    g_SItemDB = "weapon"
    g_SItemID = 27
    g_TItemDB = "weapon"
    g_TItemID = 228
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 77, 0, 0) == 1 then
    mswk61570 = "TALKFONT02/font00/I<440>"
    funcOneMessage(mswk61570)
    mswk61571 = "TALKFONT02/font00/I<452>"
    funcOneMessage(mswk61571)
    g_SItemDB = "weapon"
    g_SItemID = 77
    g_TItemDB = "weapon"
    g_TItemID = 178
elseif be:SYSctlDeviceFolder("IS", 0, "armor1", 6, 0, 0) == 1 then
    mswk61572 = "TALKFONT02/font00/I<453>"
    funcOneMessage(mswk61572)
    mswk61573 = "TALKFONT02/font00/I<454>"
    funcOneMessage(mswk61573)
    g_SItemDB = "armor1"
    g_SItemID = 6
    g_TItemDB = "weapon"
    g_TItemID = 74
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 24, 0, 0) == 1 then
    mswk61574 = "TALKFONT02/font00/I<455>"
    funcOneMessage(mswk61574)
    mswk61575 = "TALKFONT02/font00/I<456>"
    funcOneMessage(mswk61575)
    g_SItemDB = "weapon"
    g_SItemID = 24
    g_TItemDB = "weapon"
    g_TItemID = 154
else
    mswk61576 = "TALKFONT02/font00/I<418>"
    funcOneMessage(mswk61576)
    mswk61577 = "TALKFONT02/font00/I<419>"
    funcOneMessage(mswk61577)
    funcCloseMessage("talk", "n_vmon", "uC")
end
if g_SItemDB ~= 0 then
    mswk61578 = "TALKFONT02/font01/I<71>"
    mswk61579 = "TALKFONT02/font02/I<72>"
    mswk61580 = "TALKFONT02/font00/I<420>"
    mswk61581 = "TALKFONT02/font00/I<421>"
    funcChoiceMessage(mswk61578, mswk61579)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61580)
    be:DMsetLua("itemchange59.lua")
    be:DMcase(1)
    funcOneMessage(mswk61581)
    funcCloseMessage("talk", "n_vmon", "uC")
    be:DMswtEnd()
end
be:DMrun()
