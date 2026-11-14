local local_0
be:COUNTERset(2, 0)
for flagNo = 23, 34 do
    be:FLGset(flagNo, 0)
end
for flagNo = 36, 66 do
    be:FLGset(flagNo, 0)
end
for flagNo = 71, 73 do
    be:FLGset(flagNo, 0)
end
be:FLGset(82, 0)
for flagNo = 84, 85 do
    be:FLGset(flagNo, 0)
end
for flagNo = 100, 319 do
    be:FLGset(flagNo, 0)
end
be:FLGset(328, 0)
be:FLGset(334, 0)
for flagNo = 336, 391 do
    be:FLGset(flagNo, 0)
end
be:FLGset(409, 0)
for flagNo = 415, 425 do
    be:FLGset(flagNo, 0)
end
for flagNo = 457, 468 do
    be:FLGset(flagNo, 0)
end
be:FLGset(475, 0)
be:FLGset(477, 0)
be:FLGset(478, 0)
be:FLGset(480, 0)
for flagNo = 481, 500 do
    be:FLGset(flagNo, 0)
end
for flagNo = 514, 517 do
    be:FLGset(flagNo, 0)
end
for flagNo = 562, 566 do
    be:FLGset(flagNo, 0)
end
for flagNo = 571, 575 do
    be:FLGset(flagNo, 0)
end
for flagNo = 593, 594 do
    be:FLGset(flagNo, 0)
end
for flagNo = 598, 610 do
    be:FLGset(flagNo, 0)
end
for flagNo = 0, 11 do
    be:SYSctlFlagFolder("CLR", flagNo)
end
if be:SYSgetDifficulty() == 0 then
    if be:FLGisOn(518) == 1 then
        be:SYSctlFlagFolder("SET", 0)
    end
    if be:FLGisOn(519) == 1 then
        be:SYSctlFlagFolder("SET", 1)
    end
    if be:FLGisOn(520) == 1 then
        be:SYSctlFlagFolder("SET", 2)
    end
    if be:FLGisOn(521) == 1 then
        be:SYSctlFlagFolder("SET", 3)
    end
    if be:FLGisOn(522) == 1 then
        be:SYSctlFlagFolder("SET", 4)
    end
    if be:FLGisOn(523) == 1 then
        be:SYSctlFlagFolder("SET", 5)
    end
    if be:FLGisOn(524) == 1 then
        be:SYSctlFlagFolder("SET", 6)
    end
    if be:FLGisOn(525) == 1 then
        be:SYSctlFlagFolder("SET", 7)
    end
    if be:FLGisOn(526) == 1 then
        be:SYSctlFlagFolder("SET", 8)
    end
    if be:FLGisOn(527) == 1 then
        be:SYSctlFlagFolder("SET", 9)
    end
    if be:FLGisOn(528) == 1 then
        be:SYSctlFlagFolder("SET", 10)
    end
elseif be:SYSgetDifficulty() == 1 then
    if be:FLGisOn(530) == 1 then
        be:SYSctlFlagFolder("SET", 0)
    end
    if be:FLGisOn(531) == 1 then
        be:SYSctlFlagFolder("SET", 1)
    end
    if be:FLGisOn(532) == 1 then
        be:SYSctlFlagFolder("SET", 2)
    end
    if be:FLGisOn(533) == 1 then
        be:SYSctlFlagFolder("SET", 3)
    end
    if be:FLGisOn(534) == 1 then
        be:SYSctlFlagFolder("SET", 4)
    end
    if be:FLGisOn(535) == 1 then
        be:SYSctlFlagFolder("SET", 5)
    end
    if be:FLGisOn(536) == 1 then
        be:SYSctlFlagFolder("SET", 6)
    end
    if be:FLGisOn(537) == 1 then
        be:SYSctlFlagFolder("SET", 7)
    end
    if be:FLGisOn(538) == 1 then
        be:SYSctlFlagFolder("SET", 8)
    end
    if be:FLGisOn(539) == 1 then
        be:SYSctlFlagFolder("SET", 9)
    end
    if be:FLGisOn(540) == 1 then
        be:SYSctlFlagFolder("SET", 10)
    end
elseif be:SYSgetDifficulty() == 2 then
    if be:FLGisOn(542) == 1 then
        be:SYSctlFlagFolder("SET", 0)
    end
    if be:FLGisOn(543) == 1 then
        be:SYSctlFlagFolder("SET", 1)
    end
    if be:FLGisOn(544) == 1 then
        be:SYSctlFlagFolder("SET", 2)
    end
    if be:FLGisOn(545) == 1 then
        be:SYSctlFlagFolder("SET", 3)
    end
    if be:FLGisOn(546) == 1 then
        be:SYSctlFlagFolder("SET", 4)
    end
    if be:FLGisOn(547) == 1 then
        be:SYSctlFlagFolder("SET", 5)
    end
    if be:FLGisOn(548) == 1 then
        be:SYSctlFlagFolder("SET", 6)
    end
    if be:FLGisOn(549) == 1 then
        be:SYSctlFlagFolder("SET", 7)
    end
    if be:FLGisOn(550) == 1 then
        be:SYSctlFlagFolder("SET", 8)
    end
    if be:FLGisOn(551) == 1 then
        be:SYSctlFlagFolder("SET", 9)
    end
    if be:FLGisOn(552) == 1 then
        be:SYSctlFlagFolder("SET", 10)
    end
else
    be:MsgBox("ïÕxÌæ¾É¸sµÜµ½/tOtH_Zbg")
end
if be:SYSgetDifficulty() == 0 then
    for flagNo = 0, 5 do
        be:FLGset(1 + flagNo, be:FLGisOn(700 + flagNo))
    end
    for flagNo = 0, 1 do
        be:FLGset(19 + flagNo, be:FLGisOn(706 + flagNo))
    end
    for flagNo = 0, 3 do
        be:FLGset(67 + flagNo, be:FLGisOn(708 + flagNo))
    end
    be:FLGset(83, be:FLGisOn(712))
    be:FLGset(86, be:FLGisOn(713))
    for flagNo = 0, 10 do
        be:FLGset(89 + flagNo, be:FLGisOn(714 + flagNo))
    end
    for flagNo = 0, 7 do
        be:FLGset(320 + flagNo, be:FLGisOn(725 + flagNo))
    end
    for flagNo = 0, 4 do
        be:FLGset(329 + flagNo, be:FLGisOn(733 + flagNo))
    end
    be:FLGset(335, be:FLGisOn(738))
    be:FLGset(49, be:FLGisOn(801))
    be:FLGset(383, be:FLGisOn(804))
    be:FLGset(82, be:FLGisOn(807))
    be:FLGset(334, be:FLGisOn(810))
elseif be:SYSgetDifficulty() == 1 then
    for flagNo = 0, 5 do
        be:FLGset(1 + flagNo, be:FLGisOn(7 + flagNo))
    end
    for flagNo = 0, 1 do
        be:FLGset(19 + flagNo, be:FLGisOn(741 + flagNo))
    end
    for flagNo = 0, 3 do
        be:FLGset(67 + flagNo, be:FLGisOn(74 + flagNo))
    end
    be:FLGset(83, be:FLGisOn(743))
    be:FLGset(86, be:FLGisOn(87))
    for flagNo = 0, 10 do
        be:FLGset(89 + flagNo, be:FLGisOn(744 + flagNo))
    end
    for flagNo = 0, 7 do
        be:FLGset(320 + flagNo, be:FLGisOn(755 + flagNo))
    end
    for flagNo = 0, 4 do
        be:FLGset(329 + flagNo, be:FLGisOn(763 + flagNo))
    end
    be:FLGset(335, be:FLGisOn(768))
    be:FLGset(49, be:FLGisOn(802))
    be:FLGset(383, be:FLGisOn(805))
    be:FLGset(82, be:FLGisOn(808))
    be:FLGset(334, be:FLGisOn(811))
elseif be:SYSgetDifficulty() == 2 then
    for flagNo = 0, 5 do
        be:FLGset(1 + flagNo, be:FLGisOn(13 + flagNo))
    end
    for flagNo = 0, 1 do
        be:FLGset(19 + flagNo, be:FLGisOn(771 + flagNo))
    end
    for flagNo = 0, 3 do
        be:FLGset(67 + flagNo, be:FLGisOn(78 + flagNo))
    end
    be:FLGset(83, be:FLGisOn(773))
    be:FLGset(86, be:FLGisOn(88))
    for flagNo = 0, 10 do
        be:FLGset(89 + flagNo, be:FLGisOn(774 + flagNo))
    end
    for flagNo = 0, 7 do
        be:FLGset(320 + flagNo, be:FLGisOn(785 + flagNo))
    end
    for flagNo = 0, 4 do
        be:FLGset(329 + flagNo, be:FLGisOn(793 + flagNo))
    end
    be:FLGset(335, be:FLGisOn(798))
    be:FLGset(49, be:FLGisOn(803))
    be:FLGset(383, be:FLGisOn(806))
    be:FLGset(82, be:FLGisOn(809))
    be:FLGset(334, be:FLGisOn(812))
else
    be:MsgBox("ïÕxÌæ¾É¸sµÜµ½/tOtH_Zbg")
end
