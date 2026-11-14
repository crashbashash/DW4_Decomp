be:FLGset(215, 1)
local local_0
if be:SYSgetDifficulty() == 2 then
    local_0 = 2
else
    local_0 = 1
end
be:COUNTERset(3, be:COUNTERget(3) + local_0)
be:sd("NUMBERCTRL", "questnm1", 0, "SETVALUE", "I<" .. be:COUNTERget(3) .. ">")
be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-14")
be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-16")
be:sd("GENERATER", nil, -1, "START", "GENE-19", 1)
