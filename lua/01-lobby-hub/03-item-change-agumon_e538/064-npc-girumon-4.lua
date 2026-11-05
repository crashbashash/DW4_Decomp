g_SItemDB = 0
funcOpenMessage("talk", "n_girumon", "M")
if be:SYSctlFlagFolder("IS", 11) == 1 then
    mswk61117 = "TALKFONT02/font00/I<234>"
    funcOneMessage(mswk61117)
    mswk61118 = "TALKFONT02/font00/I<256>"
    funcOneMessage(mswk61118)
    g_SItemDB = "impItem"
    g_SItemID = 11
    g_TItemDB = "weapon"
    g_TItemID = 26
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 9, 0, 0) == 1 then
    mswk61119 = "TALKFONT02/font00/I<242>"
    funcOneMessage(mswk61119)
    mswk61120 = "TALKFONT02/font00/I<257>"
    funcOneMessage(mswk61120)
    g_SItemDB = "armor2"
    g_SItemID = 9
    g_TItemDB = "weapon"
    g_TItemID = 0
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 6, 0, 0) == 1 then
    mswk61121 = "TALKFONT02/font00/I<258>"
    funcOneMessage(mswk61121)
    mswk61122 = "TALKFONT02/font00/I<259>"
    funcOneMessage(mswk61122)
    g_SItemDB = "armor2"
    g_SItemID = 6
    g_TItemDB = "weapon"
    g_TItemID = 2
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 3, 0, 0) == 1 then
    mswk61123 = "TALKFONT02/font00/I<260>"
    funcOneMessage(mswk61123)
    mswk61124 = "TALKFONT02/font00/I<261>"
    funcOneMessage(mswk61124)
    g_SItemDB = "armor2"
    g_SItemID = 3
    g_TItemDB = "weapon"
    g_TItemID = 56
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 1, 0, 0) == 1 then
    mswk61125 = "TALKFONT02/font00/I<262>"
    funcOneMessage(mswk61125)
    mswk61126 = "TALKFONT02/font00/I<263>"
    funcOneMessage(mswk61126)
    g_SItemDB = "weapon"
    g_SItemID = 1
    g_TItemDB = "weapon"
    g_TItemID = 100
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 76, 0, 0) == 1 then
    mswk61127 = "TALKFONT02/font00/I<264>"
    funcOneMessage(mswk61127)
    mswk61128 = "TALKFONT02/font00/I<265>"
    funcOneMessage(mswk61128)
    g_SItemDB = "weapon"
    g_SItemID = 76
    g_TItemDB = "armor2"
    g_TItemID = 18
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 201, 0, 0) == 1 then
    mswk61129 = "TALKFONT02/font00/I<266>"
    funcOneMessage(mswk61129)
    mswk61130 = "TALKFONT02/font00/I<267>"
    funcOneMessage(mswk61130)
    g_SItemDB = "weapon"
    g_SItemID = 201
    g_TItemDB = "armor2"
    g_TItemID = 15
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 75, 0, 0) == 1 then
    mswk61131 = "TALKFONT02/font00/I<268>"
    funcOneMessage(mswk61131)
    mswk61132 = "TALKFONT02/font00/I<269>"
    funcOneMessage(mswk61132)
    g_SItemDB = "weapon"
    g_SItemID = 75
    g_TItemDB = "weapon"
    g_TItemID = 127
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 227, 0, 0) == 1 then
    mswk61133 = "TALKFONT02/font00/I<270>"
    funcOneMessage(mswk61133)
    mswk61134 = "TALKFONT02/font00/I<271>"
    funcOneMessage(mswk61134)
    g_SItemDB = "weapon"
    g_SItemID = 227
    g_TItemDB = "armor2"
    g_TItemID = 30
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 177, 0, 0) == 1 then
    mswk61135 = "TALKFONT02/font00/I<272>"
    funcOneMessage(mswk61135)
    mswk61136 = "TALKFONT02/font00/I<273>"
    funcOneMessage(mswk61136)
    g_SItemDB = "weapon"
    g_SItemID = 177
    g_TItemDB = "armor2"
    g_TItemID = 27
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 187, 0, 0) == 1 then
    mswk61137 = "TALKFONT02/font00/I<274>"
    funcOneMessage(mswk61137)
    mswk61138 = "TALKFONT02/font00/I<275>"
    funcOneMessage(mswk61138)
    g_SItemDB = "weapon"
    g_SItemID = 187
    g_TItemDB = "weapon"
    g_TItemID = 62
else
    mswk61139 = "TALKFONT02/font00/I<252>"
    funcOneMessage(mswk61139)
    mswk61140 = "TALKFONT02/font00/I<253>"
    funcOneMessage(mswk61140)
    funcCloseMessage("talk", "n_girumon", "M")
end
if g_SItemDB ~= 0 then
    mswk61141 = "TALKFONT02/font01/I<71>"
    mswk61142 = "TALKFONT02/font02/I<72>"
    mswk61143 = "TALKFONT02/font00/I<254>"
    mswk61144 = "TALKFONT02/font00/I<255>"
    funcChoiceMessage(mswk61141, mswk61142)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61143)
    be:DMsetLua("itemchange21.lua")
    be:DMcase(1)
    funcOneMessage(mswk61144)
    funcCloseMessage("talk", "n_girumon", "M")
    be:DMswtEnd()
end
be:DMrun()
