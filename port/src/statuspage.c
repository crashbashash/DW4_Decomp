#include "dw4/statuspage.h"

int dw4_statuspage_turn(int32_t *page,int pages,int next,const dw4_statuspage_input *p,dw4_statuspage_io io,void *u)
{
    if(!page || !p || !io || pages<1 || *page<0 || *page>=pages || (next!=0 && next!=1))return -1;
    int edge=(p->horizontal&(next?2u:8u)) || (p->digital&(next?0x20u:0x80u));
    if(!edge || (p->analog&5) || (next?*page==pages-1:*page==0))return 0;
    *page+=next?1:-1;
    const char *moving=next?"i_stcursorright":"i_stcursorleft";
    const char *other=next?"i_stcursorleft":"i_stcursorright";
    if(io(u,moving,(next?*page==pages-1:*page==0)?"SQ_MOVEEND":"SQ_MOVENEXT") ||
       io(u,other,"SQ_SELECT"))return -1;
    return 1;
}
