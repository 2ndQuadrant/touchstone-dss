/*
 * Copyright 2017 PostgreSQL Global Development Group
 */

#include <string.h>

#include <touchstone.h>

#include "common.h"

const char *category[] = { "aran", "bulky", "cobweb", "dk", "fingering",
		"jumbo", "lace", "light fingering", "sport", "super bulky", "thread",
		"worsted" };

int init_format(int data_format, struct df_t *df)
{
	int i;

	/* For ease of testing, try to work with everything in GMT/UTC. */
	putenv("TZ=\":GMT\"");

	if (df->seed == -1) {
		struct timeval tv;

		gettimeofday(&tv, NULL);

		df->seed = getpid();
		df->seed ^= tv.tv_sec ^ tv.tv_usec;
	}

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

