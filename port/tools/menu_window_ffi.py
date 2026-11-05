"""Host wrapper ABI for window-tree oracles; game fields resolve in the arena."""
import ctypes as C


class Window(C.Structure):
    pass


WP = C.POINTER(Window)
IO = C.CFUNCTYPE(C.c_int, WP, C.c_void_p, C.c_size_t)


class Game(C.Structure):
    _fields_ = [('header', C.c_ubyte * 24), ('active', C.c_ubyte),
                ('padding', C.c_ubyte * 3)] + [(n, C.c_int32) for n in ('state', 'sub', 'delay', 'latch')]


Window._fields_ = [('arena', C.c_void_p), ('object', C.c_uint32), ('update', IO),
                   ('user', C.c_void_p), ('release', C.c_void_p), ('children', C.POINTER(WP))]


def bind_windows(lib):
    lib.dw4_menu_window_data.argtypes = [WP]
    lib.dw4_menu_window_data.restype = C.POINTER(Game)
    lib.dw4_menu_window_count.argtypes = [WP]
    lib.dw4_menu_window_count.restype = C.c_size_t
    for name in ('active', 'state', 'sub', 'delay', 'latch'):
        def get(self, field=name):
            return getattr(lib.dw4_menu_window_data(C.byref(self)).contents, field)

        def set_value(self, value, field=name):
            setattr(lib.dw4_menu_window_data(C.byref(self)).contents, field, value)

        setattr(Window, name, property(get, set_value))
    Window.count = property(lambda self: lib.dw4_menu_window_count(C.byref(self)))
