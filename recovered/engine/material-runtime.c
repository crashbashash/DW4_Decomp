/* Entire beMatCtrl update (0x38b1f0) and message (0x38bdf0) bodies.
 * Behavioral reconstruction, not byte-matched C. */
#include "material-runtime.h"
#include "../frontend/eefloat.h"
#define P(x) a->read(a->user,(x),4)
#define B(x) a->read(a->user,(x),1)
#define W(x,v) a->write(a->user,(x),4,(v))
#define WB(x,v) a->write(a->user,(x),1,(v))
#define CALL(x,...) a->call(a->user,(x),(const uint32_t[8]){__VA_ARGS__})

static void retain(const Dw4MaterialRuntimeApi *a, uint32_t object)
{
    if (object) W(object+4,P(object+4)+1u);
}
static void release(const Dw4MaterialRuntimeApi *a, uint32_t object)
{
    if (object) {
        W(object+4,P(object+4)-1u);
        if (!(P(object+4)&0x7fffffu)) CALL(0x2ff820,object);
    }
}
static uint32_t allocator(const Dw4MaterialRuntimeApi *a,uint32_t self)
{
    uint32_t result=CALL(0x301000,self);
    if (!B(0x554c14)) result=CALL(0x2f88e0,P(0x587110));
    return result;
}
static void resize(const Dw4MaterialRuntimeApi *a,uint32_t list,int32_t count,unsigned width)
{
    if (count>=0) {
        if ((int32_t)P(list+12)<count) CALL(0x2d6790,list,(uint32_t)count,width);
        else W(list+8,(uint32_t)count);
    }
}
static void fill(const Dw4MaterialRuntimeApi *a,uint32_t list,uint32_t value,unsigned width)
{
    int32_t count=(int32_t)P(list+8),i;
    uint32_t data=P(list+16);
    for(i=0;i<count;i++) a->write(a->user,data+(uint32_t)i*width,width,value);
}

/* 0x38af70: initialize Lua owner, clear/release both published mask lists. */
void dw4_material_initialize(const Dw4MaterialRuntimeApi *a,uint32_t self)
{
    uint32_t list;
    W(self+36,CALL(0x236f80,P(self+12),P(0x589208)));
    list=P(self+56);
    if (list) { W(list+8,0); release(a,P(self+56)); W(self+56,0); }
    list=P(self+60);
    if (list) { W(list+8,0); release(a,P(self+60)); W(self+60,0); }
}

/* 0x38b050: a1 is an incoming selector, not an omitted argument. */
void dw4_material_register(const Dw4MaterialRuntimeApi *a,uint32_t self,uint32_t selector)
{
    CALL(0x38d560,P(self+20),selector,0x50ed58,0,0xffffffffu);
}

/* 0x38b080: recurse into the X-range search tree. Geometry leaf 18b630
 * returns 2 for membership; a rejected parent box does not reject children. */
int dw4_material_box_contains(const Dw4MaterialRuntimeApi *a,uint32_t box,uint32_t point)
{
    unsigned axis;
    for(axis=0;axis<3;axis++) {
        uint32_t value=P(point+axis*4);
        if (ee_f32_cmp(P(box+8+axis*4),value)>0 ||
            ee_f32_cmp(value,P(box+20+axis*4))>0) return 0;
    }
    return 2;
}

void dw4_material_accumulate(const Dw4MaterialRuntimeApi *a,uint32_t self,
                             uint32_t masks,uint32_t search,int32_t player,
                             uint32_t point,uint32_t materials)
{
    int32_t count=(int32_t)P(search+8),i;
    uint32_t bit=1u<<((uint32_t)player&31u);
    for(i=0;i<count;i++) {
        uint32_t node=P(P(search+16)+(uint32_t)i*4),x=P(point);
        int32_t index;
        if (ee_f32_cmp(P(node+8),x)>0 || ee_f32_cmp(P(node+12),x)<0) continue;
        index=(int32_t)P(node+16);
        if (index!=-1) {
            uint32_t material=P(P(materials+16)+(uint32_t)index*4);
            if (CALL(0x18b630,P(material+12),point)==2) {
                uint32_t address=P(masks+16)+(uint32_t)index*4;
                uint32_t value=P(address)|bit;
                if (P(masks+8) && index>=0 && index<(int32_t)P(masks+8)) W(address,value);
            }
        }
        dw4_material_accumulate(a,self,masks,P(node+24),player,point,materials);
    }
}

void dw4_material_update(const Dw4MaterialRuntimeApi *a,uint32_t self,uint32_t ram,uint32_t scratch)
{
    uint32_t work=P(ram+44),info=P(ram+12),first,second,list,object;
    int32_t count,i,player,j;
    /* Retail checks the RAM instance, not the manager's reflected run flag. */
    if (!B(ram+20)) return;
    if (P(ram+24)!=1) {
        release(a,P(ram+44)); W(ram+44,0);
        object=CALL(0x359480,allocator(a,self)); retain(a,object);
        release(a,P(ram+44)); W(ram+44,object); release(a,object);
        work=P(ram+44); count=(int32_t)P(P(info+32)+8);
        first=CALL(0x2caa70,allocator(a,self));
        resize(a,first,count,4); fill(a,first,P(0x4c8f70),4);
        CALL(0x301e30,P(work+12),first); release(a,first);
        second=CALL(0x2caa70,allocator(a,self));
        resize(a,second,count,4); fill(a,second,P(0x4c8f78),4);
        CALL(0x301e30,P(work+12),second); release(a,second);
        list=P(work+8); resize(a,list,count,1); fill(a,list,B(0x5549d0),1);
        for(i=0;i<4;i++) WB(self+32u+(uint32_t)i,0);
        W(ram+24,1); W(ram+36,0); W(ram+32,0); W(ram+28,0);
        return;
    }
    list=P(work+12); first=P(P(list+16)); retain(a,first);
    second=P(P(list+16)+4); retain(a,second);
    fill(a,first,P(0x4c8f80),4);
    CALL(0x38e670,P(self+20),0x50ed60,0x50ed68);
    count=(int32_t)CALL(0x38f5a0,P(self+20));
    for(player=0;player<4;player++) {
        WB(self+32u+(uint32_t)player,0);
        for(j=0;j<count;j++) {
            if ((uint32_t)player==CALL(0x38f320,P(self+20),(uint32_t)j)) {
                WB(self+32u+(uint32_t)player,1); break;
            }
        }
    }
    for(i=0;i<count;i++) {
        uint32_t id=CALL(0x38f320,P(self+20),(uint32_t)i);
        if (B(self+32+id)) {
            CALL(0x38f630,scratch,P(self+20),(uint32_t)i);
            CALL(0x190a30,scratch,scratch+288);
            dw4_material_accumulate(a,self,first,P(info+36),(int32_t)id,scratch+288,P(info+32));
        }
    }
    count=(int32_t)P(P(info+32)+8);
    retain(a,first); release(a,P(self+56)); W(self+56,first);
    retain(a,second); release(a,P(self+60)); W(self+60,second);
    for(i=0;i<count;i++) {
        uint32_t offset=(uint32_t)i*4;
        if (!B(P(P(work+8)+16)+(uint32_t)i)) continue;
        for(player=0;player<4;player++) {
            uint32_t bit=1u<<player;
            int now=(P(P(first+16)+offset)&bit)==bit;
            int old=(P(P(second+16)+offset)&bit)==bit;
            if (now==old) continue;
            W(self+40,(uint32_t)i); W(self+48,0xffffffffu); WB(self+52,1);
            object=P(P(P(info+32)+16)+offset);
            CALL(0x129e60,scratch+256,0x50ed78,P(object+8)?P(object+8):0x4e0858);
            if (B(self+64)==1) {
                for(j=0;j<4;j++) {
                    bit=1u<<j;
                    now=(P(P(first+16)+offset)&bit)==bit;
                    old=(P(P(second+16)+offset)&bit)==bit;
                    CALL(0x129e60,scratch+64+(uint32_t)j*16,now?0x50ed80:0x50ed90);
                    CALL(0x129e60,scratch+128+(uint32_t)j*16,now&&!old?0x50ed80:0x50ed88);
                    CALL(0x129e60,scratch+192+(uint32_t)j*16,!now&&old?0x50ed80:0x50ed88);
                }
            }
            W(0x58a1e0,0);
            CALL(0x389ff0,P(self+36),scratch+256,0);
            j=(int32_t)P(self+48);
            if (j!=-1) {
                list=P(work+8);
                if (P(list+8) && j>=0 && j<(int32_t)P(list+8))
                    WB(P(list+16)+(uint32_t)j,B(self+52));
            }
            break; /* one callback per material with any changed player bit */
        }
    }
    list=P(work+12); retain(a,second); release(a,P(P(list+16)));
    if ((int32_t)P(list+8)>0) W(P(list+16),second);
    list=P(work+12); retain(a,first); release(a,P(P(list+16)+4));
    if ((int32_t)P(list+8)>1) W(P(list+16)+4,first);
    release(a,second); release(a,first);
}

int dw4_material_message(const Dw4MaterialRuntimeApi *a,uint32_t self,uint32_t ram,uint32_t message)
{
    uint32_t info=P(ram+12),table=CALL(0x35a6b0);
    uint32_t command=CALL(0x38d4a0,P(self+20),table,P(message+20));
    switch(command) {
    case 0: CALL(0x1dc870,P(info+28)); break;
    case 1: CALL(0x1dc8d0,P(info+28)); break;
    case 2: WB(self+64,1); break;
    case 3: WB(self+64,0); break;
    case 4: WB(ram+20,0); break;
    case 5: WB(ram+20,1); break;
    default: return 0;
    }
    return 1;
}
