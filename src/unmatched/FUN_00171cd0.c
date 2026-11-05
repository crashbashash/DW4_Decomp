typedef struct V4 { float x, y, z, w; } V4;
typedef struct St { V4 a; V4 b; V4 c; V4 d; float e; unsigned f; } St;
typedef struct O { char pad[1344]; St *s; } O;
extern int DAT_005608f8[4];
extern int DAT_005608fc[4];
extern int DAT_00560900[4];
extern int DAT_00560904[4];
extern int DAT_00560908[4];
int FUN_00172330(O *, St *);
#define EQ4(S, FLD, Q, CTR) do { V4 *a5; St *v1 = (S); int v0; \
    a5 = &v1->FLD; v0 = 1; if (v1->FLD.x != (Q)->x) v0 = 0; \
    if (v0 != 0) { v0 = 1; if (a5->y != (Q)->y) v0 = 0; } \
    if (v0 != 0) { v0 = 1; if (a5->z != (Q)->z) v0 = 0; } \
    if (v0 != 0) { v0 = 1; if (a5->w != (Q)->w) v0 = 0; } \
    if (v0 != 0) CTR[0] += 1; } while (0)
void FUN_00171cd0(O *arg0, V4 *arg1, V4 *arg2, V4 *arg3, V4 *arg4, float fparg0) {
    EQ4(arg0->s, b, arg2, DAT_005608f8);
    EQ4(arg0->s, a, arg1, DAT_005608fc);
    EQ4(arg0->s, d, arg4, DAT_00560900);
    EQ4(arg0->s, c, arg3, DAT_00560904);
    if (arg0->s->e == fparg0) {
        DAT_00560908[0] += 1;
    }
    { St *t = arg0->s; t->b.x = arg2->x; t->b.y = arg2->y; t->b.z = arg2->z; t->b.w = arg2->w; }
    { St *t = arg0->s; t->a.x = arg1->x; t->a.y = arg1->y; t->a.z = arg1->z; t->a.w = arg1->w; }
    { St *t = arg0->s; t->d.x = arg4->x; t->d.y = arg4->y; t->d.z = arg4->z; t->d.w = arg4->w; }
    { St *t = arg0->s; t->c.x = arg3->x; t->c.y = arg3->y; t->c.z = arg3->z; t->c.w = arg3->w; }
    arg0->s->e = fparg0;
    {
        unsigned a2 = arg0->s->f;
        if (arg3->x != 0.0f || arg3->y != 0.0f || arg3->z != 0.0f) {
            arg0->s->f = arg0->s->f | 1;
        } else {
            arg0->s->f = a2 & ~1;
        }
        if (arg1->x != 0.0f || arg1->y != 0.0f || arg1->z != 0.0f) {
            arg0->s->f = arg0->s->f | 4;
        } else {
            arg0->s->f = arg0->s->f & ~4;
        }
        if (a2 != arg0->s->f) {
            arg0->s->f = arg0->s->f | 2;
        }
    }
    FUN_00172330(arg0, arg0->s);
}
