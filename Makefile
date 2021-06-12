# Copyright (C) 2021  Jimmy Aguilar Mena

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


all: benchmark-c-parser

benchmark-c-parser: main.c
	gcc -I tree-sitter/lib/include $< tree-sitter-c/src/parser.c -ltree-sitter -o $@

.PHONY: test clean

clean:
	rm -rf benchmark-c-parser

test: benchmark-c-parser
	./$<
