if be:MATisPlayer() == 1 then
    if be:FLGisOn(123) + be:FLGisOn(128) + be:FLGisOn(129) == 3 then
        be:MATsetRun(0)
    elseif be:FLGisOn(137) ~= 1 then
        if be:FLGisOn(123) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", "GENE-04")
            if g_gene04 ~= 1 then
                g_gene04 = 1
                g_mummyStock = g_mummyStock + -1
            end
        end
        if be:FLGisOn(128) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", "GENE-09")
            if g_gene09 ~= 1 then
                g_gene09 = 1
                g_mummyStock = g_mummyStock + -1
            end
        end
        if be:FLGisOn(129) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", "GENE-10")
            if g_gene10 ~= 1 then
                g_gene10 = 1
                g_mummyStock = g_mummyStock + -1
            end
        end
    end
end
