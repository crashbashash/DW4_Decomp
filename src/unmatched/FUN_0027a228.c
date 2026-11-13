/* Library shutdown: while active (not mode 1 with no entries), counts the init reference
 * 0x004b1e0c down and, at zero, frees the work areas 0x004b1ddc and 0x004b1e14 (FUN_001122d8),
 * releases 0x004b4860 (FUN_002734d0), tears down the entry table and the request, transfer and
 * support state (FUN_002795d0, FUN_00279f08, FUN_002737a8, FUN_0027df08, FUN_0027db68). */
extern void FUN_001122d8(int area);
extern void FUN_002734d0(int object);
extern void FUN_002795d0(void);
extern int FUN_00279f08(void);
extern void FUN_002737a8(void);
extern void FUN_0027df08(void);
extern void FUN_0027db68(void);
extern int ps2rna_nvoice;
extern int ps2rna_setup_voice;
extern int DAT_004b1ddc;
extern int DAT_004b1e0c;
extern int DAT_004b1e14;
extern int DAT_004b4860;

/* matching construct: hand search — int return type with no return value (implicit-int style); a void
   return type lets GCC turn the last call into a sibling call */
int FUN_0027a228(void) {
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        if (--DAT_004b1e0c == 0) {
            FUN_001122d8(DAT_004b1ddc);
            DAT_004b1ddc = 0;
            FUN_002734d0(DAT_004b4860);
            DAT_004b4860 = 0;
            FUN_001122d8(DAT_004b1e14);
            DAT_004b1e14 = 0;
            FUN_002795d0();
            FUN_00279f08();
            FUN_002737a8();
            FUN_0027df08();
            FUN_0027db68();
        }
    }
}
