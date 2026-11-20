#ifndef DW4_IGOBJECTMACROS_H
#define DW4_IGOBJECTMACROS_H

/* The reflection members every registered class declares, as Alchemy's object macros spell them
 * (alchemy-kit_202309 include/igCore/igObjectMacros.h: IG_OBJECT_COMMON, IG_OBJECT_DEFINE,
 * IG_ABSTRACT_OBJECT_DEFINE, IG_OBJECT_BOOTSTRAP, IG_BOOTSTRAP_ABSTRACT_OBJECT_DEFINE), kept to the members
 * this engine's registration has: _Meta is the handle
 * the registrar fills, arkRegisterInternal registers the class (a subclass passes it as its parent
 * registrar), arkRegister runs that once, getClassTypeSafe registers on first use and returns _Meta,
 * getClassTypeLazy creates the bare metaobject, _instantiateFromPool registers the class and creates an
 * instance from a pool, getClassMetaSafe is the class's own accessor and
 * getClassMeta the one a subclass passes for its parent, arkRegisterInitialize adds the fields, and
 * retrieveVTablePointer reads the vtable of a class that can be instantiated. Their definitions are the
 * library's generated boilerplate. getMeta is the kit's inline accessor: in a class derived from the
 * polymorphic Gap::Core::igObject it overrides that root's virtual slot 20, so the compiler writes it
 * with the class's vtable; in a flat struct it is a plain accessor and adds no vtable. */
#ifdef __cplusplus
struct igMetaObject;
struct igMetaField;
struct igMemoryPoolView;
struct CallbackArray;

#define IG_OBJECT_COMMON(CLASSNAME) \
    typedef CLASSNAME ThisClass; \
    protected: \
    static igMetaObject *_Meta; \
    private: \
    static void arkRegisterInitialize(); \
    public: \
    static CLASSNAME *_instantiateFromPool(igMemoryPoolView *pool); \
    static void arkRegister(); \
    static CallbackArray *arkRegisterInternal(); \
    static inline igMetaObject *getClassMeta() { return _Meta; } \
    static inline igMetaObject *getClassMetaSafe() { return getClassTypeSafe(); } \
    static igMetaObject *getClassTypeSafe(); \
    static igMetaObject *getClassTypeLazy(); \
    inline igMetaObject *getMeta() const { return _Meta; }

#define IG_OBJECT_NON_ABSTRACT(CLASSNAME) \
    public: \
    static void *retrieveVTablePointer();

#define IG_OBJECT_DEFINE(CLASSNAME) \
    IG_OBJECT_NON_ABSTRACT(CLASSNAME) \
    IG_OBJECT_COMMON(CLASSNAME)

#define IG_ABSTRACT_OBJECT_DEFINE(CLASSNAME) \
    IG_OBJECT_COMMON(CLASSNAME)

/* A bootstrap class (igMetaField, igMetaObject, ...) is constructed before the object system runs: it
 * declares its constructors and the slot-0 destruct override itself. */
#define IG_OBJECT_BOOTSTRAP(CLASSNAME) \
    public: \
    CLASSNAME(); \
    CLASSNAME(bool boot); \
    CLASSNAME(const CLASSNAME &other); \
    virtual void __bootstrapDestruct();

#define IG_BOOTSTRAP_ABSTRACT_OBJECT_DEFINE(CLASSNAME) \
    IG_OBJECT_BOOTSTRAP(CLASSNAME) \
    IG_OBJECT_COMMON(CLASSNAME)
#endif

#endif
