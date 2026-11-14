be:FLGset(132, 1)
local local_0 = 5
be:COUNTERset(3, be:COUNTERget(3) + local_0)
be:sd("NUMBERCTRL", "questnm1", 0, "SETVALUE", "I<" .. be:COUNTERget(3) .. ">")
if be:SYSgetDifficulty() == 2 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "START", "GENE-11", 1)
end
