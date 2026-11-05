#!/usr/bin/env python3
"""make_iso.py — put the built executable into a copy of your disc image (`make iso`).

The build reproduces the executable's load image, build/<GAMEID>/main.bin. This copies a disc image
to build/<GAMEID>/, writes that image over the load segment of the boot executable in the copy and
reads the file back to check it. The executable keeps its size and position, so nothing else on the
disc moves. The disc you supply is only read, and the copy is game data: it stays in build/.

    python3 tools/make_iso.py [--version GAMEID] [--disc PATH] [--out PATH]

The disc defaults to the *.iso in orig/<GAMEID>/. This is a publishing step, not part of the build.
"""
import argparse
import hashlib
import os
import shutil
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "port", "tools"))
import project
from extract_iso import Iso, SECTOR


def find_disc(version):
    folder = os.path.join(ROOT, "orig", version)
    discs = sorted(name for name in os.listdir(folder) if name.lower().endswith(".iso"))
    if not discs:
        raise SystemExit(f"no disc image in orig/{version}/: put your .iso there or pass --disc PATH")
    return os.path.join(folder, discs[0])


def boot_entry(path, boot_file):
    iso = Iso(path)
    try:
        entry = dict(iso.walk()).get(boot_file)
    finally:
        iso.f.close()
    if entry is None:
        raise SystemExit(f"{path}: disc has no {boot_file}")
    return entry


def read_file(path, entry):
    with open(path, "rb") as handle:
        handle.seek(entry["lba"] * SECTOR)
        return handle.read(entry["size"])


def build_iso(disc, out, image, boot_file, file_offset):
    """Copy `disc` to `out` with `image` over the load segment of `boot_file` -> the new executable."""
    entry = boot_entry(disc, boot_file)
    if file_offset + len(image) > entry["size"]:
        raise SystemExit(f"{boot_file}: {len(image)} bytes at 0x{file_offset:x} do not fit in {entry['size']} bytes")
    if os.path.abspath(disc) == os.path.abspath(out):
        raise SystemExit("the output must not be the disc itself")
    os.makedirs(os.path.dirname(os.path.abspath(out)), exist_ok=True)
    shutil.copyfile(disc, out)
    with open(out, "r+b") as handle:
        handle.seek(entry["lba"] * SECTOR + file_offset)
        handle.write(image)
    written = read_file(out, entry)
    if written[file_offset:file_offset + len(image)] != image:
        raise SystemExit(f"{out}: the executable does not read back as written")
    return written


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--version", default="SLUS-20836")
    ap.add_argument("--disc", help="the disc image to copy (default: the *.iso in orig/<GAMEID>/)")
    ap.add_argument("--out", help="the new disc image (default: build/<GAMEID>/<GAMEID>.iso)")
    a = ap.parse_args(argv)
    cfg = project.read_config(a.version)
    image_path = os.path.join(ROOT, "build", a.version, "main.bin")
    if not os.path.exists(image_path):
        raise SystemExit(f"build/{a.version}/main.bin is missing: run `make iso` or `ninja` first")
    with open(image_path, "rb") as handle:
        image = handle.read()
    disc = a.disc or find_disc(a.version)
    out = a.out or os.path.join(ROOT, "build", a.version, a.version + ".iso")
    written = build_iso(disc, out, image, cfg["boot_file"], int(cfg["image"]["file_offset"], 0))
    same = hashlib.sha1(written).hexdigest() == cfg["hash"]
    print(f"{os.path.relpath(out, ROOT)}: {cfg['boot_file']} written, "
          f"{'identical to retail' if same else 'differs from retail'}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
