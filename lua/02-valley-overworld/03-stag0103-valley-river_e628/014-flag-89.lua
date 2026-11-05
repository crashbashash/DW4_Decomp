be:MDLsetDMGTurn(0)
if funcTechWazaHitCheck() == 1 then
elseif funcTameWazaHitCheck() == 0 then
    be:MDLaddHp(-20)
    if be:MDLgetHp() >= 20 then
        be:MDLsetSeq("SQ_SDMG")
    elseif be:MDLgetHp() == 0 then
        be:MDLsetSeq("SQ_DDMG")
        if be:MDLisLive("n_digilfm", local_0) == 1 then
            if local_0 == 0 then
                be:sd("MODELCTRL", "n_digilfm", 0, "SQ_THANK", 25)
                be:sd("MODELCTRL", "n_digilfm", 0, "SQ_EXIT", 75)
                be:sd("MODELCTRL", "i_digilfcount", 0, "SQ_OF2ON", 75)
                be:FLGset(89, 1)
            elseif local_0 == 1 then
                be:sd("MODELCTRL", "n_digilfm", 1, "SQ_THANK", 25)
                be:sd("MODELCTRL", "n_digilfm", 1, "SQ_EXIT", 75)
                be:sd("MODELCTRL", "i_digilfcount", 2, "SQ_OF2ON", 75)
                be:FLGset(90, 1)
            elseif local_0 == 2 then
                be:sd("MODELCTRL", "n_digilfm", 2, "SQ_THANK", 25)
                be:sd("MODELCTRL", "n_digilfm", 2, "SQ_EXIT", 75)
                be:sd("MODELCTRL", "i_digilfcount", 1, "SQ_OF2ON", 75)
                be:FLGset(91, 1)
            elseif local_0 == 3 then
                be:sd("MODELCTRL", "n_digilfm", 3, "SQ_THANK", 25)
                be:sd("MODELCTRL", "n_digilfm", 3, "SQ_EXIT", 75)
                be:sd("MODELCTRL", "i_digilfcount", 3, "SQ_OF2ON", 75)
                be:FLGset(92, 1)
            elseif local_0 == 4 then
                be:sd("MODELCTRL", "n_digilfm", 4, "SQ_THANK", 25)
                be:sd("MODELCTRL", "n_digilfm", 4, "SQ_EXIT", 75)
                be:sd("MODELCTRL", "i_digilfcount", 4, "SQ_OF2ON", 75)
                be:FLGset(93, 1)
            elseif local_0 == 5 then
                be:sd("MODELCTRL", "n_digilfm", 5, "SQ_THANK", 25)
                be:sd("MODELCTRL", "n_digilfm", 5, "SQ_EXIT", 75)
                be:sd("MODELCTRL", "i_digilfcount", 5, "SQ_OF2ON", 75)
                be:FLGset(94, 1)
            elseif local_0 == 6 then
                be:sd("MODELCTRL", "n_digilfm", 6, "SQ_THANK", 25)
                be:sd("MODELCTRL", "n_digilfm", 6, "SQ_EXIT", 75)
                be:sd("MODELCTRL", "i_digilfcount", 6, "SQ_OF2ON", 75)
                be:FLGset(95, 1)
            elseif local_0 == 7 then
                be:sd("MODELCTRL", "n_digilfm", 7, "SQ_THANK", 25)
                be:sd("MODELCTRL", "n_digilfm", 7, "SQ_EXIT", 75)
                be:sd("MODELCTRL", "i_digilfcount", 7, "SQ_OF2ON", 75)
                be:FLGset(96, 1)
            elseif local_0 == 8 then
                be:sd("MODELCTRL", "n_digilfm", 8, "SQ_THANK", 25)
                be:sd("MODELCTRL", "n_digilfm", 8, "SQ_EXIT", 75)
                be:sd("MODELCTRL", "i_digilfcount", 8, "SQ_OF2ON", 75)
                be:FLGset(97, 1)
            elseif local_0 == 9 then
                be:sd("MODELCTRL", "n_digilfm", 9, "SQ_THANK", 25)
                be:sd("MODELCTRL", "n_digilfm", 9, "SQ_EXIT", 75)
                be:sd("MODELCTRL", "i_digilfcount", 9, "SQ_OF2ON", 75)
                be:FLGset(98, 1)
            end
        end
    else
    end
end
be:MDLsetSeq("SQ_DDMG")
if be:MDLisLive("n_digilfm", local_0) == 1 then
    if local_0 == 0 then
        be:sd("MODELCTRL", "n_digilfm", 0, "SQ_THANK", 25)
        be:sd("MODELCTRL", "n_digilfm", 0, "SQ_EXIT", 75)
        be:sd("MODELCTRL", "i_digilfcount", 0, "SQ_OF2ON", 75)
        be:FLGset(89, 1)
    elseif local_0 == 1 then
        be:sd("MODELCTRL", "n_digilfm", 1, "SQ_THANK", 25)
        be:sd("MODELCTRL", "n_digilfm", 1, "SQ_EXIT", 75)
        be:sd("MODELCTRL", "i_digilfcount", 2, "SQ_OF2ON", 75)
        be:FLGset(90, 1)
    elseif local_0 == 2 then
        be:sd("MODELCTRL", "n_digilfm", 2, "SQ_THANK", 25)
        be:sd("MODELCTRL", "n_digilfm", 2, "SQ_EXIT", 75)
        be:sd("MODELCTRL", "i_digilfcount", 1, "SQ_OF2ON", 75)
        be:FLGset(91, 1)
    elseif local_0 == 3 then
        be:sd("MODELCTRL", "n_digilfm", 3, "SQ_THANK", 25)
        be:sd("MODELCTRL", "n_digilfm", 3, "SQ_EXIT", 75)
        be:sd("MODELCTRL", "i_digilfcount", 3, "SQ_OF2ON", 75)
        be:FLGset(92, 1)
    elseif local_0 == 4 then
        be:sd("MODELCTRL", "n_digilfm", 4, "SQ_THANK", 25)
        be:sd("MODELCTRL", "n_digilfm", 4, "SQ_EXIT", 75)
        be:sd("MODELCTRL", "i_digilfcount", 4, "SQ_OF2ON", 75)
        be:FLGset(93, 1)
    elseif local_0 == 5 then
        be:sd("MODELCTRL", "n_digilfm", 5, "SQ_THANK", 25)
        be:sd("MODELCTRL", "n_digilfm", 5, "SQ_EXIT", 75)
        be:sd("MODELCTRL", "i_digilfcount", 5, "SQ_OF2ON", 75)
        be:FLGset(94, 1)
    elseif local_0 == 6 then
        be:sd("MODELCTRL", "n_digilfm", 6, "SQ_THANK", 25)
        be:sd("MODELCTRL", "n_digilfm", 6, "SQ_EXIT", 75)
        be:sd("MODELCTRL", "i_digilfcount", 6, "SQ_OF2ON", 75)
        be:FLGset(95, 1)
    elseif local_0 == 7 then
        be:sd("MODELCTRL", "n_digilfm", 7, "SQ_THANK", 25)
        be:sd("MODELCTRL", "n_digilfm", 7, "SQ_EXIT", 75)
        be:sd("MODELCTRL", "i_digilfcount", 7, "SQ_OF2ON", 75)
        be:FLGset(96, 1)
    elseif local_0 == 8 then
        be:sd("MODELCTRL", "n_digilfm", 8, "SQ_THANK", 25)
        be:sd("MODELCTRL", "n_digilfm", 8, "SQ_EXIT", 75)
        be:sd("MODELCTRL", "i_digilfcount", 8, "SQ_OF2ON", 75)
        be:FLGset(97, 1)
    elseif local_0 == 9 then
        be:sd("MODELCTRL", "n_digilfm", 9, "SQ_THANK", 25)
        be:sd("MODELCTRL", "n_digilfm", 9, "SQ_EXIT", 75)
        be:sd("MODELCTRL", "i_digilfcount", 9, "SQ_OF2ON", 75)
        be:sd("MODELCTRL", "i_digilfcount", 9, "SQ_OF2ON", 75)
        be:FLGset(98, 1)
    end
end
