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

int gen_sales_data(char *outdir, struct df_t *df)
{
	long long i;
	FILE *output;
	char filename[FILENAME_LEN + 1];
	long long row_size;
	long long max_rows;

	struct sales_t sales_t;

	snprintf(filename, FILENAME_LEN, "%s/%s", outdir, DATAFILE_SALES);
	output = fopen(filename, "w");

	init_genrand64(df->seed);

	/* 1 gibibytes = 1 073 741 824 bytes */
	row_size = sizeof(sales_t);
	max_rows = 1073741824 / row_size;

	for (i = 0; i < max_rows; i++) {
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
