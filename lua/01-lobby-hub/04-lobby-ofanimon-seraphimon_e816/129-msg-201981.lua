mswk201981 = "TALKFONT02/font00/I<29>"
funcOneMessage(mswk201981)
mswk201982 = "TALKFONT02/font00/I<30>"
funcOneMessage(mswk201982)
mswk201983 = "TALKFONT02/font00/I<31>"
funcOneMessage(mswk201983)
mswk201984 = "TALKFONT02/font00/I<32>"
mswk204308 = "TALKFONT02/font00/I<33>"
if be:SYSgetTarget() == 3 then
    funcOneMessage(mswk204308)
else
    funcOneMessage(mswk201984)
end
mswk201985 = "TALKFONT02/font00/I<34>"
funcOneMessage(mswk201985)
mswk201986 = "TALKFONT02/font00/I<35>"
funcOneMessage(mswk201986)
mswk201987 = "TALKFONT02/font00/I<36>"
funcOneMessage(mswk201987)
be:DMsetLua("bML02017.lua")
be:DMrun()
