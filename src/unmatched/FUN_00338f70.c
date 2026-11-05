typedef struct O { char p[32]; int w; int h; char q[20]; int cw; int ch; } O;
extern int DAT_004c2c50[4];
extern int DAT_004c2c58[4];
int FUN_00338f70(O *o, int *a1, int *a2, int *a3, int *a4) {
    int v;
    v = o->cw;
    *a1 = (v != -1) ? v : DAT_004c2c50[0];
    v = o->ch;
    *a2 = (v != -1) ? v : DAT_004c2c58[0];
    if (*a1 == -1) {
        *a1 = o->w;
        *a3 = 1;
    } else {
        if (o->w < *a1) *a1 = o->w;
        *a3 = o->w / *a1;
        if (o->w % *a1 != 0) *a3 = *a3 + 1;
    }
    if (*a2 == -1) {
        *a2 = o->h;
        *a4 = 1;
    } else {
        if (o->h < *a2) *a2 = o->h;
        *a4 = o->h / *a2;
        if (o->h % *a2 != 0) *a4 = *a4 + 1;
    }
    return 1;
}
