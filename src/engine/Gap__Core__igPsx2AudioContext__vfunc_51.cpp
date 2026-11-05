/* 0x00144680
 * Issue IOP audio RPC command 0x10000 on the context's connection and return
 * the 32-byte reply block it fills.  The block is allocated from the
 * context's own allocator (igObject_GetAllocator reads the allocator index
 * from the object in a0, which is still `self` at that call, so the
 * argument-less spelling is the one that matches).  The allocator's virtual
 * at vtable byte offset 220 takes size 32 and alignment 16, because the RPC
 * wrapper FUN_0032d6d0 requires 16-byte-aligned buffers and sizes (its asm
 * tests each with `andi 0xf`).  The caller owns the returned block.
 * The sibling vfunc_52 sends command 0xE0000 and unpacks four ints; the
 * layout of this reply is not recovered. */
#include "dw4/reflected.h"
extern "C" {
void **igObject_GetAllocator(...);
/* The IOP RPC call wrapper: waits on the connection's semaphore, calls the SIF
 * RPC entry (FUN_0010e2a8) and signals the semaphore again.  Arguments are
 * (status out, connection, command, send buffer, send size, reply buffer,
 * reply size, completion callback). */
int FUN_0032d6d0(...);
int Gap__Core__igPsx2AudioContext__vfunc_51(igPsx2AudioContext *self);
}
/* Dummy class: allocator virtual at vtable byte offset 220 (53 slots precede it). */
class AllocatorAllocateSlot {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34();
    virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44();
    virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49();
    virtual void d50(); virtual void d51(); virtual void d52();
    virtual int Allocate(int size, int alignment);
};
int Gap__Core__igPsx2AudioContext__vfunc_51(igPsx2AudioContext *self) {
    int rpcStatus;
    int replyBuffer;
    void **allocator;

    allocator = (void **)(igObject_GetAllocator());
    replyBuffer = ((AllocatorAllocateSlot *)(allocator))->Allocate((int)(0x20), (int)(0x10));
    FUN_0032d6d0(&rpcStatus, self->_connection, 0x10000, 0, 0, replyBuffer, 0x20, 0);
    return replyBuffer;
}
