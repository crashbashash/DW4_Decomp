if not g_lifeaid0 then
    g_lifeaid0 = 0
end
if not g_lifeaid1 then
    g_lifeaid1 = 0
end
if not g_lifeaid2 then
    g_lifeaid2 = 0
end
if not g_lifeaid3 then
    g_lifeaid3 = 0
end
if be:MDLisCallName("setaid") == 1 then
    if be:MDLgetRamNo() == 0 then
        g_lifeaid0 = 0
    elseif be:MDLgetRamNo() == 1 then
        g_lifeaid1 = 0
    elseif be:MDLgetRamNo() == 2 then
        g_lifeaid2 = 0
    elseif be:MDLgetRamNo() == 3 then
        g_lifeaid3 = 0
    end
elseif be:MDLisCallName("switch") == 1 then
    if be:MDLgetRamNo() == 0 then
        g_lifeaid0 = 1
    elseif be:MDLgetRamNo() == 1 then
        g_lifeaid1 = 1
    elseif be:MDLgetRamNo() == 2 then
        g_lifeaid2 = 1
    elseif be:MDLgetRamNo() == 3 then
        g_lifeaid3 = 1
    end
elseif be:MDLisCallName("aid") == 1 then
    be:MDLaddHp(be:MDLgetMHp() / 2)
    if be:MDLgetRamNo() == 0 and g_lifeaid0 == 1 then
        g_lifeaid0 = 2
    elseif be:MDLgetRamNo() == 1 and g_lifeaid1 == 1 then
        g_lifeaid1 = 2
    elseif be:MDLgetRamNo() == 2 and g_lifeaid2 == 1 then
        g_lifeaid2 = 2
    elseif be:MDLgetRamNo() == 3 and g_lifeaid3 == 1 then
        g_lifeaid3 = 2
    end
end
