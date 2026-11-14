if not g_magic then
    g_magic = 0
end
if not g_switch then
    g_switch = 0
end
if be:MDLgetBulletName() == "ENSP" then
    be:MDLsetDMGTurn(0)
elseif be:MDLgetBulletName() == "PCBA" then
    be:MDLsetSeq("SQ_PUSHED")
else
    if be:BLTisHitCheck() ~= 0 then
        if be:MDLgetBulletBoxNo() == 0 then
        end
    end
    be:MDLsetSeq("SQ_GUARD")
end
