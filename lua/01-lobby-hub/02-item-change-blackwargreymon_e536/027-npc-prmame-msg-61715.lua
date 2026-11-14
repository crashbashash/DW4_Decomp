g_SItemDB = 0
funcOpenMessage("talk", "n_prmame", "vX}")
if be:SYSctlDeviceFolder("IS", 0, "weapon", 28, 0, 0) == 1 then
    mswk61715 = "TALKFONT02/font00/I<387>"
    funcOneMessage(mswk61715)
    mswk61716 = "TALKFONT02/font00/I<388>"
    funcOneMessage(mswk61716)
    mswk61717 = "TALKFONT02/font00/I<389>"
    funcOneMessage(mswk61717)
    g_SItemDB = "weapon"
    g_SItemID = 28
    g_TItemDB = "weapon"
    g_TItemID = 124
elseif be:SYSctlDeviceFolder("IS", 0, "armor1", 1, 0, 0) == 1 then
    mswk61718 = "TALKFONT02/font00/I<387>"
    funcOneMessage(mswk61718)
    mswk61719 = "TALKFONT02/font00/I<390>"
    funcOneMessage(mswk61719)
    mswk61720 = "TALKFONT02/font00/I<391>"
    funcOneMessage(mswk61720)
    g_SItemDB = "armor1"
    g_SItemID = 1
    g_TItemDB = "weapon"
    g_TItemID = 249
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 74, 0, 0) == 1 then
    mswk61721 = "TALKFONT02/font00/I<387>"
    funcOneMessage(mswk61721)
    mswk61722 = "TALKFONT02/font00/I<392>"
    funcOneMessage(mswk61722)
    mswk61723 = "TALKFONT02/font00/I<393>"
    funcOneMessage(mswk61723)
    g_SItemDB = "weapon"
    g_SItemID = 74
    g_TItemDB = "weapon"
    g_TItemID = 154
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 29, 0, 0) == 1 then
    mswk61724 = "TALKFONT02/font00/I<387>"
    funcOneMessage(mswk61724)
    mswk61725 = "TALKFONT02/font00/I<394>"
    funcOneMessage(mswk61725)
    mswk61726 = "TALKFONT02/font00/I<395>"
    funcOneMessage(mswk61726)
    g_SItemDB = "weapon"
    g_SItemID = 29
    g_TItemDB = "armor2"
    g_TItemID = 32
else
    mswk61727 = "TALKFONT02/font00/I<396>"
    funcOneMessage(mswk61727)
    mswk61728 = "TALKFONT02/font00/I<397>"
    funcOneMessage(mswk61728)
    funcCloseMessage("talk", "n_prmame", "vX}")
end
if g_SItemDB ~= 0 then
    mswk61729 = "TALKFONT02/font01/I<71>"
    mswk61730 = "TALKFONT02/font02/I<72>"
    mswk61731 = "TALKFONT02/font00/I<398>"
    mswk61732 = "TALKFONT02/font00/I<399>"
    funcChoiceMessage(mswk61729, mswk61730)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61731)
    be:DMsetLua("itemchange173.lua")
    be:DMcase(1)
    funcOneMessage(mswk61732)
    funcCloseMessage("talk", "n_prmame", "vX}")
    be:DMswtEnd()
end
be:DMrun()
