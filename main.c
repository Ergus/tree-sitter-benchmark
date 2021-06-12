/*
 * Copyright (C) 2021  Jimmy Aguilar Mena
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <tree_sitter/api.h>

// Declare the `tree_sitter_c` function, which is
TSLanguage *tree_sitter_c();

int main() {

	// Create a parser.
	TSParser *parser = ts_parser_new();

	TSLanguage *clang = tree_sitter_c();

	// Set the parser's language (JSON in this case).
	ts_parser_set_language(parser, tree_sitter_c());

	// Build a syntax tree based on source code stored in a string.
	FILE *fp = fopen("xdisp.c", "r");
	if (fp == NULL) {
		printf("No abrio el fichero\n");
		return 1;
	}


	fseek(fp, 0, SEEK_END);
	const size_t nchars = ftell(fp) + 1;

	printf("File has %zu chars\n", nchars);

	char *source_code = malloc(nchars * sizeof(char));
	char *source_code2 = malloc(nchars * sizeof(char));

	fseek(fp, 0, SEEK_SET);

	size_t count = 0;
	for (char c = getc(fp); c != EOF; c = getc(fp)) {
		source_code[count++] = c;
	}
	source_code[count] = '\0';

	clock_t start, end;

	start = clock();
	memcpy(source_code2, source_code,  nchars * sizeof(char));
	end = clock();
	float tcopy = (float)(end - start) / CLOCKS_PER_SEC;

	start = clock();
	TSTree *tree = ts_parser_parse_string(
		parser,
		NULL,
		source_code,
		nchars
	);
	end = clock();
	float tparse = (float)(end - start) / CLOCKS_PER_SEC;
	printf("tparse %f tcopy %f secs\n", tparse, tcopy);

	start = clock();
	TSTree *tree_copy = ts_tree_copy(tree);
	end = clock();
	float ttree = (float)(end - start) / CLOCKS_PER_SEC;

	start = clock();
	TSTree *tree2 = ts_parser_parse_string(
		parser,
		tree_copy,
		source_code2,
		nchars
	);
	end = clock();
	float treparse = (float)(end - start) / CLOCKS_PER_SEC;

	printf("ttree %f treparse %f secs\n", ttree, treparse);

	// Get the root node of the syntax tree.
	TSNode root_node = ts_tree_root_node(tree);

	// Free all of the heap-allocated memory.
	//free(string);
	free(source_code);
	fclose(fp);
	ts_tree_delete(tree);
	ts_parser_delete(parser);
	return 0;
}
