extern "C" long long __fixsfdi(float);
extern "C" long long FUN_00398e80(int, long long);
extern "C" int FUN_001ac140(int, long long);
typedef struct Clock { char p[80]; long long time; } Clock;
typedef struct Node { char p[120]; float scale; } Node;
typedef struct Work { char p[20]; int state; } Work;
typedef struct Owner { char p[12]; Clock *clock; } Owner;
typedef struct Piece { char p[28]; char flag; char q[27]; float rate; char r[4]; long long pos; long long getPos() const { return pos; } } Piece;
typedef struct Pieces { char p[8]; int count; char q[4]; Piece **items; } Pieces;
typedef struct Track { char p[56]; Pieces *pieces; } Track;
typedef struct Tracks { char p[16]; Track **items; } Tracks;
typedef struct Sys { char p[36]; Tracks *tracks; } Sys;
typedef struct Ctx { char p[32]; Sys *sys; } Ctx;
typedef struct Act { char p[8]; int index; Ctx *ctx; char q[28]; Node *node; char r[8]; Work *work; } Act;

extern "C" void beAction2MOTIONSET_Update(Owner *arg0, Act *arg1) {
    Track *track;
    int n;
    int i;
    Work *work;
    Pieces *pieces;
    Piece *first;
    float f;
    float rate;
    Node *node;
    long long v;
    long long d;
    long long p;

    work = arg1->work;
    switch (work->state) {
    case 1:
        work->state = 2;
        return;
    case 2:
        track = arg1->ctx->sys->tracks->items[arg1->index];
        pieces = track->pieces;
        if (pieces->count != 1) {
            v = FUN_00398e80((int)arg1->node, arg0->clock->time);
            FUN_001ac140((int)track, v);
            n = track->pieces->count;
            i = 0;
            while (i < n) {
                track->pieces->items[i]->flag = 0;
                i++;
            }
        }
        if (pieces->count == 1) {
            if (pieces->items[0]->rate != arg1->node->scale) {
                v = FUN_00398e80((int)arg1->node, arg0->clock->time);
                node = arg1->node;
                rate = node->scale;
                first = pieces->items[0];
                f = (float)(unsigned int)(int)(v >> 18);
                d = __fixsfdi(f * first->rate);
                p = first->getPos();
                first->pos = (d << 18) + p;
                first->pos = first->pos - (__fixsfdi(f * rate) << 18);
                first->rate = rate;
            }
            work->state = 0;
        }
        break;
    }
}
