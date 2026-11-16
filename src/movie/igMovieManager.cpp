#include "dw4/igSmartPointer.h"
#include "dw4/reflected.h"
#include "dw4/igMatrix44f.h"
#include "dw4/igVec3f.h"
#include "dw4/igWindowDispatchView.h"
#include "dw4/igTextureBindAttrDispatchView.h"
#include "dw4/igTransformDispatchView.h"
#include "dw4/igMovieManagerDispatchView.h"

/* igMovieInfo::_type: an ADX audio stream, which plays without a scene. */
enum { kMovieTypeAdx = 2 };

/* igMovieInfo::_state; a movie the manager does not hold reads as finished. */
enum { kMovieStatePlaying = 0, kMovieStatePaused = 1, kMovieStateFinished = 2 };

/* igGeometryAttr's primitive types, as the draw call takes them. */
enum { kPrimitiveTriangleStrip = 4 };

/* The size of an MPEG macroblock: a tile this wide holds one column of the decoded picture. */
enum { kMacroblockSize = 16 };

/* The status Alchemy's operations return. */
struct igResult {
    int value;
};

/* An object list with its inline accessors. */
struct igObjectListView : igObject {
    int _count;
    int _capacity;
    igObject **_data;
    int getCount() const { return _count; }
    igObject *get(int index) const { return _data[index]; }
};

/* The movie list as the manager searches it. */
struct igMovieInfoListView : igObject {
    int _count;
    int _capacity;
    igObject **_data;
    /* matching construct: reading the search key through a pointer keeps it in a stack slot, as retail does */
    static igObject *key(igObject *const *item) { return *item; }
    /* igObjectList::indexOf: linear search, -1 when absent */
    int indexOf(igObject *item) {
        int n = _count;
        int i = 0;
        if (0 < n) {
            igObject **p = _data;
            do {
                if (key(&item) == *p) return i;
                i++;
                p++;
            } while (i < n);
        }
        return -1;
    }
};

/* The igMovieCodec slots the manager calls on a movie's codec: slot 20 is GetMeta, from igObject.
 * ABI view only: never instantiated. */
class igMovieCodecDispatchView : public igObjectDispatchView {
public:
    virtual int isReusable();                                                                    /* slot 21 */
    virtual void initialize(igVisualContextDispatchView *visualContext, igObject *audioContext);  /* slot 22 */
    virtual int open(igMovieInfo *movie);                                                        /* slot 23 */
    virtual int close(igMovieInfo *movie);                                                       /* slot 24 */
    virtual int play(igMovieInfo *movie);                                                        /* slot 25 */
    virtual int pause(igMovieInfo *movie, int state);                                            /* slot 26 */
    virtual int update(igMovieInfo *movie);                                                      /* slot 27 */
    virtual int initializeDrawing(igMovieInfo *movie, igSmartPointer<igObject> visualContext);   /* slot 28 */
    virtual int releaseDrawing(igMovieInfo *movie);                                              /* slot 29 */
};

/* The audio context the manager creates for movie sound.
 * ABI view only: never instantiated. */
class igAudioContextDispatchView : public igObjectDispatchView {
public:
    virtual void d21();
    virtual igResult initialize();                                                               /* slot 22 */
    virtual void d23();
    virtual void setWindow(igObject *window);                                                    /* slot 24 */
};

/* Which components a vertex array holds: positions, normals and a count of texture coordinate sets. */
struct igVertexFormat {
    unsigned int _flags;
    void setVertices(bool on) {
        if (on) _flags |= 1;
        else _flags &= ~1;
    }
    void setNormals(bool on) {
        if (on) _flags |= 2;
        else _flags &= ~2;
    }
    void setTextureCoordCount(unsigned int count) {
        _flags &= ~0xF0000;
        _flags |= count << 16;
    }
};

/* The scene-graph classes the movie scene is built from, with the virtual functions it calls.
 * ABI view only: never instantiated. */
class igStateAttrDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void setEnabled(bool enabled);                                   /* slot 30 */
};
class igBlendStateAttrDispatchView : public igStateAttrDispatchView {};
class igTextureStateAttrDispatchView : public igStateAttrDispatchView {};

class igTextureAttrDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void setMagFilter(int filter);                                   /* slot 30 */
    virtual void setMinFilter(int filter);                                   /* slot 31 */
    char _pad8[36];
    int _source;                                                             /* +44 */
    char _pad48[20];
    void *_videoBuffer;                                                      /* +68 */
};

/* igTextureBindAttr with the texture it binds, which sits after the vptr and reference count at +12. */
class igTextureBindAttrView : public igTextureBindAttrDispatchView {
public:
    char _pad8[4];
    igTextureAttrDispatchView *_texture;                                     /* +12 */
};

class igImageDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25();
    virtual void setWidth(int width);                                        /* slot 26 */
    virtual void setHeight(int height);                                      /* slot 27 */
    virtual void setFormat(int format);                                      /* slot 28 */
    virtual void allocateImage();                                            /* slot 29 */
    virtual void setOrder(int order);                                        /* slot 30 */
    char _pad8[40];
    int _imageSize;                                                          /* +48 */
    void *_pImage;                                                           /* +52 */
};

class igVertexArrayDispatchView : public igObjectDispatchView {
public:
    virtual void d21();
    virtual void configure(igVertexFormat &format, int vertexCount, int, int);     /* slot 22 */
    virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26();
    virtual void setPosition(int index, const igVec3f &position);            /* slot 27 */
    virtual void d28(); virtual void d29();
    virtual void setNormal(int index, const igVec3f &normal);                /* slot 30 */
    virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40();
    virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void setTextureCoord(int unit, int index, const igVec2f &coord); /* slot 48 */
};

class igGeometryAttrDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30();
    virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36();
    virtual void configure(int primType, int primCount, int offset);        /* slot 37 */
    virtual void setVertexRange(int first, int count);                      /* slot 38 */
    char _pad8[4];
    igVertexArrayDispatchView *_vertexArray;                                 /* +12 */
    void setVertexArray(igVertexArrayDispatchView *vertices) {
        if (vertices != 0) vertices->_refCount = vertices->_refCount + 1;
        igRelease(_vertexArray);
        _vertexArray = vertices;
    }
};

extern "C" {
int igMovieInfo_GetTiling(igMovieInfo *movie, int *tileWidth, int *tileHeight, int *tilesAcross, int *tilesDown);
void igMovieManager_Activate(void);
void igMovieManager_Deactivate(igMovieManager *self);
void igMovieManager_InitializeDrawing(igMovieManager *self, igSmartPointer<igObject> visualContext);
void igMovieManager_ReleaseDrawing(igMovieManager *self);
void igMovieManager_Start(void);
void igMovieManager_Stop(void);
int igMovieManager_StopMovie(igMovieManager *self, void *object);
int igMovieManager_AddInfo(igMovieManager *self, igObject *object);
void igMovieManager_RemoveAllInfo(igMovieManager *self);
int igMovieManager_BuildScene(igMovieManager *self, igMovieInfo *movie);
void igMovieManager_Update(void);
void igMovieManager_UpdateMovies(igMovieManager *self);
int igMovieManager_GetMovieState(igMovieManager *self, const char *path);
void igMovieRenderer_InitializeDrawing(igMovieRenderer *self);
void igMovieRenderer_Traverse(void);
void igMovieRenderer_Render(igMovieRenderer *self);
void igMovieRenderer_ReleaseDrawing(igMovieRenderer *self);
int igMovieRenderer_GetMeta(void);
int igMovieManager_GetMeta(void);

int igObject_GetAllocator(void *object);
int Memory_GetAllocatorBySelector(int selector);
int igObject_IsKindOf(void *object, int metaObject);
int strcmp(const char *a, const char *b);
int igObjectSystem_FindMetaByNameDefault(const char *name);
igObject *igMetaObject_CreateInstance(int metaObject, int allocator);
int ObjectList_AppendRetained(void *list, void *object);
int List_RemoveWordAt(void *list, int index);
int igReportError(const char *format, ...);
igObject *igMovieCodecList_Create(int allocator);
igObject *igMovieInfoList_Create(int allocator);
igAudioContextDispatchView *igAudioContext_CreateInstance(int allocator);
igObject *igRendererOrderedList_CreateInstance(int allocator);
void igInsightCore_AddToScheduler(int insight, igMovieManager *manager);
void igInsightCore_RemoveFromScheduler(int insight, igMovieManager *manager);
void igInsightCore_AddRenderer(int insight, int renderer);
void igRendererOrderedList_Append(int list, igObject *renderer, int unique);
void igRendererOrderedList_Clear(int list);
igAttrSet *igAttrSet_CreateInstance(int allocator);
igGeometry *igGeometry_CreateInstance(int allocator);
igCamera *igCamera_CreateInstance(int allocator);
igTransformDispatchView *igTransform_CreateInstance(int allocator);
igSceneInfo *igSceneInfo_CreateInstance(int allocator);
igImageDispatchView *igImage_CreateInstance(int allocator);
igTextureAttrDispatchView *igTextureAttr_CreateInstance(int allocator);
igTextureBindAttrView *igTextureBindAttr_CreateInstance(int allocator);
igTextureList *igTextureList_CreateInstance(int allocator);
igTextureBindAttrList *igTextureBindAttrList_Create(int allocator);
igBlendStateAttrDispatchView *igBlendStateAttr_CreateInstance(int allocator);
igTextureStateAttrDispatchView *igTextureStateAttr_CreateInstance(int allocator);
igGeometryAttrDispatchView *igGeometryAttr_Create(int allocator);
igVertexArrayDispatchView *igVertexArray_Create(int allocator);
void igTextureAttr_SetImage(igTextureAttrDispatchView *texture, igImageDispatchView *image, int level);
igImageDispatchView *igTextureAttr_GetImage(igTextureAttrDispatchView *texture, int level);
void igNamedObject_SetName(void *object, const char *name);
void igGroup_AppendChild(void *group, void *child);
void igMatrix44f_FromTranslation(igMatrix44f *matrix, const igVec3f &translation);
igResult igMatrix44f_Invert(igMatrix44f *inverse, const igMatrix44f *matrix);
void igSceneInfo_CollectCameras(igSceneInfo *info);
void igInsightCore_AddInfo(int insight, igSceneInfo *info);
int snprintf(char *buffer, unsigned int size, const char *format, ...);
void *memset(void *s, int c, unsigned int n);

extern unsigned char g_useOwnerAllocator;
extern int kIGMemoryPoolHandleUser1[];
extern int g_igMovieManager_metaObject[];
extern int g_igMovieRenderer_metaObject[];
extern int g_igMovieCodec_metaObject[];
extern int g_igMovieInfo_metaObject[];
extern int g_igSceneInfo_metaObject[];
extern int g_igAttrSet_metaObject[];
extern int g_igTextureBindAttr_metaObject[];
extern int g_movieDefaultTileWidth;
extern int g_movieDefaultTileHeight;
extern igVec3f g_vec3ZAxis;
extern char emptyString[];
extern unsigned char g_movieUnknownCodecMuted;
extern unsigned char g_movieStartFailedMuted;
extern unsigned char g_movieSceneFailedMuted;
extern unsigned char g_moviePlayFailedMuted;
extern unsigned char g_movieSceneRootTypeMuted;
extern unsigned char g_movieSceneNoTextureBindsMuted;
extern unsigned char g_movieSceneNoSizeMuted;
extern unsigned char g_movieRendererNoManagerMuted;
extern char text_Could_not_create_a_codec_of_type[];
extern char text_Failed_to_start_movie_s[];
extern char text_Failed_to_create_the_scene_for_m[];
extern char text_Failed_to_play_movie_info_s[];
extern char text_igMovieRenderer_initializeDrawin[];
extern char Auto_generated_scene_graph_doesn_t_have_the_right_structure_wrong_root_type[];
extern char Auto_generated_scene_graph_doesn_t_have_the_right_structure_no_texture_binds[];
extern char Scene_Root[];
extern char Movie_camera[];
extern char Default_primitive_camera[];
extern char s_Scene[];
extern char Failed_to_build_the_scene_for_a_movie_info[];
}

/* The pool the manager creates objects in: its own, unless the user pool is selected. */
static inline int MovieAllocator(igMovieManager *self) {
    int allocator = igObject_GetAllocator(self);
    return g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
}

/* Gives the movie renderer its reference to the manager. */
static inline void SetMovieManager(igMovieRenderer *renderer, igMovieManager *manager) {
    if (manager != 0) manager->_refCount = manager->_refCount + 1;
    igRelease((igObject *)renderer->_movieManager);
    renderer->_movieManager = (int)manager;
}

/* A movie's name for a report: the empty string when it has none. */
static inline const char *MovieName(igMovieInfo *movie) {
    const char *name = (const char *)movie->_name;
    const char *shown;
    if (name != 0) {
        shown = name;
    } else {
        shown = emptyString;
    }
    return shown;
}

/* The smallest power of two at least n (1 for n below 2): the size of the texture a tile goes in. */
static inline int NextPowerOfTwo(int n) {
    if (n < 2) return 1;
    int rest = n - 1;
    int bits = 0;
    while ((rest >>= 1) != 0) bits++;
    return 1 << (bits + 1);
}

static inline igSceneInfo *AsSceneInfo(igObject *object) {
    if (object != 0 && igObject_IsKindOf(object, g_igSceneInfo_metaObject[0])) {
        return (igSceneInfo *)object;
    }
    return 0;
}

static inline igAttrSet *AsAttrSet(igObject *object) {
    if (object != 0 && igObject_IsKindOf(object, g_igAttrSet_metaObject[0])) {
        return (igAttrSet *)object;
    }
    return 0;
}

static inline igTextureBindAttrView *AsTextureBindAttr(igObject *object) {
    if (object != 0 && igObject_IsKindOf(object, g_igTextureBindAttr_metaObject[0])) {
        return (igTextureBindAttrView *)object;
    }
    return 0;
}

/* igGroup's child list, which a group may not have yet, and igAttrSet's attribute list: the counts
 * read through a const node and the entries through a writable one. */
static inline int GetChildCount(const igAttrSet *group) {
    return group->_childList != 0 ? ((igObjectListView *)group->_childList)->getCount() : 0;
}
static inline igObject *GetChild(const igAttrSet *group, int index) {
    return ((igObjectListView *)group->_childList)->get(index);
}
static inline int GetAttrCount(const igAttrSet *set) {
    return ((igObjectListView *)set->_attributes)->getCount();
}
static inline igObject *GetAttr(igAttrSet *set, int index) {
    return ((igObjectListView *)set->_attributes)->get(index);
}

/* The tiles a movie's frame is cut into: the movie's tile size, else the default, capped at the
 * frame; a size of -1 is one tile across the frame. */
int igMovieInfo_GetTiling(igMovieInfo *movie, int *tileWidth, int *tileHeight, int *tilesAcross, int *tilesDown) {
    int size;
    size = movie->_tileWidth;
    *tileWidth = (size != -1) ? size : g_movieDefaultTileWidth;
    size = movie->_tileHeight;
    *tileHeight = (size != -1) ? size : g_movieDefaultTileHeight;
    if (*tileWidth == -1) {
        *tileWidth = movie->_width;
        *tilesAcross = 1;
    } else {
        if (movie->_width < *tileWidth) *tileWidth = movie->_width;
        *tilesAcross = movie->_width / *tileWidth;
        if (movie->_width % *tileWidth != 0) *tilesAcross = *tilesAcross + 1;
    }
    if (*tileHeight == -1) {
        *tileHeight = movie->_height;
        *tilesDown = 1;
    } else {
        if (movie->_height < *tileHeight) *tileHeight = movie->_height;
        *tilesDown = movie->_height / *tileHeight;
        if (movie->_height % *tileHeight != 0) *tilesDown = *tilesDown + 1;
    }
    return 1;
}

void igMovieManager_Activate(void)
{
}

void igMovieManager_Deactivate(igMovieManager *self) {
    ((igMovieManagerDispatchView *)self)->stopAllMovies();
}

/* Hands the visual context to the codec of every playing movie. */
void igMovieManager_InitializeDrawing(igMovieManager *self, igSmartPointer<igObject> visualContext) {
    for (int i = 0; i < ((igMovieInfoListView *)self->_movieList)->_count; i++) {
        igMovieInfo *movie = (igMovieInfo *)((igMovieInfoListView *)self->_movieList)->_data[i];
        ((igMovieCodecDispatchView *)movie->_codec)->initializeDrawing(movie, igSmartPointer<igObject>(visualContext.p, kRetainReference));
    }
}

/* Has the codec of every playing movie release what it draws with. */
void igMovieManager_ReleaseDrawing(igMovieManager *self) {
    for (int i = 0; i < ((igMovieInfoListView *)self->_movieList)->_count; i++) {
        igMovieInfo *movie = (igMovieInfo *)((igMovieInfoListView *)self->_movieList)->_data[i];
        ((igMovieCodecDispatchView *)movie->_codec)->releaseDrawing(movie);
    }
}

void igMovieManager_Start(void)
{
}

void igMovieManager_Stop(void)
{
}

/* Starts a movie: finds a reusable codec of the movie's codec type or creates one, opens the movie
 * in it, builds its scene (an ADX stream needs none) and starts it, then schedules the manager and
 * puts the movie renderer in place of the insight's renderers, which it keeps until the last movie
 * stops. Returns 0 when the movie cannot be played. */
int igMovieManager_AddInfo(igMovieManager *self, igObject *object) {
    int i;
    igMovieInfo *movie;
    int allocator;
    if (object != 0 && igObject_IsKindOf(object, g_igMovieInfo_metaObject[0]) != 0) {
        movie = (igMovieInfo *)object;
    } else {
        movie = 0;
    }
    if (movie != 0) {
        const char *codecType = (const char *)movie->_codecType;
        if (codecType != 0) {
            igMovieInfoListView *movies = (igMovieInfoListView *)self->_movieList;
            if (movies != 0) {
                if (movies->indexOf(movie) != -1) return 0;
            }
            igSmartPointer<igMovieCodecDispatchView> codec(0, kRetainReference);
            if (self->_codecList != 0) {
                for (i = 0; i < ((igObjectListView *)self->_codecList)->_count; i++) {
                    igMovieCodecDispatchView *candidate = (igMovieCodecDispatchView *)((igObjectListView *)self->_codecList)->_data[i];
                    if (strcmp((const char *)candidate->GetMeta()->_name, codecType) == 0) {
                        codec = candidate;
                        break;
                    }
                }
            }
            if (codec.p == 0) {
                int meta = igObjectSystem_FindMetaByNameDefault(codecType);
                if (meta == 0) {
                    if (g_movieUnknownCodecMuted == 0) {
                        int answer = igReportError(text_Could_not_create_a_codec_of_type, codecType);
                        if (answer != 1) {
                            if (answer == 2) g_movieUnknownCodecMuted = 1;
                        }
                    }
                    return 0;
                }
                allocator = MovieAllocator(self);
                igObject *created = igMetaObject_CreateInstance(meta, allocator);
                igMovieCodecDispatchView *createdCodec;
                if (created != 0 && igObject_IsKindOf(created, g_igMovieCodec_metaObject[0]) != 0) {
                    createdCodec = (igMovieCodecDispatchView *)created;
                } else {
                    createdCodec = 0;
                }
                codec = createdCodec;
                /* the factory's reference */
                {
                    igMovieCodecDispatchView *held = codec.p;
                    held->_refCount = held->_refCount - 1;
                    if ((held->_refCount & 0x7FFFFF) == 0) igObject_Destroy(held);
                }
                if (codec->isReusable() != 0) {
                    if (self->_codecList == 0) {
                        allocator = MovieAllocator(self);
                        igRelease((igObject *)self->_codecList);
                        self->_codecList = (int)igMovieCodecList_Create(allocator);
                    }
                    ObjectList_AppendRetained((void *)self->_codecList, codec.p);
                }
            }
            (igSmartPointer<igMovieCodecDispatchView> &)movie->_codec = codec;
            if (self->_audioDisabled == 0 && self->_audio == 0) {
                allocator = MovieAllocator(self);
                igRelease((igObject *)self->_audio);
                self->_audio = (int)igAudioContext_CreateInstance(allocator);
                ((igAudioContextDispatchView *)self->_audio)->setWindow((igObject *)((igInsightCore *)self->_insight)->_window);
                ((igAudioContextDispatchView *)self->_audio)->initialize();
            }
            codec->initialize(((igWindowDispatchView *)((igInsightCore *)self->_insight)->_window)->getVisualContext(), (igObject *)self->_audio);
            if (codec->open(movie) != 0) {
                if (movie->_type == kMovieTypeAdx || ((igMovieManagerDispatchView *)self)->buildScene(movie) != 0) {
                    if (codec->play(movie) == 0) {
                        if (g_movieStartFailedMuted == 0) {
                            int answer = igReportError(text_Failed_to_start_movie_s, MovieName(movie));
                            if (answer != 1) {
                                if (answer == 2) g_movieStartFailedMuted = 1;
                            }
                        }
                        return 0;
                    }
                    if (self->_movieList == 0) {
                        allocator = MovieAllocator(self);
                        igRelease((igObject *)self->_movieList);
                        self->_movieList = (int)igMovieInfoList_Create(allocator);
                    }
                    ObjectList_AppendRetained((void *)self->_movieList, movie);
                    igInsightCore_AddToScheduler(self->_insight, self);
                    SetMovieManager((igMovieRenderer *)self->_movieRenderer, self);
                    if (self->_rendererList == 0) {
                        allocator = MovieAllocator(self);
                        igRelease((igObject *)self->_rendererList);
                        self->_rendererList = (int)igRendererOrderedList_CreateInstance(allocator);
                    }
                    {
                        int n = ((igObjectListView *)((igRendererOrderedList *)((igInsightCore *)self->_insight)->_rendererList)->_objectList)->_count;
                        for (i = 0; i < n; i++) {
                            igRendererOrderedList_Append(self->_rendererList,
                                ((igObjectListView *)((igRendererOrderedList *)((igInsightCore *)self->_insight)->_rendererList)->_objectList)->_data[(unsigned)i] /* matching construct: unsigned index keeps the scale inside the loop */, 0);
                        }
                    }
                    igRendererOrderedList_Clear(((igInsightCore *)self->_insight)->_rendererList);
                    igInsightCore_AddRenderer(self->_insight, self->_movieRenderer);
                    return 1;
                }
                if (g_movieSceneFailedMuted == 0) {
                    int answer = igReportError(text_Failed_to_create_the_scene_for_m, MovieName(movie));
                    if (answer != 1) {
                        if (answer == 2) g_movieSceneFailedMuted = 1;
                    }
                }
                return 0;
            }
            if (g_moviePlayFailedMuted == 0) {
                int answer = igReportError(text_Failed_to_play_movie_info_s, MovieName(movie));
                if (answer != 1) {
                    if (answer == 2) g_moviePlayFailedMuted = 1;
                }
            }
            return 0;
        }
    }
    return 0;
}

/* Stops a playing movie: pauses and closes it in its codec, drops it from the movie list,
 * unschedules the manager once no movie is left, releases the codec list and gives the insight
 * back the renderers it held before the movie started. */
int igMovieManager_StopMovie(igMovieManager *self, void *object) {
    int index;
    igMovieInfo *movie;
    if (object != 0 && igObject_IsKindOf(object, g_igMovieInfo_metaObject[0]) != 0) {
        movie = (igMovieInfo *)object;
    } else {
        movie = 0;
    }
    igMovieInfoListView *movies = (igMovieInfoListView *)self->_movieList;
    if (movies != 0 && movie != 0) {
        /* matching construct: fdiff — igMovieInfoListView::indexOf written out with the result copied
         * into `index`, declared before `movie`: the inline's return value colours before the movie
         * (s0/s1 swapped); the caller's index keeps the movie in s0 as retail does */
        {
            igObject *key = movie;
            int n = movies->_count;
            int i = 0;
            if (0 < n) {
                igObject **p = movies->_data;
                do {
                    if (igMovieInfoListView::key(&key) == *p) {
                        index = i;
                        goto found;
                    }
                    i++;
                    p++;
                } while (i < n);
            }
            index = -1;
        found:;
        }
        if (index != -1) {
            ((igMovieCodecDispatchView *)movie->_codec)->pause(movie, kMovieStatePaused);
            ((igMovieCodecDispatchView *)movie->_codec)->close(movie);
            {
                igMovieInfoListView *list = (igMovieInfoListView *)self->_movieList;
                igRelease(list->_data[index]);
                List_RemoveWordAt(list, index);
                list->_data[list->_count] = 0;
            }
            if (((igMovieInfoListView *)self->_movieList)->_count == 0) {
                igInsightCore_RemoveFromScheduler(self->_insight, self);
                igRelease((igObject *)self->_movieList);
                self->_movieList = 0;
            }
            if (self->_codecList != 0) {
                igRelease((igObject *)self->_codecList);
                self->_codecList = 0;
            }
            igRendererOrderedList_Clear(((igInsightCore *)self->_insight)->_rendererList);
            {
                igRendererOrderedList *saved = (igRendererOrderedList *)self->_rendererList;
                int n = ((igObjectListView *)saved->_objectList)->_count;
                int i;
                for (i = 0; i < n; i++) {
                    igRendererOrderedList_Append(((igInsightCore *)self->_insight)->_rendererList,
                                                 ((igObjectListView *)((igRendererOrderedList *)self->_rendererList)->_objectList)->_data[(unsigned)i], 0);
                }
            }
            igRendererOrderedList_Clear(self->_rendererList);
            igRelease((igObject *)self->_rendererList);
            self->_rendererList = 0;
            return 1;
        }
    }
    return 0;
}

/* Stops the playing movies one by one until none is left or one will not stop. */
void igMovieManager_RemoveAllInfo(igMovieManager *self) {
    igMovieInfoListView *movies;
    /* matching construct: variant test — the (bool) conversion materialises the list test (sltu, xori) where a
     * plain pointer test branches on it */
    while ((movies = (igMovieInfoListView *)self->_movieList, (bool)movies) && movies->_count != 0) {
        if (((igMovieManagerDispatchView *)self)->stopMovie(movies->_data[0]) == 0) break;
    }
}

/* Builds what a movie draws into: its texture bind attributes come from the movie info, from the
 * scene the info already has, or from a new scene of one textured quad per tile; then one image
 * and texture per bind, and the image the codec decodes into. Returns 0 when the movie has no size
 * or its scene has the wrong structure. */
int igMovieManager_BuildScene(igMovieManager *self, igMovieInfo *movie) {
    if (movie->_width != -1 && movie->_height != -1) {
        igSmartPointer<igTextureBindAttrList> binds(0, kRetainReference);
        igSmartPointer<igTextureList> textures(0, kRetainReference);
        int tileWidth;
        int tileHeight;
        int tilesAcross;
        int tilesDown;
        if (igMovieInfo_GetTiling(movie, &tileWidth, &tileHeight, &tilesAcross, &tilesDown) == 0) {
            return 0;
        }
        movie->_tileWidth = tileWidth;
        movie->_tileHeight = tileHeight;
        int textureWidth = NextPowerOfTwo(tileWidth);
        int textureHeight = NextPowerOfTwo(tileHeight);

        if (movie->_sceneInfo != 0) {
            bool found = false;
            for (int i = 0; i < ((igInfoList *)((igInsightCore *)self->_insight)->_infoList)->_count; i++) {
                igSmartPointer<igSceneInfo> info(
                    AsSceneInfo(((igObject **)((igInfoList *)((igInsightCore *)self->_insight)->_infoList)->_data)[i]),
                    kRetainReference);
                if (info != 0 && info == (igSceneInfo *)movie->_sceneInfo) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                (igSmartPointer<igSceneInfo> &)movie->_sceneInfo = 0;
            }
        }

        igTextureBindAttrList *videoTextures = (igTextureBindAttrList *)movie->_videoTextures;
        if (videoTextures != 0 && videoTextures->_count != 0) {
            binds = videoTextures;
        } else if (movie->_sceneInfo != 0) {
            igSmartPointer<igAttrSet> root(
                AsAttrSet((igObject *)((igSceneInfo *)movie->_sceneInfo)->_sceneGraph),
                kRetainReference);
            igSmartPointer<igTextureBindAttrView> bind;
            igSmartPointer<igAttrSet> child;
            if (root == 0) {
                if (g_movieSceneRootTypeMuted == 0) {
                    int answer = igReportError(Auto_generated_scene_graph_doesn_t_have_the_right_structure_wrong_root_type);
                    if (answer != 1 && answer == 2) g_movieSceneRootTypeMuted = 1;
                }
                return 0;
            }
            for (int i = 0; i < GetChildCount(root.p); i++) {
                child = AsAttrSet(GetChild(root.p, i));
                if (child != 0) {
                    for (int j = 0; j < GetAttrCount(child); j++) {
                        bind = AsTextureBindAttr(GetAttr(child, j));
                        if (bind != 0 && bind->_texture != 0) {
                            if (binds == 0) {
                                int allocator = MovieAllocator(self);
                                binds.release();
                                binds.p = igTextureBindAttrList_Create(allocator);
                            }
                            ObjectList_AppendRetained(binds.p, bind.p);
                            if (textures == 0) {
                                int allocator = MovieAllocator(self);
                                textures.release();
                                textures.p = igTextureList_CreateInstance(allocator);
                            }
                            ObjectList_AppendRetained(textures.p, bind->_texture);
                        }
                    }
                }
            }
            if (binds == 0) {
                if (g_movieSceneNoTextureBindsMuted == 0) {
                    int answer = igReportError(Auto_generated_scene_graph_doesn_t_have_the_right_structure_no_texture_binds);
                    if (answer != 1 && answer == 2) g_movieSceneNoTextureBindsMuted = 1;
                }
                return 0;
            }
        } else {
            igSmartPointer<igSceneInfo> sceneInfo;
            igSmartPointer<igAttrSet> root;
            igSmartPointer<igAttrSet> tile;
            igSmartPointer<igTextureBindAttrView> bind;
            {
                int allocator = MovieAllocator(self);
                root.release();
                root.p = igAttrSet_CreateInstance(allocator);
            }
            igNamedObject_SetName(root.p, Scene_Root);
            igSmartPointer<igBlendStateAttrDispatchView> blend(igBlendStateAttr_CreateInstance(MovieAllocator(self)));
            blend->setEnabled(true);
            ObjectList_AppendRetained((void *)root->_attributes, blend.p);
            igSmartPointer<igTextureStateAttrDispatchView> textureState(igTextureStateAttr_CreateInstance(MovieAllocator(self)));
            textureState->setEnabled(true);
            ObjectList_AppendRetained((void *)root->_attributes, textureState.p);

            float width;
            int movieHeight = movie->_height;
            int movieWidth = movie->_width;
            float aspect = (float)movieWidth / (float)movieHeight;
            if (aspect >= 1.0f) {
                width = 1.0f;
            } else {
                width = 1.0f / aspect;
            }
            float height;
            if (aspect <= 1.0f) {
                height = 1.0f;
            } else {
                height = 1.0f / aspect;
            }
            float x = -(width / 2.0f);
            float y = height / 2.0f;
            int usedWidth = movieWidth - movieWidth % tilesAcross;
            int texturesWidth = tilesAcross * textureWidth;
            int usedHeight = movieHeight - movieHeight % tilesDown;
            int texturesHeight = tilesDown * textureHeight;
            float minU = 0.0f;
            float minV = 0.0f;
            float tileSizeX = width / (float)tilesAcross;
            float tileSizeY = height / (float)tilesDown;
            float maxU = (float)usedWidth / (float)texturesWidth;
            float maxV = (float)usedHeight / (float)texturesHeight;
            igVertexFormat format;
            format._flags = 0;
            format.setVertices(true);
            format.setNormals(true);
            format.setTextureCoordCount(1);
            {
                int allocator = MovieAllocator(self);
                binds.release();
                binds.p = igTextureBindAttrList_Create(allocator);
            }
            for (int row = 0; row < tilesDown; row++) {
                for (int column = 0; column < tilesAcross; column++) {
                    {
                        int allocator = MovieAllocator(self);
                        tile.release();
                        tile.p = igAttrSet_CreateInstance(allocator);
                    }
                    igSmartPointer<igGeometry> geometry(igGeometry_CreateInstance(MovieAllocator(self)));
                    igSmartPointer<igGeometryAttrDispatchView> geometryAttr(igGeometryAttr_Create(MovieAllocator(self)));
                    igSmartPointer<igVertexArrayDispatchView> vertices(igVertexArray_Create(MovieAllocator(self)));
                    vertices->configure(format, 4, 2, 0);
                    /* the quad's left edge (0) and right edge (1), top vertex then bottom */
                    for (int edge = 0; edge <= 1; edge++) {
                        vertices->setPosition(edge * 2, igVec3f(x + (float)edge * tileSizeX, y, 0.0f));
                        vertices->setNormal(edge * 2, g_vec3ZAxis);
                        vertices->setTextureCoord(0, edge * 2, igVec2f(minU + (float)edge * maxU, minV));
                        vertices->setPosition(edge * 2 + 1, igVec3f(x + (float)edge * tileSizeX, y - tileSizeY, 0.0f));
                        vertices->setNormal(edge * 2 + 1, g_vec3ZAxis);
                        vertices->setTextureCoord(0, edge * 2 + 1, igVec2f(minU + (float)edge * maxU, minV + maxV));
                    }
                    geometryAttr->setVertexArray(vertices);
                    geometryAttr->configure(kPrimitiveTriangleStrip, 1, 0);
                    geometryAttr->setVertexRange(0, 4);
                    {
                        int allocator = MovieAllocator(self);
                        bind.release();
                        bind.p = igTextureBindAttr_CreateInstance(allocator);
                    }
                    ObjectList_AppendRetained(binds.p, bind.p);
                    ObjectList_AppendRetained((void *)tile->_attributes, bind.p);
                    igGroup_AppendChild(tile.p, geometry.p);
                    ObjectList_AppendRetained((void *)geometry->_attributes, geometryAttr.p);
                    igGroup_AppendChild(root.p, tile.p);
                    x += tileSizeX;
                }
                y -= tileSizeY;
                x = -(width / 2.0f);
            }

            igMatrix44f view;
            igMatrix44f_FromTranslation(&view, igVec3f(0.0f, 0.0f, -1.2f));
            igMatrix44f_Invert(&view, &view);
            igSmartPointer<igCamera> camera(igCamera_CreateInstance(MovieAllocator(self)));
            igNamedObject_SetName(camera.p, Movie_camera);
            camera->_nearPlane = 0.0f;
            camera->_farPlane = 1.2f;
            igSmartPointer<igTransformDispatchView> transform(igTransform_CreateInstance(MovieAllocator(self)));
            igNamedObject_SetName(transform.p, Default_primitive_camera);
            transform->SetMatrix(view.m);
            igGroup_AppendChild(transform.p, camera.p);
            igGroup_AppendChild(root.p, transform.p);
            char name[256];
            snprintf(name, sizeof(name), s_Scene, movie->_name != 0 ? (const char *)movie->_name : (const char *)emptyString);
            {
                int allocator = MovieAllocator(self);
                sceneInfo.release();
                sceneInfo.p = igSceneInfo_CreateInstance(allocator);
            }
            igNamedObject_SetName(sceneInfo.p, name);
            (igSmartPointer<igAttrSet> &)sceneInfo->_sceneGraph = root;
            igSceneInfo_CollectCameras(sceneInfo.p);
            igInsightCore_AddInfo(self->_insight, sceneInfo.p);
            (igSmartPointer<igSceneInfo> &)movie->_sceneInfo = sceneInfo;
        }

        if (textures == 0) {
            int allocator = MovieAllocator(self);
            textures.release();
            textures.p = igTextureList_CreateInstance(allocator);
        }
        igSmartPointer<igImageDispatchView> image;
        igSmartPointer<igTextureAttrDispatchView> texture;
        for (int i = 0; i < binds->_count; i++) {
            {
                int allocator = MovieAllocator(self);
                image.release();
                image.p = igImage_CreateInstance(allocator);
            }
            image->setWidth(textureWidth);
            image->setHeight(textureHeight);
            image->setFormat(movie->_imageFormat);
            image->setOrder(102);
            image->allocateImage();
            memset(image->_pImage, 0, image->_imageSize);
            {
                int allocator = MovieAllocator(self);
                texture.release();
                texture.p = igTextureAttr_CreateInstance(allocator);
            }
            texture->_source = 2;
            texture->_videoBuffer = image->_pImage;
            texture->setMinFilter(movie->_minificationFilter);
            texture->setMagFilter(movie->_magnificationFilter);
            igTextureAttr_SetImage(texture.p, image.p, 0);
            ((igTextureBindAttrView **)binds->_data)[i]->setTexture((igObject *)texture.p);
            ObjectList_AppendRetained(textures.p, texture.p);
        }
        (igSmartPointer<igTextureList> &)movie->_runtimeTextures = textures;
        if (binds->_count == 1) {
            image = igTextureAttr_GetImage(((igTextureBindAttrView **)binds->_data)[0]->_texture, 0);
        } else {
            {
                int allocator = MovieAllocator(self);
                image.release();
                image.p = igImage_CreateInstance(allocator);
            }
            image->setWidth(movie->_width);
            image->setHeight(movie->_height);
            image->setFormat(movie->_imageFormat);
            image->setOrder(102);
            if (tileWidth != kMacroblockSize || tileHeight != movie->_height) {
                image->allocateImage();
                memset(image->_pImage, 0, image->_imageSize);
            }
        }
        (igSmartPointer<igImageDispatchView> &)movie->_runtimeImage = image;
        return 1;
    }
    if (g_movieSceneNoSizeMuted == 0) {
        int answer = igReportError(Failed_to_build_the_scene_for_a_movie_info);
        if (answer != 1 && answer == 2) g_movieSceneNoSizeMuted = 1;
    }
    return 0;
}

void igMovieManager_Update(void)
{
}

/* Runs the codec of every playing movie for the frame: decodes and hands on its picture. */
void igMovieManager_UpdateMovies(igMovieManager *self) {
    if (self->_movieList != 0) {
        for (int i = 0; i < ((igMovieInfoListView *)self->_movieList)->_count; i++) {
            igMovieInfo *movie = (igMovieInfo *)((igMovieInfoListView *)self->_movieList)->_data[i];
            ((igMovieCodecDispatchView *)movie->_codec)->update(movie);
        }
    }
}

/* The state of the playing movie with this path; finished when the manager holds none. */
int igMovieManager_GetMovieState(igMovieManager *self, const char *path) {
    igMovieInfoListView *movies = (igMovieInfoListView *)self->_movieList;
    if (movies == 0) {
        return kMovieStateFinished;
    }
    int count = movies->_count;
    if (count <= 0) {
        return kMovieStateFinished;
    }
    for (int i = 0; i < count; i++) {
        igMovieInfo *movie = (igMovieInfo *)movies->_data[i];
        if (strcmp((const char *)movie->_path, path) == 0) {
            return movie->_state;
        }
        movies = (igMovieInfoListView *)self->_movieList;
        count = movies->_count;
    }
    return kMovieStateFinished;
}

void igMovieRenderer_InitializeDrawing(igMovieRenderer *self) {
    if (self->_movieManager == 0 && g_movieRendererNoManagerMuted == 0) {
        int answer = igReportError(text_igMovieRenderer_initializeDrawin);
        if (answer != 1 && answer == 2) {
            g_movieRendererNoManagerMuted = 1;
        }
    }
    igMovieManager_InitializeDrawing((igMovieManager *)self->_movieManager,
                                     igSmartPointer<igObject>((igObject *)self->_visualContext, kRetainReference));
}

void igMovieRenderer_Traverse(void)
{
}

void igMovieRenderer_Render(igMovieRenderer *self)
{
    igMovieManager_UpdateMovies((igMovieManager *)self->_movieManager);
}

void igMovieRenderer_ReleaseDrawing(igMovieRenderer *self)
{
    igMovieManager_ReleaseDrawing((igMovieManager *)self->_movieManager);
}

int igMovieRenderer_GetMeta(void)
{
    return g_igMovieRenderer_metaObject[0];
}

int igMovieManager_GetMeta(void)
{
    return g_igMovieManager_metaObject[0];
}
