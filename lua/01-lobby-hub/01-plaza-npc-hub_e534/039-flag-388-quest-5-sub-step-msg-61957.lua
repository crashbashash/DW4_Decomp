local skip
if g_SItemDB == "impItem" then
    if be:SYSctlDeviceFolder("ISMAX", 0, nil, 0, 0, 0) == 1 then
        mswk61957 = "TALKFONT02/font00/I<30>"
        funcOneMessage(mswk61957)
        mswk61958 = "TALKFONT02/font00/I<31>"
        funcOneMessage(mswk61958)
        skip = 1
    else
        be:SYSctlFlagFolder("CLR", g_SItemID)
    end
elseif g_SItemDB == "conItem" then
    be:SYSctlDiskFolder("CLR", 0, g_SItemID, 1)
elseif be:SYSctlDeviceFolder("CLR", 0, g_SItemDB, g_SItemID, 0, 0) == 0 then
    skip = 1
    mswk61959 = "TALKFONT02/font00/I<32>"
    funcOneMessage(mswk61959)
    mswk61960 = "TALKFONT02/font00/I<33>"
    funcOneMessage(mswk61960)
end
if skip ~= 1 then
    if g_TItemDB == "impItem" then
        be:SYSctlFlagFolder("SET", g_TItemID)
    elseif g_TItemDB == "conItem" then
        be:SYSctlDiskFolder("SET", 0, g_TItemID, 1)
    else
        be:SYSctlDeviceFolder("SET", 0, g_TItemDB, g_TItemID, 0, 0)
    end
    be:FLGset(388, 1)
end
funcCloseMessage("talk", "n_girumon", "M")
be:DMrun()
