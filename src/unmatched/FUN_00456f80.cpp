struct In { char p[160]; unsigned char f160; };
struct Ob { char p[12]; In *f12; };
extern "C" {
int FUN_00456eb0(Ob *, int);
int FUN_004570a0(Ob *);
bool FUN_00456f80(Ob *arg0, int arg1, int arg2);
}
bool FUN_00456f80(Ob *arg0, int arg1, int arg2) {
    if (arg0->f12->f160 == 0) {
        return false;
    }
    bool r = false;
    switch (arg1) {
    case 0x81:
        if (arg2 != 0) {
            FUN_00456eb0(arg0, 2);
        }
        r = true;
        break;
    case 0x83:
        if (arg2 != 0) {
            FUN_00456eb0(arg0, 3);
        }
        r = true;
        break;
    case 0x80:
        if (arg2 != 0) {
            FUN_00456eb0(arg0, 0);
        }
        r = true;
        break;
    case 0x82:
        if (arg2 != 0) {
            FUN_00456eb0(arg0, 1);
        }
        r = true;
        break;
    case 0x9:
        if (arg2 != 0) {
            FUN_00456eb0(arg0, 4);
        }
        r = true;
        break;
    case 0xD:
    case 0x20:
        if (arg2 != 0) {
            FUN_004570a0(arg0);
        }
        r = true;
        break;
    default:
        break;
    }
    return r;
}
