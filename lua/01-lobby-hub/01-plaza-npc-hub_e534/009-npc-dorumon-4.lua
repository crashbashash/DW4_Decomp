g_SItemDB = 0
funcOpenMessage("talk", "n_dorumon", "h")
if be:SYSctlFlagFolder("IS", 11) == 1 then
    mswk61145 = "TALKFONT02/font00/I<178>"
    funcOneMessage(mswk61145)
    mswk61146 = "TALKFONT02/font00/I<200>"
    funcOneMessage(mswk61146)
    g_SItemDB = "impItem"
    g_SItemID = 11
    g_TItemDB = "weapon"
    g_TItemID = 51
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 24, 0, 0) == 1 then
    mswk61147 = "TALKFONT02/font00/I<201>"
    funcOneMessage(mswk61147)
    mswk61148 = "TALKFONT02/font00/I<202>"
    funcOneMessage(mswk61148)
    g_SItemDB = "armor2"
    g_SItemID = 24
    g_TItemDB = "weapon"
    g_TItemID = 52
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 18, 0, 0) == 1 then
    mswk61149 = "TALKFONT02/font00/I<203>"
    funcOneMessage(mswk61149)
    mswk61150 = "TALKFONT02/font00/I<204>"
    funcOneMessage(mswk61150)
    g_SItemDB = "armor2"
    g_SItemID = 18
    g_TItemDB = "weapon"
    g_TItemID = 230
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 0, 0, 0) == 1 then
    mswk61151 = "TALKFONT02/font00/I<205>"
    funcOneMessage(mswk61151)
    mswk61152 = "TALKFONT02/font00/I<206>"
    funcOneMessage(mswk61152)
    g_SItemDB = "armor2"
    g_SItemID = 0
    g_TItemDB = "weapon"
    g_TItemID = 6
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 30, 0, 0) == 1 then
    mswk61153 = "TALKFONT02/font00/I<207>"
    funcOneMessage(mswk61153)
    mswk61154 = "TALKFONT02/font00/I<208>"
    funcOneMessage(mswk61154)
    g_SItemDB = "armor2"
    g_SItemID = 30
    g_TItemDB = "weapon"
    g_TItemID = 212
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 26, 0, 0) == 1 then
    mswk61155 = "TALKFONT02/font00/I<209>"
    funcOneMessage(mswk61155)
    mswk61156 = "TALKFONT02/font00/I<210>"
    funcOneMessage(mswk61156)
    g_SItemDB = "weapon"
    g_SItemID = 26
    g_TItemDB = "armor2"
    g_TItemID = 12
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 76, 0, 0) == 1 then
    mswk61157 = "TALKFONT02/font00/I<190>"
    funcOneMessage(mswk61157)
    mswk61158 = "TALKFONT02/font00/I<211>"
    funcOneMessage(mswk61158)
    g_SItemDB = "weapon"
    g_SItemID = 76
    g_TItemDB = "armor1"
    g_TItemID = 10
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 176, 0, 0) == 1 then
    mswk61159 = "TALKFONT02/font00/I<212>"
    funcOneMessage(mswk61159)
    mswk61160 = "TALKFONT02/font00/I<213>"
    funcOneMessage(mswk61160)
    g_SItemDB = "weapon"
    g_SItemID = 176
    g_TItemDB = "armor2"
    g_TItemID = 9
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 50, 0, 0) == 1 then
    mswk61161 = "TALKFONT02/font00/I<214>"
    funcOneMessage(mswk61161)
    mswk61162 = "TALKFONT02/font00/I<215>"
    funcOneMessage(mswk61162)
    g_SItemDB = "weapon"
    g_SItemID = 50
    g_TItemDB = "weapon"
    g_TItemID = 27
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 37, 0, 0) == 1 then
    mswk61163 = "TALKFONT02/font00/I<216>"
    funcOneMessage(mswk61163)
    mswk61164 = "TALKFONT02/font00/I<217>"
    funcOneMessage(mswk61164)
    g_SItemDB = "weapon"
    g_SItemID = 37
    g_TItemDB = "armor2"
    g_TItemID = 1
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 202, 0, 0) == 1 then
    mswk61165 = "TALKFONT02/font00/I<218>"
    funcOneMessage(mswk61165)
    mswk61166 = "TALKFONT02/font00/I<191>"
    funcOneMessage(mswk61166)
    g_SItemDB = "weapon"
    g_SItemID = 202
    g_TItemDB = "armor2"
    g_TItemID = 36
else
    mswk61167 = "TALKFONT02/font00/I<196>"
    funcOneMessage(mswk61167)
    mswk61168 = "TALKFONT02/font00/I<197>"
    funcOneMessage(mswk61168)
    funcCloseMessage("talk", "n_dorumon", "h")
end
if g_SItemDB ~= 0 then
    mswk61169 = "TALKFONT02/font01/I<71>"
    mswk61170 = "TALKFONT02/font02/I<72>"
    mswk61171 = "TALKFONT02/font00/I<198>"
    mswk61172 = "TALKFONT02/font00/I<199>"
    funcChoiceMessage(mswk61169, mswk61170)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61171)
    be:DMsetLua("itemchange40.lua")
    be:DMcase(1)
    funcOneMessage(mswk61172)
    funcCloseMessage("talk", "n_dorumon", "h")
    be:DMswtEnd()
end
be:DMrun()
