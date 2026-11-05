if g_SItemDB == "impItem" then
    if be:SYSctlDeviceFolder("ISMAX", 0, nil, 0, 0, 0) == 1 then
        local_0 = 1
    else
        be:SYSctlFlagFolder("CLR", g_SItemID)
    end
end
if g_SItemDB == "conItem" then
    be:SYSctlDiskFolder("CLR", 0, g_SItemID, 1)
elseif be:SYSctlDeviceFolder("CLR", 0, g_SItemDB, g_SItemID, 0, 0) == 0 then
    local_0 = 1
    mswk61982 = "TALKFONT02/font00/I<22>"
    funcOneMessage(mswk61982)
    mswk61983 = "TALKFONT02/font00/I<23>"
    funcOneMessage(mswk61983)
end
if local_0 ~= 1 then
    if g_TItemDB == "impItem" then
        be:SYSctlFlagFolder("SET", g_TItemID)
    elseif g_TItemDB == "conItem" then
        be:SYSctlDiskFolder("SET", 0, g_TItemID, 1)
    else
        be:SYSctlDeviceFolder("SET", 0, g_TItemDB, g_TItemID, 0, 0)
    end
    be:FLGset(388, 1)
end
funcCloseMessage("talk", "n_bwargrey", "BLEH[OC")
be:DMrun()
