g_StChangeKind = "trans"
if be:MATisAllPlayer() == 1 and be:DMgetCount() == 0 then
    be:FLGset(389, 1)
    mswk70051 = "STCHGFONT00/font00/I<12>"
    funcStageChange("stagML11", 0, mswk70051)
end
