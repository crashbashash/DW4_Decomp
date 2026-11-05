if be:SYSgetDifficulty() ~= 2 then
    be:MATsetRun(0)
else
    funcHealGate("HP", "g_dhphealeffect", 0)
end
