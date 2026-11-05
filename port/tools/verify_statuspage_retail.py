#!/usr/bin/env python3
"""Execute retail list paging 40dbf0/40dd30 with controlled pad/SD leaves."""
import ctypes as C
import itertools
from pathlib import Path
import subprocess
import tempfile
from verify_statusctrl_retail import Retail as BaseRetail, ROOT, BASE, NODE

PAD = BASE + 0x250000
class Input(C.Structure):
    _fields_ = [(name, C.c_uint32) for name in ('horizontal', 'analog', 'digital')]
IO = C.CFUNCTYPE(C.c_int, C.c_void_p, C.c_char_p, C.c_char_p)
class Retail(BaseRetail):
    def call(self, entry, args):
        if entry == 0x39b810:
            return PAD
        if entry == 0x38e5f0:
            self.events.append((self.string(args[2]), self.string(args[4])))
            return 0
        return super().call(entry, args)
    def turn(self, page, pages, next_page, pad):
        self.events = []
        self.w(NODE + 84, 4, page)
        self.w(NODE + 88, 4, pages)
        for offset, value in ((28, pad.horizontal), (32, 0), (36, pad.analog),
                              (72, pad.digital), (76, 0)):
            self.w(PAD + offset, 4, value)
        result = self.invoke(0x40dd30 if next_page else 0x40dbf0, NODE)
        return result, self.read(NODE + 84, 4), self.events

def main():
    elf = ROOT.parent.parent / 'local/extracted/SLUS_208.36'
    if not elf.exists():
        print('STATUS paging: private ELF unavailable, skipped')
        return
    retail = Retail(elf.read_bytes())
    total = 0
    with tempfile.TemporaryDirectory() as tmp:
        so = Path(tmp) / 'paging.so'
        subprocess.run(['cc', '-shared', '-fPIC', '-std=c99', '-I' + str(ROOT/'include'),
                        str(ROOT/'src/statuspage.c'), '-o', str(so)], check=True)
        native = C.CDLL(str(so))
        native.dw4_statuspage_turn.argtypes = [C.POINTER(C.c_int32), C.c_int, C.c_int,
                                               C.POINTER(Input), IO, C.c_void_p]
        for pages in range(1, 4):
            for page, next_page, horizontal, analog, digital in itertools.product(
                    range(pages), range(2), (0, 2, 8, 10), (0, 1, 4, 5, 2, 8),
                    (0, 0x20, 0x80, 0xa0)):
                pad = Input(horizontal, analog, digital)
                expected = retail.turn(page, pages, next_page, pad)
                events = []
                @IO
                def io(user, model, sequence):
                    events.append((model.decode(), sequence.decode()))
                    return 0
                current = C.c_int32(page)
                result = native.dw4_statuspage_turn(C.byref(current), pages, next_page,
                                                     C.byref(pad), io, None)
                assert (result, current.value, events) == expected, (
                    page, pages, next_page, horizontal, analog, digital,
                    (result, current.value, events), expected)
                total += 1
        print(f'STATUS paging: {total} page/input/boundary states and arrow traces match retail instructions')
if __name__ == '__main__':
    main()
