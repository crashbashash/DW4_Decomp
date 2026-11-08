struct Obj00290ac0;

struct Vtbl00290ac0 {
    char pad0[24];
    void (*get)(struct Obj00290ac0 *obj, int flag, int arg, int *out);  /* +24 */
    char pad28[4];
    void (*put)(struct Obj00290ac0 *obj, int flag, int *in);            /* +32 */
};

struct Obj00290ac0 {
    struct Vtbl00290ac0 *vt;
};

int FUN_00290ac0(struct Obj00290ac0 *obj, int flag, int arg) {
    int buf[4];
    int other = flag == 0;

    obj->vt->get(obj, flag, arg, buf);
    obj->vt->put(obj, other, buf);
    return buf[1];
}
