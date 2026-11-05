g_StChangeKind = "run"
if be:MATisAllPlayer() == 1 and be:DMgetCount() == 0 then
    mswk70044 = "STCHGFONT00/font00/I<23>"
    if be:SYSgetDifficulty() == 0 then
        funcStageChange("dngq4b1e", 0, mswk70044, 9)
    elseif be:SYSgetDifficulty() == 1 then
        funcStageChange("dngq4b1h", 0, mswk70044, 9)
    else
        funcStageChange("dngq4b1v", 0, mswk70044, 9)
    end
end
