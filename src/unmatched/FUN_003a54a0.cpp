struct Pad { char pad[36]; int f36; char p2[28]; int f68; };
struct O { char pad[20]; int f20; };
extern "C" {
struct Pad *bePadManager_GetPadForPlayer(int, int);
int FUN_003a54a0(struct O *arg0);
}
int FUN_003a54a0(struct O *arg0) {
    int i = 0;
    struct Pad *p;
    int z;
    do {
        p = bePadManager_GetPadForPlayer(arg0->f20, i);
        /* matching construct: the double negation keeps the retail sltu/xori normalisation of the first test
         * without the bool truncation the C++ front end adds to a `!= 0` comparison */
        if (!!p->f36) { return 1; }
        if (p->f68 != 0) { return 1; }
        i++;
    } while (i < 4);
    return 0;
}
