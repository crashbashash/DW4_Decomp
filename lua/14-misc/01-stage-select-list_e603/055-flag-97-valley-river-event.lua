local local_0
local count = 0
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 and be:SYSgetPlayerLevel(playerIndex) >= 16 then
        count = count + 1
    end
end
if count ~= 0 then
    be:FLGset(97, 1)
    be:FLGset(63, 1)
    be:FLGset(98, 1)
    be:FLGset(64, 1)
    mswk80025 = "TALKFONT02/font00/I<41>"
    funcOneMessage(mswk80025)
    funcCloseMessage("talk", "n_digilff", "fWt")
    be:DMrun()
else
    mswk80026 = "TALKFONT02/font00/I<42>"
    funcOneMessage(mswk80026)
    funcCloseMessage("talk", "n_digilff", "fWt")
    be:DMrun()
end
