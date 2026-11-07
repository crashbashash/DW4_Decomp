extern "C" {
struct M { float m[16]; };
struct V3 { float x, y, z; };
int sprintf(char *, char *, int, int, int);
int igMatrix44f_SetIdentity(struct M *);
int FUN_00230298(float);
int Matrix44_Copy(struct M *, void *);
int Matrix44_GetTranslation(struct M *, struct V3 *);
int Matrix44_TranslateLocal(struct M *, struct V3 *);
extern char DAT_0050db00[32];
extern void *DAT_0058a1e8[4];
extern char DAT_0058a230[32];
char *MDLgetPosStr(float fparg0, float fparg1, float fparg2);
}

char *MDLgetPosStr(float fparg0, float fparg1, float fparg2) {
    struct M m;
    struct V3 b;
    struct V3 a;
    int s1;
    int s0;

    igMatrix44f_SetIdentity(&m);
    Matrix44_Copy(&m, DAT_0058a1e8[0]);
    b.x = fparg0;
    b.y = fparg1;
    b.z = fparg2;
    Matrix44_TranslateLocal(&m, &b);
    Matrix44_GetTranslation(&m, &a);
    s1 = FUN_00230298(a.x);
    s0 = FUN_00230298(a.y);
    sprintf(DAT_0058a230, DAT_0050db00, s1, s0, FUN_00230298(a.z));
    return DAT_0058a230;
}
