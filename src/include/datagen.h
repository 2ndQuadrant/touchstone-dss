/*
 * Copyright 2016 PostgreSQL Global Development Group
 */

#ifndef _DATAGEN_H_
#define _DATAGEN_H_

#include <touchstone.h>

#define OUTDIR_LEN 256
#define FILENAME_LEN OUTDIR_LEN + 64

#define DATA_FORMAT_PGSQL 0

#define DATAFILE_TIME "time.data"

#define START_YEAR 2001

struct df_t
{
	int days;
	char sep;
	int years;
};

int gen_time_data(char *, struct df_t *);

#endif /* _DATAGEN_H_ */
