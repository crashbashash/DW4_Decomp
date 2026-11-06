/* Clears a 64-word object, then initialises its sub-records and callback slot; returns it. */
extern void FUN_0028b530(void *dst, int value, int words); /* word fill: stores `value` into `words` words */
extern void FUN_0028d880(void *rec);
extern void FUN_0028dbb8(void *rec);
extern void FUN_0028dbd0(void *rec);
extern void FUN_0028dbf8(void *rec);
extern void FUN_0028b7f8(void);

typedef struct {
    int f0;
    char rec4[12];          /* 4 */
    int f16;
    char pad20[4];
    char rec24[16];         /* 24 */
    char rec40[32];         /* 40 */
    char rec72[32];         /* 72 */
    char rec104[32];        /* 104 */
    char rec136[32];        /* 136 */
    char rec168[40];        /* 168 */
    int f208;
    void (*callback)(void); /* 212 */
    int f216;
    int f220;
    int f224;
    int f228;
    int f232;
} Obj28db18;

Obj28db18 *FUN_0028db18(Obj28db18 *obj) {
    FUN_0028b530(obj, 0, 64);
    obj->f0 = 2;
    FUN_0028d880(obj->rec4);
    obj->f16 = 2;
    FUN_0028dbb8(obj->rec24);
    FUN_0028dbd0(obj->rec40);
    FUN_0028dbd0(obj->rec72);
    FUN_0028dbd0(obj->rec104);
    FUN_0028dbd0(obj->rec136);
    FUN_0028dbf8(obj->rec168);
    obj->f208 = 0;
    obj->f216 = 0;
    obj->f220 = 0;
    obj->callback = FUN_0028b7f8;
    obj->f224 = 0;
    obj->f228 = 0;
    obj->f232 = 0;
    return obj;
}
