Readme
======

Very simple benchmark testing tree-sitter parsing a very long C file.

This measures 3 basic times.

1. Parse from scratch
2. Tree copy
3. Reparse reusing an old tree.

An extra time of memcpy the whole file text is also calculated to use
it as a scale comparison.
