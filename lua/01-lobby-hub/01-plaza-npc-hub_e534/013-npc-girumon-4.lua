g_SItemDB = 0
funcOpenMessage("talk", "n_girumon", "M")
if be:SYSctlFlagFolder("IS", 11) == 1 then
    mswk61504 = "TALKFONT02/font00/I<234>"
    funcOneMessage(mswk61504)
    mswk61505 = "TALKFONT02/font00/I<257>"
    funcOneMessage(mswk61505)
    g_SItemDB = "impItem"
    g_SItemID = 11
    g_TItemDB = "weapon"
    g_TItemID = 0
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 25, 0, 0) == 1 then
    mswk61506 = "TALKFONT02/font00/I<276>"
    funcOneMessage(mswk61506)
    mswk61507 = "TALKFONT02/font00/I<277>"
    funcOneMessage(mswk61507)
    g_SItemDB = "weapon"
    g_SItemID = 25
    g_TItemDB = "weapon"
    g_TItemID = 235
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 50, 0, 0) == 1 then
    mswk61508 = "TALKFONT02/font00/I<278>"
    funcOneMessage(mswk61508)
    mswk61509 = "TALKFONT02/font00/I<279>"
    funcOneMessage(mswk61509)
    g_SItemDB = "weapon"
    g_SItemID = 50
    g_TItemDB = "weapon"
    g_TItemID = 60
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 75, 0, 0) == 1 then
    mswk61510 = "TALKFONT02/font00/I<268>"
    funcOneMessage(mswk61510)
    mswk61511 = "TALKFONT02/font00/I<280>"
    funcOneMessage(mswk61511)
    g_SItemDB = "weapon"
    g_SItemID = 75
    g_TItemDB = "weapon"
    g_TItemID = 10
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 160, 0, 0) == 1 then
    mswk61512 = "TALKFONT02/font00/I<281>"
    funcOneMessage(mswk61512)
    mswk61513 = "TALKFONT02/font00/I<282>"
    funcOneMessage(mswk61513)
    g_SItemDB = "weapon"
    g_SItemID = 160
    g_TItemDB = "weapon"
    g_TItemID = 78
elseif be:SYSctlDeviceFolder("IS", 0, "armor1", 10, 0, 0) == 1 then
    mswk61514 = "TALKFONT02/font00/I<283>"
    funcOneMessage(mswk61514)
    mswk61515 = "TALKFONT02/font00/I<284>"
    funcOneMessage(mswk61515)
    g_SItemDB = "armor1"
    g_SItemID = 10
    g_TItemDB = "weapon"
    g_TItemID = 199
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 177, 0, 0) == 1 then
    mswk61516 = "TALKFONT02/font00/I<272>"
    funcOneMessage(mswk61516)
    mswk61517 = "TALKFONT02/font00/I<285>"
    funcOneMessage(mswk61517)
    g_SItemDB = "weapon"
    g_SItemID = 177
    g_TItemDB = "weapon"
    g_TItemID = 34
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 2, 0, 0) == 1 then
    mswk61518 = "TALKFONT02/font00/I<286>"
    funcOneMessage(mswk61518)
    mswk61519 = "TALKFONT02/font00/I<285>"
    funcOneMessage(mswk61519)
    g_SItemDB = "weapon"
    g_SItemID = 2
    g_TItemDB = "weapon"
    g_TItemID = 34
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 127, 0, 0) == 1 then
    mswk61520 = "TALKFONT02/font00/I<287>"
    funcOneMessage(mswk61520)
    mswk61521 = "TALKFONT02/font00/I<288>"
    funcOneMessage(mswk61521)
    g_SItemDB = "weapon"
    g_SItemID = 127
    g_TItemDB = "weapon"
    g_TItemID = 103
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 153, 0, 0) == 1 then
    mswk61522 = "TALKFONT02/font00/I<289>"
    funcOneMessage(mswk61522)
    mswk61523 = "TALKFONT02/font00/I<290>"
    funcOneMessage(mswk61523)
    g_SItemDB = "weapon"
    g_SItemID = 153
    g_TItemDB = "weapon"
    g_TItemID = 29
else
    mswk61524 = "TALKFONT02/font00/I<252>"
    funcOneMessage(mswk61524)
    mswk61525 = "TALKFONT02/font00/I<253>"
    funcOneMessage(mswk61525)
    funcCloseMessage("talk", "n_girumon", "M")
end
if g_SItemDB ~= 0 then
    mswk61526 = "TALKFONT02/font01/I<71>"
    mswk61527 = "TALKFONT02/font02/I<72>"
    mswk61528 = "TALKFONT02/font00/I<254>"
    mswk61529 = "TALKFONT02/font00/I<255>"
    funcChoiceMessage(mswk61526, mswk61527)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61528)
    be:DMsetLua("itemchange21.lua")
    be:DMcase(1)
    funcOneMessage(mswk61529)
    funcCloseMessage("talk", "n_girumon", "M")
    be:DMswtEnd()
end
be:DMrun()
