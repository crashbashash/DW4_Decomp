struct PA {
    char p0[20];
    float f20;
    float f24;
    float f28;
    char p32[20];
    int f52;
    unsigned int f56;
    char p60[24];
    float f84;
    char p88[4];
    unsigned char f92;
    char p93[7];
    int f100;
    unsigned char f104;
    char p105[7];
    long long f112;
};
extern "C" {
int FUN_001e7500(int);
int FUN_001e7560(int);
long long FUN_001f0560();
int FUN_001fe390(int, unsigned, int, float);
int Gap__Bec__ParticleArray__vfunc_27(PA *);
extern long long DAT_00560660[4];
void Gap__Gfx__igPsx2ParticleArray__vfunc_29(PA *arg0);
}
void Gap__Gfx__igPsx2ParticleArray__vfunc_29(PA *arg0) {
    if (arg0->f92 == 0) {
        Gap__Bec__ParticleArray__vfunc_27(arg0);
        return;
    }
    float t = arg0->f28;
    if (!(t <= arg0->f24 + arg0->f84) || t < arg0->f20) return;
        DAT_00560660[0] += arg0->f56;
        if (FUN_001e7560(0x17) != 0) {
            FUN_001e7500(0x17);
        }
        FUN_001fe390(arg0->f100, arg0->f56, arg0->f52, arg0->f28);
        if (arg0->f104 != 0) {
            arg0->f112 = FUN_001f0560();
        }
}
