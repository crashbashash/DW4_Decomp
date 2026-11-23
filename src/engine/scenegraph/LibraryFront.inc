unsigned char g_SceneGraphLibrary_registered;

void SceneGraphLibrary_MarkRegistered(void) {
    if (g_SceneGraphLibrary_registered == 0) {
        g_SceneGraphLibrary_registered = 1;
    }
}

namespace Gap {
namespace Sg {

igMetaObject *igGroup::_Meta;
igMetaField *igGroup::k_childList;
}
}

