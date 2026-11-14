g_StChangeKind = "run"
if be:MATisAllPlayer() == 1 and be:DMgetCount() == 0 then
    mswk70045 = "STCHGFONT00/font00/I<30>"
    if be:SYSgetDifficulty() == 0 then
        funcStageChange("dngq5b1e", 0, mswk70045, 10)
    elseif be:SYSgetDifficulty() == 1 then
        funcStageChange("dngq5b1h", 0, mswk70045, 10)
    else
        funcStageChange("dngq5b1v", 0, mswk70045, 10)
    end
else
end
