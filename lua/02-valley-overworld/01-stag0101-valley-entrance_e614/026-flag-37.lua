be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 then
    g_sbutton00 = 1
end
if be:MDLgetRamNo() == 1 then
    g_sbutton01 = 1
end
if be:MDLgetRamNo() == 2 then
    g_sbutton02 = 1
end
if be:MDLgetRamNo() == 3 then
    g_sbutton03 = 1
end
if be:FLGisOn(37) == 0 and g_sbutton00 == 1 and g_sbutton01 == 1 and g_sbutton02 == 1 and g_sbutton03 == 1 and g_spdemocheck ~= 1 then
    be:FLGset(37, 1)
end
