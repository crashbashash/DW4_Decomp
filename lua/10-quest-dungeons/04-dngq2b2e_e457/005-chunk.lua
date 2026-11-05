if be:MATisPlayer() == 1 then
    if be:FLGisOn(123) + be:FLGisOn(128) + be:FLGisOn(129) == 3 then
        be:MATsetRun(0)
    elseif be:FLGisOn(137) ~= 1 and g_gene09(1, be:FLGisOn(), be, 129) ~= 1 and g_gene10 ~= 1 then
        g_gene10 = 1
        g_mummyStock = g_mummyStock + -1
    end
end
