#include "sectl.h"
#define P(a) api->peek(api->user,(a),4)
#define W(a,v) api->poke(api->user,(a),4,(v))
#define CALL(addr,...) api->call(api->user,(addr),(const int32_t[8]){__VA_ARGS__})
/* 0x0039c900 */
void se_attach(const Dw4LoadIntf2Api *api, int32_t self)
{
    if (!P(self+0x20)) W(self+0x20,CALL(0x236f80,P(self+0xc),P(0x587ea8)));
}
/* 0x0039c940 */
void se_register(const Dw4LoadIntf2Api *api, int32_t self, int32_t descriptor)
{
    CALL(0x38d560,P(self+0x14),descriptor,0x50f760,0,-1);
}
/* 0x0039c970 */
int32_t se_meta(const Dw4LoadIntf2Api *api) { return P(0x587fb0); }
/* 0x0039c980 */
void se_tick(const Dw4LoadIntf2Api *api) { (void)api; }
/* 0x0039c990: select the LAST matching model, then every matching action. */
int32_t se_action(const Dw4LoadIntf2Api *api, int32_t self, int32_t context, int32_t msg)
{
    int32_t name=P(msg+0xc), slot=P(msg+0x10), action=P(msg+0x14);
    int32_t list=P(P(context+0xc)+0x14), chosen=-1, i;
    for (i=0;i<P(list+8);i++) {
        int32_t row=P(P(list+0x10)+i*4), text=P(row+8);
        if (!text) text=0x4e0858;
        if (!CALL(0x12a4a4,text,name)) chosen=i;
    }
    if (chosen!=-1) {
        list=P(P(P(list+0x10)+chosen*4)+0x10);
        for (i=0;i<P(list+8);i++) {
            int32_t row=P(P(list+0x10)+i*4), text=P(row+8);
            if (!text) text=0x4e0858;
            if (!CALL(0x12a4a4,text,action)) {
                int32_t delay=(int16_t)api->peek(api->user,row+0x10,2), bits;
                CALL(0x38d860,P(self+0x14),0x50f778,name,slot);
                CALL(0x38f830,P(self+0x14),P(row+0xc));
                bits=CALL(0x22fd70,delay);
                /* Float argument bits represent retail f12 at the messenger boundary. */
                CALL(0x38f350,P(self+0x14),bits);
                CALL(0x38e060,P(self+0x14),0x50f788);
            }
        }
    }
    return 1;
}
/* 0x0039cb60 */
int32_t se_data_meta(const Dw4LoadIntf2Api *api) { return P(0x587fe8); }
