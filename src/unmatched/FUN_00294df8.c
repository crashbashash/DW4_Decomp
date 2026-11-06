/* Drops the init reference count at 0x4bd250; when it reaches zero, finishes every active one of
 * the 8 player slots and shuts the subsystems down in order. */
extern char *FUN_00294a30(void);
extern void FUN_00293118(void *slot);
extern void FUN_0029a1d0(void);
extern void FUN_0029a0e0(void);
extern void FUN_0029a180(void);
extern void FUN_0029a130(void);
extern void FUN_002977c0(void);
extern void FUN_00277918(void);
extern void FUN_00294ff0(void);
extern void FUN_00263470(void);
extern void FUN_0029b080(void);
extern void FUN_0027c810(void);
extern void FUN_0027b390(void);
extern void FUN_0027bcd0(void);
extern void FUN_00295e70(void);
extern void FUN_0029a008(void);
extern int DAT_004bd250; /* init reference count */

typedef struct {
    int f0;
    int active;   /* 4: 1 while the slot is in use */
    char rest[688];
} PlySlot;        /* 696 bytes */

void FUN_00294df8(void) {
    char *work = FUN_00294a30();
    PlySlot *slot;
    int i;

    if (--DAT_004bd250 != 0) {
        return;
    }
    slot = (PlySlot *)(work + 108);
    for (i = 0; i < 8; i++) {
        if (slot->active == 1) {
            FUN_00293118(slot);
        }
        slot++;
    }
    FUN_0029a1d0();
    FUN_0029a0e0();
    FUN_0029a180();
    FUN_0029a130();
    FUN_002977c0();
    FUN_00277918();
    FUN_00294ff0();
    FUN_00263470();
    FUN_0029b080();
    FUN_0027c810();
    FUN_0027b390();
    FUN_0027bcd0();
    FUN_00295e70();
    FUN_0029a008();
}
