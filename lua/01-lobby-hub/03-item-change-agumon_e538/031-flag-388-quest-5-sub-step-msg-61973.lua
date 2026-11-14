local skip
if g_SItemDB == "impItem" then
    if be:SYSctlDeviceFolder("ISMAX", 0, nil, 0, 0, 0) == 1 then
        mswk61973 = "TALKFONT02/font00/I<46>"
        funcOneMessage(mswk61973)
        mswk61974 = "TALKFONT02/font00/I<47>"
        funcOneMessage(mswk61974)
        skip = 1
    else
        be:SYSctlFlagFolder("CLR", g_SItemID)
    end
elseif g_SItemDB == "conItem" then
    be:SYSctlDiskFolder("CLR", 0, g_SItemID, 1)
elseif be:SYSctlDeviceFolder("CLR", 0, g_SItemDB, g_SItemID, 0, 0) == 0 then
    skip = 1
    mswk61975 = "TALKFONT02/font00/I<48>"
    funcOneMessage(mswk61975)
    mswk61976 = "TALKFONT02/font00/I<49>"
    funcOneMessage(mswk61976)
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
funcCloseMessage("talk", "n_agumon", "AO")
be:DMrun()
