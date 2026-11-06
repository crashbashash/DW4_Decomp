struct R { char pad[4]; int f4; };
int igObject_Destroy(struct R *);
extern struct R *DAT_00562528[4];
extern struct R *DAT_00562540[4];
extern struct R *DAT_00562558[4];
void FUN_001abdf0(void) {
    struct R *p;
    p = DAT_00562528[0];
    if (p != 0) {
        p->f4 = p->f4 - 1;
        if ((p->f4 & 0x7FFFFF) == 0) {
            igObject_Destroy(p);
        }
    }
    DAT_00562528[0] = 0;
    p = DAT_00562540[0];
    if (p != 0) {
        p->f4 = p->f4 - 1;
        if ((p->f4 & 0x7FFFFF) == 0) {
            igObject_Destroy(p);
        }
    }
    DAT_00562540[0] = 0;
    p = DAT_00562558[0];
    if (p != 0) {
        p->f4 = p->f4 - 1;
        if ((p->f4 & 0x7FFFFF) == 0) {
            igObject_Destroy(p);
        }
    }
    DAT_00562558[0] = 0;
}
