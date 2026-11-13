typedef struct PtsPushSub {
    char pad[492];
    int last;
    int f496;
    int wr;
    int rd;
    int items[32];
} PtsPushSub;

typedef struct PtsPushObj {
    char pad[3368];
    PtsPushSub sub;
} PtsPushObj;

void sfd_Lock(void *lock);
void sfd_Unlock(void *lock);

int FUN_0029ee80(PtsPushObj *obj, int item, int last)
{
    PtsPushSub *sub = &obj->sub;
    char lock[16];
    int ok = 0;

    sfd_Lock(lock);
    if (sub->wr - sub->rd < 32) {
        sub->last = last;
        sub->items[sub->wr % 32] = item;
        ok = 1;
        sub->wr++;
    }
    sfd_Unlock(lock);
    return ok;
}
