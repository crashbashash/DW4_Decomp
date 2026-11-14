if g_SItemDB == "impItem" then
    be:SYSctlFlagFolder("CLR", g_SItemID)
elseif g_SItemDB == "conItem" then
    be:SYSctlDiskFolder("CLR", 0, g_SItemID, 1)
else
    be:SYSctlDeviceFolder("CLR", 0, g_SItemDB, g_SItemID, 0, 0)
end
if g_TItemDB == "impItem" then
    be:SYSctlFlagFolder("SET", g_TItemID)
elseif g_TItemDB == "conItem" then
    be:SYSctlDiskFolder("SET", 0, g_TItemID, 1)
else
    be:SYSctlDeviceFolder("SET", 0, g_TItemDB, g_TItemID, 0, 0)
end
be:FLGset(388, 1)
