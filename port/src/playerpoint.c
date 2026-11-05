#include "dw4/playerpoint.h"
#include "dw4/object.h"
#include <limits.h>
#include <string.h>
static uint32_t slot(const dw4_igb_record *r,unsigned ordinal)
{for(unsigned i=0;i<r->nvalues;i++)if(r->values[i].ordinal==ordinal)return r->values[i].raw;return UINT32_MAX;}
static int record(dw4_igb *g,uint32_t id,dw4_igb_record *r)
{uint32_t off;return dw4_igb_ref(g,id,&off,NULL)==2 && dw4_igb_decode(g,off,r);}
static const uint8_t *list(dw4_igb *g,uint32_t id,const char *kind,uint32_t *count)
{
    dw4_igb_record r={0};if(!record(g,id,&r))return NULL;
    if(strcmp(r.class_name,kind)){dw4_igb_record_free(&r);return NULL;}
    *count=slot(&r,2);uint32_t capacity=slot(&r,3),size;
    const uint8_t *bytes=dw4_igb_block(g,slot(&r,4),&size);
    dw4_igb_record_free(&r);
    if(*count>INT_MAX || *count>capacity || !bytes || *count>size/4)return NULL;
    return bytes;
}
static uint32_t at(const uint8_t *p,unsigned i){uint32_t v;memcpy(&v,p+4*i,4);return v;}
int dw4_playerpoint_matrix(const void *blob,size_t size,int32_t group,unsigned player,float matrix[16])
{
    if(!blob || !matrix || group<0 || player>=4)return -1;
    dw4_igb g={0};int rc=-1;
    if(dw4_igb_open(&g,blob,size,0) || dw4_igb_refs_open(&g))goto done;
    for(uint32_t i=0;i<g.table_n;i++) {
        dw4_igb_record info={0},node={0},transform={0};dw4_object object={0};
        if(!record(&g,i,&info))continue;
        int match=!strcmp(info.class_name,"bePoint01Info");
        if(!match){dw4_igb_record_free(&info);continue;}
        if(dw4_object_from_record(&object,&g,&info))goto row_done;
        uint32_t count;const uint8_t *groups=list(&g,dw4_object_get_ref(&object,"_dataList"),"beGroupKeepList",&count);
        if(!groups || !count)goto row_done;
        unsigned index=(uint32_t)group>=count?0:(unsigned)group;
        uint32_t id=at(groups,index);float out[16]={0};
        if(id==UINT32_MAX)goto row_done; /* Retail copies global4e0ef0 here;
         * its initialized value is outside this resolver. Never invent it. */
        else {
            /* beGroupKeep inherits igGroup._childList at +28 (ordinal7).
             * Each child is one joined player's igTransform._m at +32. */
            if(!record(&g,id,&node) || strcmp(node.class_name,"beGroupKeep"))goto row_done;
            const uint8_t *players=list(&g,slot(&node,7),"igNodeList",&count);
            if(!players || player>=count || !record(&g,at(players,player),&transform) ||
               strcmp(transform.class_name,"igTransform"))goto row_done;
            int found=0;
            for(unsigned k=0;k<transform.nvalues;k++)if(transform.values[k].ordinal==8 &&
                transform.values[k].type==40 && transform.values[k].voff<=g.size &&
                g.size-transform.values[k].voff>=sizeof out) {
                memcpy(out,g.data+transform.values[k].voff,sizeof out);found=1;break;
            }
            if(!found)goto row_done;
        }
        memcpy(matrix,out,sizeof out);rc=0;
row_done:
        dw4_object_free(&object);dw4_igb_record_free(&transform);dw4_igb_record_free(&node);dw4_igb_record_free(&info);
        break;
    }
done:dw4_igb_close(&g);return rc;
}
