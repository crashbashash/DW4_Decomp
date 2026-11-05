typedef struct Stk { int a; int b; int count; int c; char *data; } Stk;
typedef struct Mat { float m[16]; } Mat;
typedef struct Obj { char pad[972]; Stk *s[8]; } Obj;
void FUN_001fbce0(int, char *);
void Matrix44_Copy(Mat *, char *);

void FUN_00172910(Obj *o, int k) {
    Mat m0, m1, m2, m3, m4;
    switch (k) {
    case 0:
        o->s[0]->count--;
        FUN_001fbce0(3, o->s[0]->data + ((o->s[0]->count - 1) << 6));
        break;
    case 1:
        o->s[1]->count--;
        FUN_001fbce0(0, o->s[1]->data + ((o->s[1]->count - 1) << 6));
        break;
    case 2: {
        Stk *s = o->s[2];
        s->count--;
        Matrix44_Copy(&m0, s->data + (s->count << 6));
        FUN_001fbce0(4, o->s[2]->data + ((o->s[2]->count - 1) << 6));
        break; }
    case 10: { Stk *s = o->s[4]; s->count--; Matrix44_Copy(&m1, s->data + (s->count << 6)); break; }
    case 11: { Stk *s = o->s[5]; s->count--; Matrix44_Copy(&m2, s->data + (s->count << 6)); break; }
    case 12: { Stk *s = o->s[6]; s->count--; Matrix44_Copy(&m3, s->data + (s->count << 6)); break; }
    case 13: { Stk *s = o->s[7]; s->count--; Matrix44_Copy(&m4, s->data + (s->count << 6)); break; }
    }
}
