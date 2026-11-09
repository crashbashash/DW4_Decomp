typedef struct {
    short f0;
    short f2;
    char pad4[8];
    char f12;
    char f13;
    signed char f14;
    signed char f15;
    int f16;
    int f20;
    int f24;
    short f28;
    char pad30[2];
    int f32;
    short f36;
    short f38;
    int f40;
    int f44;
    int f48;
    int f52;
    char pad56[4];
    int f60;
    int f64;
    int f68;
    char pad72[8];
    int f80;
    int f84;
    int f88;
    int f92;
    int f96;
    int f100;
    char pad104[32];
    int f136;
    int f140;
    char pad144[8];
    short f152;
    char pad154[2];
    short f156;
} AdxDecoder;

int FUN_0025c038(void *data, int size, short *hdrlen, char *f12, char *f13, signed char *f15,
                 signed char *f14, int *f20, int *f24, int *f16);

/* matching construct: 150-step hill climb over the order of the copies after the call */
int FUN_0025c148(AdxDecoder *d, void *data, int size)
{
    short hdrlen;

    d->f2 = 1;
    if (FUN_0025c038(data, size, &hdrlen, &d->f12, &d->f13, &d->f15, &d->f14, &d->f20, &d->f24,
                     &d->f16) < 0) {
        return 0;
    }
    d->f52 = 0;
    d->f48 = 0;
    d->f44 = 0;
    d->f40 = 0;
    d->f32 = 0;
    d->f28 = 0;
    d->f38 = 0;
    d->f36 = 0;
    d->f80 = d->f14;
    d->f84 = d->f15;
    d->f92 = d->f60;
    d->f152 = 3;
    d->f88 = d->f16;
    d->f140 = 0;
    d->f96 = d->f64;
    d->f136 = 0;
    d->f100 = d->f68;
    if (d->f13 == 8) {
        d->f156 = 1;
    } else {
        d->f156 = 0;
    }
    return hdrlen;
}
