/*
 * Copyright 2016-2017 PostgreSQL Global Development Group
 */

#include <stdio.h>

#include "datagen.h"

struct sales_t {
	int64 product_id;
	int64 store_id;
	int64 time_id;
	int64 units;
	double unit_price;
};

int write_sales_files(char *, struct df_t *, long long, long long);

int gen_sales_data(char *outdir, struct df_t *df)
{
	int i;
	char filename[FILENAME_LEN + 1];
	long long row_size;
	long long max_rows;

	/* 1 gibibytes = 1 073 741 824 bytes */

	row_size = sizeof(struct sales_t);
	max_rows = 1073741824 / row_size;

	if (df->chunks == 1) {
		snprintf(filename, FILENAME_LEN, "%s/%s", outdir, DATAFILE_SALES);
		write_sales_files(filename, df, 0, max_rows);
	} else {
		long long chunk;

		chunk = (long long) (max_rows / df->chunks);

		if (df->only_one_chunk) {
			snprintf(filename, FILENAME_LEN, "%s/%s.%d", outdir,
						DATAFILE_SALES, df->chunk);
			if (df->chunk == df->chunks)
				write_sales_files(filename, df, (df->chunk - 1) * chunk,
						max_rows);
			else
				write_sales_files(filename, df, (df->chunk - 1) * chunk,
						df->chunk * chunk);
			return 0;
		}

		for (i = 0; i < df->chunks - 1; i++) {
			snprintf(filename, FILENAME_LEN, "%s/%s.%d", outdir,
					DATAFILE_SALES, i + 1);
			write_sales_files(filename, df, i * chunk, (i + 1) * chunk);
		}
		snprintf(filename, FILENAME_LEN, "%s/%s.%d", outdir,
					DATAFILE_SALES, df->chunks);
		write_sales_files(filename, df, (df->chunks - 1) * chunk, max_rows);
	}

	return 0;
}

int write_sales_files(char *filename, struct df_t *df, long long start,
		long long stop)
{
	long long i;
	FILE *output;

	struct sales_t sales_t;

	init_genrand64(df->seed);

	output = fopen(filename, "w");

	for (i = 0; i < start; i++) {
		getrand(1, df->products);
		getrand(1, 50);
		getrand(1, df->days);
		getGaussianRand(1, 10000, 5);
		getrand(1, 10000000);
	}

	for (i = start; i < stop; i++) {
		sales_t.product_id = getrand(1, df->products);
		sales_t.store_id = getrand(1, 50);
		sales_t.time_id = 978307200 + getrand(0, df->days - 1) * 86400;
		sales_t.units = getGaussianRand(1, 10000, 5);
		sales_t.unit_price = (double) getrand(1, 10000000) / 100.0;

		fprintf(output, "%ld%c%ld%c%ld%c%ld%c%f\n",
				sales_t.product_id, df->sep, /* product_id */
				sales_t.store_id, df->sep, /* store_id */
				sales_t.time_id, df->sep, /* time_id */
				sales_t.units, df->sep, /* units */
				sales_t.unit_price / 100.0); /* unit_price */
	}

	fclose(output);

	return 0;
}