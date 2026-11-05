#include "dw4/reflected.h"
/* float -> nanosecond-tick conversion helper */
extern "C" long long FUN_00230110(float);
typedef struct Clock { char p[80]; long long time; } Clock;
typedef struct Node { char p[120]; float scale; char q[4]; long long bias; } Node;
typedef struct Work { char p[28]; int state; long long start; long long end; char isEnd; } Work;
typedef struct Owner { char p[12]; Clock *clock; } Owner;

/* matching construct: _work/_node/_loopMode are 4-byte reference fields in the reflected structs; the casts give the typed views (no layout effect) */
extern "C" int beAction2JOINTSET_Start(Owner *arg0, beAction2InfoRam *arg1, beAction2JOINTSET *arg2) {
    long long start;
    Work *work;
    Node *node;
    long long t;
    float f;

    work = (Work *)arg1->_work;
    if (*(char *)arg2->_loopMode == 0x4C) {
        work->state = 1;
    } else {
        work->state = 2;
    }
    float m = arg2->_startTime;
    float n = 1e9f * m;
    work->start = FUN_00230110(n / 60.0f);
    m = arg2->_endTime;
    n = 1e9f * m;
    m = n / 60.0f;
    work->end = FUN_00230110(m);
    t = (int)(arg0->clock->time >> 18);
    node = (Node *)arg1->_node;
    f = (float)(unsigned int)(int)t;
    f = f * node->scale;
    start = work->start;
    node->bias = start - (FUN_00230110(f) << 18);
    work->isEnd = 0;
    return 1;
}
