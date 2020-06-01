#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>

#include "keyvalues.h"

#include <x86intrin.h> 
#include <unistd.h> 

#ifndef VERSION
#define VERSION ""
#endif

#ifndef COMPILER
#define COMPILER "gcc"
#endif

#ifndef FLAGS
#define FLAGS ""
#endif

int main(int argc, char** argv)
{

	printf("============================================================\n");
	printf("Built with %s %s\n", COMPILER, VERSION);
	printf("============================================================\n");
	printf("Flags: %s\n", FLAGS);
	printf("============================================================\n");

	float f = 0;
	for(int i = 0; i < 1e8 * argc; i++) f += (float)i;
	printf("%f\n", f);

	timeval first, second;

	if(argc < 2)
	{
		printf("Please specify a file\n");
		return 1;
	}

	printf("File: %s\n", argv[1]);
	printf("============================================================\n");
	
	KeyValues* pKV = new KeyValues();

	/* Time budget for reading file */
	gettimeofday(&first, NULL);
	unsigned long long t1 = __rdtsc();

	FILE* fs = fopen(argv[1], "r");

	if(!fs)
	{
		printf("Failed to open %s\n", argv[1]);
		return 1;
	}

	/* Get file size */
	fseek(fs, 0, SEEK_END);
	long int size = ftell(fs);

	/* Read the entire file */
	char* buffer = static_cast<char*>(malloc(size + 1));
	fseek(fs, 0, SEEK_SET);
	fread(buffer, size, 1, fs);
	fclose(fs);
	buffer[size] = 0;
	
	/* SECOND TIME READ */
	unsigned long long t2 = __rdtsc();
	gettimeofday(&second, NULL);

	printf("Cycles to read file: %llu\n", t2-t1);
	printf("\tTime to read file: %fs   %fms   %fus\n", (float)(second.tv_sec-first.tv_sec+((second.tv_usec-first.tv_usec)/1000000.0f)),
			(float)(second.tv_sec-first.tv_sec)*1000.0f + ((second.tv_usec-first.tv_usec)/1000.0f),
			(float)(second.tv_sec-first.tv_sec)*1000000.0f + (second.tv_usec-first.tv_usec));


	gettimeofday(&first, NULL);
	t1 = __rdtsc();
	
	pKV->ParseString(buffer, false, size);

	t2 = __rdtsc();
	gettimeofday(&second, NULL);
	printf("Cycles to parse file: %llu\n", t2-t1);
	printf("\tTime to parse file: %fs   %fms   %fus\n", (float)(second.tv_sec-first.tv_sec+((second.tv_usec-first.tv_usec)/1000000.0f)),
			(float)(second.tv_sec-first.tv_sec)*1000.0f + ((second.tv_usec-first.tv_usec)/1000.0f),
			(float)(second.tv_sec-first.tv_sec)*1000000.0f + (second.tv_usec-first.tv_usec));


	printf("VMF Verification\n");

	pKV->DumpToStream(stdout);

	KeyValues* kv = pKV->GetChild("versioninfo");
	if(kv)
	{
		printf("Editor Version: %u\n", kv->GetInt("editorversion"));
	}

	printf("String Allocator Test\n");

	delete pKV;
	free(buffer);
}
