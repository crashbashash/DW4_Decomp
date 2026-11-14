be:FLGset(201, 1)
local random = be:SYSgetRandom(11)
be:COUNTERset(3, be:COUNTERget(3) + random)
be:sd("NUMBERCTRL", "questnm1", 0, "SETVALUE", "I<" .. be:COUNTERget(3) .. ">")
