g_SItemDB = 0
funcOpenMessage("talk", "n_prmame", "vX}")
if be:SYSctlDeviceFolder("IS", 0, "weapon", 175, 0, 0) == 1 then
    mswk61644 = "TALKFONT02/font00/I<370>"
    funcOneMessage(mswk61644)
    mswk61645 = "TALKFONT02/font00/I<348>"
    funcOneMessage(mswk61645)
    mswk61646 = "TALKFONT02/font00/I<371>"
    funcOneMessage(mswk61646)
    g_SItemDB = "weapon"
    g_SItemID = 175
    g_TItemDB = "weapon"
    g_TItemID = 77
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 75, 0, 0) == 1 then
    mswk61647 = "TALKFONT02/font00/I<372>"
    funcOneMessage(mswk61647)
    mswk61648 = "TALKFONT02/font00/I<348>"
    funcOneMessage(mswk61648)
    mswk61649 = "TALKFONT02/font00/I<373>"
    funcOneMessage(mswk61649)
    g_SItemDB = "weapon"
    g_SItemID = 75
    g_TItemDB = "weapon"
    g_TItemID = 235
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 200, 0, 0) == 1 then
    mswk61650 = "TALKFONT02/font00/I<374>"
    funcOneMessage(mswk61650)
    mswk61651 = "TALKFONT02/font00/I<348>"
    funcOneMessage(mswk61651)
    mswk61652 = "TALKFONT02/font00/I<375>"
    funcOneMessage(mswk61652)
    g_SItemDB = "weapon"
    g_SItemID = 200
    g_TItemDB = "weapon"
    g_TItemID = 152
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 10, 0, 0) == 1 then
    mswk61653 = "TALKFONT02/font00/I<376>"
    funcOneMessage(mswk61653)
    mswk61654 = "TALKFONT02/font00/I<348>"
    funcOneMessage(mswk61654)
    mswk61655 = "TALKFONT02/font00/I<377>"
    funcOneMessage(mswk61655)
    g_SItemDB = "weapon"
    g_SItemID = 10
    g_TItemDB = "weapon"
    g_TItemID = 34
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 35, 0, 0) == 1 then
    mswk61656 = "TALKFONT02/font00/I<378>"
    funcOneMessage(mswk61656)
    mswk61657 = "TALKFONT02/font00/I<348>"
    funcOneMessage(mswk61657)
    mswk61658 = "TALKFONT02/font00/I<379>"
    funcOneMessage(mswk61658)
    g_SItemDB = "weapon"
    g_SItemID = 35
    g_TItemDB = "armor1"
    g_TItemID = 10
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 2, 0, 0) == 1 then
    mswk61659 = "TALKFONT02/font00/I<380>"
    funcOneMessage(mswk61659)
    mswk61660 = "TALKFONT02/font00/I<348>"
    funcOneMessage(mswk61660)
    mswk61661 = "TALKFONT02/font00/I<381>"
    funcOneMessage(mswk61661)
    g_SItemDB = "weapon"
    g_SItemID = 2
    g_TItemDB = "armor1"
    g_TItemID = 6
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 3, 0, 0) == 1 then
    mswk61662 = "TALKFONT02/font00/I<382>"
    funcOneMessage(mswk61662)
    mswk61663 = "TALKFONT02/font00/I<348>"
    funcOneMessage(mswk61663)
    mswk61664 = "TALKFONT02/font00/I<377>"
    funcOneMessage(mswk61664)
    g_SItemDB = "weapon"
    g_SItemID = 3
    g_TItemDB = "weapon"
    g_TItemID = 34
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 78, 0, 0) == 1 then
    mswk61665 = "TALKFONT02/font00/I<383>"
    funcOneMessage(mswk61665)
    mswk61666 = "TALKFONT02/font00/I<348>"
    funcOneMessage(mswk61666)
    mswk61667 = "TALKFONT02/font00/I<384>"
    funcOneMessage(mswk61667)
    g_SItemDB = "weapon"
    g_SItemID = 78
    g_TItemDB = "weapon"
    g_TItemID = 29
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 228, 0, 0) == 1 then
    mswk61668 = "TALKFONT02/font00/I<385>"
    funcOneMessage(mswk61668)
    mswk61669 = "TALKFONT02/font00/I<348>"
    funcOneMessage(mswk61669)
    mswk61670 = "TALKFONT02/font00/I<386>"
    funcOneMessage(mswk61670)
    g_SItemDB = "weapon"
    g_SItemID = 228
    g_TItemDB = "weapon"
    g_TItemID = 224
else
    mswk61671 = "TALKFONT02/font00/I<366>"
    funcOneMessage(mswk61671)
    mswk61672 = "TALKFONT02/font00/I<367>"
    funcOneMessage(mswk61672)
    funcCloseMessage("talk", "n_prmame", "vX}")
end
if g_SItemDB ~= 0 then
    mswk61673 = "TALKFONT02/font01/I<71>"
    mswk61674 = "TALKFONT02/font02/I<72>"
    mswk61675 = "TALKFONT02/font00/I<368>"
    mswk61676 = "TALKFONT02/font00/I<369>"
    funcChoiceMessage(mswk61673, mswk61674)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61675)
    be:DMsetLua("itemchange116.lua")
    be:DMcase(1)
    funcOneMessage(mswk61676)
    funcCloseMessage("talk", "n_prmame", "vX}")
    be:DMswtEnd()
end
be:DMrun()
