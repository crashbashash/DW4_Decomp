void FUN_001479b0(igPsx2Controller *arg0) {
    int i;
    char *p = (char *)arg0;
    for (i = 0; i < 6; i++) {
        *(p + i + 91) = 0;
    }
    for (i = 0; i < 12; i++) {
        *(p + i + 97) = 0;
    }
    for (i = 0; i < 2; i++) {
        arg0->_x[i] = 0;
        arg0->_y[i] = 0;
        *(p + i + 76) = 0;
        *(p + i + 78) = 0;
    }
    arg0->_connected = 0;
    arg0->_buttonState = 0xFFFF;
    arg0->_hasPressure = 0;
    arg0->_phase = 0;
    arg0->_term_id = 0;
    arg0->_lockState = 1;
    arg0->_analogState = 1;
}

void Gap__igPsx2Controller__vfunc_11(int arg0) {
    Gap__Core__igObject__vfunc_09();
    FUN_001479b0((igPsx2Controller *)arg0);
}

void Gap__igPsx2Controller__vfunc_12(void *arg0) {
    int temp_a0;

    scePadPortClose(*(int *)((char *)arg0 + 64), *(int *)((char *)arg0 + 60));
    temp_a0 = *(int *)((char *)arg0 + 72);
    if (temp_a0 != 0) {
        Memory_FreeBuffer(temp_a0);
    }
    Gap__Core__igObject__vfunc_10(arg0);
}

void Gap__igPsx2Controller__vfunc_31(void *arg0, int arg1, float *arg2, float *arg3) {
    int temp_a1;
    int idx;
    int temp_v1;
    temp_a1 = arg1 & 0xFFFF;
    if (temp_a1 < (int) *(unsigned short *)((char *)(arg0) + 28)) {
        idx = temp_a1 * 4;
        temp_v1 = idx + (int)arg0;
        *arg2 = *(float *)(temp_v1 + 36);
        *arg3 = *(float *)(temp_v1 + 44);
    }
}

/* matching construct: a small sweep of spellings */
extern "C" void Gap__igPsx2Controller__vfunc_23(igPsx2Controller *self, ControllerListener *listener) {
    int state;
    unsigned char analog;
    unsigned char lock;
    bool firstConnect;
    int id;

    state = scePadGetState(self->_port, self->_slot);
    if (state == 0 || self->_userReset) {
        if (self->_connected || self->_userReset) {
            analog = self->_analogState;
            lock = self->_lockState;
            FUN_001479b0(self);
            self->_analogState = analog;
            self->_lockState = lock;
            if (listener) {
                listener->onReset(self->_attachedWindow, self);
            }
            self->_userReset = 0;
        }
        return;
    }
    switch (self->_phase) {
    case 0:
        if (state == 6 || state == 2) {
            self->_curr_id = scePadInfoMode(self->_port, self->_slot, 1, 0);
            if (self->_curr_id) {
                id = scePadInfoMode(self->_port, self->_slot, 2, 0);
                if (id > 0) {
                    self->_curr_id = id;
                }
                firstConnect = !self->_connected;
                self->_connected = 1;
                if (firstConnect && listener) {
                    listener->onConnect(self->_attachedWindow, self);
                    self->_reseting = 1;
                }
                if (self->_curr_id == 4 || self->_curr_id == 7) {
                    if (self->_reseting) {
                        self->_type = 1;
                        self->_phase = 1;
                    } else if (self->_curr_id == 4) {
                        self->_phase = 7;
                    } else if (self->_userResetAnalogOnly) {
                        self->_type = 6;
                        self->_phase = 7;
                    } else {
                        self->_type = 6;
                        self->_phase = 3;
                    }
                } else {
                    self->_reseting = 0;
                    self->_type = 7;
                    self->_phase = 7;
                }
            }
        }
        break;
    case 1:
        self->_reseting = 0;
        if (scePadInfoMode(self->_port, self->_slot, 2, 0) == 0) {
            self->_analogState = 0;
        } else {
            scePadSetMainMode(self->_port, self->_slot, 1, self->_lockState ? 3 : 2);
            self->_analogState = 1;
        }
        self->_phase = 2;
        break;
    case 2:
        if (scePadGetReqState(self->_port, self->_slot) == 1) {
            self->_phase = 1;
        }
        if (scePadGetReqState(self->_port, self->_slot) == 0) {
            self->_phase = 0;
        }
        break;
    case 3:
        if (scePadInfoComb(self->_port, self->_slot, -1, 0) == 0) {
            self->_phase = 7;
        } else {
            PadActAlign align = DAT_00487760;
            scePadSetActAlign(self->_port, self->_slot, align.data);
            self->_phase = 4;
        }
        break;
    case 4:
        if (scePadGetReqState(self->_port, self->_slot) == 1) {
            self->_phase = 3;
        }
        if (scePadGetReqState(self->_port, self->_slot) == 0) {
            self->_phase = 5;
        }
        break;
    case 5:
        if (scePadInfoPressMode(self->_port, self->_slot) == 0) {
            self->_hasPressure = 0;
            self->_phase = 7;
        } else {
            self->_hasPressure = 1;
            if (self->_usePressure) {
                scePadEnterPressMode(self->_port, self->_slot);
            } else {
                scePadExitPressMode(self->_port, self->_slot);
            }
            self->_phase = 6;
        }
        break;
    case 6:
        if (scePadGetReqState(self->_port, self->_slot) == 1) {
            self->_phase = 5;
        }
        if (scePadGetReqState(self->_port, self->_slot) == 0) {
            self->_phase = 7;
        }
        break;
    default:
        if (state == 6 || state == 2) {
            FUN_00148160(self, listener);
            if (self->_term_id != self->_curr_id) {
                if (self->_term_id == 7) {
                    self->_analogState = 1;
                    self->_phase = 0;
                } else if (self->_term_id == 4) {
                    self->_curr_id = self->_term_id;
                    self->_analogState = 0;
                }
                self->_phase = 0;
            }
        }
        break;
    }
}

void Gap__igPsx2Controller__vfunc_37(C *arg0, int arg1, float fparg0) {
    if ((arg1 >= 0) && (arg1 < 6)) {
        arg0->b91[arg1] = (unsigned char)(255.0f * fparg0);
        scePadSetActDirect(arg0->f64, arg0->f60, &arg0->b91[0]);
    }
}

int FUN_00147ff0(void *arg0, unsigned int arg1) {
    int var_a1;

    switch (arg1) {
    case 0:
        var_a1 = 5;
        break;
    case 1:
        var_a1 = 7;
        break;
    case 2:
        var_a1 = 4;
        break;
    case 3:
        var_a1 = 6;
        break;
    case 4:
        var_a1 = 0xC;
        break;
    case 5:
        var_a1 = 0xD;
        break;
    case 6:
        var_a1 = 0xE;
        break;
    case 7:
        var_a1 = 0xF;
        break;
    case 8:
        var_a1 = 0xA;
        break;
    case 9:
        var_a1 = 0xB;
        break;
    case 10:
        var_a1 = 8;
        break;
    default:
        var_a1 = 9;
        break;
    }
    if (*(unsigned char *)((char *)(arg0) + 12) != 0) {
        return FUN_00147430(arg0, var_a1);
    }
    return var_a1;
}

int FUN_001480a0(struct O_1480a0 *o, int a) {
    int v = o->f12 != 0 ? FUN_00147450(o, a) : a;
    unsigned t = v - 4;
    switch (t) {
    case 1: return 0;
    case 3: return 1;
    case 0: return 2;
    case 2: return 3;
    case 8: return 4;
    case 9: return 5;
    case 10: return 6;
    case 11: return 7;
    case 6: return 8;
    case 7: return 9;
    case 4: return 10;
    case 5: return 11;
    default: return -1;
    }
}

