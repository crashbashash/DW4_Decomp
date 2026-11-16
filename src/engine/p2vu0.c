/* VU0 ownership: code that runs a VU0 microcode program holds the VU0 lock around it (p2LockVu0,
 * whose C++ draft stays a function of its own, waits for it and counts the wait in
 * p2Vu0LockWaitTime). */
#include "dw4/eekernel.h"
#include "dw4/p2core.h"
#include "dw4/p2vu0.h"

#define P2_VU0_REQUESTS 64

/* A VU0 request record; the free ones form a list. */
typedef struct p2Vu0Request {
    struct p2Vu0Request *next;
    int f4;
    int f8;
} p2Vu0Request;

typedef struct p2Vu0Lock {
    int sema;
    int f4;
    int owner;
} p2Vu0Lock;

p2Vu0Lock p2Vu0LockState;
int p2Vu0LoadSema;
p2Vu0Request *p2FreeVu0Requests;
p2Vu0Request p2Vu0Requests[P2_VU0_REQUESTS];
int p2Vu0Program;
struct SemaParam p2Vu0LoadSemaParam = {0, 64, 0, 2, 0, 0};
struct SemaParam p2Vu0LockSemaParam = {0, 64, 1, 16, 0, 0};

int p2GetVu0Program(void) {
    return p2Vu0Program;
}

void p2InitVu0(void) {
    struct SemaParam loadParam;
    struct SemaParam lockParam;
    p2Vu0Request *request;
    p2Vu0Request **link;

    loadParam = p2Vu0LoadSemaParam;
    lockParam = p2Vu0LockSemaParam;
    if (p2FirstOpen != 0) {
        p2Vu0LoadSema = CreateSema(&loadParam);
        p2Vu0LockState.sema = CreateSema(&lockParam);
        link = &p2FreeVu0Requests;
        for (request = p2Vu0Requests; request < p2Vu0Requests + P2_VU0_REQUESTS; request++) {
            *link = request;
            request->next = 0;
            link = &request->next;
        }
    }
}

void p2UnlockVu0(void) {
    p2Vu0LockState.owner = 0;
    SignalSema(p2Vu0LockState.sema);
}
