"""The verification-oracle holes an audit found, each closed by a failing counterexample.

Every counterexample compiles to the retail instruction words of
`igObjectSystem_FindMetaByNameDefault` (0x2fe460, 16 bytes) and used to print
MATCH. The tests that need the private compiler and retail image skip without
them; the resolver and relocation-type rules are checked without either.
"""
import os
from pathlib import Path
import shutil
import tempfile
import unittest
from unittest.mock import patch

import verify

ROOT = Path(verify.ROOT)
VA, NAME = 0x2fe460, "igObjectSystem_FindMetaByNameDefault"
CALLEE = "extern int igObjectSystem_FindMetaByName(void *objectSystem, const char *name);\n"
BODY = ("int igObjectSystem_FindMetaByNameDefault(const char *name)"
        "{return igObjectSystem_FindMetaByName(g_objectSystem_00586dc8[0],name);}\n")

# counterexample 1b: unreferenced data, strings and bss smuggled next to a matched body
SMUGGLED_DATA = CALLEE + """extern void *g_objectSystem_00586dc8[4];
int g_smuggled_global = 7;
char g_smuggled_small = 1;
int g_smuggled_bss[64];
const char *g_smuggled_string = "smuggled string literal";
int (*g_smuggled_fnptr)(void *, const char *) = igObjectSystem_FindMetaByName;
""" + BODY

# counterexample 2: the candidate DEFINES the global it should only reference
DEFINES_DATUM = CALLEE + """void *g_objectSystem_00586dc8[4] = { (void *)1, (void *)2, (void *)3, (void *)4 };
""" + BODY

# counterexample 3b: calls the function by an address-bearing name of its own making
WRONG_NAME = """extern int whatever_002d3070(void *objectSystem, const char *name);
extern void *g_objectSystem_00586dc8[4];
int igObjectSystem_FindMetaByNameDefault(const char *name){return whatever_002d3070(g_objectSystem_00586dc8[0],name);}
"""

# a FUN_ name for an address inside the callee, compensated by the compiler's addend
INSIDE_FUNCTION = CALLEE + """extern void *g_objectSystem_00586dc8[4];
extern char FUN_002d3074[];
int igObjectSystem_FindMetaByNameDefault(const char *name){return igObjectSystem_FindMetaByName(g_objectSystem_00586dc8[0],name) + (int)FUN_002d3074;}
"""

# a data name pointing into a function's code
DATA_INTO_CODE = CALLEE + """extern void *g_objectSystem_00586dc8[4];
extern char DAT_002d3074[];
int igObjectSystem_FindMetaByNameDefault(const char *name){return igObjectSystem_FindMetaByName(g_objectSystem_00586dc8[0],name) + (int)DAT_002d3074;}
"""


# a body that reads one compiler float literal, the retail pool's entry at 0x5548b8
LITERAL_VA, LITERAL_NAME = 0x20d290, "FUN_0020d290"
LITERAL_BODY = """extern long long DAT_0056c190[];
void FUN_0020d290(long long *arg0) {
    unsigned int t;
    float f;
    unsigned int u;
    t = *(volatile unsigned int *)0x10000800;
    f = %s * (float)t;
    u = (unsigned int)f;
    *arg0 = (DAT_0056c190[0] + u) * 100;
}
"""
LITERAL_HONEST = LITERAL_BODY % "1.08506942f"
LITERAL_WRONG_VALUE = LITERAL_BODY % "1.08506954f"
# a second body carries a literal retail never reaches from this function
LITERAL_EXTRA_BODY = LITERAL_HONEST + "float carried(float x) { return x * 3.25f; }\n"


def retail_available():
    return (all(Path(p).exists() for p in (verify.WIBO_DEFAULT, verify.MWCC_DEFAULT, verify.ELF_DEFAULT))
            and shutil.which("mipsel-linux-gnu-readelf"))


class SharedResolver(unittest.TestCase):
    """Item 3(b)/(c): one address-in-name rule, with the name's claim checked."""
    SYMBOLS = {"igObjectSystem_FindMetaByName": (0x2d3070, 0x3c),
               "thunk_FUN_001145c8": (0x100228, 8),
               "Memory_SelectAllocator_003e9370": (0x3e9370, 0x40),
               "Stale_002d3070": (0x2d3080, 0x10)}

    def setUp(self):
        self.table = tempfile.NamedTemporaryFile("w", suffix=".txt", delete=False)
        for name, (va, size) in self.SYMBOLS.items():
            self.table.write(f"{va:08x} {size:06x} {name}\n")
        self.table.close()
        self.addCleanup(os.remove, self.table.name)
        self.by_name = {name: value for name, value in self.SYMBOLS.items()}

    def resolve(self, name):
        return verify.sym_address(name, self.by_name, self.table.name)

    def test_six_to_eight_trailing_hex_digits_behind_a_boundary(self):
        self.assertEqual(verify.address_in_name("D_0056df30"), 0x56df30)
        self.assertEqual(verify.address_in_name("g_objectSystem_00586dc8"), 0x586dc8)
        self.assertIsNone(verify.address_in_name("vfunc_44"))          # two digits
        self.assertIsNone(verify.address_in_name("Register"))
        self.assertIsNone(verify.address_in_name("tbl_a0ff0"))        # five digits are no address

    def test_mapped_name_wins_and_its_claim_must_agree(self):
        self.assertEqual(self.resolve("Memory_SelectAllocator_003e9370"), 0x3e9370)
        with self.assertRaises(verify.SymbolError):
            self.resolve("Stale_002d3070")

    def test_thunk_names_their_target_by_convention(self):
        self.assertEqual(self.resolve("thunk_FUN_001145c8"), 0x100228)

    def test_function_style_name_must_be_a_function_start(self):
        self.assertEqual(self.resolve("FUN_002d3070"), 0x2d3070)
        with self.assertRaisesRegex(verify.SymbolError, "not a recorded function start"):
            self.resolve("FUN_002d3074")
        with self.assertRaisesRegex(verify.SymbolError, "not a recorded function start"):
            self.resolve("FUN_00586dc8")

    def test_data_style_name_may_not_point_into_code(self):
        self.assertEqual(self.resolve("g_objectSystem_00586dc8"), 0x586dc8)
        self.assertEqual(self.resolve("DAT_00586dc4"), 0x586dc4)
        for name in ("DAT_002d3070", "D_002d3074", "g_002d3080", "s_text_002d3084", "PTR_002d3070"):
            with self.assertRaisesRegex(verify.SymbolError, "inside the code"):
                self.resolve(name)

    def test_other_names_resolve_to_starts_or_data_never_inside_a_body(self):
        # cx3b: a wrong NAME with the right function-start address is not detectable by bytes.
        self.assertEqual(self.resolve("whatever_002d3070"), 0x2d3070)
        self.assertEqual(self.resolve("whatever_00586dc8"), 0x586dc8)
        with self.assertRaisesRegex(verify.SymbolError, "not a function start"):
            self.resolve("whatever_002d3074")

    def test_scratchpad_and_hardware_addresses_resolve(self):
        self.assertEqual(self.resolve("DAT_70000000"), 0x70000000)     # EE scratchpad
        self.assertEqual(self.resolve("DAT_10000000"), 0x10000000)     # hardware registers
        self.assertEqual(self.resolve("DAT_00004000"), 0x4000)         # kernel area
        self.assertIsNone(self.resolve("no_address_here"))

    def data_table(self, rows):
        """Write `rows` as the data-names.tsv of a fresh folder; returns its symbols.txt path."""
        folder = tempfile.mkdtemp()
        self.addCleanup(shutil.rmtree, folder)
        symbols = os.path.join(folder, "symbols.txt")
        with open(self.table.name) as source, open(symbols, "w") as out:
            out.write(source.read())
        with open(os.path.join(folder, "data-names.tsv"), "w") as out:
            out.writelines("0x%08x\t%s\t%s\n" % row for row in rows)
        return symbols

    def test_a_recovered_data_name_resolves_from_the_table(self):
        symbols = self.data_table([(0x586dc8, "g_objectSystem", "class-handle")])
        self.assertEqual(verify.sym_address("g_objectSystem", self.by_name, symbols), 0x586dc8)
        self.assertEqual(verify.sym_address("g_objectSystem+4", self.by_name, symbols), 0x586dc8)

    def test_a_bare_name_outside_the_table_stays_unresolved(self):
        symbols = self.data_table([(0x586dc8, "g_objectSystem", "class-handle")])
        self.assertIsNone(verify.sym_address("g_otherSystem", self.by_name, symbols))

    def test_a_table_name_inside_code_is_refused(self):
        symbols = self.data_table([(0x2d3074, "g_inCode", "class-handle")])
        with self.assertRaises(verify.SymbolError):
            verify.sym_address("g_inCode", self.by_name, symbols)

    def test_a_string_name_at_a_function_start_is_refused(self):
        symbols = self.data_table([(0x2d3070, "ISUSE", "string-literal")])
        with self.assertRaises(verify.SymbolError):
            verify.sym_address("ISUSE", self.by_name, symbols)

    def test_a_function_symbol_row_does_not_resolve(self):
        symbols = self.data_table([(0x586dc8, "OldFunctionName", "function-symbol")])
        self.assertIsNone(verify.sym_address("OldFunctionName", self.by_name, symbols))

    def test_a_table_with_two_addresses_for_a_name_is_refused(self):
        symbols = self.data_table([(0x586dc8, "g_twice", "class-handle"), (0x586dcc, "g_twice", "class-handle")])
        with self.assertRaises(ValueError):
            verify.data_symbols(symbols)

    def test_a_row_spelling_another_address_is_refused(self):
        symbols = self.data_table([(0x586dc8, "g_liar_00586dcc", "class-handle")])
        with self.assertRaises(ValueError):
            verify.data_symbols(symbols)

    def test_defining_a_bare_table_name_is_still_smuggling(self):
        name = next(iter(verify.data_symbols())) if verify.data_symbols() else None
        if name is None:
            self.skipTest("no recovered data names")
        found = verify.defined_outside({name: (1, 0, 4)}, [], [(0x100000, 0x100004)])
        self.assertEqual(found, [(name, verify.data_symbols()[name])])

    def test_linkgen_shares_the_resolver(self):
        import linkgen
        source = Path(linkgen.__file__).read_text()
        self.assertIn("verify.sym_address(", source)
        self.assertNotIn('re.search(r"([0-9a-fA-F]{6,8})$"', source)


class Categories(unittest.TestCase):
    """check.py's one-of categories and their precedence (verify.category)."""

    def test_precedence(self):
        gap = verify.SymbolError("gap", "gap")
        name = verify.SymbolError("name", "name")
        extent = verify.SymbolError("extent", "extent")
        self.assertEqual(verify.category(True, [], "-"), "match")
        self.assertEqual(verify.category(True, [], "ok"), "match")
        self.assertEqual(verify.category(True, [], "missing"), "code-only")
        self.assertEqual(verify.category(True, [], "extra"), "code-only")
        self.assertEqual(verify.category(True, [name], "ok"), "name-defect")
        self.assertEqual(verify.category(True, [name], "missing"), "name-defect")
        self.assertEqual(verify.category(True, [gap, name], "-"), "inventory-gap")
        self.assertEqual(verify.category(True, [extent], "-"), "inventory-gap")
        self.assertEqual(verify.category(False, [name], "differ"), "mismatch")

    def test_refusal_kinds(self):
        with self.assertRaises(verify.SymbolError) as caught:
            verify.sym_address("DAT_002d3070", {}, "config/SLUS-20836/symbols.txt")
        self.assertEqual(caught.exception.kind, "name")
        with self.assertRaises(verify.SymbolError) as caught:
            verify.sym_address("FUN_002d3074", {}, "config/SLUS-20836/symbols.txt")
        self.assertEqual(caught.exception.kind, "extent")


class RelocationTypes(unittest.TestCase):
    """Item 5: an unknown relocation type is an error naming the type, never dropped."""

    def test_unknown_type_raises_with_its_name(self):
        output = """Relocation section '.rel.text' at offset 0x200 contains 2 entries:
 Offset Info Type Sym.Value Symbol's Name
00000000 00000404 R_MIPS_26 00000000 callee
00000008 00000403 R_MIPS_REL32 00000000 DAT_0058f000
"""
        with patch.object(verify.subprocess, "run") as run:
            run.return_value.stdout = output
            with self.assertRaisesRegex(ValueError, r"unsupported relocation type R_MIPS_REL32 against 'DAT_0058f000' at \+0x8"):
                verify.object_relocs("owner.o")

    def test_known_types_still_parse(self):
        output = """Relocation section '.rel.text' at offset 0x200 contains 1 entry:
 Offset Info Type Sym.Value Symbol's Name
00000000 00000404 R_MIPS_26 00000000 callee
"""
        with patch.object(verify.subprocess, "run") as run:
            run.return_value.stdout = output
            self.assertEqual(verify.object_relocs("owner.o"), [(".text", 0, verify.R_26, "callee", 0)])


class LiteralPool(unittest.TestCase):
    """A compiler literal must be the retail pool entry its instruction names."""

    def setUp(self):
        self.image = bytearray(verify.LITERAL_POOL[1] - verify.VADDR_BASE + verify.FILE_BASE + 64)
        self.at = verify.LITERAL_POOL[0] + 0x40
        offset = self.at - verify.VADDR_BASE + verify.FILE_BASE
        self.image[offset:offset + 8] = bytes(range(1, 9))

    def test_the_entry_at_its_address_is_accepted(self):
        self.assertIsNone(verify.literal_error(self.at, bytes(range(1, 5)), self.image))
        self.assertIsNone(verify.literal_error(self.at, bytes(range(1, 9)), self.image))

    def test_another_value_is_refused(self):
        self.assertIn("is not the retail pool entry", verify.literal_error(self.at, b"\0\0\0\1", self.image))

    def test_an_address_outside_the_pool_is_refused(self):
        for address in (verify.LITERAL_POOL[0] - 4, verify.LITERAL_POOL[1]):
            self.assertIn("outside the retail pool", verify.literal_error(address, bytes(4), self.image))

    def test_a_misaligned_entry_is_refused(self):
        self.assertIn("not aligned", verify.literal_error(self.at + 4, bytes(8), self.image))


class DefinedSymbols(unittest.TestCase):
    """Item 3(a): defining a symbol that names a retail address outside the body."""

    def test_definitions_outside_the_body_are_listed(self):
        headers = [("", (0,) * 10), (".text", (0,) * 10), (".data", (0,) * 10)]
        syms = {"igObjectSystem_FindMetaByNameDefault": (1, 0, 16),
                "g_objectSystem_00586dc8": (2, 0, 16),
                "@21": (2, 16, 4),
                ".text": (1, 0, 0),
                "igObjectSystem_FindMetaByName": ("UND", 0, 0)}
        self.assertEqual(verify.defined_outside(syms, headers, [(VA, VA + 16)]),
                         [("g_objectSystem_00586dc8", 0x586dc8)])
        self.assertEqual(verify.defined_outside({"FUN_002fe460": (1, 0, 16)}, headers, [(VA, VA + 16)]), [])
        # a thunk body is named after its target; it is the unit's own definition
        thunk = {"thunk_FUN_001145c8": (1, 0, 8)}
        self.assertEqual(verify.defined_outside(thunk, headers, [(0x100228, 0x100230)], exempt={"thunk_FUN_001145c8"}), [])
        self.assertEqual(verify.defined_outside(thunk, headers, [(0x100228, 0x100230)]), [("thunk_FUN_001145c8", 0x1145c8)])


@unittest.skipUnless(retail_available(), "private retail compiler/ELF or GNU binutils unavailable")
class Counterexamples(unittest.TestCase):
    """The audit's sources, verified against retail through `verify_one`."""

    def verify(self, source):
        with tempfile.TemporaryDirectory(prefix="dw4-oracle-") as td:
            path = Path(td) / "cand.c"
            path.write_text(source)
            # the fixture is verified alone: the live table folds this address into a library unit
            ungrouped = Path(td) / "unit-objects.json"
            ungrouped.write_text("{}")
            return verify.verify_one(VA, str(path), symbols=str(ROOT / "config/SLUS-20836/symbols.txt"),
                                     unit_objects=str(ungrouped))

    def verify_literal(self, source):
        with tempfile.TemporaryDirectory(prefix="dw4-oracle-") as td:
            path = Path(td) / "cand.c"
            path.write_text(source)
            return verify.verify_one(LITERAL_VA, str(path), symbols=str(ROOT / "config/SLUS-20836/symbols.txt"),
                                     flags="-O4,s -sdatathreshold 2 -Iinclude -Cpp_exceptions off",
                                     mwcc=str(ROOT / "local/mwcps2/3.0b52-030722/mwccps2.exe"),
                                     units="/dev/null", unit_flags="/dev/null", unit_compilers="/dev/null",
                                     unit_objects=None)

    def test_honest_literal_matches(self):
        ok, report = self.verify_literal(LITERAL_HONEST)
        self.assertTrue(ok, report)

    def test_literal_with_another_value_fails(self):
        ok, report = self.verify_literal(LITERAL_WRONG_VALUE)
        self.assertFalse(ok, report)
        self.assertIn("is not the retail pool entry at 0x5548b8", report)

    def test_literal_of_another_body_fails(self):
        ok, report = self.verify_literal(LITERAL_EXTRA_BODY)
        self.assertFalse(ok, report)

    def test_honest_source_still_matches(self):
        ok, report = self.verify(CALLEE + "extern void *g_objectSystem_00586dc8[4];\n" + BODY)
        self.assertTrue(ok, report)

    def test_smuggled_data_fails_naming_every_section(self):
        ok, report = self.verify(SMUGGLED_DATA)
        self.assertFalse(ok, report)
        self.assertIn("unowned allocated section .data", report)
        self.assertIn("unowned allocated section .bss", report)
        self.assertIn("unowned allocated section .sdata", report)

    def test_defining_the_referenced_datum_fails(self):
        ok, report = self.verify(DEFINES_DATUM)
        self.assertFalse(ok, report)
        self.assertIn("object defines g_objectSystem_00586dc8, which names retail address 0x586dc8 outside the function", report)

    def test_function_name_pointing_inside_a_body_fails(self):
        ok, report = self.verify(INSIDE_FUNCTION)
        self.assertFalse(ok, report)
        self.assertIn("FUN_002d3074 names 0x2d3074, which is not a recorded function start", report)

    def test_data_name_pointing_into_code_fails(self):
        ok, report = self.verify(DATA_INTO_CODE)
        self.assertFalse(ok, report)
        self.assertIn("data name DAT_002d3074 points at 0x2d3074 inside the code of", report)

    def test_wrong_function_name_with_the_right_address_is_a_documented_limit(self):
        # cx3b: bytes cannot tell `whatever_002d3070` from the map's name for 0x2d3070.
        ok, report = self.verify(WRONG_NAME)
        self.assertTrue(ok, report)
        doc = (ROOT / "docs/engine/compiler-object-verification.md").read_text()
        self.assertIn("whatever_002d3070", doc)


if __name__ == "__main__":
    unittest.main()
