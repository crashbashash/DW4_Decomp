if not g_Rocksh0 then
    g_Rocksh0 = 0
end
if not g_Rocksh1 then
    g_Rocksh1 = 0
end
if not g_Rocksh2 then
    g_Rocksh2 = 0
end
if not g_Rocksh3 then
    g_Rocksh3 = 0
end
local ramNo = be:MDLgetRamNo()
if be:MDLisCallName("swon") == 1 then
    if ramNo == 0 then
        g_Rocksh0 = 1
    elseif ramNo == 1 then
        g_Rocksh1 = 1
    elseif ramNo == 2 then
        g_Rocksh2 = 1
    elseif ramNo == 3 then
        g_Rocksh3 = 1
    end
elseif be:MDLisCallName("swof") == 1 then
    if ramNo == 0 then
        g_Rocksh0 = 0
    elseif ramNo == 1 then
        g_Rocksh1 = 0
    elseif ramNo == 2 then
        g_Rocksh2 = 0
    elseif ramNo == 3 then
        g_Rocksh3 = 0
    end
end
