extern "C" int FUN_0015a010();
extern "C" bool FUN_00159f80(int arg0) {
    bool r = true;
    if (FUN_0015a010() == 0) {
        bool b = true;
        bool a = false;
        unsigned int t = arg0 - 2;
        if (t < 0x18U && ((1 << t) & 0x987FD5)) {
            a = true;
        }
        if (!a && 1U < (unsigned int)(arg0 - 0x22)) {
            b = false;
        }
        if (!b) {
            r = false;
        }
    }
    return r;
}
