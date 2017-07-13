#! /bin/sh
#
# Copyright 2016 PostgreSQL Global Development Group
#

PRODUCTFILE="product.data"
SALESFILE="sales.data"
STOREFILE="store.data"
TIMEFILE="time.data"

oneTimeSetUp() {
	export PATH=$PWD/../bin:$PWD/../scripts:$PWD/../scripts/pgsql:$PATH
	tsdss-datagen -d $SHUNIT_TMPDIR
	assertEquals "create all data files" 0 $?
}

testProductDataExists() {
	if [[ -f "$SHUNIT_TMPDIR/$PRODUCTFILE" ]]; then
		RC=1
	else
		RC=0
	fi
	assertEquals "Check $PRODUCTFILE exists" 1 $RC
}

testProductDataOnly() {
	mkdir $SHUNIT_TMPDIR/p
	tsdss-datagen -d $SHUNIT_TMPDIR/p -t product
	assertEquals "create product data file" 0 $?

	if [[ -f "$SHUNIT_TMPDIR/p/$PRODUCTFILE" ]]; then
		RC=1
	else
		RC=0
	fi
	assertEquals "Check $PRODUCTFILE exists" 1 $RC
}

testProductDataRows() {
	C=`wc -l $SHUNIT_TMPDIR/$PRODUCTFILE | cut -d " " -f 1`
	assertEquals "Check number of rows in $PRODUCTFILE" 1 $C
}

testSalesDataExists() {
	if [[ -f "$SHUNIT_TMPDIR/$SALESFILE" ]]; then
		RC=1
	else
		RC=0
	fi
	assertEquals "Check $SALESFILE exists" 1 $RC
}

testSalesDataOnly() {
	mkdir $SHUNIT_TMPDIR/l
	tsdss-datagen -d $SHUNIT_TMPDIR/l -t sales
	assertEquals "create sales data file" 0 $?

	if [[ -f "$SHUNIT_TMPDIR/l/$SALESFILE" ]]; then
		RC=1
	else
		RC=0
	fi
	assertEquals "Check $SALESFILE exists" 1 $RC
}

testStoreDataExists() {
	if [[ -f "$SHUNIT_TMPDIR/$STOREFILE" ]]; then
		RC=1
	else
		RC=0
	fi
	assertEquals "Check $STOREFILE exists" 1 $RC
}

testStoreDataOnly() {
	mkdir $SHUNIT_TMPDIR/s
	tsdss-datagen -d $SHUNIT_TMPDIR/s -t store
	assertEquals "create store data file" 0 $?

	if [[ -f "$SHUNIT_TMPDIR/s/$STOREFILE" ]]; then
		RC=1
	else
		RC=0
	fi
	assertEquals "Check $STOREFILE exists" 1 $RC
}

testStoreDataRows() {
	C=`wc -l $SHUNIT_TMPDIR/$STOREFILE | cut -d " " -f 1`
	assertEquals "Check number of rows in $STOREFILE" 50 $C
}

testTimeDataExists() {
	if [[ -f "$SHUNIT_TMPDIR/$TIMEFILE" ]]; then
		RC=1
	else
		RC=0
	fi
	assertEquals "Check $TIMEFILE exists" 1 $RC
}

testTimeDataOnly() {
	mkdir $SHUNIT_TMPDIR/t
	tsdss-datagen -d $SHUNIT_TMPDIR/t -t time
	assertEquals "create time data file" 0 $?

	if [[ -f "$SHUNIT_TMPDIR/t/$TIMEFILE" ]]; then
		RC=1
	else
		RC=0
	fi
	assertEquals "Check $TIMEFILE exists" 1 $RC
}

testTimeDataRows() {
	C=`wc -l $SHUNIT_TMPDIR/$TIMEFILE | cut -d " " -f 1`
	assertEquals "Check number of rows in $TIMEFILE" 365 $C
}

. `which shunit2`
