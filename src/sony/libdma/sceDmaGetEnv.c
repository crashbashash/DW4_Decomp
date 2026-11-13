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
extern DmaEnv sceDmaCurrentEnv;

DmaEnv *sceDmaGetEnv(DmaEnv *env) {
    *env = sceDmaCurrentEnv;
    return env;
}
