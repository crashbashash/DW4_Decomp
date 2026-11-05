struct Ref {
    int pad;
    union {
        int w;
        struct {
            unsigned cnt : 23;
            unsigned f : 9;
        } b;
    } u;
};
int igObject_Destroy(void *);
extern struct Ref *DAT_00587000[4];
extern int DAT_00587010[4];

struct Ref *FUN_002f8760(void) {
    int n;
    struct Ref *s;
    if (DAT_00587010[0] > 0 && DAT_00587010[0] < 5) {
        n = DAT_00587010[0] - 1;
        DAT_00587010[0] = n;
        s = DAT_00587000[n];
        if (s != 0) {
            s->u.w = s->u.w - 1;
            if (s->u.b.cnt == 0) igObject_Destroy(s);
        }
        return s;
    }
    return 0;
}
