/* Developer aid: census of the Action2 data in every model pack of the asset tree: every action that starts two or more MOTIONSETs, and every
 * action whose MOTIONSET is reached only after another component that stops the walk (a WAITCHECK) -- the actions whose motion start time the host's
 * component walk (action2host.c, 0x377340) decides.  One line per distinct (model, action, component list); usage: census_motionset <extracted> [all|extend].
 * With `all` the single-MOTIONSET actions are listed too. With `extend` only the actions whose Motion wait the blend model lengthens are listed (see
 * extension()): a MOTIONSET followed by a WAITCHECK Motion ends that wait at max(animation length, blend) after it started, so a blend longer than the
 * animation adds the difference; the line shows the added and the total ticks. */
#include "dw4/modelctrl.h"
#include "dw4/mount.h"
#include "dw4/igb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

struct seen { char *line; };
static struct seen *seen;static size_t nseen,capseen;
static int remember(const char *line)
{
    for(size_t i=0;i<nseen;i++)if(!strcmp(seen[i].line,line))return 0;
    if(nseen==capseen){capseen=capseen?capseen*2:256;seen=realloc(seen,capseen*sizeof *seen);if(!seen)exit(1);}
    seen[nseen++].line=strdup(line);return 1;
}
#define TICK_NS (1e9/60.0)
/* The ticks the blend model adds to one action: for every WAITCHECK Motion, the last MOTIONSET before it contributes max(0, blend - length). A Frame/Joint
 * wait in between drops the pending MOTIONSET (its blend has run by the time a later Motion wait is reached, the wait would then not be extended by it).
 * `list` is the bracketed component text of a census line ("[4 name first blend loop d=ns] ..."); *total gets the summed motion lengths of the waits. */
static double extension(const char *list,double *total)
{
    double extra=0,pend_len=-1,pend_blend=0;*total=0;
    for(const char *p=list;(p=strchr(p,'['));p++) {
        int kind=atoi(p+1);char name[64]="";const char *q=p+1;
        while(*q && *q!=' ')q++;
        if(*q==' ')q++;
        int n=0;while(*q && *q!=' ' && n<63)name[n++]=*q++;
        const char *end=strchr(p,']');if(!end)break;
        if(kind==4) {
            char *e1,*e2;double a=strtod(q,&e1);(void)a;double b=strtod(e1,&e2);
            const char *d=strstr(e2,"d=");const char *stop=end;
            pend_len=d&&d<stop?atof(d+2):-1;pend_blend=b*1e9/60.0;
        } else if(kind==3) {
            if(!strcmp(name,"Motion")) {
                if(pend_len>=0) {
                    double wait=pend_len>pend_blend?pend_len:pend_blend;
                    if(pend_blend>pend_len)extra+=pend_blend-pend_len;
                    *total+=wait;
                }
                pend_len=-1;
            } else pend_len=-1;
        }
        p=end;
    }
    return extra/TICK_NS;
}
int main(int argc,char **argv)
{
    dw4_mount m;int all=argc>2 && !strcmp(argv[2],"all"),extend=argc>2 && !strcmp(argv[2],"extend");
    unsigned extended=0;double biggest=0;
    if(dw4_mount_open(&m,argc>1?argv[1]:"../../local/extracted")){fprintf(stderr,"mount failed\n");return 1;}
    unsigned files=0,models=0,multi=0,late=0,single=0;
    /* Every entry of every archive, not the manifest names: the stage packs (USA_pack.igb and friends) share their names across stages. */
    for(int pt=0;pt<m.nparts;pt++)for(uint32_t entry=0;entry<m.parts[pt].count;entry++) {
        uint32_t size=0,bytes=0;char n[64];snprintf(n,sizeof n,"[%d.%u]",pt,entry);
        const uint8_t *blob=dw4_mount_entry(&m,pt,(int)entry,&size,&bytes);if(!blob || size<64)continue;
        dw4_igb g={0};if(dw4_igb_open(&g,blob,size,0))continue;
        if(dw4_igb_refs_open(&g) || !g.id_kind){dw4_igb_close(&g);continue;}
        int counted=0;
        for(uint32_t i=0;i<g.table_n;i++) {
            dw4_igb_record r={0};
            if(g.id_kind[i]!=2 || !dw4_igb_decode(&g,g.id_off[i],&r))continue;
            int info=!strcmp(r.class_name,"beModelCtrlInfo");char model[128]="?";if(info && r.name)snprintf(model,sizeof model,"%s",r.name);dw4_igb_record_free(&r);
            if(!info)continue;
            dw4_modelctrl *c=dw4_modelctrl_open_info(&g,i);if(!c)continue;
            if(!counted){files++;counted=1;}
            models++;
            char *buf=NULL;size_t bl=0;FILE *o=open_memstream(&buf,&bl);dw4_modelctrl_census(c,o);fclose(o);
            for(char *line=strtok(buf,"\n");line;line=strtok(NULL,"\n")) {
                if(strncmp(line,"ACTION ",7))continue;
                /* "ACTION name components N supported S: [k name a b loop] ..." */
                char *list=strstr(line,": [");if(!list)continue;list+=2;
                int motionsets=0,stopped=0,late_set=0;
                for(char *p=list;(p=strchr(p,'['));p++) {
                    int kind=atoi(p+1);
                    if(kind==4){motionsets++;if(stopped)late_set=1;}
                    else if(kind==3)stopped=1;   /* a WAITCHECK stops the walk until its wait ends */
                }
                if(!motionsets)continue;
                char out[4096],key[4096];
                snprintf(out,sizeof out,"%s %s %s",motionsets>1?"MULTI ":late_set?"LATE  ":"single",model,line+7);
                if(extend) {
                    double total;double extra=extension(list,&total);
                    if(extra<=0)continue;
                    if(!remember(out))continue;
                    printf("EXT +%.2f ticks (motion waits %.2f ticks) %s %s  (%s)\n",extra,total/TICK_NS,model,line+7,n);
                    extended++;if(extra>biggest)biggest=extra;
                    continue;
                }
                if(motionsets==1 && !late_set && !all)continue;
                /* the census text carries each MOTIONSET's length (" d=ns"): the repeated-line filter keys on the component list without it */
                {char *w=key;for(const char *r=out;*r && w<key+sizeof key-1;) {if(!strncmp(r," d=",3)){r+=3;while(*r>='0' && *r<='9')r++;} else *w++=*r++;}*w=0;}
                if(!remember(key))continue;
                printf("%s  (%s)\n",out,n);
                if(motionsets>1)multi++;else if(late_set)late++;else single++;
            }
            free(buf);dw4_modelctrl_close(c);
        }
        dw4_igb_close(&g);
    }
    if(extend)printf("files with models %u, models %u, distinct actions whose Motion wait the blend lengthens %u, largest addition %.2f ticks\n",files,models,extended,biggest);
    else printf("files with models %u, models %u, distinct multi-MOTIONSET actions %u, MOTIONSET after a wait %u, single %u listed\n",files,models,multi,late,single);
    return 0;
}
