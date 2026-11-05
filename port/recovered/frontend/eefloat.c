#include "eefloat.h"
#define MAXF 0x7fffffffu
typedef struct { int sign; uint32_t mant; int e2; } Unpacked;   /* value = mant * 2^e2 */
static Unpacked unpack(ee_f32 b)
{
    Unpacked u;
    int e=(int)((b>>23)&255);
    u.sign=(int)(b>>31);
    if(!e){u.mant=0;u.e2=0;}
    else{u.mant=0x800000u|(b&0x7fffffu);u.e2=e-127-23;}
    return u;
}
static ee_f32 pack(int sign,uint64_t mant,int e2)
{
    int n=0,biased;
    uint64_t t;
    if(!mant)return (ee_f32)sign<<31;
    for(t=mant;t;t>>=1)++n;
    if(n>24){mant>>=n-24;e2+=n-24;}
    else{mant<<=24-n;e2-=24-n;}
    biased=e2+23+127;
    if(biased>=256)return ((ee_f32)sign<<31)|MAXF;
    if(biased<=0)return (ee_f32)sign<<31;
    return ((ee_f32)sign<<31)|((ee_f32)biased<<23)|(ee_f32)(mant&0x7fffffu);
}
ee_f32 ee_f32_mul(ee_f32 a,ee_f32 b)
{
    Unpacked x=unpack(a),y=unpack(b);
    if(!x.mant||!y.mant)return (ee_f32)(x.sign^y.sign)<<31;
    return pack(x.sign^y.sign,(uint64_t)x.mant*y.mant,x.e2+y.e2);
}
ee_f32 ee_f32_div(ee_f32 a,ee_f32 b)
{
    Unpacked x=unpack(a),y=unpack(b);
    if(!y.mant)return ((ee_f32)(x.sign^y.sign)<<31)|MAXF;
    if(!x.mant)return (ee_f32)(x.sign^y.sign)<<31;
    /* (mx<<32)/my has at least 32 significant bits, so truncating it to 24
     * bits equals truncating the exact quotient. */
    return pack(x.sign^y.sign,((uint64_t)x.mant<<32)/y.mant,x.e2-y.e2-32);
}
static ee_f32 add_signed(Unpacked x,Unpacked y)
{
    int64_t va,vb,v;
    int e,d;
    if(!x.mant&&!y.mant)return (ee_f32)(x.sign&y.sign)<<31;
    if(!x.mant)return pack(y.sign,y.mant,y.e2);
    if(!y.mant)return pack(x.sign,x.mant,x.e2);
    /* Keep x as the operand with the larger exponent. */
    if(y.e2>x.e2){Unpacked t=x;x=y;y=t;}
    d=x.e2-y.e2;
    if(d>30){
        /* y lies below 2^-6 ulp of x: only its sign and non-zeroness can
         * influence a truncated sum, so a sticky bit stands in for it. */
        y.mant=1;y.e2=x.e2-38;d=38;
    }
    e=y.e2;
    va=(int64_t)((uint64_t)x.mant<<d);
    vb=(int64_t)y.mant;
    if(x.sign)va=-va;
    if(y.sign)vb=-vb;
    v=va+vb;
    if(!v)return 0;
    return pack(v<0,(uint64_t)(v<0?-v:v),e);
}
ee_f32 ee_f32_add(ee_f32 a,ee_f32 b){return add_signed(unpack(a),unpack(b));}
ee_f32 ee_f32_sub(ee_f32 a,ee_f32 b){Unpacked y=unpack(b);y.sign^=1;return add_signed(unpack(a),y);}
ee_f32 ee_f32_from_s32(int32_t v)
{
    uint64_t m=v<0?(uint64_t)(-(int64_t)v):(uint64_t)v;
    return pack(v<0,m,0);
}
int32_t ee_f32_trunc_s32(ee_f32 a)
{
    Unpacked u=unpack(a);
    uint64_t mag;
    if(!u.mant)return 0;
    if(u.e2>=0){
        if(u.e2>=8)mag=1u<<31;           /* >= 2^31 whatever the mantissa */
        else mag=(uint64_t)u.mant<<u.e2;
    }else mag=-u.e2>=24?0:(uint64_t)u.mant>>-u.e2;
    if(u.sign)return mag>=(1u<<31)?(int32_t)0x80000000u:(int32_t)(-(int64_t)mag);
    return mag>=(1u<<31)?(int32_t)MAXF:(int32_t)mag;
}
int ee_f32_cmp(ee_f32 a,ee_f32 b)
{
    Unpacked x=unpack(a),y=unpack(b);
    int xs=!x.mant?0:(x.sign?-1:1),ys=!y.mant?0:(y.sign?-1:1);
    if(!x.mant||!y.mant||xs!=ys)return xs<ys?-1:xs>ys;
    if(x.e2!=y.e2||x.mant!=y.mant){
        int bigger=x.e2!=y.e2?x.e2>y.e2:x.mant>y.mant;
        return (bigger?1:-1)*xs;
    }
    return 0;
}
int64_t ee_f32_to_s64(ee_f32 f)
{
    int neg=ee_f32_cmp(f,0)<0;
    Unpacked u=unpack(neg?(f^0x80000000u):f);
    uint64_t mag;
    if(!u.mant)mag=0;
    else if(u.e2>=41)mag=~(uint64_t)0;
    else if(u.e2>=0)mag=(uint64_t)u.mant<<u.e2;
    else mag=-u.e2>=24?0:(uint64_t)u.mant>>-u.e2;
    return (int64_t)(neg?(uint64_t)0-mag:mag);
}
ee_f32 ee_f32_from_u32(uint32_t u)
{
    ee_f32 f;
    if(!(u>>31))return ee_f32_from_s32((int32_t)u);
    f=ee_f32_from_s32((int32_t)((u>>1)|(u&1u)));
    return ee_f32_add(f,f);
}
ee_f32 ee_f32_from_clock_ticks(int64_t clock)
{
    return ee_f32_from_u32((uint32_t)((uint64_t)clock>>18));   /* low word of dsra 18 */
}
