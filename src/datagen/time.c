/*
 * Copyright 2016 PostgreSQL Global Development Group
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "datagen.h"

const char *month_name[12] = {
		"January", "February", "March", "April", "May", "June", "July",
		"August", "September", "October", "November", "December"
};

int gen_time_data(char *outdir, struct df_t *df)
{
	int i;
	FILE *output;
	char filename[FILENAME_LEN + 1];

	time_t tloc;
	struct tm tm;

	bzero(&tm, sizeof(struct tm));

	/* Set the first day to generate data from. */

	tm.tm_year = START_YEAR - 1900;
	tm.tm_mday = 1;
	tloc = mktime(&tm);

	snprintf(filename, FILENAME_LEN, "%s/%s", outdir, DATAFILE_TIME);
	output = fopen(filename, "w");

	for (i = 0; i < df->days; i++) {
		int year;
		int quarter;

		localtime_r(&tloc, &tm);

		year = tm.tm_year + 1900;

		switch (tm.tm_mon) {
			case 0:
			case 1:
			case 2:
				quarter = 1;
				break;
			case 3:
			case 4:
			case 5:
				quarter = 2;
				break;
			case 6:
			case 7:
			case 8:
				quarter = 3;
				break;
			case 9:
			case 10:
			case 11:
				quarter = 4;
				break;
		}

		fprintf(output,
				"%d-%d-%d%c%d%c%d%c%d%c%s%c%d%cQ%d%c%d\n",
				year, tm.tm_mon + 1, tm.tm_mday, df->sep, /* id */
				tm.tm_mday, df->sep, /* day of the month */
				tm.tm_wday + 1, df->sep, /* day of the week */
				tm.tm_mon + 1, df->sep, /* month */
				month_name[tm.tm_mon], df->sep, /* month_name */
				quarter, df->sep, /* quarter */
				quarter, df->sep, /* quarter_name */
				year); /* year */

		tloc += 86400;
	}
	fclose(output);

	return 0;
}
