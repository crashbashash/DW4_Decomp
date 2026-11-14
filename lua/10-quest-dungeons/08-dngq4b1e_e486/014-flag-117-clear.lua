if be:MDLgetRamNo() == 0 then
    be:FLGset(117, 0)
    be:FLGset(119, 1)
elseif be:MDLgetRamNo() == 1 then
    be:FLGset(118, 0)
    be:FLGset(119, 1)
end
