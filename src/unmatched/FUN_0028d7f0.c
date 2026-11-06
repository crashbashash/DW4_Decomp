typedef struct Slot { int state; char pad[252]; } Slot;
typedef struct Mgr { char pad[12]; int count; Slot slot[1]; } Mgr;

extern Mgr *D_004bcc68;
extern void FUN_0028dc28(Slot *);
extern void FUN_0028b600(void);
extern void FUN_0028d4a0(void);

void FUN_0028d7f0(void)
{
    Mgr *m = D_004bcc68;
    Slot *first = m->slot;
    int n = m->count;
    int i;
    for (i = 0; i < n; i++) {
        Slot *s = &first[i];
        if (s->state != 1)
            FUN_0028dc28(s);
    }
    FUN_0028b600();
    FUN_0028d4a0();
}
