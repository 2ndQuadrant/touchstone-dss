/*
 * Copyright 2017 PostgreSQL Global Development Group
 */

#include <string.h>

#include <touchstone.h>

#include "common.h"

const char *brand[] = {
		"Adriafil",
		"The Alpaca Yarn Company",
		"AMANO",
		"Anzula",
		"Araucania",
		"Artyarns",
		"Baa Ram Ewe",
		"Baah Yarn",
		"BC Garn",
		"Be Sweet",
		"Berroco",
		"Big Bad Wool",
		"Blue Sky Fibers",
		"Borgo de’ Pazzi",
		"Briggs & Little",
		"Brown Sheep",
		"Cascade Yarns",
		"Classic Elite Yarns",
		"Cleckheaton",
		"Conway + Bliss",
		"Debbie Bliss",
		"DMC",
		"Done Roving Yarns",
		"Dream in Color",
		"Ella Rae",
		"Elsebeth Lavold",
		"Erika Knight",
		"Euro Baby",
		"Euro Yarn",
		"Fibra Natura",
		"The Fibre Co.",
		"Filatura Di Crosa",
		"Freia Fine Handpaints",
		"GGH Yarns",
		"Great Adirondack Yarn Co",
		"Harrisville Designs",
		"Hayfield",
		"HiKoo",
		"A Hundred Ravens",
		"Imperial Yarn",
		"Jade Sapphire",
		"Jaggerspun",
		"James C. Brett",
		"Jil Eaton",
		"Jo Sharp",
		"Jojoland",
		"Juniper Moon Farm",
		"Katia",
		"Kauni",
		"Kelbourne Woolens",
		"Knit Collage",
		"Knit One Crochet Too",
		"Knitting Fever",
		"Koigu",
		"Lana Grossa",
		"Lana Vida",
		"Lang",
		"Lopi",
		"Loren",
		"Lorna's Laces",
		"Louet",
		"Louisa Harding",
		"Lux Adorna Knits",
		"Madelinetosh",
		"Malabrigo",
		"Mango Moon",
		"Manos Del Uruguay",
		"Maysville",
		"MillaMia",
		"Mirasol",
		"Mrs. Crosby",
		"My Mountain Schachenmayr",
		"Nako",
		"Noro",
		"On-Line",
		"Opal",
		"Plymouth Yarn",
		"Prism",
		"Queensland Collection",
		"Red Heart",
		"Regia",
		"Rowan",
		"Rozetti Yarns",
		"Sesia",
		"Schachenmayr",
		"Scheepjes",
		"Schoppel Wolle",
		"Shalimar Yarns",
		"Shibui Knits",
		"Sirdar",
		"Spincycle Yarns",
		"Spud & Chloë by Blue Sky Fibers",
		"Stacy Charles Fine Yarns",
		"Sublime",
		"Swans Island",
		"SweetGeorgia",
		"Tahki Yarns",
		"The Third Piece",
		"Trendsetter Yarns",
		"UKI",
		"Universal Yarn",
		"Valley Yarns",
		"Viking of Norway",
		"West Yorkshire Spinners",
		"Wildwood Yarns",
		"Wisdom Yarns",
		"Wonderland Yarns",
		"Wool and The Gang",
		"Yarn Stories",
		"Zealana",
		"Zen Yarn Garden"
};

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

