#include "dw4/cri/sfdhn.h"

enum {
    SFD_COND_LNKSTM = 49,
    SFD_COND_SUPPLY_END = 56,
    SFD_COND_DECODE_END = 57
};

int sfd_ReportError(SfdHandle *hn, int code);
int SFLIB_CheckHn(SfdHandle *hn);
void sfd_Lock(void *guard);
void sfd_Unlock(void *guard);
int SFD_GetCond(SfdHandle *hn, int index);
void sfd_SetCond(SfdHandle *hn, int index, int value);

int SFD_SetLnkStm(SfdHandle *hn) {
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000161);
    }
    sfd_SetCond(hn, SFD_COND_LNKSTM, 1);
    return 0;
}

int sfd_IsLnkStm(SfdHandle *hn) {
    return SFD_GetCond(hn, SFD_COND_LNKSTM) != 0;
}

int sfd_IsSupplyEnd(SfdHandle *hn) {
    if (SFD_GetCond(hn, SFD_COND_LNKSTM) != 0 || SFD_GetCond(hn, SFD_COND_SUPPLY_END) != 0) {
        return 1;
    }
    return 0;
}

int sfd_IsDecodeEnd(SfdHandle *hn) {
    if (SFD_GetCond(hn, SFD_COND_LNKSTM) != 0 || SFD_GetCond(hn, SFD_COND_DECODE_END) != 0) {
        return 1;
    }
    return 0;
}

/* matching construct: manual — declared int with no return statement (implicit-int style), which keeps the final call a jal */
int sfsync_AddTotal(SfdHandle *hn, int amount) {
    char guard[16];
    SfdTimView *tim = &hn->tim;
    int total;
    int count;

    sfd_Lock(guard);
    total = tim->tally.total + amount;
    count = tim->tally.count;
    count++; /* matching construct: manual — separate increment stops count + 1 + 31 folding into + 32 */
    tim->tally.total = total;
    tim->tally.history[count % 32] = total;
    tim->tally.count = count;
    sfd_Unlock(guard);
}

int sfsync_PushPts(SfdHandle *hn, int pts, int last) {
    SfdTimView *tim = &hn->tim;
    char guard[16];
    int ok = 0;

    sfd_Lock(guard);
    if (tim->queue.wr - tim->queue.rd < 32) {
        tim->queue.last = last;
        tim->queue.items[tim->queue.wr % 32] = pts;
        ok = 1;
        tim->queue.wr++;
    }
    sfd_Unlock(guard);
    return ok;
}

int sfsync_PopPts(SfdHandle *hn, int *pts, int *last) {
    SfdTimView *tim = &hn->tim;
    char guard[16];
    int ok;

    sfd_Lock(guard);
    if (tim->queue.wr - tim->queue.rd <= 0) {
        *pts = -1;
        ok = 0;
    } else {
        ok = 1;
        *last = tim->queue.last;
        *pts = tim->queue.items[tim->queue.rd % 32];
        tim->queue.rd++;
    }
    sfd_Unlock(guard);
    return ok;
}

