be:MDLaddHp(g_headuphp)
if be:MDLisLive("i_bosshp05", 0) == 1 then
    be:sd("METERCTRL", "bshp05", 0, "SETPERCENT", "F<" .. be:MDLgetHp() * 100 / be:MDLgetMHp() .. ">")
end
