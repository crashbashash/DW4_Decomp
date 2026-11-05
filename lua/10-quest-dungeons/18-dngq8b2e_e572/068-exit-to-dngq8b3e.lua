g_StChangeKind = "stay"
if be:MATisAllPlayer() == 1 and be:DMgetCount() == 0 then
    if be:SYSgetDifficulty() == 0 then
        funcStageChange("dngq8b3e", 0)
    elseif be:SYSgetDifficulty() == 1 then
        funcStageChange("dngq8b3h", 0)
    elseif be:SYSgetDifficulty() == 2 then
        funcStageChange("dngq8b3v", 0)
    end
end
