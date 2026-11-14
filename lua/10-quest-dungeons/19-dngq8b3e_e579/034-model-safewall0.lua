if be:MATisPlayer() == 1 then
    be:sd("HITLANDMODEL", "safewall0", 0, "ONHIT")
else
    be:sd("HITLANDMODEL", "safewall0", 0, "OFFHIT")
end
