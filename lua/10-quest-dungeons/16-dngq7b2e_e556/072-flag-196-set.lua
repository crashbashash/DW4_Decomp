be:FLGset(196, 1)
local local_0 = 1
be:COUNTERset(3, be:COUNTERget(3) + local_0)
be:sd("NUMBERCTRL", "questnm1", 0, "SETVALUE", "I<" .. be:COUNTERget(3) .. ">")
