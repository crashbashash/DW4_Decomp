"""Checksum and memory-card entry helpers for retail save-format probes.

Two mirrored 0xA000-byte blocks each store their u32 word sum at offset zero.
Standalone save-editing commands live outside the repository.
"""
import struct
from pathlib import Path

BLOCK = 0xA000
NBLOCKS = 2
SAVE_NAME = "BASLUS-20836savedata"


def read_save_payload(path):
    """Read an extracted USA save or its memory-card entry without modifying it."""
    path = Path(path)
    if path.stat().st_size == BLOCK * NBLOCKS:
        return path.read_bytes()
    from ps2mc_extract import SB_MAGIC, open_card
    with path.open("rb") as stream:
        if not stream.read(len(SB_MAGIC)).startswith(SB_MAGIC):
            raise ValueError("expected an 81920-byte DW4 save or a PS2 memory-card image")
    try:
        card, _ = open_card(path)
    except ModuleNotFoundError as exc:
        if exc.name != "ps2mc":
            raise
        raise ValueError("memory-card images require the optional ps2mc package; "
                         "an extracted 81920-byte save needs no extra package") from exc
    try:
        entry = find_entry(card, SAVE_NAME, SAVE_NAME)
        if entry is None:
            raise ValueError("memory card has no USA DW4 savedata entry")
        payload = card.read_data_cluster(entry)
        if len(payload) != BLOCK * NBLOCKS:
            raise ValueError("DW4 savedata entry must contain 81920 bytes")
        return bytes(payload)
    finally:
        card.file.close()


def block_sum(d, base):
    s = 0
    for i in range(base + 4, base + BLOCK, 4):
        s = (s + struct.unpack_from("<I", d, i)[0]) & 0xFFFFFFFF
    return s


def fix_checksums(d):
    for b in range(NBLOCKS):
        struct.pack_into("<I", d, b * BLOCK, block_sum(d, b * BLOCK))


def find_entry(mc, dirname, filename):
    for e in mc.find_sub_entries(mc.get_root_entry()):
        if e.name == dirname and e.is_dir():
            for f in mc.find_sub_entries(e):
                if f.is_file() and f.name == filename:
                    return f
    return None
