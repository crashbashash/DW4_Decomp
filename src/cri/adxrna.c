typedef struct AdxRnaStream AdxRnaStream;
typedef struct AdxRnaStreamOps {
    void *slot[9];
    unsigned int (*query)(AdxRnaStream *stream, int which);
} AdxRnaStreamOps;
struct AdxRnaStream {
    AdxRnaStreamOps *ops;
};
typedef struct AdxRnaTrack {
    int f0;
    void *handle;
    AdxRnaStream *stream;
} AdxRnaTrack;
typedef struct AdxRnaTrackList {
    int f0;
    int f4;
    AdxRnaTrack *tracks[1];
} AdxRnaTrackList;
typedef struct AdxRna {
    int f0;
    int f4;
    int f8;
    AdxRnaTrackList *tracks;
} AdxRna;

extern char DAT_004ee378[];

int FUN_00279218();
int FUN_00279b00();
int FUN_00279dd0();
int FUN_00279f68();
int FUN_00279fd8();
int FUN_0027a040();
int FUN_0027a090();
int FUN_0027a0e0();
int FUN_0027a0e8();
int FUN_0027a178();
int FUN_0027a200();
int FUN_0027a228();
int FUN_0027a2e8();
int FUN_0027a688();
int FUN_0027a770();
int FUN_0027a7b8();
int FUN_0027a818();
int FUN_0027a8b0();
int FUN_0027a8e0();
int FUN_0027a910();
int FUN_0027aa08();
int FUN_0027aa40();
int FUN_0027aaa8();
int FUN_0027acc8();
int FUN_0027ad70();
int FUN_0027adb8();
int FUN_0027ade8();
int FUN_0027ae18();
int FUN_0027ae58();
int FUN_0027aea8();
int FUN_0027aed8();
int FUN_0027af70();
int FUN_0027afa0();
int FUN_0027afd0();
int FUN_0027b008();
int FUN_0027b038();
int FUN_0027b0f8();
int FUN_0027b188();
unsigned int FUN_0027da60(void *handle, int mode);
void FUN_002659a0(const char *format, ...);

void FUN_00265a20(void) {
    FUN_00279218();
}

unsigned int FUN_00265a38(AdxRna *rna, int ch)
{
    AdxRnaStream *s = rna->tracks->tracks[ch]->stream;
    return (unsigned int)s->ops->query(s, 1) >> 1;
}

unsigned int FUN_00265a78(AdxRna *rna, int index) {
    AdxRnaStream *stream = rna->tracks->tracks[index]->stream;
    return stream->ops->query(stream, 0) >> 1;
}

unsigned int FUN_00265ab8(AdxRna *rna, int index) {
    return FUN_0027da60(rna->tracks->tracks[index]->handle, 1) >> 1;
}

unsigned int FUN_00265af0(AdxRna *rna, int index) {
    return FUN_0027da60(rna->tracks->tracks[index]->handle, 0) >> 1;
}

void FUN_00265b28(void) {
    FUN_00279dd0();
}

void FUN_00265b40(void) {
    FUN_00279f68();
}

void FUN_00265b58(void) {
    FUN_00279fd8();
}

void FUN_00265b70(AdxRna *rna) {
    FUN_0027a040(rna->tracks);
}

void FUN_00265b88(AdxRna *rna) {
    FUN_0027a090(rna->tracks);
}

void FUN_00265ba0(AdxRna *rna)
{
    FUN_0027a0e0(rna->tracks);
}

void FUN_00265bb8(void) {
    FUN_0027a0e8();
}

void FUN_00265bd0(void) {
    FUN_0027a178();
}

void FUN_00265be8(void) {
    FUN_0027a200();
}

void FUN_00265c00(void) {
    FUN_00279b00();
}

void FUN_00265c18(void) {
    FUN_0027a228();
}

void FUN_00265c30(void)
{
}

void FUN_00265c38(void) {
    FUN_0027a2e8();
}

void FUN_00265c50(void *handle) {
    FUN_0027a8b0(handle, 0);
    FUN_0027a818(handle, 0);
    FUN_0027a688(handle);
}

void FUN_00265c88(void) {
    FUN_0027a770();
}

void FUN_00265ca0(void) {
    FUN_0027a7b8();
}

void FUN_00265cb8(void) {
    FUN_0027a818();
}

void FUN_00265cd0(void) {
    FUN_0027a8b0();
}

void FUN_00265ce8(void) {
    FUN_0027aa08();
}

void FUN_00265d00(void) {
    FUN_0027aa40();
}

void FUN_00265d18(void) {
    FUN_0027aaa8();
}

void FUN_00265d30(void) {
    FUN_002659a0(DAT_004ee378);
    for (;;) {
    }
}

void FUN_00265d68(void) {
    FUN_0027acc8();
}

void FUN_00265d80(void) {
    FUN_0027ad70();
}

void FUN_00265d98(void) {
    FUN_0027adb8();
}

void FUN_00265db0(void) {
    FUN_0027ade8();
}

void FUN_00265dc8(void) {
    FUN_0027ae18();
}

void FUN_00265de0(void) {
    FUN_0027ae58();
}

void FUN_00265df8(void) {
    FUN_0027aea8();
}

void FUN_00265e10(void) {
    FUN_0027aed8();
}

void FUN_00265e28(void) {
    FUN_0027af70();
}

void FUN_00265e40(void) {
    FUN_0027afa0();
}

void FUN_00265e58(void) {
    FUN_0027afd0();
}

void FUN_00265e70(void) {
    FUN_0027b008();
}

void FUN_00265e88(void) {
    FUN_0027b038();
}

void FUN_00265ea0(void) {
    FUN_0027b0f8();
}

void FUN_00265eb8(void)
{
}

void FUN_00265ec0(void)
{
}

void FUN_00265ec8(void) {
    FUN_0027a8e0();
}

void FUN_00265ee0(void) {
    FUN_0027a910();
}

void FUN_00265ef8(void)
{
}

void FUN_00265f00(void)
{
}

int FUN_00265f08(void) {
    FUN_0027b188();
    return 0;
}
