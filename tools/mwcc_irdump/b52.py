"""b52.py: what the IR dump tools know about the MWCC PS2 3.0b52-030722 executable.

Every address here is a virtual address in the compiler's `.text` (image base 0x400000, `.text` at 0x401000, file
offset 0x400). The tools refuse any other build.
"""
import hashlib
import os

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
COMPILER = os.path.join(ROOT, "local", "mwcps2", "3.0b52-030722", "mwccps2.exe")
SHA256 = "4a9d1289d2b444e240d79dd7f579eb2c0179f15d191fe51c0ac7d387e6de646c"
GAME_FLAGS = "-O4,p -sdatathreshold 2 -inline level=8,bottomup -Iinclude"

# The optimizer's setup clears two switches with `movb $0,<switch>`; the dump copy stores 1 instead.
#   0x4d52a2  movb $0,0x5b7fa7   dumps enabled (opens <source>.log)
#   0x4d53d5  movb $0,0x5a5d4e   dump after every phase
DUMP_SWITCHES = [(0x4D52A2, bytes.fromhex("c605a77f5b0000")), (0x4D53D5, bytes.fromhex("c6054e5d5a0000"))]

DUMP_AFTER_PHASE = 0x51F5B0    # IRO_DumpAfterPhase(const char *phase, int flag), called after every phase
NODE_LIST = 0x5B64E4           # head of the IR node list
COMMON_SUBS = 0x532920         # IRO_CommonSubs
NODE_EQUAL_FLAGS = 0x4F9D1B    # in the node comparison: node kinds and type bytes are equal, nodeflags compared next
NODE_EQUAL_TYPES = 0x4F9D45    # in the node comparison: just after the IRO_TypesEqual(rtype) call, result in al
# IRO_CommonSubs (0x532920) groups the expressions (0x531e70), computes which groups are available on entry to each
# flow node (0x531f50), then decides, walking each flow node in order (0x5322e0, 0x532670), which occurrences reuse
# a value computed before and which compute it, gives the computations whose value is reused a temporary, one per
# connected set (0x532770), and finally replaces the reuses by the temporary (0x532850).
# Grouping walks the expressions in flow order and compares each, through GROUP_MATCH(expr, group list) -> al, with
# the LATEST member of every group in creation order: the first match adds it to that group through
# GROUP_ADD(expr, index); no match opens a new group (index = the group count).
GROUP_MATCH = 0x531DB0
GROUP_ADD = 0x531E10
SHARE_KILLS = 0x532505   # 0x5322e0 after an IR node's kills are known: ebp the node, [esp+0x10] its flow node, the
KILLED = 0x5B4DEC        # groups it kills the bit vector at *KILLED (bit vector: word count, then the words)
SHARE_DONE = 0x532949    # IRO_CommonSubs before the replacement phase: the decisions below are all made
FLOW_HEAD = 0x5B63D4     # first flow node
FLOW_INDEX, FLOW_FIRST, FLOW_LAST, FLOW_NEXT = 0, 0x10, 0x14, 0x30   # u16 index; first and last IR node; next
NODE_EXPR, NODE_ROLE = 0x18, 0x20  # an IR node's expression record; its role byte: 0 reuses a value computed earlier in
#                                    its flow node, 1 computes it again after a kill there, 2 first in its flow node
# expression record: its IR node, the temporary of a computation whose value is reused, its group index, the list of
# computations a reuse takes its value from (cells (expr, next)), and whether the group was available on entry
EXPR_NODE, EXPR_TEMP, EXPR_GROUP, EXPR_SOURCES, EXPR_ENTRY = 6, 0x0A, 0x16, 0x1A, 0x1E

# IR node fields (offsets into a node)
NODE_KIND, NODE_TYPE, NODE_FLAGS, NODE_INDEX, NODE_RTYPE, NODE_NEXT = 0, 1, 6, 8, 0x10, 0x38
# nodeflags bit 0x0001 is `const` on what a pointer-valued node points at; the comparison ignores 0x0200.
FLAG_IGNORED = 0x200
NODE_TYPES = {4: "EINDIRECT", 15: "EADD", 0x25: "ETYPCON", 58: "operand"}


def file_offset(va):
    return va - 0x401000 + 0x400


def sha256(path):
    with open(path, "rb") as fh:
        return hashlib.sha256(fh.read()).hexdigest()


def dump_copy(data):
    """The bytes of the dump copy, from the bytes of the retail compiler."""
    out = bytearray(data)
    for va, old in DUMP_SWITCHES:
        off = file_offset(va)
        if bytes(out[off:off + len(old)]) != old:
            raise SystemExit("unexpected bytes at %#x: not 3.0b52-030722" % va)
        out[off + len(old) - 1] = 1
    return bytes(out)


def known_builds():
    """{sha256: 'retail' | 'dump'} of the two executables the tools accept."""
    data = open(COMPILER, "rb").read()
    return {SHA256: "retail", hashlib.sha256(dump_copy(data)).hexdigest(): "dump"}


def inside_repository(path):
    """True when `path` lies in the repository or in the toolchain folder it links to."""
    real = os.path.realpath(path)
    for top in (ROOT, os.path.join(ROOT, "local")):
        top = os.path.realpath(top)
        if real == top or real.startswith(top + os.sep):
            return True
    return False
