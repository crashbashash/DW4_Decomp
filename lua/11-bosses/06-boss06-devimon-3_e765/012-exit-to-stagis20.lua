g_StChangeKind = "trans"
if be:MATisAllPlayer() == 1 and be:MDLisLive("g_dreturngate", 0) == 1 and be:DMgetCount() == 0 then
    mswk70027 = "STCHGFONT00/font00/I<9>"
    funcStageChange("stagIS20", 0, mswk70027)
end
