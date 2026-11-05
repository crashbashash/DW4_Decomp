/* Original SUBWND command receiver: generate/remove, status snapshots, previews,
 * shop-list results and running-state result. Services retain guest ABI calls. */
#include "subwindow-command.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define B(p) ((uint32_t)a->read(a->user,(p),1))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define SB(p,v) a->write(a->user,(p),1,(uint8_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
#define MSG word(P(owner+20))
static uint64_t word(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t player(const Dw4MessengerResultsApi*a,uint32_t owner,uint64_t slot){
    CALL(0x38e5d0,MSG,0x516848);CALL(0x38f250,MSG,slot);
    CALL(0x38e060,MSG,0x516850);return CALL(0x38f800,MSG,0);
}
static uint32_t property(const Dw4MessengerResultsApi*a,uint64_t folder,uint32_t key){
    uint32_t p=(uint32_t)CALL(0x3a9220,folder,key);return P(p+12);
}
static void begin_text(const Dw4MessengerResultsApi*a,uint32_t owner,uint32_t window,uint32_t font){
    CALL(0x38e5d0,MSG,0x516938);CALL(0x38f830,MSG,window);CALL(0x38f830,MSG,font);
}
static void text(const Dw4MessengerResultsApi*a,uint32_t owner,uint32_t window,uint32_t font,uint64_t value){
    begin_text(a,owner,window,font);CALL(0x38f830,MSG,value);CALL(0x38e060,MSG,0x516958);
}
static void number(const Dw4MessengerResultsApi*a,uint32_t owner,uint32_t buffer,uint32_t window,uint32_t font,uint32_t value){
    CALL(0x129e60,buffer,0x516968,word(value));text(a,owner,window,font,buffer);
}
static void append(const Dw4MessengerResultsApi*a,uint32_t work,uint32_t value){
    uint32_t list=P(work+8),count=P(list+8);
    if((int32_t)count<(int32_t)P(list+12))W(list+8,P(list+8)+1);
    else CALL(0x2d6790,word(list),word(count+1),4);
    W(P(list+16)+count*4,value);
}
static void release(const Dw4MessengerResultsApi*a,uint32_t p){
    if(p){W(p+4,P(p+4)-1);if(!(P(p+4)&0x7fffff))CALL(0x2ff820,word(p));}
}
static const uint32_t keys[11]={0x5169e8,0x5169f8,0x516a08,0x516a18,0x516a28,0x516a40,0x516a50,0x516a68,0x516a80,0x516a98,0x516ab0};
static const uint32_t fonts[11]={0x5169f0,0x516a00,0x516a10,0x516a20,0x516a38,0x516a48,0x516a60,0x516a78,0x516a90,0x516aa8,0x516ac0};
uint64_t dw4_subwindow_command(const Dw4MessengerResultsApi*a,const uint64_t v[8],uint32_t scratch){
    uint32_t owner=(uint32_t)v[0],ram=(uint32_t)v[1],message=(uint32_t)v[2];
    uint64_t table=CALL(0x3bb730);
    uint64_t command=CALL(0x38d4a0,MSG,table,word(P(message+20)));
    switch(command){
    case 0: /* GENERATE */
        if(!B(ram+20)){
            uint64_t who=CALL(0x38f320,MSG,0),name=CALL(0x38f8f0,MSG,0);
            table=CALL(0x3b1d70);uint64_t mode=CALL(0x38d4a0,MSG,table,name);
            SB(ram+20,1);W(ram+24,0);W(ram+36,0);W(ram+32,0);W(ram+28,0);
            W(owner+40,mode);W(owner+36,who);
            CALL(0x38e670,MSG,0x516838,0x516910);CALL(0x38e670,MSG,0x516828,0x516910);
            CALL(0x38d470,MSG,1);CALL(0x38e670,MSG,0x5167e8,0x516910);
        }
        return 1;
    case 1: /* REMOVE: only the exact active byte1 requests removal. */
        if(B(ram+20)==1){
            uint32_t root=P(owner+32);
            if(root){W(root+28,2);W(root+40,0);W(root+36,0);W(root+32,0);}
            else{CALL(0x38d470,MSG,0);CALL(0x38ecf0,MSG,0x516788,0x516920,1);}
        }
        return 1;
    case 2:{ /* UPDATE: collect the displayed stats and original HP/MP. */
        uint32_t work=P(ram+44);uint64_t slot=CALL(0x38f320,MSG,0);
        if(!work){CALL(0x3d8740,v[0],v[1]);work=P(ram+44);}
        W(P(work+8)+8,0);uint64_t folder=player(a,owner,slot);
        uint32_t name_property=(uint32_t)CALL(0x3a9340,folder,0x516928);
        W(scratch+396,P(P(P(name_property+12)+16)));
        uint32_t name=P(scratch+396);if(name)W(name+4,P(name+4)+1);
        begin_text(a,owner,0x516940,0x516950);
        CALL(0x38f670,MSG,word(P(scratch+396)));CALL(0x38e060,MSG,0x516958);
        uint32_t level=property(a,folder,0x516960);
        if((int32_t)level>999)level=999;
        number(a,owner,scratch+208,0x516970,0x516950,level);
        CALL(0x38e5f0,MSG,0x516980,0x516990,0,0x516998);
        uint64_t data=CALL(0x38f800,MSG,0);uint32_t species=property(a,folder,0x5169a8);
        uint64_t species_name=CALL(0x3a9580,data,word(species),0x5169b8);
        text(a,owner,0x516970,0x5169c0,species_name);
        uint32_t hp=property(a,folder,0x5169c8);
        number(a,owner,scratch+208,0x5169d0,0x516950,hp);
        uint32_t mp=property(a,folder,0x5169e0);
        number(a,owner,scratch+208,0x5169d0,0x5169c0,mp);
        for(unsigned i=0;i<11;i++){
            uint32_t value=property(a,folder,keys[i]);
            number(a,owner,scratch+208,0x5169d0,fonts[i],value);append(a,work,value);
        }
        number(a,owner,scratch+208,0x5169d0,0x516ad0,property(a,folder,0x516ac8));
        number(a,owner,scratch+208,0x5169d0,0x516ae0,property(a,folder,0x516ad8));
        uint32_t exp=property(a,folder,0x516ae8),next=property(a,folder,0x516af0),remaining=next-exp;
        if((int32_t)level>=999){W(scratch+208,P(0x516af8));SB(scratch+212,B(0x516afc));}
        else if((int32_t)remaining<0)a->write(a->user,scratch+208,2,a->read(a->user,0x516b00,2));
        else CALL(0x129e60,scratch+208,0x516968,word(remaining));
        text(a,owner,0x5169d0,0x516b08,scratch+208);
        append(a,work,hp);append(a,work,mp);release(a,P(scratch+396));return 1;
    }
    case 3:{ /* GETSHOPDATA: no implicit preparation. */
        uint32_t work=P(ram+44);uint64_t mode=CALL(0x38f320,MSG,0);
        if(mode==9){CALL(0x38f670,MSG,word(P(work+28)));CALL(0x38f250,MSG,word(P(work+32)));}
        else if(mode==8)CALL(0x38f670,MSG,word(P(work+24)));
        else if(mode==7)CALL(0x38f670,MSG,word(P(work+20)));
        else if(mode==6)CALL(0x38f670,MSG,word(P(work+16)));
        return 1;
    }
    case 4:{ /* ONPREVIEW: compare live stats with the saved baseline. */
        uint32_t work=P(ram+44);uint64_t slot=CALL(0x38f320,MSG,0),folder=player(a,owner,slot);
        for(unsigned i=0;i<11;i++){
            uint32_t value=property(a,folder,keys[i]),baseline=P(P(P(work+8)+16)+4*i),r,g,b;
            if(value==baseline)r=g=b=0x3f666666;
            else if((int32_t)value<(int32_t)baseline){r=0x3f70a3d7;g=0x3ecccccd;b=0x3e800000;}
            else{r=0;g=0x3f75c28f;b=0x3f800000;}
            number(a,owner,scratch+192,0x5169d0,fonts[i],value);
            begin_text(a,owner,0x5169d0,fonts[i]);
            uint32_t vector=scratch+384-16*i;W(vector,r);W(vector+4,g);W(vector+8,b);
            CALL(0x38f4b0,MSG,vector);CALL(0x38e060,MSG,0x516b10);
        }
        return 1;
    }
    case 5:{ /* OFPREVIEW: restore displayed baseline and saved HP/MP. */
        uint32_t work=P(ram+44);uint64_t slot=CALL(0x38f320,MSG,0);
        for(unsigned i=0;i<11;i++){
            uint32_t value=P(P(P(work+8)+16)+4*i);
            number(a,owner,scratch+176,0x5169d0,fonts[i],value);
            begin_text(a,owner,0x5169d0,fonts[i]);CALL(0x38e060,MSG,0x516b18);
        }
        uint32_t data=P(P(work+8)+16),hp=P(data+44),mp=P(data+48);
        uint64_t folder=player(a,owner,slot);
        uint32_t target=(uint32_t)CALL(0x3a9220,folder,0x5169c8);W(target+12,hp);
        target=(uint32_t)CALL(0x3a9220,folder,0x5169e0);W(target+12,mp);return 1;
    }
    case 6:CALL(0x38f150,MSG,B(ram+20));return 1; /* ISRUN */
    default:return 0;
    }
}
