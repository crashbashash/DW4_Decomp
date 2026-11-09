typedef struct {
    char f0;
    signed char stat;
    char f2;
    signed char f3;
    int sj;
    char pad8[12];
    int f20;
    char pad24[8];
    int f32;
} Sjr;

int FUN_0026a138(int);
int FUN_0026a160(int);
void FUN_00261c18(Sjr *);

void FUN_002622d0(Sjr *s)
{
    int req;
    int st;
    int n;

    if (s->stat == 2) {
        s->stat = FUN_0026a138(s->sj);
        n = FUN_0026a160(s->sj) - s->f20;
        s->f32 = n;
        if ((unsigned char)s->stat == 3 || (unsigned char)s->stat == 4) {
            s->f20 += n;
            FUN_00261c18(s);
        }
    }
    req = s->f3;
    if (req == 1) {
        st = FUN_0026a138(s->sj);
        if (st == req) {
            s->f32 = FUN_0026a160(s->sj) - s->f20;
            FUN_00261c18(s);
            s->stat = st;
            s->f3 = 0;
        }
    }
}
