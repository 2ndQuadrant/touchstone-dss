/*
 * Copyright 2016-2017 PostgreSQL Global Development Group
 */

#ifndef _DATAGEN_H_
#define _DATAGEN_H_

#include <touchstone.h>

#include "common.h"

#define DIR_LEN 256
#define FILENAME_LEN DIR_LEN + 64

#define DATAFILE_PRODUCT "product.data"
#define DATAFILE_SALES "sales.data"
#define DATAFILE_STORE "store.data"
#define DATAFILE_TIME "time.data"

#define CATEGORY_MAX 12
#define CATEGORY_LEN 15

int gen_product_data(char *, struct df_t *);
int gen_sales_data(char *, struct df_t *);
int gen_store_data(char *, struct df_t *);
int gen_time_data(char *, struct df_t *);

#endif /* _DATAGEN_H_ */
