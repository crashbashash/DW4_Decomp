extern "C" {
void FUN_00347970(void);
extern struct G *DAT_00588088[4];
void *FUN_00347820(void);
}
struct G { int pad[9]; int f; };
void *FUN_00347820(void) {
    struct G *g = DAT_00588088[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00347970();
    }
    return DAT_00588088[0];
}
