if g_UFOPos == 0 then
    be:MDLsetWorldPosTarget("V<40.0,10.0,-40.0>/V<0.0,0.0,0.0>")
elseif g_UFOPos == 1 then
    be:MDLsetWorldPosTarget("V<40.0,10.0,40.0>/V<0.0,0.0,0.0>")
elseif g_UFOPos == 2 then
    be:MDLsetWorldPosTarget("V<-40.0,10.0,40.0>/V<0.0,0.0,0.0>")
elseif g_UFOPos == 3 then
    be:MDLsetWorldPosTarget("V<-40.0,10.0,-40.0>/V<0.0,0.0,0.0>")
end
