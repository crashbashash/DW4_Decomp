/* Reports two positions for a stream object, by direct query, by its interface slot +36, or zero. */
typedef struct SfdStreamObj SfdStreamObj;
typedef struct SfdStreamVtbl {
    char pad0[36];
    int (*f36)(SfdStreamObj *obj, int mode);  /* +36 */
} SfdStreamVtbl;
struct SfdStreamObj {
    SfdStreamVtbl *vtbl;
};

extern int FUN_0029ec40(SfdStreamObj *obj);
extern int FUN_0029ec78(SfdStreamObj *obj);
extern int FUN_0027c760(SfdStreamObj *obj, int a, int b);
extern int FUN_0027bc30(SfdStreamObj *obj);

void FUN_0029eaf8(SfdStreamObj *obj, int *first, int *second) {
    if (FUN_0029ec40(obj) != 0) {
        *first = FUN_0027c760(obj, 1, 1);
        *second = FUN_0027c760(obj, 0, 1);
    } else if (FUN_0029ec78(obj) != 0) {  /* a1/a2 still hold 1, 1 from the call above */
        *first = FUN_0027bc30(obj);
        *second = *first - obj->vtbl->f36(obj, 1);
    } else {
        *first = 0;
        *second = 0;
    }
}
