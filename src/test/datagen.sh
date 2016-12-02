#! /bin/sh
#
# Copyright 2016 PostgreSQL Global Development Group
#

TIMEFILE="time.data"

oneTimeSetUp() {
	TMPDIR=`mktemp -d`

	../bin/tsdss-datagen -d $TMPDIR
	assertEquals "create all data files" 0 $?
}

oneTimeTearDown() {
	rm -rf $TMPDIR
}

testTimeDataExists() {
	if [[ -f $TMPDIR/$TIMEFILE ]]; then
		RC=1
	else
		RC=0
	fi
	assertEquals "Check $TIMEFILE exists" 1 $RC
}

testTimeDataOnly() {
	mkdir $TMPDIR/t
	../bin/tsdss-datagen -d $TMPDIR/t -t time
	assertEquals "create time data file" 0 $?

	if [[ -f $TMPDIR/t/$TIMEFILE ]]; then
		RC=1
	else
		RC=0
	fi
	assertEquals "Check $TIMEFILE exists" 1 $RC
}

testTimeDataRows() {
	C=`wc -l $TMPDIR/$TIMEFILE | cut -d " " -f 1`
	assertEquals "Check number of rows in $TIMEFILE" 365 $C
}

. `which shunit2`
