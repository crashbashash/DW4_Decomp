typedef struct Rc { int w0; int refs; int f8; } Rc;
typedef struct V4 { float x, y, z, w; } V4;
Rc *FUN_002b9500();
int FUN_00230298(float);
int FUN_002eb010();
int FUN_0030b7e0();
int StringPool_Construct();
int StringPool_Intern();
int igObject_Destroy();
extern int DAT_004c22f0[16];
extern int DAT_00586f20[16];
int FUN_001e6f10(int *arg0, V4 *arg1, int arg2) {
    Rc *volatile sp5C;
    volatile char sp58[4];
    int s3;
    int s2;
    int s1;
    int name;
    int res;
    int obj;
    Rc *t;
    sp58[0] = 0;
    sp5C = FUN_002b9500(0);
    s3 = FUN_00230298(arg1->x);
    s2 = FUN_00230298(arg1->y);
    s1 = FUN_00230298(arg1->z);
    FUN_0030b7e0(sp5C, arg2, s3, s2, s1, FUN_00230298(arg1->w));
    name = sp5C->f8;
    if (name == 0) {
        name = DAT_004c22f0[0];
    }
    if (name == 0) {
        res = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            obj = FUN_002eb010(0x10);
            if (obj != 0) {
                obj = StringPool_Construct(obj);
            }
            DAT_00586f20[0] = obj;
        }
        res = StringPool_Intern(DAT_00586f20[0], name);
    }
    *arg0 = res;
    t = sp5C;
    if (t != 0) {
        t->refs = t->refs - 1;
        if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) {
            igObject_Destroy(t);
        }
    }
    return 0;
}
