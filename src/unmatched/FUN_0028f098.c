/* Fills entry `index` of the 12-byte record table at +952 with three values. */
typedef struct {
    int f0;
    int f4;
    int f8;
} Entry28f098;

typedef struct {
    char pad0[952];
    Entry28f098 entries[1]; /* 952: indexed by the caller */
} Obj28f098;

void FUN_0028f098(Obj28f098 *obj, int index, int a, int b, int c) {
    Entry28f098 *e = &obj->entries[index];

    e->f0 = a;
    e->f4 = b;
    e->f8 = c;
}
