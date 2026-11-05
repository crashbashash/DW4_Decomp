if be:MATisPlayer() == 1 then
    if be:FLGisOn(123) + be:FLGisOn(132) + be:FLGisOn(133) == 3 then
        be:MATsetRun(0)
    elseif be:FLGisOn(137) ~= 1 and g_gene13(1, be:FLGisOn(), be, 133) ~= 1 and g_gene14 ~= 1 then
        g_gene14 = 1
        g_mummyStock = g_mummyStock + -1
    end
end
