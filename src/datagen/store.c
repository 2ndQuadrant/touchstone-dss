/*
 * Copyright 2016 PostgreSQL Global Development Group
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "datagen.h"

const char *states[50] = {
	"Alabama", "Alaska", "Arizona", "Arkansas", "California", "Colorado",
	"Connecticut", "Delaware", "Florida", "Georgia", "Hawaii", "Idaho",
	"Illinois", "Indiana", "Iowa", "Kansas", "Kentucky", "Louisiana", "Maine",
	"Maryland", "Massachusetts", "Michigan", "Minnesota", "Mississippi",
	"Missouri", "Montana", "Nebraska", "Nevada", "New Hampshire", "New Jersey",
	"New Mexico", "New York", "North Carolina", "North Dakota", "Ohio",
	"Oklahoma", "Oregon", "Pennsylvania", "Rhode Island", "South Carolina",
	"South Dakota", "Tennessee", "Texas", "Utah", "Vermont", "Virginia",
	"Washington", "West Virginia", "Wisconsin", "Wyoming"
};

const char *state_abbrs[50] = {
	"AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DE", "FL", "GA", "HI", "ID",
	"IL", "IN", "IA", "KS", "KY", "LA", "ME", "MD", "MA", "MI", "MN", "MS",
	"MO", "MT", "NE", "NV", "NH", "NJ", "NM", "NY", "NC", "ND", "OH", "OK",
	"OR", "PA", "RI", "SC", "SD", "TN", "TX", "UT", "VT", "VA", "WA", "WV",
	"WI", "WY"
};

int gen_store_data(char *outdir, struct df_t *df)
{
	int i;
	FILE *output;
	char filename[FILENAME_LEN + 1];

	int num_states;

	num_states = (int) (sizeof(states) / sizeof(states[0]));

	snprintf(filename, FILENAME_LEN, "%s/%s", outdir, DATAFILE_STORE);
	output = fopen(filename, "w");

	for (i = 0; i < num_states; i++) {
		fprintf(output,
				"%d%c%d%c%s%c%s\n",
				i + 1, df->sep, /* id */
				i + 1, df->sep, /* store_number */
				states[i], df->sep, /* state */
				state_abbrs[i]); /* state abbreviation */
	}
	fclose(output);

	return 0;
}
