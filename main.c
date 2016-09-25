#include "generators.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SEQ_SIZE 1000000

int main() {
	BYTE seq[SEQ_SIZE]; 
	printf(BOLDWHITE"Embeded Generator:\n"RESET);
	memset(seq, 0, SEQ_SIZE);
	ByteGenGenerateSequence(EmbededGenerator, NULL, seq, SEQ_SIZE);
	UniformnessTest(seq, SEQ_SIZE);
	IndependanceTest(seq, SEQ_SIZE);
	HomogeneousnessTest(seq, SEQ_SIZE);

	printf(BOLDWHITE"\nLehmer Low Generator(very bad idea):\n"RESET);
	memset(seq, 0, SEQ_SIZE);
	unsigned int seed_lehmer_low = time(NULL);
	ByteGenGenerateSequence(LehmerLowGenerator, &seed_lehmer_low, seq, SEQ_SIZE);
	UniformnessTest(seq, SEQ_SIZE);
	IndependanceTest(seq, SEQ_SIZE);
	HomogeneousnessTest(seq, SEQ_SIZE);

	printf(BOLDWHITE"\nLehmer High Generator:\n"RESET);
	memset(seq, 0, SEQ_SIZE);
	unsigned int seed_lehmer_high = time(NULL);
	ByteGenGenerateSequence(LehmerHighGenerator, &seed_lehmer_high, seq, SEQ_SIZE);
	UniformnessTest(seq, SEQ_SIZE);
	IndependanceTest(seq, SEQ_SIZE);
	HomogeneousnessTest(seq, SEQ_SIZE);

	printf(BOLDWHITE"\nL20 Generator:\n"RESET);
	memset(seq, 0, SEQ_SIZE);
	unsigned int seed_l20 = time(NULL)%65556;
	BitGenGenerateSequence(L20Generator, &seed_l20, seq, SEQ_SIZE);
	UniformnessTest(seq, SEQ_SIZE);
	IndependanceTest(seq, SEQ_SIZE);
	HomogeneousnessTest(seq, SEQ_SIZE);

	printf(BOLDWHITE"\nL89 Generator:\n"RESET);
	memset(seq, 0, SEQ_SIZE);
	L_NUMBER seed_l89;
	l_init_by_len(&seed_l89, 128);
	seed_l89.words[0] = time(NULL);
	BitGenGenerateSequence(L89Generator, &seed_l89, seq, SEQ_SIZE);
	UniformnessTest(seq, SEQ_SIZE);
	IndependanceTest(seq, SEQ_SIZE);
	HomogeneousnessTest(seq, SEQ_SIZE);

	printf(BOLDWHITE"\nGeffe Generator:\n"RESET);
	memset(seq, 0, SEQ_SIZE);
	int seed_geffe[3];
	seed_geffe[0] = time(NULL)%100;
	seed_geffe[1] = time(NULL)%100;
	seed_geffe[2] = time(NULL)%100;
	BitGenGenerateSequence(GeffeGenerator, &seed_geffe, seq, SEQ_SIZE);
	UniformnessTest(seq, SEQ_SIZE);
	IndependanceTest(seq, SEQ_SIZE);
	HomogeneousnessTest(seq, SEQ_SIZE);

	printf(BOLDWHITE"\nLibrarian Generator:\n"RESET);
	memset(seq, 0, SEQ_SIZE);
	FILE *f = fopen( "NZ.txt", "rb" );
	fseek( f, 0, SEEK_END );
	long fileSize = ftell( f );
	fseek( f, 0, SEEK_SET );
	char* seed_librarian = malloc(fileSize);
	char* begin_file = seed_librarian;
	if (!fread( seed_librarian, fileSize, 1, f )) printf("Err\n");;
	fclose( f );

	ByteGenGenerateSequence(LibrarianGenerator, &seed_librarian, seq, SEQ_SIZE);
	UniformnessTest(seq, SEQ_SIZE);
	IndependanceTest(seq, SEQ_SIZE);
	HomogeneousnessTest(seq, SEQ_SIZE);
	free(begin_file);

	printf(BOLDWHITE"\nWolfram Generator:\n"RESET);
	memset(seq, 0, SEQ_SIZE);
	unsigned seed_wolfram = time(NULL);
	BitGenGenerateSequence(WolframGenerator, &seed_wolfram, seq, SEQ_SIZE);
	UniformnessTest(seq, SEQ_SIZE);
	IndependanceTest(seq, SEQ_SIZE);
	HomogeneousnessTest(seq, SEQ_SIZE);

	printf(BOLDWHITE"\nBM bits Generator:\n"RESET);
	memset(seq, 0, SEQ_SIZE);
	L_NUMBER seed_bm[5];
	l_init_by_str(&seed_bm[0], "0x5B88C41246790891C095E2878880342E88C79974303BD0400B090FE38A688356"); // a
	l_init_by_str(&seed_bm[1], "0xCEA42B987C44FA642D80AD9F51F10457690DEF10C83D0BC1BCEE12FC3B6093E3"); // p
	l_init_by_str(&seed_bm[2], "0x675215CC3E227D3216C056CFA8F8822BB486F788641E85E0DE77097E1DB049F1"); // (p-1)/2
	l_init_by_len(&seed_bm[3], 512);
	m_pre_barret(8, &seed_bm[1], &seed_bm[3]);
	l_init_by_len(&seed_bm[4], 256); 
	seed_bm[4].words[0] = time(NULL);

	BitGenGenerateSequence(BMGenerator, seed_bm, seq, SEQ_SIZE);
	UniformnessTest(seq, SEQ_SIZE);
	IndependanceTest(seq, SEQ_SIZE);
	HomogeneousnessTest(seq, SEQ_SIZE);

	printf(BOLDWHITE"\nBM bytes Generator:\n"RESET);
	memset(seq, 0, SEQ_SIZE);
	L_NUMBER seed_bm_bytes[5];
	L_NUMBER seed_q_table[256];
	L_NUMBER c;
	l_init_by_len(&c, 256);
	l_shift_r(&seed_bm[2], 7, &seed_bm[2]);
	for (u32 i=0; i<256; i++) {
		l_init_by_len(&seed_q_table[i], 256);
		l_mul(&seed_bm[2], &c, &seed_q_table[i]);
		c.words[0]++;
	}
	l_init_by_str(&seed_bm_bytes[0], "0x5B88C41246790891C095E2878880342E88C79974303BD0400B090FE38A688356"); // a
	l_init_by_str(&seed_bm_bytes[1], "0xCEA42B987C44FA642D80AD9F51F10457690DEF10C83D0BC1BCEE12FC3B6093E3"); // p
	seed_bm_bytes[4] = seed_q_table[0];
	l_init_by_len(&seed_bm_bytes[2], 512);
	m_pre_barret(8, &seed_bm_bytes[1], &seed_bm_bytes[2]);
	l_init_by_len(&seed_bm_bytes[3], 256); 
	seed_bm_bytes[3].words[0] = time(NULL);

	ByteGenGenerateSequence(BMByteGenerator, seed_bm_bytes, seq, SEQ_SIZE);
	UniformnessTest(seq, SEQ_SIZE);
	IndependanceTest(seq, SEQ_SIZE);
	HomogeneousnessTest(seq, SEQ_SIZE);

	printf(BOLDWHITE"\nBBS bits Generator:\n"RESET);
	memset(seq, 0, SEQ_SIZE);
	L_NUMBER seed_bbs[3];
	l_init_by_str(&seed_bbs[0], "0x37682F6947AAAB110517C20B76DF64781DA78B3E87EB58379085D3395793BDB9D9"); // a
	l_init_by_len(&seed_bbs[1], 640);
	m_pre_barret(10, &seed_bbs[0], &seed_bbs[1]);
	l_init_by_len(&seed_bbs[2], 320); 
	seed_bbs[2].words[4]=1;
	seed_bbs[2].words[0]=time(NULL);
	BitGenGenerateSequence(BBSGenerator, seed_bbs, seq, SEQ_SIZE);
	UniformnessTest(seq, SEQ_SIZE);
	IndependanceTest(seq, SEQ_SIZE);
	HomogeneousnessTest(seq, SEQ_SIZE);

	printf(BOLDWHITE"\nBBS bytes Generator:\n"RESET);
	memset(seq, 0, SEQ_SIZE);
	ByteGenGenerateSequence(BBSByteGenerator, seed_bbs, seq, SEQ_SIZE);
	UniformnessTest(seq, SEQ_SIZE);
	IndependanceTest(seq, SEQ_SIZE);
	HomogeneousnessTest(seq, SEQ_SIZE);

	return 0;
}