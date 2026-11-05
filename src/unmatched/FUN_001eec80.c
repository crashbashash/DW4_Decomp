extern int DAT_00490c60[4];
struct E { char p[48]; int f48; int f52; int f56; int f60; char pad[384]; };
extern struct E DAT_00569340[];
struct N { char p[12]; int *begin; int *end; struct N *next; };
int FUN_001eec80(struct N *arg0) {
    int r = 0;
    int *p;
    struct E *e;
    int t;
    int idx;
    do {
        for (p = arg0->begin; p < arg0->end; p++) {
            if (p[0] == DAT_00490c60[0] && p[2] == 0x1234) {
                t = p[1];
                if (t == p[3] && t < 0x10) {
if (t > 1) {
 idx = t - 1;
 } else {
 idx = 0;
 }
                    e = &DAT_00569340[idx];
                    if (p[12] == 7) {
                        p[10] = e->f56;
                        p[11] = e->f60;
                    } else {
                        p[10] = e->f48;
                        p[11] = e->f52;
                    }
                    r = 1;
                }
            }
        }
        arg0 = arg0->next;
    } while (arg0 != 0);
    return r;
}
