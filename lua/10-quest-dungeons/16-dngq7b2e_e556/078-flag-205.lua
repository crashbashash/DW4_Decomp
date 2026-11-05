be:FLGset(205, 1)
if be:SYSgetDifficulty() == 2 then
    local_0 = 10
else
    local_0 = 5
end
be:COUNTERset(3, be:COUNTERget(3) + local_0)
be:sd("NUMBERCTRL", "questnm1", 0, "SETVALUE", "I<" .. be:COUNTERget(3) .. ">")
