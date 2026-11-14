if be:MATisAllPlayer() == 1 then
    be:sd("HITLANDMODEL", "safewall0", 0, "OFFHIT")
else
    be:sd("HITLANDMODEL", "safewall0", 0, "ONHIT")
end
