/*
 * Copyright 2016 PostgreSQL Global Development Group
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <values.h>

#include "datagen.h"

/*
 * https://en.wikipedia.org/wiki/International_Article_Number
 *
 * The 13-digit EAN-13 number consists of four components:
 *
 * GS1 Prefix
 *
 *    The first 3 digits - usually identifying the national GS1 Member
 *    Organization to which the manufacturer is registered (not necessarily
 *    where the product is actually made).
 *
 *    The GS1 Prefix is 978 or 979, when the EAN-13 symbol encodes a conversion
 *    of an International Standard Book Number (ISBN). Likewise the prefix
 *    is 979 for International Standard Music Number (ISMN) and 977 for
 *    International Standard Serial Number (ISSN).
 *
 * Manufacturer Code

 *    The manufacturer code is a unique code assigned to each manufacturer by
 *    the numbering authority indicated by the GS1 Prefix. All products
 *    produced by a given company will use the same manufacturer code. EAN-13
 *    uses what is called "variable-length manufacturer codes." Assigning
 *    fixed-length 5-digit manufacturer codes, as the UCC has done until
 *    recently, means that each manufacturer can have up to 99,999 product
 *    codes--and many manufacturers don't have that many products, which means
 *    hundreds or even thousands of potential product codes are being wasted on
 *    manufacturers that only have a few products. Thus if a potential
 *    manufacturer knows that it is only going to produce a few products,
 *    EAN-13 may issue it a longer manufacturer code, leaving less space for
 *    the product code. This results in more efficient use of the available
 *    manufacturer and product codes.
 *
 *    In ISBN and ISSN, this component is used to identify the language in
 *    which the publication was issued and managed by a transnational agency
 *    covering several countries, or to identify the country where the legal
 *    deposits are made by a publisher registered with a national agency, and
 *    it is further subdivided any allocating subblocks for publishers; many
 *    countries have several prefixes allocated in the ISSN and ISBN
 *    registries.
 *
 * Product Code
 *
 *    The product code is assigned by the manufacturer. The product code
 *    immediately follows manufacturer code. The total length of manufacturer
 *    code plus product code should be 9 or 10 digits depending on the length
 *    of country code(2-3 digits).
 *
 *    In ISBN and ISSN, it uniquely identifies the publication from the same
 *    publisher; it should be used and allocated by the registered publisher in
 *    order to avoid creating gaps; however it happens that a registered book
 *    or serial never gets published and sold.
 *
 * Check digit
 *
 *    The check digit is an additional digit, used to verify that a barcode has
 *    been scanned correctly. It is computed modulo 10, where the weights in
 *    the checksum calculation alternate 3 and 1. In particular, since the
 *    weights are relatively prime to 10, the EAN-13 system will detect all
 *    single digit errors. It also recognizes 90% of transposition errors (all
 *    cases, where the difference between adjacent digits is not 5).
 */

int gen_product_data(char *outdir, struct df_t *df)
{
	int i;
	FILE *output;
	char filename[FILENAME_LEN + 1];

	char name[21];
	char brand[21];
	char category[21];

	snprintf(filename, FILENAME_LEN, "%s/%s", outdir, DATAFILE_PRODUCT);
	output = fopen(filename, "w");

	init_genrand64(df->seed);

	for (i = 0; i < df->products; i++) {
		get_alpha(name, 1, 20);
		get_alpha(brand, 1, 20);
		get_alpha(category, 1, 20);

		fprintf(output,
				"%d%c%03d%05d%03d%d%c%s%c%s%c%s\n",
				i + 1, df->sep, /* id */
				(int) getrand(0, 999), /* ean gs1 */
				(int) getrand(0, 99999), /* ean manufacturer code */
				(int) getrand(0, 999), /* ean product code */
				(int) getrand(0, 9),  df->sep, /* ean check digit */
				name, df->sep, /* name */
				brand, df->sep, /* brand */
				category /* category */
				);
	}
	fclose(output);

	return 0;
}

