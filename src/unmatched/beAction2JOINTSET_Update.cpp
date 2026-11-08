extern "C" long long __fixsfdi(float);
extern "C" long long FUN_00398e80(int, long long);
typedef struct Clock { char p[80]; long long time; } Clock;
typedef struct Node { char p[120]; float scale; char q[4]; long long bias; } Node;
typedef struct Work { char p[28]; int state; long long start; long long end; char isEnd; } Work;
typedef struct Owner { char p[12]; Clock *clock; } Owner;
typedef struct Act { char p[44]; Node *node; char q[8]; Work *work; } Act;

extern "C" void beAction2JOINTSET_Update(Owner *arg0, Act *arg1) {
    Work *work;
    long long now;
    long long end;
    bool changed;
    int state;
    long long t;
    Node *node;
    float f;

    work = arg1->work;
    state = work->state;
    if (state == 2) goto body;
    if (state == 1) goto body;
    if (state == 0) return;
    return;
    body:
    {
        now = FUN_00398e80((int)arg1->node, arg0->clock->time);
        end = work->end;
        changed = false;
        if (end < now) {
            state = work->state;
            do {
                switch (state) {
                case 1:
                    changed = true;
                    now += work->start - end;
                    break;
                case 2:
                    now = end;
                    changed = true;
                    break;
                }
            } while (now > end);
        }
        if (changed) {
            node = arg1->node;
            f = (float)(unsigned int)(int)(arg0->clock->time >> 18);
            f = f * node->scale;
            node->bias = now - (__fixsfdi(f) << 18);
            work->isEnd = 1;
        }
    }
}
