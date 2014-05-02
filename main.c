/*
 * bmp2raw.c
 * 
 * Copyright 2014 doctorxyz
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#define PROGRAM_NAME "bmp2raw"
#define PROGRAM_EXTNAME "BMP to RAW converter"
#define PROGRAM_VER "0.0.1"

#define EXIT_OK 0
#define EXIT_FAILURE 1

#include <stdio.h>

int convert_file(char *source_filename, char  *target_filename)
{
	int  r, g, b, i;

	printf("Opening %s...\n", source_filename);
	FILE* ptr_src = fopen(source_filename, "rb");
	if(ptr_src == NULL)
		return  EXIT_FAILURE;

	printf("Opening %s...\n", target_filename);
	FILE* ptr_tgt = fopen(target_filename, "wb");
	if(ptr_tgt == NULL)
	{
		fclose(ptr_src);
		return  EXIT_FAILURE;
	}

	printf("Skipping BMP header (first 54 bytes)...\n");
	for(i = 1; i<=54; i++)
	{
		fgetc(ptr_src);
	}
	
	printf("Reading each three (24-bit) RGB bytes, reversing them and writing in BGR style... ");
	while(1)
	{
		r = fgetc(ptr_src);
		g = fgetc(ptr_src);
		b = fgetc(ptr_src);

		if(!feof(ptr_src)) {
			fputc(b, ptr_tgt);
			fputc(g, ptr_tgt);
			fputc(r, ptr_tgt);
		} else
			break;
	}

	fclose(ptr_tgt);
	fclose(ptr_src);
	printf("Done!\n");
	return  EXIT_OK;
}

int main(int argc, char **argv, char **env) {
#ifdef _WIN32
	printf("\n%s - %s version %s (Win32 Build)\n\n", PROGRAM_NAME, PROGRAM_EXTNAME, PROGRAM_VER);
#else
	printf("\n%s - %s version %s\n\n", PROGRAM_NAME, PROGRAM_EXTNAME, PROGRAM_VER);
#endif
	printf("Convert 24-bit coloured RGB BMP (Windows Bitmap) to BGR RAW files\n");
	
	// args check
	if (argc == 3) {
		printf("Source filename: %s\n", argv[1]);
		printf("Target filename: %s\n", argv[2]);
		if(convert_file(argv[1], argv[2]) == EXIT_OK) {
			printf("Conversion Successful!\n");
			return EXIT_OK;
		} else {
			fprintf(stderr, "Error during conversion!");
			return EXIT_FAILURE;
		}
	} else {
		printf("Usage: bmp2raw SOURCE TARGET\n");
		printf("Example: bmp2raw source.bmp target.raw\n");
		return EXIT_FAILURE;
	}
}
