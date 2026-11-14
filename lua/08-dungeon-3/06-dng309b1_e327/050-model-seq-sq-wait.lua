if not g_magicCount then
    g_magicCount = 0
end
if g_magicCount < 4 then
    g_magicCount = g_magicCount + 1
else
    be:MDLsetSeq("SQ_WAIT")
end
