typedef struct { char p0[396]; int state; } M;
typedef struct { char pad[64]; M *sys; } sceMpeg;
int FUN_00109730(sceMpeg *, void *, int);
int FUN_001095c8(sceMpeg *, void *, int);
int FUN_001096e8(sceMpeg *mp, void *d, int e) {
    if (mp->sys->state != 3) {
        return FUN_00109730(mp, d, e);
    }
    return FUN_001095c8(mp, d, e);
}
