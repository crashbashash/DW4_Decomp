"""Tests for tools/changedunits.py: the files changed since a revision and the units they reach."""
import os
import subprocess
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import changedunits  # noqa: E402


class Tree(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(prefix="dw4-changed-")
        self.addCleanup(temp.cleanup)
        self.root = temp.name

    def write(self, path, text=""):
        full = os.path.join(self.root, path)
        os.makedirs(os.path.dirname(full), exist_ok=True)
        with open(full, "w") as fh:
            fh.write(text)

    def affected(self, sources, *changed):
        return changedunits.affected(set(sources), set(changed), self.root)


class Affected(Tree):
    def setUp(self):
        super().setUp()
        self.write("include/dw4/Base.h", "typedef int base;\n")
        self.write("include/dw4/Mid.h", '#include "dw4/Base.h"\n')
        self.write("src/game/a.c", '#include "dw4/Mid.h"\nint a(void) { return 0; }\n')
        self.write("src/game/b.c", "#include <stdio.h>\nint b(void) { return 0; }\n")
        self.sources = {"src/game/a.c", "src/game/b.c"}

    def test_a_changed_source_is_its_own_unit(self):
        self.assertEqual(self.affected(self.sources, "src/game/b.c"), {"src/game/b.c"})

    def test_a_header_reaches_the_units_that_include_it_through_others(self):
        self.assertEqual(self.affected(self.sources, "include/dw4/Base.h"), {"src/game/a.c"})

    def test_an_unrelated_change_reaches_nothing(self):
        self.assertEqual(self.affected(self.sources, "include/dw4/Other.h", "docs/x.md"), set())

    def test_a_name_is_tried_beside_the_includer_and_in_every_include_folder(self):
        self.write("src/game/local.h")
        self.write("src/lib/frag.inc")
        self.write("include/sys.h")
        self.write("src/game/c.c", '#include "local.h"\n#include "src/lib/frag.inc"\n#include <sys.h>\n')
        sources = self.sources | {"src/game/c.c"}
        for header in ("src/game/local.h", "src/lib/frag.inc", "include/sys.h"):
            self.assertEqual(self.affected(sources, header), {"src/game/c.c"}, header)

    def test_a_deleted_header_still_reaches_the_units_that_name_it(self):
        os.remove(os.path.join(self.root, "include/dw4/Base.h"))
        self.assertEqual(self.affected(self.sources, "include/dw4/Base.h"), {"src/game/a.c"})

    def test_an_include_cycle_ends(self):
        self.write("include/dw4/Base.h", '#include "dw4/Mid.h"\n')
        self.assertEqual(self.affected(self.sources, "include/dw4/Mid.h"), {"src/game/a.c"})


class NotFollowed(unittest.TestCase):
    def test_tables_checking_tools_and_kernel_patches_are_named(self):
        patch = os.path.relpath(changedunits.kpatch.PATCH_DIR, changedunits.ROOT) + "/x.c"
        changed = {"config/SLUS-20836/units.tsv", "tools/verify.py", "tools/eegcc_compile.py", patch, "src/game/a.c",
                   "docs/x.md", "tools/README.md", "tools/test_changedunits.py", "tools/m2c_batch.py"}
        self.assertEqual(changedunits.not_followed(changed),
                         sorted(["config/SLUS-20836/units.tsv", "tools/verify.py", "tools/eegcc_compile.py", patch]))


class ChangedFiles(Tree):
    def git(self, *args):
        subprocess.run(("git",) + args, cwd=self.root, check=True, capture_output=True)

    def test_committed_staged_unstaged_untracked_deleted_and_renamed(self):
        self.git("init", "-q")
        self.git("config", "user.email", "t@example.invalid")
        self.git("config", "user.name", "t")
        for name in ("kept.c", "committed.c", "staged.c", "unstaged.c", "deleted.c", "moved.c"):
            self.write("src/" + name, name + "\n")
        self.write(".gitignore", "*.o\n")
        self.git("add", "-A")
        self.git("commit", "-qm", "base")
        self.git("tag", "base")
        self.write("src/committed.c", "changed\n")
        self.git("commit", "-qam", "change")
        self.write("src/staged.c", "changed\n")
        self.git("add", "src/staged.c")
        self.write("src/unstaged.c", "changed\n")
        self.git("rm", "-q", "src/deleted.c")
        self.git("mv", "src/moved.c", "src/renamed.c")
        self.write("src/new.c", "new\n")
        self.write("src/ignored.o", "object\n")
        self.assertEqual(changedunits.changed_files("base", self.root),
                         {"src/committed.c", "src/staged.c", "src/unstaged.c", "src/deleted.c", "src/moved.c",
                          "src/renamed.c", "src/new.c"})

    def test_an_unknown_revision_is_an_error(self):
        self.git("init", "-q")
        with self.assertRaisesRegex(ValueError, "git diff"):
            changedunits.changed_files("no-such-revision", self.root)


if __name__ == "__main__":
    unittest.main()
