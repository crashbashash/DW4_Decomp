if not g_count2run then
    g_count2run = 1
else
    g_count2run = g_count2run + 1
end
if g_count2run > 5 then
    g_count2run = 0
    be:MDLsetSeq("SQ_ATCKON")
end
