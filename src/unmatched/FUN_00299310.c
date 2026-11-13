/* Enters a file name with a range into the playback list: forwards (a, 0, b, c) to LSC_EntryFileRange on the +76 stream, rejecting an
 * invalid handle. */
extern int FUN_002968c0(void *ply);
extern void mwsfd_Error(const char *msg);
extern void LSC_EntryFileRange(int stream, int a, int zero, int b, int c);
extern char DAT_004f4850[]; /* "E407023: mwPlyEntryFnameRange: handle is invalid." */

typedef struct {
    char pad0[76];
    int f76;
} Ply299310;

void FUN_00299310(Ply299310 *ply, int a, int b, int c) {
    if (FUN_002968c0(ply) == 0) {
        mwsfd_Error(DAT_004f4850);
        return;
    }
    LSC_EntryFileRange(ply->f76, a, 0, b, c);
}
