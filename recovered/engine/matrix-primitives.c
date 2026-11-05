/* Complete copy/translation helper run, 0x1908f0..0x190b24. Behavioral C.
 * Words carry raw float bits. Guest-address alignment controls copy semantics. */
#include "matrix-primitives.h"
#include "../frontend/eefloat.h"
#define P(x) a->read(a->user,(x))
#define W(x,v) a->write(a->user,(x),(v))
void dw4_matrix_copy(const Dw4MatrixApi *a,uint32_t destination,uint32_t source)
{
    unsigned i;
    if (!((destination|source)&15u)) {
        uint32_t words[16];
        for(i=0;i<16;i++) words[i]=P(source+i*4);
        for(i=0;i<16;i++) W(destination+i*4,words[i]);
    } else {
        for(i=0;i<16;i++) W(destination+i*4,P(source+i*4));
    }
}
void dw4_matrix_set_translation(const Dw4MatrixApi *a,uint32_t matrix,uint32_t vector)
{
    unsigned i;
    for(i=0;i<3;i++) W(matrix+48+i*4,P(vector+i*4));
}
void dw4_matrix_get_translation(const Dw4MatrixApi *a,uint32_t matrix,uint32_t vector)
{
    unsigned i;
    for(i=0;i<3;i++) W(vector+i*4,P(matrix+48+i*4));
}
void dw4_matrix_from_translation(const Dw4MatrixApi *a,uint32_t matrix,uint32_t vector)
{
    unsigned i;
    for(i=0;i<12;i++) W(matrix+i*4,i%5==0?0x3f800000u:0);
    dw4_matrix_set_translation(a,matrix,vector);
    W(matrix+60,0x3f800000u);
}
void dw4_matrix_translate_local(const Dw4MatrixApi *a,uint32_t matrix,uint32_t vector)
{
    unsigned row;
    for(row=0;row<4;row++) {
        uint32_t x=P(vector),y=P(vector+4),z=P(vector+8);
        uint32_t first=ee_f32_mul(P(matrix+row*4),x);
        uint32_t second=ee_f32_mul(P(matrix+16+row*4),y);
        uint32_t sum=ee_f32_add(first,second);
        sum=ee_f32_add(sum,ee_f32_mul(P(matrix+32+row*4),z));
        W(matrix+48+row*4,ee_f32_add(P(matrix+48+row*4),sum));
    }
}
