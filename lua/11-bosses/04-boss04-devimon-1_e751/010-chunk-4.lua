if not g_devl1b then
    g_devl1b = ""
end
if be:MDLisCallName("pos") == 1 then
    g_devl1b = be:MDLgetPosStr(0, 0, 0)
    g_Ramno = be:MDLgetRamNo()
end
