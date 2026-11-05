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
if be:MDLisCallName("swon") == 1 then
    if local_0 == 0 then
        g_Rocksh0 = 1
    elseif local_0 == 1 then
        g_Rocksh1 = 1
    elseif local_0 == 2 then
        g_Rocksh2 = 1
    elseif local_0 == 3 then
        g_Rocksh3 = 1
    else
    end
end
if be:MDLisCallName("swof") == 1 then
    if local_0 == 0 then
        g_Rocksh0 = 0
    elseif local_0 == 1 then
        g_Rocksh1 = 0
    elseif local_0 == 2 then
        g_Rocksh2 = 0
    elseif local_0 == 3 then
        g_Rocksh3 = 0
    end
end
