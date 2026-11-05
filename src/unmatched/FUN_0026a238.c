/* 0x0026a238 — FUN_0026a238 (104 bytes). Inside the FUN_0027e1c0/FUN_0027e1d8 critical section: for an object whose header word (+0) carries type 0x0102 in bits 8-23, raises the flag at +72 and clears the one at +71 when set; any other object gets its error byte (+1) set. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Obj_26a238 {
    union {
        int word;               /* type code in bits 8-23 */
        struct {
            signed char pad0;
            signed char error;  /* 0x01 */
        } bytes;
    } header;                   /* 0x00 */
    char pad4[67];
    signed char f71; /* 0x47 */
    signed char f72; /* 0x48 */
} Obj_26a238;

void FUN_0027e1c0(void);
void FUN_0027e1d8(void);

void FUN_0026a238(Obj_26a238 *obj) {
    FUN_0027e1c0();
    if ((obj->header.word & 0xffff00) == 0x10200) {
        obj->f72 = 1;
        if (obj->f71 == 1) {
            obj->f71 = 0;
        }
    } else {
        obj->header.bytes.error = 1;
    }
    FUN_0027e1d8();
}
