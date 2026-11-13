typedef struct PtsPopSub {
    char pad[492];
    int last;
    int f496;
    int wr;
    int rd;
    int items[32];
} PtsPopSub;

typedef struct PtsPopObj {
    char pad[3368];
    PtsPopSub sub;
} PtsPopObj;

void sfd_Lock(void *lock);
void sfd_Unlock(void *lock);

int FUN_0029ef38(PtsPopObj *obj, int *item, int *last)
{
    PtsPopSub *sub = &obj->sub;
    char lock[16];
    int ok;

    sfd_Lock(lock);
    if (sub->wr - sub->rd <= 0) {
        *item = -1;
        ok = 0;
    } else {
        ok = 1;
        *last = sub->last;
        *item = sub->items[sub->rd % 32];
        sub->rd++;
    }
    sfd_Unlock(lock);
    return ok;
}
