struct DisplayRecord {
    char pad0[28];
    unsigned char field : 1;
    unsigned char unused1 : 1;
    unsigned char interlaced : 1;
    unsigned char unused3 : 5;
    char pad29[3];
    int mode;
    int offsetX;
    int offsetY;
    int frame;
    short magnifyX;
    short magnifyY;
};
struct ChainHeader { unsigned int address : 31; unsigned int flag : 1; };
struct ChainOwner { char pad0[16]; struct ChainHeader *data; };
struct DmaChain { char pad0[12]; char *start; char *end; char pad20[4]; struct ChainOwner *owner; };
char *FUN_003307b0(char *start, int size, int channel);
extern int DAT_0048dce0[4];
extern int DAT_00490c10[4];
extern int DAT_00490c14[4];
extern int DAT_00490c18[4];
extern int DAT_00490c1c[4];
extern int DAT_00491478[4];
extern int DAT_00491480[4];
extern unsigned int DAT_00562c70[4];
extern int DAT_00562d48[4];
extern int DAT_00568e50[4];
extern int DAT_00568e60[4];
extern int *DAT_00568ea0[4];
extern struct DmaChain *DAT_00568eb8[4];
extern struct DisplayRecord *DAT_00568ec0[4];
extern int DAT_00568f04[4];
extern int DAT_00569228[4];
extern int DAT_00569230[4];
extern int DAT_00569240[4];
extern long long DAT_00569250[4];
extern long long DAT_00569258[4];
extern int DAT_00569330[4];
void FUN_001ee3f0(void) {
    int interlaced = DAT_00562c70[DAT_00569330[0]] >> 27 & 1;
    if (DAT_00568e50[0] != 0) {
        struct DisplayRecord *record = DAT_00568ec0[0];
        struct DmaChain *chain;
        int *packet;
        char *start;
        int size;
        record->frame = DAT_00491480[0];
        record->field = DAT_00569240[0];
        record->offsetX = DAT_00569250[0] - record->offsetX;
        record->offsetY = DAT_00569258[0] - record->offsetY;
        if (DAT_00569228[0] & 0x10) {
            record->magnifyX = DAT_0048dce0[0];
            record->magnifyY = DAT_00562d48[0];
        } else {
            record->magnifyX = 0;
            record->magnifyY = 0;
        }
        record->interlaced = interlaced;
        record->mode = DAT_00569228[0];
        DAT_00569230[0] = 0;
        DAT_00569228[0] &= ~0x20;
        DAT_00491478[0] |= 0x90;
        packet = DAT_00568ea0[0];
        packet[0] = DAT_00490c10[0];
        packet[1] = DAT_00490c14[0];
        packet[2] = DAT_00490c18[0];
        packet[3] = DAT_00490c1c[0];
        chain = DAT_00568eb8[0];
        chain->end = (char *)(packet + 4);
        DAT_00568e50[0] = 0;
        DAT_00568f04[0] = DAT_00568e60[0];
        size = chain->end - chain->start;
        start = FUN_003307b0(chain->start, size, 11);
        if (start != chain->start && chain->owner) {
            chain->owner->data[-3].address = (unsigned int)start;
        }
        chain->start = start;
        chain->end = start + size;
    }
}
