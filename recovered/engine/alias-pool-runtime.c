/* Original alias-pool methods. Widths/order follow retail instructions, #902. */
#include "alias-pool-runtime.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define Q(p) a->read(a->user,(p),8)
#define B(p) ((uint32_t)a->read(a->user,(p),1))
#define H(p) ((uint32_t)a->read(a->user,(p),2))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define S(p,n,v) a->write(a->user,(p),(n),(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[12]){__VA_ARGS__})
static uint64_t word(uint32_t x){return (uint64_t)(int64_t)(int32_t)x;}
static uint32_t method(const Dw4MessengerResultsApi *a,uint32_t p,unsigned slot){return P(P(p)+slot);}
static void retain(const Dw4MessengerResultsApi *a,uint32_t p){if(p)W(p+4,P(p+4)+1);}
static void release(const Dw4MessengerResultsApi *a,uint32_t p){
    if(p){W(p+4,P(p+4)-1);if(!(P(p+4)&0x7fffff))CALL(0x2ff820,word(p));}
}
uint64_t dw4_alias_pool_runtime(const Dw4MessengerResultsApi *a,uint32_t entry,const uint64_t v[8],uint32_t scratch){
    uint32_t self=(uint32_t)v[0],out=self;
    switch(entry){
    case 0x2cd170:case 0x2d0560:case 0x2d0600:case 0x2d0620:case 0x2d0640:
    case 0x2d0670:case 0x2d0680:case 0x2d0690:case 0x2d06a0:case 0x2d06b0:
        return dw4_alias_pool_binding(a,entry,v);
    case 0x2d06c0:{
        self=(uint32_t)v[1];unsigned mode=(uint8_t)v[2];
        if(mode==0){
            uint32_t lock=P(self+116);retain(a,lock);release(a,P(self+116));W(self+116,0);
            if(lock){CALL(method(a,lock,132),scratch,word(lock),1);CALL(method(a,lock,96),scratch+4,word(lock));}
            release(a,lock);
        }else if(mode==1&&!P(self+116)){
            uint32_t allocator=(uint32_t)CALL(0x301000,v[1]);
            uint32_t lock=(uint32_t)CALL(0x2ba650,word(allocator));
            CALL(method(a,lock,92),scratch+8,word(lock));
            retain(a,lock);release(a,P(self+116));W(self+116,lock);release(a,lock);
        }
        W(out,P(0x4fb410));return 0;
    }
    case 0x2d08b0:W(out,P(0x4fb418));return 0;
    case 0x2d08c0:return 0;
    case 0x2d08d0:S((uint32_t)v[1]+144,8,v[2]);W(out,P(0x4fb410));return 0;
    case 0x2d08f0:return Q(self+144);
    case 0x2d0900:S((uint32_t)v[1]+176,2,v[2]);W(out,P(0x4fb410));return 0;
    case 0x2d0920:return H(self+176);
    case 0x2d0930:W((uint32_t)v[1]+172,v[2]);W(out,P(0x4fb410));return 0;
    case 0x2d0950:return word(P(self+172));
    case 0x2d0960:CALL(0x2f0880,scratch);W(out,P(scratch));return 0;
    case 0x2d0990:case 0x2d09e0:return Q(self+144)-Q(self+128);
    case 0x2d09a0:case 0x2d09b0:return Q(self+128);
    case 0x2d09c0:case 0x2d09d0:return Q(self+160);
    case 0x2d09f0:return CALL(method(a,self,216),v[0],word(P(self+172)));
    case 0x2d0a10:{uint32_t lock=P(self+116);if(lock)CALL(method(a,lock,132),scratch,word(lock),1);return 0;}
    case 0x2d0a50:case 0x2d0a80:{
        uint32_t lock=P(self+116);if(lock)CALL(method(a,lock,124),scratch,word(lock));
        return entry==0x2d0a80?v[1]:0;
    }
    case 0x2d0ac0:return CALL(method(a,self,412),v[0],0,v[1],H(self+176));
    case 0x2d0ae0:return CALL(method(a,self,412),v[0],0,v[1],v[2]);
    case 0x2d0b00:case 0x2d0b70:{
        uint64_t size=word((uint32_t)((uint64_t)(uint32_t)v[1]*(uint32_t)v[2]));
        uint64_t result=CALL(method(a,self,412),v[0],0,size,entry==0x2d0b00?H(self+176):v[3]);
        if(result&&size)CALL(0x12724c,result,0,size);
        return result;
    }
    case 0x2d0be0:return CALL(method(a,self,412),v[0],v[1],v[2],H(self+176));
    case 0x2d0c00:return CALL(method(a,self,412),v[0],v[1],v[2],v[3]);
    case 0x2d0c10:{
        if(!P(self+180))return 0;
        uint32_t alias=P(self+180);
        uint64_t before=CALL(method(a,alias,192),word(alias));
        alias=P(self+180);uint64_t result=CALL(method(a,alias,260),word(alias),v[1]);
        alias=P(self+180);uint64_t after=CALL(method(a,alias,192),word(alias));
        if(B(self+104))CALL(method(a,self,200),v[0],v[1],word((uint32_t)(after-before)),1);
        return result;
    }
    case 0x2d0cd0:case 0x2d0d10:{
        uint32_t alias=P((uint32_t)v[1]+180);
        if(alias)CALL(method(a,alias,entry==0x2d0cd0?248:252),v[0],word(alias));
        else W(out,P(0x4fb418));
        return 0;
    }
    case 0x2d0d50:{uint32_t alias=P(self+180);if(alias)CALL(method(a,alias,256),word(alias));return 0;}
    case 0x2d0d80:return CALL(method(a,self,412),v[0],v[1],UINT64_MAX,H(self+176));
    case 0x2d0da0:{
        if(B(self+113)){
            uint64_t index=word(P(self+120));uint32_t alias=P(self+180);
            return index==CALL(method(a,alias,380),word(alias));
        }
        CALL(0x2f0180,scratch,v[1],scratch+4);
        return P(scratch)==P(0x4fb410)&&P(scratch+4)==self;
    }
    case 0x2d0e30:{uint32_t alias=P(self+180);return CALL(method(a,alias,336),word(alias),v[1]);}
    case 0x2d0e50:{
        if(v[1]&&B((uint32_t)v[1])){CALL(0x304430,0x4f90b0,v[1]);CALL(0x304680);}
        uint32_t frees=P(self+140),allocs=P(self+136),high=P(self+168);
        uint64_t net=word(allocs-frees),name;
        if(CALL(method(a,self,396),v[0]))name=CALL(0x2f89a0,CALL(method(a,self,396),v[0]));
        else name=0x4f90b8;
        uint64_t current=word((uint32_t)CALL(method(a,self,188),v[0]));
        uint64_t bytes=word((uint32_t)CALL(method(a,self,192),v[0]));
        uint64_t peak=word((uint32_t)CALL(method(a,self,404),v[0]));
        uint64_t peak2=word((uint32_t)CALL(method(a,self,408),v[0]));
        uint64_t max=word((uint32_t)CALL(method(a,self,168),v[0]));
        uint64_t index=CALL(method(a,self,364),v[0]);
        CALL(0x304430,0x4f90c0,name,current,bytes,peak,peak2,word(allocs),word(frees),net,word(high),max,index);
        CALL(0x304680);return 0;
    }
    case 0x2d1020:return word(P(self+152));
    case 0x2d1030:{uint32_t tracker=(uint32_t)v[1];retain(a,tracker);release(a,P(self+152));W(self+152,tracker);return 0;}
    case 0x2d10b0:{
        CALL(0x2d0a10,v[0]);
        if(v[4]){
            uint32_t allocator=(uint32_t)CALL(0x301000,v[0]);
            uint32_t file=(uint32_t)CALL(0x2c4ca0,word(allocator));
            if(!CALL(method(a,file,100),word(file),v[4],0x4f92f0)){
                CALL(0x2d0a50,v[0]);release(a,file);return 0;
            }
            CALL(method(a,file,124),word(file),0x4f92b0);CALL(method(a,file,104),word(file));release(a,file);
        }else CALL(0x128528,0x4f92b0);
        CALL(0x2d0a50,v[0]);return 0;
    }
    case 0x2d11f0:return word(P(self+120));
    case 0x2d1200:W(self+120,v[1]);return 0;
    case 0x2d1210:{
        uint64_t old=v[1],size=v[2],alignment=v[3],result=0;
        CALL(0x2d0a10,v[0]);
        if((alignment&0xffff)<H(self+176))alignment=H(self+176);
        if(size==UINT64_MAX){
            if(!old){CALL(0x2d0a50,v[0]);return 0;}
            uint64_t bytes=word((uint32_t)CALL(method(a,self,336),v[0],old));
            S(self+128,8,Q(self+128)-bytes);W(self+140,P(self+140)+1);
            if(B(self+113)){
                uint32_t alias=P(self+180);CALL(method(a,alias,372),scratch,word(alias),old,word(alias));
            }else CALL(0x2f0320,scratch,old,v[0]);
            uint32_t alias=P(self+180);CALL(method(a,alias,264),word(alias),old);
            return CALL(0x2d0a80,v[0],0);
        }
        while(Q(self+128)+word((uint32_t)size)>Q(self+144)){
            if(!CALL(method(a,self,92),v[0],size,1))return CALL(0x2d0a80,v[0],0);
        }
        if(old){
            if(P(self+180)){
                uint64_t bytes=word((uint32_t)CALL(method(a,self,336),v[0],old));
                S(self+128,8,Q(self+128)-bytes);W(self+140,P(self+140)+1);
                if(B(self+113)){
                    uint32_t alias=P(self+180);CALL(method(a,alias,372),scratch+4,word(alias),old,word(alias));
                }else CALL(0x2f0320,scratch+8,old,v[0]);
                uint32_t alias=P(self+180);result=CALL(method(a,alias,236),word(alias),old,size,alignment);
            }
        }else{
            uint32_t alias=P(self+180);if(alias)result=CALL(method(a,alias,220),word(alias),size,alignment);
        }
        if(result){
            S(self+128,8,Q(self+128)+word((uint32_t)size));
            if(Q(self+160)<Q(self+128))S(self+160,8,Q(self+128));
            W(self+136,P(self+136)+1);uint32_t live=P(self+136)-P(self+140);
            if((int32_t)P(self+168)<(int32_t)live)W(self+168,live);
            if(B(self+113)){
                uint32_t alias=P(self+180);CALL(method(a,alias,372),scratch+12,word(alias),result,v[0]);
            }else CALL(0x2f0220,scratch+16,result,v[0]);
        }
        return CALL(0x2d0a80,v[0],result);
    }
    case 0x2d1500:case 0x2d1540:case 0x2d1590:
        CALL(entry==0x2d1500?0x2eff70:entry==0x2d1540?0x2effb0:0x2efff0,v[0],v[1]);
        W(self,0x5313a0);W(self+116,0);W(self+152,0);W(self+180,0);
        if(entry==0x2d1540&&v[0])CALL(0x2d1500,v[0]);
        return v[0];
    case 0x2d15d0:
        release(a,P(self+180));CALL(method(a,self,392),v[0]);CALL(0x2f0030,v[0]);return 0;
    default:return UINT64_MAX;
    }
}
