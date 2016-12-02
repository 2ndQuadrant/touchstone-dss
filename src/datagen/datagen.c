/*
 * Copyright 2016 PostgreSQL Global Development Group
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "datagen.h"

#define TABLE_STORE 1
#define TABLE_TIME 2

void usage(char *filename)
{
	printf("usage: %s [options]\n", filename);
	printf("  options:\n");
	printf("    -d <path> - directory to generate data files, default: .\n");
	printf("    -t <table> - generate data for only 1 table: store, time\n");
	printf("    -y <int> - number of years of data to generate, default: 1\n");
}

int init_format(int data_format, struct df_t *df)
{
	int i;

	/* For ease of testing, try to work with everything in GMT/UTC. */
	putenv("TZ=\":GMT\"");

	for (i = 0; i < df->years; i++)
		df->days += get_days(START_YEAR + i);

	switch (data_format) {
	case DATA_FORMAT_PGSQL:
		df->sep = '\t';
		break;
	default:
		return -1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int c;
	char outdir[OUTDIR_LEN + 1] = ".";
	int data_format = DATA_FORMAT_PGSQL;
	struct df_t df;

	int table = 0;

	/* Initialize default values. */

	df.days = 0;
	df.years = 1;

	while (1) {
		int option_index = 1;
		static struct option long_options[] = {
			{0, 0, 0, 0,}
		};

		c = getopt_long(argc, argv, "d:f:ht:y:",
				long_options, &option_index);
		if (c == -1)
			break;

		switch (c) {
		case 0:
			break;
		case 'd':
			strncpy(outdir, optarg, OUTDIR_LEN);
			break;
		case 'f':
			if (strcmp("pgsql", optarg) == 0) {
				data_format = DATA_FORMAT_PGSQL;
			} else {
				printf("unknown data format: %s\n", optarg);
				return 3;
			}
			break;
		case 'h':
			usage(argv[0]);
			return 0;
		case 't':
			if (strcmp("store", optarg) == 0) {
				table = TABLE_STORE;
			} else if (strcmp("time", optarg) == 0) {
				table = TABLE_TIME;
			} else {
				printf("unknown table: %s\n", optarg);
				return 4;
			}
			break;
		case 'y':
			df.years = atoi(optarg);
			break;
		default:
			printf("?? getopt returned character code 0%o ??\n", c);
			return 2;
		}
	}

	init_format(data_format, &df);

	if (table == 0 || table == TABLE_STORE)
		gen_store_data(outdir, &df);

	if (table == 0 || table == TABLE_TIME)
		gen_time_data(outdir, &df);

	return 0;
}
