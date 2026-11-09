#include "dw4/reflected.h"

class ControllerListener {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void onConnect(int window, igPsx2Controller *pad); virtual void onReset(int window, igPsx2Controller *pad);
};

struct PadActAlign {
    unsigned char data[6];
};

extern "C" {
extern PadActAlign DAT_00487760;
int FUN_00118390(int port, int slot);
int FUN_001184a8(int port, int slot);
int FUN_00118530(int port, int slot, int actno, int term);
int FUN_00118770(int port, int slot, int term, int offs);
int FUN_00118c60(int port, int slot);
int scePadSetMainMode(int port, int slot, int offs, int lock);
int scePadSetActAlign(int port, int slot, const unsigned char *data);
int scePadEnterPressMode(int port, int slot);
int scePadExitPressMode(int port, int slot);
void FUN_001479b0(igPsx2Controller *pad);
void FUN_00148160(igPsx2Controller *pad, ControllerListener *listener);
}

/* matching construct: a small sweep of spellings */
extern "C" void Gap__igPsx2Controller__vfunc_23(igPsx2Controller *self, ControllerListener *listener) {
    int state;
    unsigned char analog;
    unsigned char lock;
    bool firstConnect;
    int id;

    state = FUN_00118390(self->_port, self->_slot);
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
            self->_curr_id = FUN_00118770(self->_port, self->_slot, 1, 0);
            if (self->_curr_id) {
                id = FUN_00118770(self->_port, self->_slot, 2, 0);
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
        if (FUN_00118770(self->_port, self->_slot, 2, 0) == 0) {
            self->_analogState = 0;
        } else {
            scePadSetMainMode(self->_port, self->_slot, 1, self->_lockState ? 3 : 2);
            self->_analogState = 1;
        }
        self->_phase = 2;
        break;
    case 2:
        if (FUN_001184a8(self->_port, self->_slot) == 1) {
            self->_phase = 1;
        }
        if (FUN_001184a8(self->_port, self->_slot) == 0) {
            self->_phase = 0;
        }
        break;
    case 3:
        if (FUN_00118530(self->_port, self->_slot, -1, 0) == 0) {
            self->_phase = 7;
        } else {
            PadActAlign align = DAT_00487760;
            scePadSetActAlign(self->_port, self->_slot, align.data);
            self->_phase = 4;
        }
        break;
    case 4:
        if (FUN_001184a8(self->_port, self->_slot) == 1) {
            self->_phase = 3;
        }
        if (FUN_001184a8(self->_port, self->_slot) == 0) {
            self->_phase = 5;
        }
        break;
    case 5:
        if (FUN_00118c60(self->_port, self->_slot) == 0) {
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
        if (FUN_001184a8(self->_port, self->_slot) == 1) {
            self->_phase = 5;
        }
        if (FUN_001184a8(self->_port, self->_slot) == 0) {
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
