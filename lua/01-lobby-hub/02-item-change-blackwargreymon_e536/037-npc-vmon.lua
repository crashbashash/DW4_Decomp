if be:SYSgetDifficulty() == 1 then
    funcOpenMessage("talk", "n_vmon", "uC")
    funcOneMessage(mswk61747)
    funcOneMessage(mswk61748)
    funcCloseMessage("talk", "n_vmon", "uC")
else
    funcOpenMessage("talk", "n_vmon", "uC")
    funcOneMessage(mswk61756)
    funcOneMessage(mswk61757)
    funcCloseMessage("talk", "n_vmon", "uC")
end
be:DMrun()
