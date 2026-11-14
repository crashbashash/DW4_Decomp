be:FLGset(211, 1)
local local_0 = 1
be:COUNTERset(3, be:COUNTERget(3) + local_0)
be:sd("NUMBERCTRL", "questnm1", 0, "SETVALUE", "I<" .. be:COUNTERget(3) .. ">")
be:sd("GENERATER", nil, -1, "START", "GENE-15")
