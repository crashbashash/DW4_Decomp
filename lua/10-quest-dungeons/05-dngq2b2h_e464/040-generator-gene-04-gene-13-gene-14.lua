if be:MATisPlayer() == 1 then
    if be:FLGisOn(123) + be:FLGisOn(132) + be:FLGisOn(133) == 3 then
        be:MATsetRun(0)
    elseif be:FLGisOn(137) ~= 1 then
        if be:FLGisOn(123) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", "GENE-04")
            if g_gene04 ~= 1 then
                g_gene04 = 1
                g_mummyStock = g_mummyStock + -1
            end
        end
        if be:FLGisOn(132) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", "GENE-13")
            if g_gene13 ~= 1 then
                g_gene13 = 1
                g_mummyStock = g_mummyStock + -1
            end
        end
        if be:FLGisOn(133) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", "GENE-14")
            if g_gene14 ~= 1 then
                g_gene14 = 1
                g_mummyStock = g_mummyStock + -1
            end
        end
    end
end
