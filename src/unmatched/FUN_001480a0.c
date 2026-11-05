int FUN_00147450();
struct O { char pad[12]; unsigned char f12; };
int FUN_001480a0(struct O *o, int a) {
    int v = o->f12 != 0 ? FUN_00147450() : a;
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
