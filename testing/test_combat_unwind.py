"""Bounded MW unwind decoding from controlled source fixtures and retail anchors.

The hex fixtures are exception metadata from the two source probes below,
compiled with the content-pinned combat compiler at -O3,p. Destructor pointer
fields are unrelocated zeros. No game binary extracts or objects are fixtures.
"""
import importlib.util
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('combat_unwind', ROOT/'scripts/combat_unwind_inventory.py')
unwind = importlib.util.module_from_spec(spec)
spec.loader.exec_module(unwind)

SCOPES_SOURCE = """extern "C" void observe(void *);
extern "C" void cleanup(int);
class ScopeWord { public: int value; ScopeWord(int v):value(v) {} ~ScopeWord(){cleanup(value);} };
extern "C" int scope_single(int n) { ScopeWord first(n); observe(&first); return n; }
extern "C" int scope_sequence(int n) { { ScopeWord first(n); observe(&first); } { ScopeWord second(n+1); observe(&second); } return n; }
extern "C" int scope_nested(int n) { ScopeWord first(n); observe(&first); { ScopeWord second(n+1); observe(&second); } return n; }
extern "C" int scope_conditional(int n) { if(n) { ScopeWord first(n); observe(&first); } return n; }
"""

GEOMETRY_SOURCE = """extern "C" int observe(void *);
extern "C" void cleanup(int);
class ScopeWord {public:int value;ScopeWord(int v):value(v){}~ScopeWord(){cleanup(value);}};
extern "C" int scope_wide(int n){volatile char pad[20000];pad[0]=n;ScopeWord r(n);observe(&r);return pad[0]+n;}
extern "C" int scope_many(int n){int a=observe((void*)n),b=observe((void*)(n+1)),c=observe((void*)(n+2));ScopeWord r(n);observe(&r);return a+b+c+n;}
extern "C" int scope_range(int n){ScopeWord r(n);n+=observe(&r);n+=observe(&r);n+=observe(&r);return n;}
extern "C" float observef(float);
extern "C" float scope_float(float n){float a=observef(n),b=observef(n+1),c=observef(n+2);ScopeWord r((int)n);observe(&r);return a+b+c+n;}
extern "C" float scope_mixed(float n,int k){float a=observef(n);int j=observe((void*)k);ScopeWord r(k);observe(&r);return a+n+j+k;}
extern "C" float scope_float_one(float n){ScopeWord r((int)n);observe(&r);return n;}
extern "C" int manyargs(int,int,int,int,int,int,int,int,int,int,int,int);
extern "C" int scope_outgoing(int n){ScopeWord r(n);n+=manyargs(n,n,n,n,n,n,n,n,n,n,n,n);observe(&r);return n;}
"""

FIXTURES = {'scope_conditional': ('01600048000e00825800000000', 68),
 'scope_float': ('40600008c0001000825800000000', 148),
 'scope_float_one': ('4060000248001000825800000000', 64),
 'scope_many': ('04c00090000e0082015c00000000', 124),
 'scope_mixed': ('42a000048000100082014c00000000', 132),
 'scope_nested': ('01600038002620001a10002600025000000000825800000000', 80),
 'scope_outgoing': ('01a04088180e0082014c00000000', 108),
 'scope_range': ('01600038300e00825800000000', 84),
 'scope_sequence': ('01600038001430002000825800000000825000000000', 80),
 'scope_single': ('01600038000e00825800000000', 56),
 'scope_wide': ('01034e50004000120082034e4c00000000', 68)}

class UnwindTests(unittest.TestCase):
    def fixture(self, name):
        raw, size = FIXTURES[name]
        return unwind.decode(bytes.fromhex(raw), 0, size)

    def test_compact_widths_and_truncation(self):
        for raw, expected in [('60', 48), ('014c', 76), ('034e50', 20048), ('034e4c', 20044)]:
            data = bytes.fromhex(raw)
            self.assertEqual(unwind.number(data, 0), (expected, len(data)))
        for raw in ['', '01', '034e', '07000000']:
            with self.assertRaises(unwind.DecodeError):
                unwind.number(bytes.fromhex(raw), 0)

    def test_sequential_nested_and_conditional_cleanup_lifetimes(self):
        expected = {'scope_single': [(28, 28, [44])],
                    'scope_sequence': [(28, 28, [44]), (52, 52, [40])],
                    'scope_nested': [(28, 28, [44]), (44, 44, [40, 44]), (52, 52, [44])],
                    'scope_conditional': [(36, 36, [44])]}
        for name, wanted in expected.items():
            with self.subTest(name=name):
                result = self.fixture(name)
                observed = [(row['start'], row['end_inclusive'],
                             [action['stack_offset'] for action in row['cleanup_chain']])
                            for row in result['ranges']]
                self.assertEqual(observed, wanted)
                self.assertEqual((result['frame'], result['saved_gprs']), (48, 1))

    def test_frame_save_area_fprs_and_nonzero_range_length(self):
        expected = {'scope_wide': (1, 0, 20048, 0, 32, 32),
                    'scope_many': (4, 0, 96, 0, 72, 72),
                    'scope_range': (1, 0, 48, 0, 28, 52),
                    'scope_float': (0, 4, 48, 0, 96, 96),
                    'scope_mixed': (2, 2, 80, 0, 64, 64),
                    'scope_float_one': (0, 1, 48, 0, 36, 36),
                    'scope_outgoing': (1, 0, 80, 32, 68, 80)}
        for name, wanted in expected.items():
            with self.subTest(name=name):
                result = self.fixture(name)
                row = result['ranges'][0]
                self.assertEqual((result['saved_gprs'], result['saved_fprs'], result['frame'],
                                  result['save_area_base'], row['start'], row['end_inclusive']), wanted)
                self.assertLessEqual(result['return_save_offset'] + 8, result['frame'])

    def test_reject_impossible_save_areas_and_malformed_records(self):
        raw, size = FIXTURES['scope_single']
        data = bytes.fromhex(raw)
        for offset, value in [(0, 0x80), (0, 9), (2, 0x40), (3, 0xfe),
                              (5, 0), (7, 1), (8, 0xfe)]:
            bad = bytearray(data)
            bad[offset] = value
            with self.subTest(offset=offset, value=value):
                with self.assertRaises(unwind.DecodeError):
                    unwind.decode(bad, 0, size)
        for bad in [data[:-1], data+b'\x01', data+b'\0\0\0\0']:
            with self.assertRaises(unwind.DecodeError):
                unwind.decode(bad, 0, size)

    @staticmethod
    def image_bytes(flags=5):
        data = bytearray(0x100)
        data[:6] = b'\x7fELF\x01\x01'
        struct.pack_into('<H', data, 18, 8)
        struct.pack_into('<I', data, 28, 52)
        struct.pack_into('<HH', data, 42, 32, 1)
        struct.pack_into('<8I', data, 52, 1, 0x80, 0x100000, 0x100000, 0x80, 0x80, flags, 16)
        return data

    def test_elf_file_backing_and_executable_bounds(self):
        data = self.image_bytes()
        data[0x90] = 0x45
        image = unwind.Image(data)
        self.assertEqual(image.read(0x100010, 1), b'E')
        self.assertTrue(image.executable(0x100010))
        self.assertFalse(unwind.Image(self.image_bytes(flags=4)).executable(0x100010))
        for address, size in [(0xfffff, 4), (0x10007f, 4), (0x100000, -1)]:
            with self.assertRaises(unwind.DecodeError):
                image.read(address, size)
        for bad in [b'', data[:60], b'INVALID'+data[7:]]:
            with self.assertRaises(unwind.DecodeError):
                unwind.Image(bad)

    @unittest.skipUnless((ROOT/'orig/SLUS-20836/SLUS_208.36').is_file(), 'private retail input required')
    def test_complete_retail_inventory_and_independent_corruptions(self):
        data = (ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes()
        result = unwind.inventory(unwind.Image(data))
        self.assertEqual((len(result['ranges']), len(result['actions']), result['frame'],
                          result['return_save_offset'], result['range_end'],
                          result['referenced_end'], result['padding']), (36, 34, 1200, 144, 175, 413, 3))
        # Change an anchor, a cleanup target, and an endpoint call instruction independently.
        image = unwind.Image(data)
        action = result['actions'][0]
        _offset, pointer_end = unwind.number(image.read(0x544fd4, 416), action['offset']+1)
        addresses = [0x553b80, 0x544fd4+pointer_end, result['ranges'][0]['start']-8]
        for address in addresses:
            bad = bytearray(data)
            for lo, hi, fileoff, _flags in image.segments:
                if lo <= address and address+4 <= hi:
                    bad[fileoff+address-lo:fileoff+address-lo+4] = b'\0'*4
                    break
            with self.subTest(address=hex(address)):
                with self.assertRaises(unwind.DecodeError):
                    unwind.inventory(unwind.Image(bad))


if __name__ == '__main__':
    unittest.main()
