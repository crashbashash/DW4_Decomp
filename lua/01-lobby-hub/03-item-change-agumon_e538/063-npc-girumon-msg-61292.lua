g_SItemDB = 0
funcOpenMessage("talk", "n_girumon", "M")
if be:SYSctlFlagFolder("IS", 11) == 1 then
    mswk61292 = "TALKFONT02/font00/I<234>"
    funcOneMessage(mswk61292)
    mswk61293 = "TALKFONT02/font00/I<235>"
    funcOneMessage(mswk61293)
    g_SItemDB = "impItem"
    g_SItemID = 11
    g_TItemDB = "weapon"
    g_TItemID = 35
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 10, 0, 0) == 1 then
    mswk61294 = "TALKFONT02/font00/I<236>"
    funcOneMessage(mswk61294)
    mswk61295 = "TALKFONT02/font00/I<237>"
    funcOneMessage(mswk61295)
    g_SItemDB = "weapon"
    g_SItemID = 10
    g_TItemDB = "weapon"
    g_TItemID = 175
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 60, 0, 0) == 1 then
    mswk61296 = "TALKFONT02/font00/I<238>"
    funcOneMessage(mswk61296)
    mswk61297 = "TALKFONT02/font00/I<239>"
    funcOneMessage(mswk61297)
    g_SItemDB = "weapon"
    g_SItemID = 60
    g_TItemDB = "weapon"
    g_TItemID = 227
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 135, 0, 0) == 1 then
    mswk61298 = "TALKFONT02/font00/I<240>"
    funcOneMessage(mswk61298)
    mswk61299 = "TALKFONT02/font00/I<241>"
    funcOneMessage(mswk61299)
    g_SItemDB = "weapon"
    g_SItemID = 135
    g_TItemDB = "weapon"
    g_TItemID = 1
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 9, 0, 0) == 1 then
    mswk61300 = "TALKFONT02/font00/I<242>"
    funcOneMessage(mswk61300)
    mswk61301 = "TALKFONT02/font00/I<243>"
    funcOneMessage(mswk61301)
    g_SItemDB = "armor2"
    g_SItemID = 9
    g_TItemDB = "armor1"
    g_TItemID = 21
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 176, 0, 0) == 1 then
    mswk61302 = "TALKFONT02/font00/I<244>"
    funcOneMessage(mswk61302)
    mswk61303 = "TALKFONT02/font00/I<245>"
    funcOneMessage(mswk61303)
    g_SItemDB = "weapon"
    g_SItemID = 176
    g_TItemDB = "armor2"
    g_TItemID = 21
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 151, 0, 0) == 1 then
    mswk61304 = "TALKFONT02/font00/I<246>"
    funcOneMessage(mswk61304)
    mswk61305 = "TALKFONT02/font00/I<247>"
    funcOneMessage(mswk61305)
    g_SItemDB = "weapon"
    g_SItemID = 151
    g_TItemDB = "weapon"
    g_TItemID = 141
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 51, 0, 0) == 1 then
    mswk61306 = "TALKFONT02/font00/I<248>"
    funcOneMessage(mswk61306)
    mswk61307 = "TALKFONT02/font00/I<249>"
    funcOneMessage(mswk61307)
    g_SItemDB = "weapon"
    g_SItemID = 51
    g_TItemDB = "armor2"
    g_TItemID = 33
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 28, 0, 0) == 1 then
    mswk61308 = "TALKFONT02/font00/I<250>"
    funcOneMessage(mswk61308)
    mswk61309 = "TALKFONT02/font00/I<251>"
    funcOneMessage(mswk61309)
    g_SItemDB = "weapon"
    g_SItemID = 28
    g_TItemDB = "weapon"
    g_TItemID = 70
else
    mswk61310 = "TALKFONT02/font00/I<252>"
    funcOneMessage(mswk61310)
    mswk61311 = "TALKFONT02/font00/I<253>"
    funcOneMessage(mswk61311)
    funcCloseMessage("talk", "n_girumon", "M")
end
if g_SItemDB ~= 0 then
    mswk61312 = "TALKFONT02/font01/I<71>"
    mswk61313 = "TALKFONT02/font02/I<72>"
    mswk61314 = "TALKFONT02/font00/I<254>"
    mswk61315 = "TALKFONT02/font00/I<255>"
    funcChoiceMessage(mswk61312, mswk61313)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61314)
    be:DMsetLua("itemchange21.lua")
    be:DMcase(1)
    funcOneMessage(mswk61315)
    funcCloseMessage("talk", "n_girumon", "M")
    be:DMswtEnd()
end
be:DMrun()
