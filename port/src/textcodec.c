#include "dw4/textcodec.h"
static const struct {uint16_t unicode,encoded;} mapping[]={
#include "textcodec_table.inc"
};
static int lookup(unsigned code)
{
    for(size_t i=0;i<sizeof mapping/sizeof *mapping;i++)if(mapping[i].encoded==code)return mapping[i].unicode;
    return -1;
}
static size_t decode(const unsigned char *bytes,size_t length,uint32_t *out)
{
    size_t n=0;
    for(size_t i=0;i<length && bytes[i];){
        unsigned b=bytes[i++];int code;
        if(b=='\r')continue;
        if(b=='\n'){if(n<=1)continue;code='\n';}
        else if(b&128){if(i==length || !bytes[i])break;code=lookup((b<<8)|bytes[i++]);}
        else code=lookup(b)<0?-1:(int)b;
        if(code<0)continue;
        if(out)out[n]=(uint32_t)code;
        n++;
    }
    if(out)out[n]=0;
    return n;
}
int dw4_textcodec_decode(const char *bytes,size_t length,uint32_t *out,size_t capacity,size_t *count)
{
    if(!count || (!bytes && length))return -1;
    size_t n=decode((const unsigned char *)bytes,length,NULL);
    if(out && capacity<=n)return -1;
    if(out)decode((const unsigned char *)bytes,length,out);
    *count=n;return 0;
}
