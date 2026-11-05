#include "dw4/fontlayout.h"
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "eefloat.h"
static uint32_t bits(float f){uint32_t b;memcpy(&b,&f,4);return b;}
static float value(uint32_t b){float f;memcpy(&f,&b,4);return f;}
static float add(float a,float b){return value(ee_f32_add(bits(a),bits(b)));}
static float sub(float a,float b){return value(ee_f32_sub(bits(a),bits(b)));}
void dw4_fontlayout_glyph(const dw4_glyph *g,float pen,float baseline,dw4_font_vertex out[6])
{
    float x=add(pen,g->bx),y=add(baseline,g->by),right=add(x,g->w),top=add(y,g->h);
    dw4_font_vertex quad[6]={{x,y,0,g->u0,g->v0},{right,top,0,g->u1,g->v1},
        {right,y,0,g->u1,g->v0},{x,y,0,g->u0,g->v0},
        {x,top,0,g->u0,g->v1},{right,top,0,g->u1,g->v1}};
    for(unsigned i=0;i<6;i++)out[i]=quad[i];
}
int dw4_fontlayout_build(const dw4_fefont *f,const uint32_t *codes,size_t n,float width,int align,
    dw4_font_vertex **vertices,size_t *count)
{
    if(!vertices || !count)return -1;
    *vertices=NULL;*count=0;
    if(!f || !f->have || (n && !codes) || !isfinite(width) || align<0 || align>2 ||
       n>SIZE_MAX/6/sizeof(dw4_font_vertex)-1)return -1;
    /* Original Unicode path allocates spare glyphs before line processing. */
    dw4_font_vertex *v=calloc((n+1)*6,sizeof(*v));
    size_t *ends=calloc(n+1,sizeof(*ends));float *lengths=calloc(n+1,sizeof(*lengths));
    if(!v || !ends || !lengths){free(v);free(ends);free(lengths);return -1;}
    float pen=0;size_t used=0;
    for(size_t i=0;i<n && codes[i];i++) {
        const dw4_glyph *g=dw4_fefont_glyph(f,codes[i]);
        if(codes[i]=='\r' || codes[i]=='\n' || !g)continue;
        dw4_fontlayout_glyph(g,pen,f->baseline,v+used);used+=6;pen=add(pen,g->advance);
    }
    /* 383bf0: line breaks rebase the following vertices; no width/height wrap. */
    float dx=0,dy=0;size_t cursor=0,lines=0,last=0;
    for(size_t i=0;i<n && codes[i];i++) {
        if(codes[i]=='\r')continue;
        if(codes[i]=='\n') {
            if(cursor){ends[lines]=cursor;lengths[lines++]=sub(v[cursor].x,value(bits(dx)&0x7fffffffu));
                dx=-v[cursor].x;dy=sub(dy,f->height);}
            continue;
        }
        if(!dw4_fefont_glyph(f,codes[i]))continue;
        for(unsigned j=0;j<6;j++){v[cursor+j].x=add(v[cursor+j].x,dx);v[cursor+j].y=add(v[cursor+j].y,dy);last=cursor+j;}
        cursor+=6;
    }
    ends[lines]=cursor;lengths[lines++]=cursor?v[last].x:0;
    cursor=0;
    for(size_t i=0;i<lines;i++) {
        float shift=align?sub(width,lengths[i]):0;
        if(align==2)shift=value(ee_f32_div(bits(shift),bits(2)));
        for(;cursor<ends[i];cursor++)v[cursor].x=add(v[cursor].x,shift);
    }
    free(ends);free(lengths);*vertices=v;*count=used;return 0;
}

int dw4_fontlayout_replace_unknown(const dw4_fefont *f,uint16_t *codes,size_t count,uint16_t replacement)
{
    if(!f || !f->have || (count && !codes))return -1;
    for(size_t i=0;i<count && codes[i];i++)
        if(!dw4_fefont_glyph(f,codes[i]))codes[i]=replacement;
    return 0;
}
