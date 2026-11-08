/* newlib_mallocr.h -- boundary-tag allocator (Doug Lea's malloc 2.6.x as shipped in newlib's mallocr.c).
 * Evidence: FUN_001253e8 walks chunk headers {prev_size, size, fd, bk}, the bin array at 0x4854b0,
 * the size-class ladder (>>3, >>6, >>9, >>12, >>15, >>18 / 126), the binblocks bitmap and the
 * trim threshold, which is the structure of that allocator. */
#ifndef NEWLIB_MALLOCR_H
#define NEWLIB_MALLOCR_H
typedef struct Reent Reent;
typedef unsigned int INTERNAL_SIZE_T;
typedef struct malloc_chunk {
    INTERNAL_SIZE_T prev_size;
    INTERNAL_SIZE_T size;
    struct malloc_chunk *fd;
    struct malloc_chunk *bk;
} *mchunkptr;
typedef struct malloc_chunk *mbinptr;

extern mbinptr D_004854b0[];            /* malloc_av_ */
extern unsigned long D_004858b8;         /* trim_threshold */
extern unsigned long D_004858c0;         /* top_pad */
extern char *D_004858c8;                 /* sbrk_base */
extern unsigned long D_004858d0;         /* max_sbrked_mem */
extern unsigned long D_004858d8;         /* max_total_mem */
struct mallinfo { int arena; int ordblks; int smblks; int hblks; int hblkhd; int usmblks; int fsmblks; int uordblks; int fordblks; int keepcost; };
extern struct mallinfo D_004858e0;          /* current_mallinfo */
extern char *FUN_00129828(Reent *, int); /* _sbrk_r */
extern void FUN_00127310(Reent *);       /* __malloc_lock */
extern void FUN_00127390(Reent *);       /* __malloc_unlock */
extern int FUN_001256e0(Reent *, unsigned int);   /* malloc_trim */

#define SIZE_SZ 4
#define PREV_INUSE 0x1
#define SIZE_BITS 0x3
#define MAX_SMALLBIN_SIZE 512
#define BINBLOCKWIDTH 4
#define av_ D_004854b0
#define bin_at(i) ((mbinptr)((char *)&(av_[2 * (i) + 2]) - 2 * SIZE_SZ))
#define top (av_[2])
#define last_remainder (bin_at(1))
#define binblocks (bin_at(0)->size)
#define trim_threshold D_004858b8
#define top_pad D_004858c0
#define sbrk_base D_004858c8
#define max_sbrked_mem D_004858d0
#define max_total_mem D_004858d8
#define current_mallinfo D_004858e0
#define sbrked_mem (current_mallinfo.arena)
#define mmapped_mem 0
#define MINSIZE 16
#define MALLOC_ALIGN_MASK 15
#define MALLOC_ALIGNMENT 16
#define initial_top ((mchunkptr)(bin_at(0)))
#define MORECORE(x) FUN_00129828(reent_ptr, x)
#define MORECORE_FAILURE (-1)
#define set_head_size(p, s) ((p)->size = (((p)->size & PREV_INUSE) | (s)))
#define chunk2mem(p) ((void *)((char *)(p) + 2 * SIZE_SZ))
#define mem2chunk(mem) ((mchunkptr)((char *)(mem) - 2 * SIZE_SZ))
#define chunk_at_offset(p, s) ((mchunkptr)(((char *)(p)) + (s)))
#define chunksize(p) ((p)->size & ~(SIZE_BITS))
#define inuse_bit_at_offset(p, s) (((mchunkptr)(((char *)(p)) + (s)))->size & PREV_INUSE)
#define set_head(p, s) ((p)->size = (s))
#define set_foot(p, s) (((mchunkptr)((char *)(p) + (s)))->prev_size = (s))
#define idx2binblock(ix) ((unsigned long)1 << ((ix) / BINBLOCKWIDTH))
#define mark_binblock(ii) (binblocks |= idx2binblock(ii))
#define smallbin_index(sz) (((unsigned long)(sz)) >> 3)
#define bin_index(sz) \
    (((((unsigned long)(sz)) >> 9) == 0) ? (((unsigned long)(sz)) >> 3) : \
     ((((unsigned long)(sz)) >> 9) <= 4) ? 56 + (((unsigned long)(sz)) >> 6) : \
     ((((unsigned long)(sz)) >> 9) <= 20) ? 91 + (((unsigned long)(sz)) >> 9) : \
     ((((unsigned long)(sz)) >> 9) <= 84) ? 110 + (((unsigned long)(sz)) >> 12) : \
     ((((unsigned long)(sz)) >> 9) <= 340) ? 119 + (((unsigned long)(sz)) >> 15) : \
     ((((unsigned long)(sz)) >> 9) <= 1364) ? 124 + (((unsigned long)(sz)) >> 18) : 126)
#define unlink(P, BK, FD) \
    { \
        BK = P->bk; \
        FD = P->fd; \
        FD->bk = BK; \
        BK->fd = FD; \
    }
#define link_last_remainder(P) \
    { \
        last_remainder->fd = last_remainder->bk = P; \
        P->fd = P->bk = last_remainder; \
    }
#define frontlink(P, S, IDX, BK, FD) \
    { \
        if (S < MAX_SMALLBIN_SIZE) { \
            IDX = smallbin_index(S); \
            mark_binblock(IDX); \
            BK = bin_at(IDX); \
            FD = BK->fd; \
            P->bk = BK; \
            P->fd = FD; \
            FD->bk = BK->fd = P; \
        } else { \
            IDX = bin_index(S); \
            BK = bin_at(IDX); \
            FD = BK->fd; \
            if (FD == BK) \
                mark_binblock(IDX); \
            else { \
                while (FD != BK && S < chunksize(FD)) \
                    FD = FD->fd; \
                BK = FD->bk; \
            } \
            P->bk = BK; \
            P->fd = FD; \
            FD->bk = BK->fd = P; \
        } \
    }


#define request2size(req) \
    ((((req) + (SIZE_SZ + MALLOC_ALIGN_MASK)) < (unsigned int)(MINSIZE + MALLOC_ALIGN_MASK)) ? MINSIZE : \
     (((req) + (SIZE_SZ + MALLOC_ALIGN_MASK)) & ~(MALLOC_ALIGN_MASK)))
#define prev_inuse(p) ((p)->size & PREV_INUSE)
#define inuse(p) ((((mchunkptr)(((char *)(p)) + ((p)->size & ~PREV_INUSE)))->size) & PREV_INUSE)
#define next_chunk(p) ((mchunkptr)(((char *)(p)) + ((p)->size & ~PREV_INUSE)))
#define prev_chunk(p) ((mchunkptr)(((char *)(p)) - ((p)->prev_size)))
#define set_inuse_bit_at_offset(p, s) (((mchunkptr)(((char *)(p)) + (s)))->size |= PREV_INUSE)
extern void *memcpy(void *, const void *, unsigned int);
extern void *FUN_00126600(Reent *, unsigned int);                /* _malloc_r */
#define MALLOC_COPY(dest,src,nbytes)                                          \
do {                                                                          \
  INTERNAL_SIZE_T mcsz = (nbytes);                                            \
  if(mcsz <= 9*sizeof(mcsz)) {                                                \
    INTERNAL_SIZE_T* mcsrc = (INTERNAL_SIZE_T*) (src);                        \
    INTERNAL_SIZE_T* mcdst = (INTERNAL_SIZE_T*) (dest);                       \
    if(mcsz >= 5*sizeof(mcsz)) {     *mcdst++ = *mcsrc++;                     \
                                     *mcdst++ = *mcsrc++;                     \
      if(mcsz >= 7*sizeof(mcsz)) {   *mcdst++ = *mcsrc++;                     \
                                     *mcdst++ = *mcsrc++;                     \
        if(mcsz >= 9*sizeof(mcsz)) { *mcdst++ = *mcsrc++;                     \
                                     *mcdst++ = *mcsrc++; }}}                 \
                                     *mcdst++ = *mcsrc++;                     \
                                     *mcdst++ = *mcsrc++;                     \
                                     *mcdst   = *mcsrc  ;                     \
  } else memcpy(dest, src, mcsz);                                             \
} while(0)
#endif
