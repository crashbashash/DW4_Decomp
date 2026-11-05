g_SItemDB = 0
funcOpenMessage("talk", "n_agumon", "AO")
if be:SYSctlFlagFolder("IS", 11) == 1 then
    mswk61089 = "TALKFONT02/font00/I<51>"
    funcOneMessage(mswk61089)
    mswk61090 = "TALKFONT02/font00/I<75>"
    funcOneMessage(mswk61090)
    g_SItemDB = "impItem"
    g_SItemID = 11
    g_TItemDB = "weapon"
    g_TItemID = 1
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 18, 0, 0) == 1 then
    mswk61091 = "TALKFONT02/font00/I<76>"
    funcOneMessage(mswk61091)
    mswk61092 = "TALKFONT02/font00/I<77>"
    funcOneMessage(mswk61092)
    g_SItemDB = "armor2"
    g_SItemID = 18
    g_TItemDB = "weapon"
    g_TItemID = 152
elseif be:SYSctlDeviceFolder("IS", 0, "armor1", 1, 0, 0) == 1 then
    mswk61093 = "TALKFONT02/font00/I<78>"
    funcOneMessage(mswk61093)
    mswk61094 = "TALKFONT02/font00/I<79>"
    funcOneMessage(mswk61094)
    g_SItemDB = "armor1"
    g_SItemID = 1
    g_TItemDB = "weapon"
    g_TItemID = 31
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 0, 0, 0) == 1 then
    mswk61095 = "TALKFONT02/font00/I<80>"
    funcOneMessage(mswk61095)
    mswk61096 = "TALKFONT02/font00/I<81>"
    funcOneMessage(mswk61096)
    g_SItemDB = "armor2"
    g_SItemID = 0
    g_TItemDB = "weapon"
    g_TItemID = 37
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 27, 0, 0) == 1 then
    mswk61097 = "TALKFONT02/font00/I<82>"
    funcOneMessage(mswk61097)
    mswk61098 = "TALKFONT02/font00/I<81>"
    funcOneMessage(mswk61098)
    g_SItemDB = "armor2"
    g_SItemID = 27
    g_TItemDB = "weapon"
    g_TItemID = 37
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 26, 0, 0) == 1 then
    mswk61099 = "TALKFONT02/font00/I<83>"
    funcOneMessage(mswk61099)
    mswk61100 = "TALKFONT02/font00/I<84>"
    funcOneMessage(mswk61100)
    g_SItemDB = "weapon"
    g_SItemID = 26
    g_TItemDB = "armor2"
    g_TItemID = 24
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 51, 0, 0) == 1 then
    mswk61101 = "TALKFONT02/font00/I<85>"
    funcOneMessage(mswk61101)
    mswk61102 = "TALKFONT02/font00/I<86>"
    funcOneMessage(mswk61102)
    g_SItemDB = "weapon"
    g_SItemID = 51
    g_TItemDB = "weapon"
    g_TItemID = 150
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 176, 0, 0) == 1 then
    mswk61103 = "TALKFONT02/font00/I<87>"
    funcOneMessage(mswk61103)
    mswk61104 = "TALKFONT02/font00/I<88>"
    funcOneMessage(mswk61104)
    g_SItemDB = "weapon"
    g_SItemID = 176
    g_TItemDB = "armor2"
    g_TItemID = 21
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 75, 0, 0) == 1 then
    mswk61105 = "TALKFONT02/font00/I<89>"
    funcOneMessage(mswk61105)
    mswk61106 = "TALKFONT02/font00/I<90>"
    funcOneMessage(mswk61106)
    g_SItemDB = "weapon"
    g_SItemID = 75
    g_TItemDB = "weapon"
    g_TItemID = 155
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 27, 0, 0) == 1 then
    mswk61107 = "TALKFONT02/font00/I<91>"
    funcOneMessage(mswk61107)
    mswk61108 = "TALKFONT02/font00/I<92>"
    funcOneMessage(mswk61108)
    g_SItemDB = "weapon"
    g_SItemID = 27
    g_TItemDB = "armor2"
    g_TItemID = 36
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 102, 0, 0) == 1 then
    mswk61109 = "TALKFONT02/font00/I<93>"
    funcOneMessage(mswk61109)
    mswk61110 = "TALKFONT02/font00/I<94>"
    funcOneMessage(mswk61110)
    g_SItemDB = "weapon"
    g_SItemID = 102
    g_TItemDB = "weapon"
    g_TItemID = 187
else
    mswk61111 = "TALKFONT02/font00/I<69>"
    funcOneMessage(mswk61111)
    mswk61112 = "TALKFONT02/font00/I<70>"
    funcOneMessage(mswk61112)
    funcCloseMessage("talk", "n_agumon", "AO")
end
if g_SItemDB ~= 0 then
    mswk61113 = "TALKFONT02/font01/I<71>"
    mswk61114 = "TALKFONT02/font02/I<72>"
    mswk61115 = "TALKFONT02/font00/I<73>"
    mswk61116 = "TALKFONT02/font00/I<74>"
    funcChoiceMessage(mswk61113, mswk61114)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61115)
    be:DMsetLua("itemchange2.lua")
    be:DMcase(1)
    funcOneMessage(mswk61116)
    funcCloseMessage("talk", "n_agumon", "AO")
    be:DMswtEnd()
end
be:DMrun()
