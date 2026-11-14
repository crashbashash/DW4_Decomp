be:FLGset(194, 1)
local local_0
if be:SYSgetDifficulty() == 0 then
    local_0 = 2
else
    local_0 = 1
end
be:COUNTERset(3, be:COUNTERget(3) + local_0)
be:sd("NUMBERCTRL", "questnm1", 0, "SETVALUE", "I<" .. be:COUNTERget(3) .. ">")
