int Matrix44_Copy(int, char *);
typedef struct St { char pad0[8]; int n; char pad12[4]; char *data; } St;
typedef struct O { char pad[972]; St *s972; St *s976; St *s980; St *s984; St *s988; St *s992; St *s996; St *s1000; } O;
void FUN_00173d60(O *o, int k, int dst) {
    St *s;
    switch (k) {
    case 0:  s = o->s972; Matrix44_Copy(dst, s->data + ((s->n - 1) << 6)); break;
    case 1:  s = o->s976; Matrix44_Copy(dst, s->data + ((s->n - 1) << 6)); break;
    case 2:  s = o->s980; Matrix44_Copy(dst, s->data + ((s->n - 1) << 6)); break;
    case 10: s = o->s988; Matrix44_Copy(dst, s->data + ((s->n - 1) << 6)); break;
    case 11: s = o->s992; Matrix44_Copy(dst, s->data + ((s->n - 1) << 6)); break;
    case 12: s = o->s996; Matrix44_Copy(dst, s->data + ((s->n - 1) << 6)); break;
    case 13: s = o->s1000; Matrix44_Copy(dst, s->data + ((s->n - 1) << 6)); break;
    }
}
