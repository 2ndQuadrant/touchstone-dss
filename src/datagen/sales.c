/*
 * Copyright 2016-2017 PostgreSQL Global Development Group
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "datagen.h"

struct sales_t {
	int64 product_id;
	int64 store_id;
	struct tm tm;
	int64 units;
	double unit_price;
	double vat;
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

	time_t tloc;

	struct sales_t sales_t;

	bzero(&sales_t.tm, sizeof(struct tm));

	init_genrand64(df->seed);

	output = fopen(filename, "w");

	for (i = 0; i < start; i++) {
		getrand(1, df->products);
		getrand(1, 50);
		getrand(0, df->days - 1);
		getrand(0, 86399);
		getGaussianRand(1, 10000, 5);
		getrand(1, 10000000);
		getrand(0, 100);
	}

	for (i = start; i < stop; i++) {
		sales_t.product_id = getrand(1, df->products);
		sales_t.store_id = getrand(1, 50);

		tloc = 978307200 + getrand(0, df->days - 1) * 86400 +
				getrand(0, 86399);
		localtime_r(&tloc, &sales_t.tm);

		sales_t.units = getGaussianRand(1, 10000, 5);
		sales_t.unit_price = (double) getrand(1, 10000000) / 100.0;
		sales_t.vat = (double) getrand(0, 100) / 100.0;

		fprintf(output, "%ld%c%ld%c%d-%02d-%d%c%d-%02d-%d %02d:%02d:%02d+00%c%ld%c%f%c%f\n",
				sales_t.product_id, df->sep, /* product_id */
				sales_t.store_id, df->sep, /* store_id */

				sales_t.tm.tm_year + 1900, /* year */
				sales_t.tm.tm_mon + 1, /* month */
				sales_t.tm.tm_mday, /* day of the month */
				df->sep,

				sales_t.tm.tm_year + 1900, /* year */
				sales_t.tm.tm_mon + 1, /* month */
				sales_t.tm.tm_mday, /* day of the month */
				sales_t.tm.tm_hour, /* hour */
				sales_t.tm.tm_min, /* minutes */
				sales_t.tm.tm_sec, /* seconds */
				df->sep,

				sales_t.units, df->sep, /* units */
				sales_t.unit_price / 100.0, df->sep, /* unit_price */
				sales_t.vat); /* vat */
	}

	fclose(output);

	return 0;
}
