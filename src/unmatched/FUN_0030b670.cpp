extern char *DAT_004c22f0[4];
struct O { char pad[8]; char *s; char *Str() { return s == 0 ? DAT_004c22f0[0] : s; } };
extern "C" bool FUN_0030b670(O *o, char *out) {
    bool r = false;
    if (*o->Str() == 't' || *o->Str() == 'T') {
        *out = 1;
        r = true;
    } else if (*o->Str() == 'f' || *o->Str() == 'F') {
        *out = 0;
        r = true;
    }
    return r;
}
