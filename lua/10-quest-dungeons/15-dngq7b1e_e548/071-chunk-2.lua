if be:SYSgetDifficulty() == 2 then
    local_0 = "GENE-02V"
end
if be:MATisPlayer() == 1 then
    if be:FLGisOn(101) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", local_0)
    else
        be:MATsetRun(0)
    end
end
be:sd("GENERATER", nil, -1, "STOP", local_0)
