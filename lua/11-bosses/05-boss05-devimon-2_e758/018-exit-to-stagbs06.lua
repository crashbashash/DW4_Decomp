g_StChangeKind = "trans"
if be:MATisAllPlayer() == 1 and be:MDLisLive("g_dbossgate", 0) == 1 and be:DMgetCount() == 0 then
    mswk70056 = "STCHGFONT00/font00/I<9>"
    funcStageChange("stagBS06", 0, mswk70056)
end
