/*
 * Copyright 2017 PostgreSQL Global Development Group
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#include "datagen.h"

#define Q1VARS 1
#define Q2VARS 1

#define TOTAL_QUERIES 2

int dss_generate_query(int, int, char *, char *, char *, int, int,
		struct df_t *);
int dss_query_values(int, struct query_t *, struct df_t *);
void usage(char *);

int dss_query_values(int q, struct query_t *qt, struct df_t *df)
{
	time_t tloc;
	struct tm tm;

	bzero(&tm, sizeof(struct tm));

	qt->id = q;
	switch (q) {
	case 1:
		qt->vars = Q1VARS;

		/*
		 * This is a gross calculation such that we don't query past the last
		 * year of data that was generated, which should be 365 days more often
		 * than not.
		 */
		tloc = 978307200 + getrand(0, df->days - 365) * 86400;
		localtime_r(&tloc, &tm);
		snprintf(qt->var[0], 11, "%04d-%02d-%02d", tm.tm_year + 1900,
				tm.tm_mon + 1, tm.tm_mday);
		break;
	case 2:
		qt->vars = Q2VARS;
		strncpy(qt->var[0], category[(int) getrand(0, CATEGORY_MAX - 1)],
				CATEGORY_LEN);
		break;
	default:
		printf("unknown query: %d\n", q);
		return 1;
	}
	return 0;
}

int dss_generate_query(int q, int o, char *indir, char *outdir, char *config,
		int flag_analyze, int flag_plan, struct df_t *df)
{
	char infile[DIR_LEN + FILENAME_LEN + 1];
	char outfile[DIR_LEN + FILENAME_LEN + 1];
	struct query_t qt;

	snprintf(infile, DIR_LEN + FILENAME_LEN, "%s/q%d.sql", indir, q);
	/*
	 * Code the output filename such that the first number is the order to
	 * execute the query and the second number is the query identifyer.
	 */
	snprintf(outfile, DIR_LEN + FILENAME_LEN, "%s/q%d-%02d.sql", outdir, o, q);

	load_query_parameters(config, &qt);
	qt.flag_analyze = flag_analyze;
	qt.flag_plan = flag_plan;
	dss_query_values(q, &qt, df);
	if (!generate_query(infile, outfile, &qt))
		return 1;
	return 0;
}

void usage(char *filename)
{
	printf("usage: %s [options]\n", filename);
	printf("  options:\n");
	printf("    -a - analyze query execution\n");
	printf("    -c <file> - query configuration file\n");
	printf("    -f <dbms> - data format\n");
	printf("    -i <dir> - query template directory\n");
	printf("    -o <dir> - query output directory, default .\n");
	printf("    -p - generate plans\n");
	printf("    -q <int> - query to generate, default: all\n");
	printf("    -s <int> - set seed, default: 0\n");
	printf("    -y <int> - number of years of data generated, default: 1\n");
}

int main(int argc, char *argv[])
{
	int c;
	int i;
	int data_format = DATA_FORMAT_PGSQL;
	char config[DIR_LEN + FILENAME_LEN + 1] = "";
	char indir[DIR_LEN + 1] = "";
	char outdir[DIR_LEN + 1] = ".";
	struct df_t df;

	int query = 0;
	int order[TOTAL_QUERIES]; /* Order to execute queries. */
	int flag_analyze = 0;
	int flag_plan = 0;

	/* Initialize default values. */
	df.years = 1;
	df.seed = 0;
	for (i = 0; i < TOTAL_QUERIES; i++)
		order[i] = i + 1;

	while (1) {
		int option_index = 1;
		static struct option long_options[] = {
			{0, 0, 0, 0,}
		};

		c = getopt_long(argc, argv, "ac:f:hi:o:pq:s:y:",
				long_options, &option_index);
		if (c == -1)
			break;

		switch (c) {
		case 0:
			break;
		case 'a':
			flag_analyze = 1;
			break;
		case 'c':
			strncpy(config, optarg, DIR_LEN + FILENAME_LEN);
			break;
		case 'f':
			if (strcmp("pgsql", optarg) == 0) {
				data_format = DATA_FORMAT_PGSQL;
			} else {
				fprintf(stderr, "unknown data format: %s\n", optarg);
				return 3;
			}
			break;
		case 'h':
			usage(argv[0]);
			return 0;
		case 'i':
			strncpy(indir, optarg, DIR_LEN);
			break;
		case 'o':
			strncpy(outdir, optarg, DIR_LEN);
			break;
		case 'p':
			flag_plan = 1;
			break;
		case 'q':
			query = atoi(optarg);
			if (query < 1 || query > TOTAL_QUERIES) {
				printf("invalid query number: %d\n", query);
				return 3;
			}
			break;
		case 's':
			df.seed = atoll(optarg);
			break;
		case 'y':
			df.years = atoi(optarg);
			break;
		default:
			printf("?? getopt returned character code 0%o ??\n", c);
			return 2;
		}
	}

	if (flag_analyze && flag_plan) {
		fprintf(stderr,
				"error: both -a and -p can't be used at the same time\n");
		return 4;
	}

	if (indir[0] == '\0') {
		fprintf(stderr, "error: use -i to specify query template directory\n");
		return 4;
	}

	init_genrand64(df.seed);
	init_format(data_format, &df);

	/* Shuffle query order. */
	for (i = 0; i < TOTAL_QUERIES - 1; i++) {
		c = getrand(i, TOTAL_QUERIES - 1);
		if (i != c) {
			order[i] ^= order[c];
			order[c] ^= order[i];
			order[i] ^= order[c];
		}
	}

	for (i = 0; i < TOTAL_QUERIES; i++) {
		if (!dss_generate_query(i + 1, order[i], indir, outdir, config,
					flag_analyze, flag_plan, &df)) {
			fprintf(stderr, "error generating query %d\n", i + 1);
			return 1;
		}
	}

	return 0;
}
