typedef struct {
    unsigned int chcr;
    unsigned int pad0[3];
    unsigned int madr;
    unsigned int pad1[3];
    unsigned int qwc;
    unsigned int pad2[3];
    unsigned int tadr;
    unsigned int pad3[3];
    unsigned int asr0;
    unsigned int pad4[3];
    unsigned int asr1;
    unsigned int pad5[11];
    unsigned int sadr;
} DmaChannel;
typedef struct {
    unsigned char sts;
    unsigned char std;
    unsigned char mfd;
    unsigned char rcycle;
    unsigned short express;
    unsigned short notify;
    unsigned short sqwc;
    unsigned short tqwc;
    void *rbadr;
    unsigned int rbmsk;
} DmaEnv;
extern DmaChannel *DAT_00481c70[];
extern const int DAT_004d1e88[];
void FUN_00102db8(unsigned char *to, int size);
int sceDmaPutEnv(DmaEnv *env);
#define D_CTRL (*(volatile unsigned int *)0x1000e000)
#define D_STAT (*(volatile unsigned int *)0x1000e010)
int sceDmaReset(int enable) {
    int wasEnabled = D_CTRL & 1;
    int i;
    DmaEnv env;

    for (i = 0; i < 10; i++) {
        if (DAT_004d1e88[i]) {
            DAT_00481c70[i]->chcr = 0;
            DAT_00481c70[i]->madr = DAT_00481c70[i]->tadr = 0;
            DAT_00481c70[i]->asr0 = DAT_00481c70[i]->asr1 = 0;
            DAT_00481c70[i]->sadr = 0;
        }
    }
    D_STAT = 0xff1f;
    D_STAT = D_STAT & 0xff1f0000;
    FUN_00102db8((unsigned char *)&env, sizeof(env));
    sceDmaPutEnv(&env);
    if (enable == 1) {
        D_CTRL = D_CTRL | 1;
    }
    return wasEnabled;
}
