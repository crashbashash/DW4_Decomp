struct T { int word0; int references; };
struct T *igMetaObject_CreateInstanceDefault();
void igObject_Destroy(struct T *);
int FUN_002fd610(struct T **arg0, int arg1) {
    struct T *volatile sp2C;
    struct T *o;
    struct T *t;
    sp2C = igMetaObject_CreateInstanceDefault(arg1);
    o = sp2C; if (o != 0) { o->references = o->references + 1; }
    o = sp2C;
    if (o != 0) {
        --o->references;
        if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0) {
            igObject_Destroy(o);
        }
    }
    *arg0 = sp2C;
    t = *arg0; if (t != 0) { t->references = t->references + 1; }
    o = sp2C;
    if (o != 0) {
        --o->references;
        if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0) {
            igObject_Destroy(o);
        }
    }
    return 0;
}
