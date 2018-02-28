/*
 * Copyright 2017 PostgreSQL Global Development Group
 */

#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#define DATA_FORMAT_PGSQL 0

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

extern const char *brand[];
extern const char *category[];

int init_format(int, struct df_t *);

#endif /* _COMMON_H_ */
