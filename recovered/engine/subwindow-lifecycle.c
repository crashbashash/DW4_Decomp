/* Original beNDMWStatus lifecycle and mode-specific root selection, #905. */
#include "subwindow-lifecycle.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define B(p) ((uint32_t)a->read(a->user,(p),1))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define SB(p,v) a->write(a->user,(p),1,(uint8_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
enum { SELECT=0x38e5d0,STRING=0x38f830,INTEGER=0x38f250,DISPATCH=0x38e060,
       SEND=0x38e670,OBJECT=0x38f800,BOOLEAN=0x38f220,FREEZE=0x38d470 };
static uint64_t word(uint32_t value){return (uint64_t)(int64_t)(int32_t)value;}
static void release(const Dw4MessengerResultsApi *a,uint32_t object){
    if(object){W(object+4,P(object+4)-1);if(!(P(object+4)&0x7fffff))CALL(0x2ff820,word(object));}
}
static void advance(const Dw4MessengerResultsApi *a,uint32_t ram){
    W(ram+24,P(ram+24)+1);W(ram+36,0);W(ram+32,0);W(ram+28,0);
}
/* The receiver is reloaded for each call, as in retail. A callback may change
 * publication, mode, root, messenger or player records during this sequence. */
static void layer(const Dw4MessengerResultsApi *a,uint32_t owner,uint32_t name,uint32_t sequence){
    CALL(SELECT,word(P(owner+20)),0x5167b8); /* LAYERCTL */
    CALL(STRING,word(P(owner+20)),name);CALL(STRING,word(P(owner+20)),sequence);
    CALL(DISPATCH,word(P(owner+20)),0x5167d8);
}
uint64_t dw4_subwindow_lifecycle(const Dw4MessengerResultsApi *a,uint32_t entry,const uint64_t v[8],uint32_t scratch){
    uint32_t owner=(uint32_t)v[0],ram=(uint32_t)v[1];
    if(entry==0x3d5950)return word(P(0x58ac30));
    if(entry==0x3d9dd0)return word(P(0x58b028));
    if(entry==0x3d58f0){release(a,P(owner+32));W(owner+32,0);return 0;}
    if(entry==0x3d5960){
        if(P(P(owner+24)+8)==1){CALL(0x38d820,word(P(owner+20)),v[1],0x516788);SB(ram+20,0);}
        return 0;
    }
    if(entry==0x3d9bd0||entry==0x3d9c50||entry==0x3d9cd0||entry==0x3d9d50){
        if(v[0]){release(a,P(owner));if((int16_t)v[1]>0)CALL(0x100610,v[0]);}
        return v[0];
    }
    if(entry!=0x3d59b0)return UINT64_MAX;
    if(!B(ram+20))return 0;
    uint32_t state=P(ram+24);
    if(state==0){
        CALL(0x3d8740,v[0],v[1]); /* Separate menu/record preparation body. */
        CALL(SELECT,word(P(owner+20)),0x516790);
        CALL(STRING,word(P(owner+20)),0x5167a0);CALL(DISPATCH,word(P(owner+20)),0x5167a8);
        W(scratch+76,0);
        uint32_t root=0,mode=P(owner+40),constructor=0;
        if(mode==0){layer(a,owner,0x5167c8,0x5167d0);layer(a,owner,0x5167e0,0x5167d0);constructor=0x3bb1d0;}
        else if(mode==2)constructor=0x3b7750;
        else if(mode==10)constructor=0x3b7eb0;
        else if(mode<11)constructor=0x3b8d90;
        if(constructor){
            uint64_t allocator=CALL(0x301000,v[0]);
            if(!B(0x554c14))allocator=CALL(0x2f88e0,word(P(0x587110)));
            release(a,P(scratch+76));
            W(scratch+76,CALL(constructor,allocator));
        }
        /* Original does not guard null here. A valid mode/factory is required;
         * controlled callback tests do not establish invalid-enum safety. */
        CALL(0x3f63c0,word(P(scratch+76)),0,word(P(owner+12)),word(P(owner+36)),0);
        W(P(scratch+76)+44,P(owner+40));root=P(scratch+76);
        if(root)W(root+4,P(root+4)+1);
        release(a,P(owner+32));W(owner+32,root);
        if(P(owner+40)!=0){
            CALL(SEND,word(P(owner+20)),0x5167e8,0x5167f0);
            CALL(SEND,word(P(owner+20)),0x5167e8,0x5167f8);
            CALL(SELECT,word(P(owner+20)),0x5167e8);CALL(STRING,word(P(owner+20)),0x516800);
            CALL(DISPATCH,word(P(owner+20)),0x516810);
        }
        release(a,P(scratch+76));advance(a,ram);
    }else if(state!=1)goto finish;
    if(P(owner+32))CALL(0x3f6490,word(P(owner+32)));
    if(B(P(owner+32)+24))return 0;
    advance(a,ram);
finish:
    release(a,P(owner+32));W(owner+32,0);
    CALL(SEND,word(P(owner+20)),0x5167e8,0x516818);
    CALL(SEND,word(P(owner+20)),0x516828,0x516818);
    CALL(SEND,word(P(owner+20)),0x516838,0x516818);
    CALL(FREEZE,word(P(owner+20)),0);SB(ram+20,0);
    for(uint32_t player=0;player<4;player++){
        CALL(SELECT,word(P(owner+20)),0x516848);CALL(INTEGER,word(P(owner+20)),player);
        CALL(DISPATCH,word(P(owner+20)),0x516850);
        uint64_t folder=CALL(OBJECT,word(P(owner+20)),0);
        uint32_t property=(uint32_t)CALL(0x3a9280,folder,0x516860);
        if(B(property+12)){
            CALL(SELECT,word(P(owner+20)),0x516848);CALL(INTEGER,word(P(owner+20)),player);
            CALL(INTEGER,word(P(owner+20)),0);CALL(DISPATCH,word(P(owner+20)),0x516868);
            CALL(SELECT,word(P(owner+20)),0x516848);CALL(INTEGER,word(P(owner+20)),player);
            CALL(INTEGER,word(P(owner+20)),0);CALL(DISPATCH,word(P(owner+20)),0x516870);
        }
    }
    if(P(owner+40)==10){
        CALL(SEND,word(P(owner+20)),0x516790,0x516878);
        if(!(uint8_t)CALL(BOOLEAN,word(P(owner+20)),0)){
            CALL(SELECT,word(P(owner+20)),0x516888);CALL(INTEGER,word(P(owner+20)),4);
            CALL(DISPATCH,word(P(owner+20)),0x516898);
            CALL(SELECT,word(P(owner+20)),0x516790);CALL(STRING,word(P(owner+20)),0x5168a8);
            CALL(DISPATCH,word(P(owner+20)),0x5168b8);
        }
    }else{
        layer(a,owner,0x5167c8,0x5168c8);layer(a,owner,0x5167e0,0x5168c8);
        if(P(owner+40)!=0){
            uint64_t receiver=CALL(0x236f80,word(P(owner+12)),word(P(0x589208)));
            CALL(0x389ff0,receiver,0x5168d0,0);
        }
    }
    return 0;
}
