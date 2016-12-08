/*
 * Copyright 2016-2017 PostgreSQL Global Development Group
 */

#include <stdio.h>

#include "datagen.h"

int gen_sales_data(char *outdir, struct df_t *df)
{
	FILE *output;
	char filename[FILENAME_LEN + 1];
	long long cur_size = 0;
	long long max_size;

	snprintf(filename, FILENAME_LEN, "%s/%s", outdir, DATAFILE_SALES);
	output = fopen(filename, "w");

	init_genrand64(df->seed);

	/* 1 gibibytes = 1 073 741 824 bytes */
	max_size = (long long) df->scale_factor * 1073741824;
	do {
		cur_size += fprintf(output, "%ld%c%ld%c%ld%c%ld%c%f\n",
				getrand(1, df->products), df->sep, /* product_id */
				getrand(1, 50), df->sep, /* store_id */
				978307200 + getrand(0, df->days - 1) * 86400, df->sep, /* time_id */
				getGaussianRand(1, 10000, 5), df->sep, /* units */
				(double) getrand(1, 10000000) / 100.0); /* unit_price */
	} while (cur_size < max_size);

	fclose(output);

	return 0;
}
