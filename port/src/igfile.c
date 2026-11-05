/* dw4/igfile.c — the host file seam; see include/dw4/igfile.h for why it is this small. */
#include "dw4/igfile.h"
#include "dw4/igb.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

/* Map a file read-only, falling back to a read when mapping is not possible (a pipe, a
 * filesystem without mmap).  Returns the bytes or NULL. */
static const uint8_t *map_file(const char *path, size_t *len_out, void **map_out,
                               uint8_t **owned_out)
{
    struct stat st;
    int fd;
    void *p;

    *map_out = NULL;
    *owned_out = NULL;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return NULL;
    if (fstat(fd, &st) != 0 || !S_ISREG(st.st_mode) || st.st_size <= 0) {
        close(fd);
        return NULL;
    }
    *len_out = (size_t)st.st_size;
    p = mmap(NULL, *len_out, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (p != MAP_FAILED) {
        *map_out = p;
        return (const uint8_t *)p;
    }
    {
        uint8_t *buf = (uint8_t *)malloc(*len_out);
        FILE *fp = fopen(path, "rb");
        if (!buf || !fp || fread(buf, 1, *len_out, fp) != *len_out) {
            free(buf);
            if (fp)
                fclose(fp);
            return NULL;
        }
        fclose(fp);
        *owned_out = buf;
        return buf;
    }
}

int dw4_igfile_open_path(dw4_igfile *f, const char *path)
{
    memset(f, 0, sizeof(*f));
    snprintf(f->path, sizeof(f->path), "%s", path);
    f->data = map_file(path, &f->len, &f->map, &f->owned);
    f->map_len = f->len;
    if (!f->data) {
        fprintf(stderr, "igfile: cannot read %s\n", path);
        return -1;
    }
    return 0;
}

int dw4_igfile_open_afs(dw4_igfile *f, const char *afs_path, uint32_t entry)
{
    dw4_afs *afs = (dw4_afs *)calloc(1, sizeof(*afs));

    memset(f, 0, sizeof(*f));
    if (!afs)
        return -1;
    if (dw4_afs_open_mmap(afs, afs_path) != 0) {
        fprintf(stderr, "igfile: cannot read %s\n", afs_path);
        free(afs);
        return -1;
    }
    if (entry >= afs->count) {
        fprintf(stderr, "igfile: %s has no entry %u\n", afs_path, entry);
        dw4_afs_close(afs);
        free(afs);
        return -1;
    }
    /* The entry borrows the archive's mapping, so the archive view outlives it: `afs` is kept
     * until close, and the entry's bytes are not copied. */
    snprintf(f->path, sizeof(f->path), "%s", afs_path);
    f->data = dw4_afs_entry_data(afs, entry);
    f->len = afs->entries[entry].size;
    f->afs = afs;
    return 0;
}

int dw4_igfile_open_named(dw4_igfile *f, dw4_mount *m, const char *name)
{
    uint32_t size = 0;
    const uint8_t *p;

    memset(f, 0, sizeof(*f));
    p = dw4_mount_data(m, name, &size);
    if (!p) {
        fprintf(stderr, "igfile: the manifest has no %s\n", name);
        return -1;
    }
    snprintf(f->name, sizeof(f->name), "%s", name);
    snprintf(f->path, sizeof(f->path), "mounted:%s", name);
    f->data = p;                    /* borrowed from the mount's own mapping */
    f->len = size;
    return 0;
}

uint32_t dw4_igfile_stage_refs(dw4_mount *m, const char *stage, dw4_ref *out, uint32_t cap)
{
    uint32_t size = 0;
    const uint8_t *p = dw4_mount_data(m, stage, &size);

    if (!p)
        return 0;
    return dw4_mount_scan_refs(p, size, out, cap);
}

int dw4_igfile_open_stage_ref(dw4_igfile *f, dw4_mount *m, const char *stage, uint32_t index)
{
    dw4_ref refs[16];
    uint32_t n = dw4_igfile_stage_refs(m, stage, refs, 16);

    memset(f, 0, sizeof(*f));
    if (index >= n) {
        fprintf(stderr, "igfile: %s has %u [pt.entry] reference(s), no %u\n", stage, n, index);
        return -1;
    }
    snprintf(f->name, sizeof(f->name), "%s[%d.%d]", stage, refs[index].pt, refs[index].entry);
    snprintf(f->path, sizeof(f->path), "mounted:%s", f->name);
    {
        uint32_t size = 0;
        f->data = dw4_mount_entry(m, refs[index].pt, refs[index].entry, &size, NULL);
        f->len = size;
    }
    if (!f->data) {
        fprintf(stderr, "igfile: %s -> part %d entry %d did not resolve\n", stage,
                refs[index].pt, refs[index].entry);
        return -1;
    }
    return 0;
}

void dw4_igfile_close(dw4_igfile *f)
{
    if (f->afs) {
        dw4_afs_close((dw4_afs *)f->afs);
        free(f->afs);
    }
    if (f->map)
        munmap(f->map, f->map_len);
    free(f->owned);
    memset(f, 0, sizeof(*f));
}

size_t dw4_igfile_size(const dw4_igfile *f)
{
    return f->len;
}

const uint8_t *dw4_igfile_data(const dw4_igfile *f)
{
    return f->data;
}

int dw4_igfile_read(const dw4_igfile *f, uint32_t off, void *dst, size_t n)
{
    if ((size_t)off > f->len || n > f->len - off)
        return -1;
    memcpy(dst, f->data + off, n);
    return 0;
}

/* Authored beFileListInfo ownership, independent of bracket-string order. */
static uint32_t stage_slot(const dw4_igb_record *r,unsigned ordinal)
{for(unsigned i=0;i<r->nvalues;i++)if(r->values[i].ordinal==ordinal)return r->values[i].raw;return UINT32_MAX;}
static int stage_record(dw4_igb *g,uint32_t id,dw4_igb_record *r)
{uint32_t off;return dw4_igb_ref(g,id,&off,NULL)==2 && dw4_igb_decode(g,off,r);}
int dw4_igfile_open_stage_pack(dw4_igfile *out,dw4_mount *mount,const char *stage,int support,uint32_t index)
{
    if(!out || !mount)return -1;
    dw4_igb g={0};dw4_igfile directory={0};int rc=-1,found=0;
    char bare[128],path[160],selected[DW4_IGFILE_NAME]={0};
    memset(out,0,sizeof *out);
    if(!stage || strlen(stage)>=sizeof bare || (support!=0 && support!=1))goto done;
    strcpy(bare,stage);size_t len=strlen(bare);
    if(len>=4 && !strcasecmp(bare+len-4,".igb"))bare[len-4]=0;
    snprintf(path,sizeof path,"%s.igb",bare);
    const char *resolved=NULL;
    for(uint32_t i=0;i<mount->man.nfiles;i++)if(!strcasecmp(mount->man.files[i].path,path)) {resolved=mount->man.files[i].path;break;}
    if(!resolved || dw4_igfile_open_named(&directory,mount,resolved) ||
       dw4_igb_open(&g,directory.data,directory.len,0) || dw4_igb_refs_open(&g))goto done;
    for(uint32_t id=0;id<g.table_n;id++) {
        dw4_igb_record info={0},list={0};
        if(!stage_record(&g,id,&info))continue;
        if(strcmp(info.class_name,"beFileListInfo") || !info.name || strcasecmp(info.name,bare)) {dw4_igb_record_free(&info);continue;}
        if(found++ || !stage_record(&g,stage_slot(&info,6),&list) || strcmp(list.class_name,"igNamedObjectList")) {
            dw4_igb_record_free(&info);dw4_igb_record_free(&list);goto done;
        }
        uint32_t count=stage_slot(&list,2),capacity=stage_slot(&list,3),size;
        const uint8_t *names=dw4_igb_block(&g,stage_slot(&list,4),&size);
        dw4_igb_record_free(&info);dw4_igb_record_free(&list);
        if(count>capacity || count>INT_MAX || !names || count>size/4)goto done;
        uint32_t selected_index=0;
        for(uint32_t i=0;i<count;i++) {
            uint32_t name_id;memcpy(&name_id,names+4*i,4);dw4_igb_record name={0};
            if(!stage_record(&g,name_id,&name))goto done;
            if(strcmp(name.class_name,"igNamedObject") || !name.name) {dw4_igb_record_free(&name);goto done;}
            len=strlen(name.name);int special=len>=2 && !strcmp(name.name+len-2,"/s");
            if(special==support && selected_index++==index) {
                size_t n=len-(special?2:0);
                if(n>=sizeof selected){dw4_igb_record_free(&name);goto done;}
                memcpy(selected,name.name,n);selected[n]=0;
            }
            dw4_igb_record_free(&name);
        }
    }
    if(!found || !selected[0])goto done;
    if(selected[0]=='[') {
        char *end;errno=0;
        if(!isdigit((unsigned char)selected[1]))goto done;
        unsigned long pt=strtoul(selected+1,&end,10);
        if(errno || *end!='.' || pt>INT_MAX || !isdigit((unsigned char)end[1]))goto done;
        unsigned long entry=strtoul(end+1,&end,10);
        if(errno || entry>INT_MAX || *end!=']' || end[1])goto done;
        uint32_t size=0;out->data=dw4_mount_entry(mount,(int)pt,(int)entry,&size,NULL);out->len=size;
        if(!out->data)goto done;
        snprintf(out->name,sizeof out->name,"%s",selected);snprintf(out->path,sizeof out->path,"mounted:%s",selected);rc=0;
    } else rc=dw4_igfile_open_named(out,mount,selected);
done:
    dw4_igb_close(&g);dw4_igfile_close(&directory);
    if(rc){dw4_igfile_close(out);fprintf(stderr,"igfile: unavailable authored %s pack %u for %s\n",support?"support":"scene",index,stage?stage:"<null>");}
    return rc;
}
