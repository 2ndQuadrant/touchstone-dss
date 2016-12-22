/*
 * Copyright 2016 PostgreSQL Global Development Group
 */

#ifndef _DATAGEN_H_
#define _DATAGEN_H_

#include <touchstone.h>

#define OUTDIR_LEN 256
#define FILENAME_LEN OUTDIR_LEN + 64

#define DATA_FORMAT_PGSQL 0

#define DATAFILE_PRODUCT "product.data"
#define DATAFILE_SALES "sales.data"
#define DATAFILE_STORE "store.data"
#define DATAFILE_TIME "time.data"

#define START_YEAR 2001

struct df_t
{
	int chunk; /* Generate only this chunk. */
	int chunks; /* Number of chunks to generate. */
	int days;
	int only_one_chunk; /* Flag to generate only one file. */
	int products;
	int scale_factor;
	unsigned long long seed;
	char sep;
	int years;
};

int gen_product_data(char *, struct df_t *);
int gen_sales_data(char *, struct df_t *);
int gen_store_data(char *, struct df_t *);
int gen_time_data(char *, struct df_t *);

#endif /* _DATAGEN_H_ */
