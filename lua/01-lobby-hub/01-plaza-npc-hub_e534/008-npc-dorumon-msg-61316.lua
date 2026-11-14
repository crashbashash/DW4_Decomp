g_SItemDB = 0
funcOpenMessage("talk", "n_dorumon", "h")
if be:SYSctlFlagFolder("IS", 11) == 1 then
    mswk61316 = "TALKFONT02/font00/I<178>"
    funcOneMessage(mswk61316)
    mswk61317 = "TALKFONT02/font00/I<179>"
    funcOneMessage(mswk61317)
    g_SItemDB = "impItem"
    g_SItemID = 11
    g_TItemDB = "weapon"
    g_TItemID = 60
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 15, 0, 0) == 1 then
    mswk61318 = "TALKFONT02/font00/I<180>"
    funcOneMessage(mswk61318)
    mswk61319 = "TALKFONT02/font00/I<181>"
    funcOneMessage(mswk61319)
    g_SItemDB = "armor2"
    g_SItemID = 15
    g_TItemDB = "weapon"
    g_TItemID = 20
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 10, 0, 0) == 1 then
    mswk61320 = "TALKFONT02/font00/I<182>"
    funcOneMessage(mswk61320)
    mswk61321 = "TALKFONT02/font00/I<183>"
    funcOneMessage(mswk61321)
    g_SItemDB = "weapon"
    g_SItemID = 10
    g_TItemDB = "weapon"
    g_TItemID = 202
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 35, 0, 0) == 1 then
    mswk61322 = "TALKFONT02/font00/I<184>"
    funcOneMessage(mswk61322)
    mswk61323 = "TALKFONT02/font00/I<185>"
    funcOneMessage(mswk61323)
    g_SItemDB = "weapon"
    g_SItemID = 35
    g_TItemDB = "weapon"
    g_TItemID = 200
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 85, 0, 0) == 1 then
    mswk61324 = "TALKFONT02/font00/I<186>"
    funcOneMessage(mswk61324)
    mswk61325 = "TALKFONT02/font00/I<187>"
    funcOneMessage(mswk61325)
    g_SItemDB = "weapon"
    g_SItemID = 85
    g_TItemDB = "weapon"
    g_TItemID = 126
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 201, 0, 0) == 1 then
    mswk61326 = "TALKFONT02/font00/I<188>"
    funcOneMessage(mswk61326)
    mswk61327 = "TALKFONT02/font00/I<189>"
    funcOneMessage(mswk61327)
    g_SItemDB = "weapon"
    g_SItemID = 201
    g_TItemDB = "weapon"
    g_TItemID = 116
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 76, 0, 0) == 1 then
    mswk61328 = "TALKFONT02/font00/I<190>"
    funcOneMessage(mswk61328)
    mswk61329 = "TALKFONT02/font00/I<191>"
    funcOneMessage(mswk61329)
    g_SItemDB = "weapon"
    g_SItemID = 76
    g_TItemDB = "armor2"
    g_TItemID = 36
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 51, 0, 0) == 1 then
    mswk61330 = "TALKFONT02/font00/I<192>"
    funcOneMessage(mswk61330)
    mswk61331 = "TALKFONT02/font00/I<193>"
    funcOneMessage(mswk61331)
    g_SItemDB = "weapon"
    g_SItemID = 51
    g_TItemDB = "weapon"
    g_TItemID = 3
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 78, 0, 0) == 1 then
    mswk61332 = "TALKFONT02/font00/I<194>"
    funcOneMessage(mswk61332)
    mswk61333 = "TALKFONT02/font00/I<195>"
    funcOneMessage(mswk61333)
    g_SItemDB = "weapon"
    g_SItemID = 78
    g_TItemDB = "weapon"
    g_TItemID = 95
else
    mswk61334 = "TALKFONT02/font00/I<196>"
    funcOneMessage(mswk61334)
    mswk61335 = "TALKFONT02/font00/I<197>"
    funcOneMessage(mswk61335)
    funcCloseMessage("talk", "n_dorumon", "h")
end
if g_SItemDB ~= 0 then
    mswk61336 = "TALKFONT02/font01/I<71>"
    mswk61337 = "TALKFONT02/font02/I<72>"
    mswk61338 = "TALKFONT02/font00/I<198>"
    mswk61339 = "TALKFONT02/font00/I<199>"
    funcChoiceMessage(mswk61336, mswk61337)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61338)
    be:DMsetLua("itemchange40.lua")
    be:DMcase(1)
    funcOneMessage(mswk61339)
    funcCloseMessage("talk", "n_dorumon", "h")
    be:DMswtEnd()
end
be:DMrun()
