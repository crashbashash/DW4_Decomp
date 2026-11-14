if not g_RNo0 then
    g_RNo0 = 0
elseif not g_RN01 then
    g_RN01 = 0
elseif not g_RNo2 then
    g_RNo2 = 0
elseif not g_RNo3 then
    g_RNo3 = 0
end
if be:MDLisCallName("swon") == 1 then
    if be:MDLgetRamNo() == 0 then
        g_RNo0 = 1
    elseif be:MDLgetRamNo() == 1 then
        g_RNo1 = 1
    elseif be:MDLgetRamNo() == 2 then
        g_RNo2 = 1
    elseif be:MDLgetRamNo() == 3 then
        g_RNo3 = 1
    end
elseif be:MDLisCallName("swof") == 1 then
    if be:MDLgetRamNo() == 0 then
        g_RNo0 = 0
    elseif be:MDLgetRamNo() == 1 then
        g_RNo1 = 0
    elseif be:MDLgetRamNo() == 2 then
        g_RNo2 = 0
    elseif be:MDLgetRamNo() == 3 then
        g_RNo3 = 0
    end
end
