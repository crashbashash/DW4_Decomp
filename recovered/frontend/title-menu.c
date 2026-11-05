/* Behavioral reconstruction of beNDMWTitle2::vfunc_31, 0x003f2ef0.
 * NOT a byte-matched translation unit. The object-creation/reference-counting
 * prologue belongs to the target runtime; this entry takes its initialized CTRL
 * and OPTION records. See README.md for the exact boundary and verification.
 * Field names are recovered reflection names; T_* tokens are retail strings.
 */
#include "title-menu.h"

void dw4_title_tick(Dw4TitleCtrl *ctrl, Dw4TitleOption *option,
                    const Dw4TitleInput *pad, int run_requested,
                    const Dw4TitleApi *api)
{
    int temp_a0_10;
    int temp_a0_11;
    int temp_a0_5;
    int temp_a0_6;
    int temp_a0_7;
    int temp_a0_9;
    int temp_a1_10;
    int temp_a1_11;
    int temp_a1_2;
    int temp_a1_3;
    int temp_a1_4;
    int temp_a1_5;
    int temp_a1_6;
    int temp_a1_7;
    int temp_a1_8;
    int temp_a1_9;
    int temp_s1_2;
    int temp_s1_3;
    int temp_s2_2;
    int temp_s2_3;
    int pressed;
    int temp_v0_4;
    int temp_v0_5;
    int temp_v0_6;
    int temp_v0_7;
    int temp_v1_10;
    int temp_v1_11;
    int temp_v1_12;
    int temp_v1_13;
    int temp_v1_14;
    int temp_v1_15;
    int temp_v1_16;
    int temp_v1_2;
    int temp_v1_3;
    int temp_v1_4;
    int temp_v1_5;
    int temp_v1_6;
    int temp_v1_7;
    int temp_v1_8;
    int temp_v1_9;
    int var_s0;
    int var_s0_2;
    int up;
    int down;
    int var_v1;
    int var_v1_2;
    int var_v1_3;
    int var_v1_4;
    int var_v1_5;
    int var_v1_6;
    int var_v1_7;
    int var_v1_8;
    int left = ((pad->direction_a | pad->direction_b) & 8) ||
               ((pad->pressed | pad->button_secondary) & 0x80);
    int right = ((pad->direction_a | pad->direction_b) & 2) ||
               ((pad->pressed | pad->button_secondary) & 0x20);
    up = ((pad->direction_a | pad->direction_b) & 1) ||
             ((pad->pressed | pad->button_secondary) & 0x10);
    down = ((pad->direction_a | pad->direction_b) & 4) ||
             ((pad->pressed | pad->button_secondary) & 0x40);
    pressed = pad->pressed;
    api->model_tick(api->user);
    temp_v1_2 = ctrl->_st0;
    switch (temp_v1_2) {
    case 0: /* Wait for TITLE2 RUN. */
        if (run_requested == 1) {
            ctrl->_st0 = 1U;
            ctrl->_st3 = 0;
            ctrl->_st2 = 0;
            ctrl->_st1 = 0;
            return;
        }
    default:
        return;
    case 1: /* Logo, Press START and the attract-loop handoff. */
        temp_a1_2 = ctrl->_st1;
        switch (temp_a1_2) {
        case 0:
            ctrl->_st1 = ctrl->_st1 + 1;
            ctrl->_st3 = 0;
            ctrl->_st2 = 0;
            return;
        case 1:
            temp_v1_3 = ctrl->_st2;
            switch (temp_v1_3) {
            case 0:
                if ((api->model_exists(api->user, 0, T_j_startlogo) & 0xFF) != 1) {
                    api->model_start(api->user, 0, T_j_startlogo, T_SQ_OPEN, 1);
                }
                ctrl->_st2 = ctrl->_st2 + 1;
                ctrl->_st3 = 0;
                return;
            case 1:
                if ((api->opening_done(api->user) & 0xFF) == 1) {
                    ctrl->_st1 = ctrl->_st1 + 1;
                    ctrl->_st3 = 0;
                    ctrl->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        case 2:
            temp_v1_4 = ctrl->_st2;
            switch (temp_v1_4) {
            case 0:
                temp_v1_5 = ctrl->_st3;
                switch (temp_v1_5) {
                case 0:
                    api->model_start(api->user, 0, T_j_startmenu01, T_SQ_OPEN, 1);
                    ctrl->_st3 = ctrl->_st3 + 1;
                    return;
                case 1:
                    if ((api->opening_done(api->user) & 0xFF) == 1) {
                        ctrl->_st2 = ctrl->_st2 + 1;
                        ctrl->_st3 = 0;
                        return;
                    }
                    break;
                }
                break;
            case 1:
                temp_a1_3 = ctrl->_st3;
                switch (temp_a1_3) {
                case 0x0:
                    if (pressed & 8) {
                        ctrl->_st2 = ctrl->_st2 + 1;
                        ctrl->_st3 = 0;
                        return;
                    }
                    api->message_begin(api->user, T_MODELCTRL, T_j_startmenu01, 0);
                    api->push_string(api->user, T_SQ_LINESL00);
                    api->message_end(api->user, T_ISSEQNAME);
                    if ((api->read_bool(api->user, 0) & 0xFF) != 1) {
                        ctrl->_st3 = 0x3E8;
                        return;
                    }
                    break;
                case 0x3E8:
                    ctrl->_st3 = 0x3E9;
                    api->message_send(api->user, T_MODELCTRL, T_i_fadewn01, 0, T_GENERATE);
                    api->message_send(api->user, T_MODELCTRL, T_i_fadewn01, 0, T_SQ_BLOUT30);
                    return;
                case 0x3E9:
                    api->message_send(api->user, T_MODELCTRL, T_j_startmenu01, 0, T_ISRUN);
                    if (!(api->read_bool(api->user, 0) & 0xFF)) {
                        ctrl->_st3 = 0x3EA;
                        return;
                    }
                    break;
                case 0x3EA:
                    api->message_target(api->user, T_STAGECTL);
                    api->push_string(api->user, T_stagIS09);
                    api->message_end(api->user, T_NEXTSTAGE);
                    ctrl->_st3 = 0x3EB;
                    return;
                }
                break;
            case 2:
                temp_v1_6 = ctrl->_st3;
                switch (temp_v1_6) {
                case 0:
                    api->model_close(api->user, 0, T_j_startmenu01, T_SQ_LINEON00, 1);
                    ctrl->_st3 = ctrl->_st3 + 1;
                    return;
                case 1:
                    if ((api->closing_done(api->user) & 0xFF) == 1) {
                        ctrl->_st0 = 2U;
                        ctrl->_st3 = 0;
                        ctrl->_st2 = 0;
                        ctrl->_st1 = 0;
                        return;
                    }
                    break;
                }
                break;
            }
            break;
        }
        break;
    case 2: /* Game Start / Option, including animation waits. */
        temp_v1_7 = ctrl->_st1;
        switch (temp_v1_7) {
        case 0:
            temp_v1_8 = ctrl->_st2;
            switch (temp_v1_8) {
            case 0:
                api->model_start(api->user, 0, T_j_startmenu02, T_SQ_OPEN, 1);
                ctrl->_st2 = ctrl->_st2 + 1;
                ctrl->_st3 = 0;
                return;
            case 1:
                if ((api->opening_done(api->user) & 0xFF) == 1) {
                    ctrl->_st1 = ctrl->_st1 + 1;
                    ctrl->_st3 = 0;
                    ctrl->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        case 1:
            temp_a0_5 = ctrl->_st2;
            switch (temp_a0_5) {
            case 0:
                ctrl->_gameMenuCnt = 0;
                ctrl->_gameMenuNext = 0;
                ctrl->_st2 = ctrl->_st2 + 1;
                ctrl->_st3 = 0;
                return;
            case 1:
                if (up != 0) {
                    if (ctrl->_gameMenuCnt == 1) {
                        ctrl->_gameMenuCnt = 0;
                        api->model_play(api->user, 0, T_j_startmenu02, T_SQ_LINEUP00, 1);
                    }
                    ctrl->_st2 = ctrl->_st2 + 1;
                    ctrl->_st3 = 0;
                    return;
                }
                if (down != 0) {
                    if (ctrl->_gameMenuCnt == 0) {
                        ctrl->_gameMenuCnt = 1;
                        api->model_play(api->user, 0, T_j_startmenu02, T_SQ_LINEDW01, 1);
                    }
                    ctrl->_st2 = ctrl->_st2 + 1;
                    ctrl->_st3 = 0;
                    return;
                }
                if (pressed & 0x4000) {
                    if (ctrl->_gameMenuCnt == 0) {
                        api->model_play(api->user, 0, T_j_startmenu02, T_SQ_LINEON00, 1);
                        ctrl->_gameMenuNext = 1;
                    } else {
                        api->model_play(api->user, 0, T_j_startmenu02, T_SQ_LINEON01, 1);
                        ctrl->_gameMenuNext = 2;
                    }
                    ctrl->_st2 = ctrl->_st2 + 1;
                    ctrl->_st3 = 0;
                    return;
                }
                if (pressed & 0x2000) {
                    api->model_close(api->user, 0, T_j_startmenu02, T_SQ_CANCEL, 1);
                    ctrl->_st2 = 3;
                    ctrl->_st3 = 0;
                    return;
                }
                break;
            case 2:
                temp_v1_9 = ctrl->_st3;
                switch (temp_v1_9) {
                case 0:
                    if ((api->opening_done(api->user) & 0xFF) == 1) {
                        temp_a0_6 = ctrl->_gameMenuNext;
                        switch (temp_a0_6) {
                        case 0:
                            ctrl->_st2 = 1;
                            ctrl->_st3 = 0;
                            return;
                        case 2:
                        case 1:
                            api->model_close(api->user, 0, T_j_startlogo, T_SQ_CLOSE, 1);
                            ctrl->_st3 = ctrl->_st3 + 1;
                            return;
                        case 3:
                            ctrl->_st0 = 1U;
                            ctrl->_st3 = 0;
                            ctrl->_st2 = 0;
                            ctrl->_st1 = 0;
                            return;
                        }
                    }
                    break;
                case 1:
                    if ((api->closing_done(api->user) & 0xFF) == 1) {
                        temp_a0_7 = ctrl->_gameMenuNext;
                        switch (temp_a0_7) {
                        case 1:
                            ctrl->_st0 = 7U;
                            ctrl->_st3 = 0;
                            ctrl->_st2 = 0;
                            ctrl->_st1 = 0;
                            return;
                        case 2:
                            ctrl->_st0 = 4U;
                            ctrl->_st3 = 0;
                            ctrl->_st2 = 0;
                            ctrl->_st1 = 0;
                            return;
                        }
                    }
                    break;
                }
                break;
            case 3:
                if ((api->closing_done(api->user) & 0xFF) == 1) {
                    ctrl->_st0 = 1U;
                    ctrl->_st3 = 0;
                    ctrl->_st2 = 0;
                    ctrl->_st1 = 0;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 4: /* Settings window, cursor, text and exit. */
        temp_a1_4 = ctrl->_st1;
        switch (temp_a1_4) {
        case 0:
            temp_v1_10 = ctrl->_st2;
            switch (temp_v1_10) {
            case 0:
                if (option->_comConf == 0) {
                    option->_dispComConf = 0;
                } else {
                    option->_dispComConf = 1;
                }
                if (option->_lightConf == 0) {
                    option->_dispLightConf = 0;
                } else {
                    option->_dispLightConf = 1;
                }
                option->_oldCountry = 1;
                option->_dispCountryConf = 1U;
                temp_v1_11 = option->_selLang;
                switch (temp_v1_11) {
                case 0:
                    api->model_start(api->user, 0, T_j_optionwin02, T_SQ_BOPEN, 1);
                    break;
                case 2:
                case 1:
                    api->model_start(api->user, 0, T_j_optionwin02, T_SQ_AOPEN, 1);
                    break;
                }
                api->model_start(api->user, 0, T_j_optioncursor11, T_SQ_OPEN, 1);
                api->model_start(api->user, 0, T_j_optioncursor12, T_SQ_OPEN, 1);
                option->_ctrlPos = 0;
                option->_isOK = 0U;
                ctrl->_st2 = ctrl->_st2 + 1;
                ctrl->_st3 = 0;
                return;
            case 1:
                if ((api->opening_done(api->user) & 0xFF) == 1) {
                    api->text_show(api->user, 0xF0001, 0);
                    if (option->_selLang != 0) {
                        api->text_show(api->user, 0xF0006, 0);
                        temp_v0_4 = option->_dispCountryConf;
                        switch (temp_v0_4) {
                        default:
                            api->text_show(api->user, 0xF0007, 0);
                            break;
                        case 1:
                            api->text_show(api->user, 0xF0008, 0);
                            break;
                        case 2:
                            api->text_show(api->user, 0xF0009, 0);
                            break;
                        case 3:
                            api->text_show(api->user, 0xF000A, 0);
                            break;
                        case 4:
                            api->text_show(api->user, 0xF000C, 0);
                            break;
                        case 5:
                            api->text_show(api->user, 0xF000B, 0);
                            break;
                        case 6:
                            api->text_show(api->user, 0xF000D, 0);
                            break;
                        }
                    }
                    if (option->_dispComConf == 0) {
                        api->text_show(api->user, 0xF0002, 0);
                    } else {
                        api->text_show(api->user, 0xF0003, 0);
                    }
                    if (option->_dispLightConf == 0) {
                        api->text_show(api->user, 0xF0004, 0);
                    } else {
                        api->text_show(api->user, 0xF0005, 0);
                    }
                    ctrl->_st1 = ctrl->_st1 + 1;
                    ctrl->_st3 = 0;
                    ctrl->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        case 1:
            temp_a1_5 = ctrl->_st2;
            switch (temp_a1_5) {
            case 0:
                if (up != 0) {
                    temp_a1_6 = option->_selLang;
                    var_s0 = option->_ctrlPos;
                    switch (temp_a1_6) {
                    case 0:
                        if (var_s0 == 3) {
                            var_s0 = 1;
                            api->model_play(api->user, 0, T_j_optioncursor11, T_SQ_MOVE, 1);
                            ctrl->_st2 = ctrl->_st2 + 1;
                            goto block_292;
                        }
                        if (var_s0 != 0) {
                            var_s0 = 0;
                            api->model_play(api->user, 0, T_j_optioncursor11, T_SQ_MOVE, 1);
                            ctrl->_st2 = ctrl->_st2 + 1;
block_292:
                            ctrl->_st3 = 0;
                        }
                        break;
                    case 2:
                    case 1:
                        var_s0 -= 1;
                        if (var_s0 < 0) {
                            var_s0 = 0;
                        } else {
                            api->model_play(api->user, 0, T_j_optioncursor11, T_SQ_MOVE, 1);
                            ctrl->_st2 = ctrl->_st2 + 1;
                            goto block_292;
                        }
                        break;
                    }
                    option->_ctrlPos = var_s0;
                    return;
                }
                if (down != 0) {
                    temp_a1_7 = option->_selLang;
                    var_s0_2 = option->_ctrlPos;
                    switch (temp_a1_7) {
                    case 0:
                        if ((var_s0_2 + 1) == 2) {
                            var_s0_2 = 3;
                            api->model_play(api->user, 0, T_j_optioncursor11, T_SQ_MOVE, 1);
                            ctrl->_st2 = ctrl->_st2 + 1;
                            goto block_305;
                        }
                        /* fall through */
                    case 2:
                    case 1:
                        var_s0_2 += 1;
                        if (var_s0_2 >= 4) {
                            var_s0_2 = 3;
                        } else {
                            api->model_play(api->user, 0, T_j_optioncursor11, T_SQ_MOVE, 1);
                            ctrl->_st2 = ctrl->_st2 + 1;
block_305:
                            ctrl->_st3 = 0;
                        }
                        break;
                    }
                    option->_ctrlPos = var_s0_2;
                    return;
                }
                if (right != 0) {
                    temp_a1_8 = option->_ctrlPos;
                    switch (temp_a1_8) {
                    case 0:
                        api->model_play(api->user, 0, T_j_optioncursor12, T_SQ_LINERT00, 1);
                        var_v1 = option->_dispComConf + 1;
                        if (var_v1 >= 2) {
                            var_v1 = 0;
                        }
                        option->_dispComConf = var_v1;
                        ctrl->_st2 = ctrl->_st2 + 1;
                        ctrl->_st3 = 0;
                        return;
                    case 1:
                        api->model_play(api->user, 0, T_j_optioncursor12, T_SQ_LINERT01, 1);
                        var_v1_2 = option->_dispLightConf + 1;
                        if (var_v1_2 >= 2) {
                            var_v1_2 = 0;
                        }
                        option->_dispLightConf = var_v1_2;
                        ctrl->_st2 = ctrl->_st2 + 1;
                        ctrl->_st3 = 0;
                        return;
                    case 2:
                        api->model_play(api->user, 0, T_j_optioncursor12, T_SQ_LINERT02, 1);
                        temp_a1_9 = option->_selLang;
                        switch (temp_a1_9) {
                        case 1:
                            var_v1_3 = option->_dispCountryConf + 1;
                            if (var_v1_3 >= 7) {
                                var_v1_3 = 2;
                            }
                            option->_dispCountryConf = (var_v1_3);
                            break;
                        case 2:
                            var_v1_4 = option->_dispCountryConf + 1;
                            if (var_v1_4 >= 7) {
                                var_v1_4 = 0;
                            }
                            option->_dispCountryConf = (var_v1_4);
                            break;
                        }
                        ctrl->_st2 = ctrl->_st2 + 1;
                        ctrl->_st3 = 0;
                        return;
                    }
                } else if (left != 0) {
                    temp_a1_10 = option->_ctrlPos;
                    switch (temp_a1_10) {
                    case 0:
                        api->model_play(api->user, 0, T_j_optioncursor12, T_SQ_LINELF00, 1);
                        var_v1_5 = option->_dispComConf - 1;
                        if (var_v1_5 < 0) {
                            var_v1_5 = 1;
                        }
                        option->_dispComConf = var_v1_5;
                        ctrl->_st2 = ctrl->_st2 + 1;
                        ctrl->_st3 = 0;
                        return;
                    case 1:
                        api->model_play(api->user, 0, T_j_optioncursor12, T_SQ_LINELF01, 1);
                        var_v1_6 = option->_dispLightConf - 1;
                        if (var_v1_6 < 0) {
                            var_v1_6 = 1;
                        }
                        option->_dispLightConf = var_v1_6;
                        ctrl->_st2 = ctrl->_st2 + 1;
                        ctrl->_st3 = 0;
                        return;
                    case 2:
                        api->model_play(api->user, 0, T_j_optioncursor12, T_SQ_LINELF02, 1);
                        temp_a0_9 = option->_selLang;
                        switch (temp_a0_9) {
                        case 1:
                            var_v1_7 = option->_dispCountryConf - 1;
                            if (var_v1_7 < 2) {
                                var_v1_7 = 6;
                            }
                            option->_dispCountryConf = (var_v1_7);
                            break;
                        case 2:
                            var_v1_8 = option->_dispCountryConf - 1;
                            if (var_v1_8 < 0) {
                                var_v1_8 = 6;
                            }
                            option->_dispCountryConf = (var_v1_8);
                            break;
                        }
                        ctrl->_st2 = ctrl->_st2 + 1;
                        ctrl->_st3 = 0;
                        return;
                    }
                } else {
                    if (pressed & 0x4000) {
                        if (option->_ctrlPos != 3) {
                            return;
                        }
                        option->_isOK = 1U;
                        ctrl->_st1 = ctrl->_st1 + 1;
                        ctrl->_st3 = 0;
                        ctrl->_st2 = 0;
                        return;
                    }
                    if (pressed & 0x2000) {
                        option->_isOK = 1U;
                        ctrl->_st1 = ctrl->_st1 + 1;
                        ctrl->_st3 = 0;
                        ctrl->_st2 = 0;
                        return;
                    }
                }
                break;
            case 1:
                if ((api->opening_done(api->user) & 0xFF) == 1) {
                    temp_v1_12 = option->_ctrlPos;
                    switch (temp_v1_12) {
                    case 0:
                        api->model_play(api->user, 0, T_j_optioncursor11, T_SQ_LINESL00, 0);
                        break;
                    case 1:
                        api->model_play(api->user, 0, T_j_optioncursor11, T_SQ_LINESL01, 0);
                        break;
                    case 2:
                        api->model_play(api->user, 0, T_j_optioncursor11, T_SQ_LINESL02, 0);
                        break;
                    case 3:
                        api->model_play(api->user, 0, T_j_optioncursor11, T_SQ_LINESL03, 0);
                        break;
                    }
                    temp_v1_13 = option->_ctrlPos;
                    switch (temp_v1_13) {
                    case 0:
                        if ((api->model_exists(api->user, 0, T_j_optioncursor12) & 0xFF) == 1) {
                            api->model_play(api->user, 0, T_j_optioncursor12, T_SQ_LINESL00, 0);
                        } else {
                            api->model_start(api->user, 0, T_j_optioncursor12, T_SQ_LINESL00, 0);
                        }
                        break;
                    case 1:
                        if ((api->model_exists(api->user, 0, T_j_optioncursor12) & 0xFF) == 1) {
                            api->model_play(api->user, 0, T_j_optioncursor12, T_SQ_LINESL01, 0);
                        } else {
                            api->model_start(api->user, 0, T_j_optioncursor12, T_SQ_LINESL01, 0);
                        }
                        break;
                    case 2:
                        if ((api->model_exists(api->user, 0, T_j_optioncursor12) & 0xFF) == 1) {
                            api->model_play(api->user, 0, T_j_optioncursor12, T_SQ_LINESL02, 0);
                        } else {
                            api->model_start(api->user, 0, T_j_optioncursor12, T_SQ_LINESL02, 0);
                        }
                        break;
                    case 3:
                        if ((api->model_exists(api->user, 0, T_j_optioncursor12) & 0xFF) == 1) {
                            api->model_close(api->user, 0, T_j_optioncursor12, T_SQ_CLOSE, 0);
                        }
                        break;
                    }
                    if (option->_selLang != 0) {
                        api->text_show(api->user, 0xF0006, 0);
                        temp_v0_5 = option->_dispCountryConf;
                        switch (temp_v0_5) {
                        default:
                            api->text_show(api->user, 0xF0007, 0);
                            break;
                        case 1:
                            api->text_show(api->user, 0xF0008, 0);
                            break;
                        case 2:
                            api->text_show(api->user, 0xF0009, 0);
                            break;
                        case 3:
                            api->text_show(api->user, 0xF000A, 0);
                            break;
                        case 4:
                            api->text_show(api->user, 0xF000C, 0);
                            break;
                        case 5:
                            api->text_show(api->user, 0xF000B, 0);
                            break;
                        case 6:
                            api->text_show(api->user, 0xF000D, 0);
                            break;
                        }
                    }
                    if (option->_dispComConf == 0) {
                        api->text_show(api->user, 0xF0002, 0);
                    } else {
                        api->text_show(api->user, 0xF0003, 0);
                    }
                    if (option->_dispLightConf == 0) {
                        api->text_show(api->user, 0xF0004, 0);
                    } else {
                        api->text_show(api->user, 0xF0005, 0);
                    }
                    ctrl->_st2 = 0;
                    ctrl->_st3 = 0;
                    return;
                }
                break;
            }
            break;
        case 2:
            temp_a1_11 = ctrl->_st2;
            switch (temp_a1_11) {
            case 0:
                temp_v0_6 = option->_ctrlPos;
                switch (temp_v0_6) {
                case 0:
                    api->model_close(api->user, 0, T_j_optioncursor11, T_SQ_LINEON00, 1);
                    break;
                case 1:
                    api->model_close(api->user, 0, T_j_optioncursor11, T_SQ_LINEON01, 1);
                    break;
                case 2:
                    api->model_close(api->user, 0, T_j_optioncursor11, T_SQ_LINEON02, 1);
                    break;
                case 3:
                    api->model_close(api->user, 0, T_j_optioncursor11, T_SQ_LINEON03, 1);
                    break;
                }
                temp_v1_14 = option->_ctrlPos;
                switch (temp_v1_14) {
                case 0:
                    api->model_close(api->user, 0, T_j_optioncursor12, T_SQ_CLOSE, 1);
                    break;
                case 1:
                    api->model_close(api->user, 0, T_j_optioncursor12, T_SQ_CLOSE, 1);
                    break;
                case 2:
                    api->model_close(api->user, 0, T_j_optioncursor12, T_SQ_CLOSE, 1);
                    break;
                }
                api->text_hide(api->user, 0xF0001);
                if (option->_selLang != 0) {
                    api->text_hide(api->user, 0xF0006);
                    api->text_hide(api->user, 0xF000D);
                }
                api->text_hide(api->user, 0xF0002);
                api->text_hide(api->user, 0xF0005);
                ctrl->_st2 = ctrl->_st2 + 1;
                ctrl->_st3 = 0;
                return;
            case 1:
                if ((api->closing_done(api->user) & 0xFF) == 1) {
                    ctrl->_st2 = ctrl->_st2 + 1;
                    ctrl->_st3 = 0;
                    return;
                }
                break;
            case 2:
                api->model_close(api->user, 0, T_j_optionwin02, T_SQ_CLOSE, 1);
                ctrl->_st2 = ctrl->_st2 + 1;
                ctrl->_st3 = 0;
                return;
            case 3:
                if ((api->closing_done(api->user) & 0xFF) == 1) {
                    if (option->_isOK == 1) {
                        option->_comConf = option->_dispComConf;
                        option->_lightConf = option->_dispLightConf;
                    }
                    if (option->_oldCountry != 1) {
                        ctrl->_st1 = 0x32;
                        ctrl->_st3 = 0;
                        ctrl->_st2 = 0;
                        return;
                    }
                    ctrl->_st1 = ctrl->_st1 + 1;
                    ctrl->_st3 = 0;
                    ctrl->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        case 3:
            temp_v1_15 = ctrl->_st2;
            switch (temp_v1_15) {
            case 0:
                api->model_start(api->user, 0, T_j_startlogo, T_SQ_OPEN, 1);
                ctrl->_st2 = ctrl->_st2 + 1;
                ctrl->_st3 = 0;
                return;
            case 1:
                if ((api->opening_done(api->user) & 0xFF) == 1) {
                    ctrl->_st0 = 2U;
                    ctrl->_st3 = 0;
                    ctrl->_st2 = 0;
                    ctrl->_st1 = 0;
                    return;
                }
                break;
            }
            break;
        case 50:
            temp_a0_10 = ctrl->_st2;
            switch (temp_a0_10) {
            case 0:
                ctrl->_st2 = 1;
                ctrl->_st3 = 0;
                api->message_send(api->user, T_MODELCTRL, T_i_fadewn01, 0, T_GENERATE);
                api->message_send(api->user, T_MODELCTRL, T_i_fadewn01, 0, T_SQ_BLOUT30);
                return;
            case 1:
                api->message_send(api->user, T_MODELCTRL, T_j_startmenu01, 0, T_ISRUN);
                if (!(api->read_bool(api->user, 0) & 0xFF)) {
                    ctrl->_st2 = 2;
                    ctrl->_st3 = 0;
                    return;
                }
                break;
            case 2:
                api->message_common(api->user, T_GAMERAM, T_GETCOMMON);
                temp_v0_7 = api->read_object(api->user, 0);
                temp_s2_2 = option->_comConf;
                temp_s1_2 = option->_lightConf;
                api->set_record(api->user, temp_v0_7, T_CAMERAMODE, temp_s2_2);
                api->set_record(api->user, temp_v0_7, T_LIGHTMODE, temp_s1_2);
                api->options_valid(api->user);
                api->message_send(api->user, T_SOUND, 0, -1, T_BGMSTOP);
                api->message_send(api->user, T_SOUND, 0, -1, T_ENVSTOP);
                api->message_send(api->user, T_SOUND, 0, -1, T_SESTOP);
                api->message_target(api->user, T_STAGECTL);
                api->push_string(api->user, T_stagIS08);
                api->message_end(api->user, T_NEXTSTAGE);
                ctrl->_st2 = 3;
                ctrl->_st3 = 0;
                return;
            }
            break;
        }
        break;
    case 7: /* White fade and title-background close. */
        temp_v1_16 = ctrl->_st1;
        switch (temp_v1_16) {
        case 0:
            api->model_start(api->user, 0, T_i_fadewn01, T_SQ_WTOUT60, 1);
            api->model_close(api->user, 0, T_j_startback, T_SQ_CLOSE, 1);
            ctrl->_st1 = ctrl->_st1 + 1;
            ctrl->_st3 = 0;
            ctrl->_st2 = 0;
            return;
        case 1:
            if ((api->closing_done(api->user) & 0xFF) == 1) {
                ctrl->_st0 = 8U;
                ctrl->_st3 = 0;
                ctrl->_st2 = 0;
                ctrl->_st1 = 0;
                return;
            }
            break;
        }
        break;
    case 8: /* Transfer camera/light to LOADCTRL2 GENERATE_TITLE. */
        temp_a0_11 = ctrl->_st1;
        switch (temp_a0_11) {
        case 0:
            temp_s2_3 = option->_comConf;
            temp_s1_3 = option->_lightConf;
            api->message_begin(api->user, T_LOADCTRL2, 0, 0);
            api->push_int(api->user, temp_s2_3);
            api->push_int(api->user, temp_s1_3);
            api->message_end(api->user, T_GENERATE_TITLE);
            ctrl->_st1 = ctrl->_st1 + 1;
            ctrl->_st3 = 0;
            ctrl->_st2 = 0;
            break;
        }
        break;
    }
}
