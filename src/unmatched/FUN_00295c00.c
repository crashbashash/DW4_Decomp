/* 0x00295c00 — FUN_00295c00 (80 bytes). Runs FUN_00295b68(sfd, a), then records b and c at +456/+460, sets the +448 flag and clears +452. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_00295b68(void *sfd, int a);

typedef struct {
    char pad0[448];
    int f448;
    int f452;
    int f456;
    int f460;
} Sfd295c00;

void FUN_00295c00(Sfd295c00 *sfd, int a, int b, int c) {
    FUN_00295b68(sfd, a);
    sfd->f456 = b;
    sfd->f460 = c;
    sfd->f448 = 1;
    sfd->f452 = 0;
}
