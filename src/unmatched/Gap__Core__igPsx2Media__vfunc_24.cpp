struct MediaResult { int v; MediaResult() {} MediaResult(const MediaResult &o) : v(o.v) {} };
struct MediaSema {
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
 virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
 virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
 virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
 virtual MediaResult release();
 virtual void d30();
 virtual MediaResult wait(int);
};
struct MediaHandlePool { unsigned short limit; unsigned short capacity; unsigned short count; short pad; short *freeList; };
struct MediaFields { int p0; int p4; int p8; int connection; MediaSema *sema; int p14; int p18; MediaHandlePool *pool; };
extern "C" {
void *Memory_ReallocateBuffer(void *, int);
void Gap__Core__igPsx2Media__vfunc_24(MediaFields *media, int handle);
}
void Gap__Core__igPsx2Media__vfunc_24(MediaFields *media, int handle) {
    media->sema->wait(1);
    MediaHandlePool *pool = media->pool;
    if (handle < pool->limit && handle >= 0) {
        if (pool->count >= pool->capacity) {
            pool->capacity += 8;
            pool->freeList = (short *)Memory_ReallocateBuffer(pool->freeList, pool->capacity * 2);
        }
        pool->freeList[pool->count] = handle;
        pool->count++;
    }
    media->sema->release();
}
