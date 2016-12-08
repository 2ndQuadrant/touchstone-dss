#! /bin/sh
#
# Copyright 2016 PostgreSQL Global Development Group
#

PRODUCTFILE="product.data"
SALESFILE="sales.data"
STOREFILE="store.data"
TIMEFILE="time.data"

oneTimeSetUp() {
	TMPDIR=`mktemp -d`

	../bin/tsdss-datagen -d $TMPDIR
	assertEquals "create all data files" 0 $?
}

oneTimeTearDown() {
	rm -rf $TMPDIR
}

testProductDataExists() {
	if [[ -f $TMPDIR/$PRODUCTFILE ]]; then
		RC=1
	else
		RC=0
	fi
	assertEquals "Check $PRODUCTFILE exists" 1 $RC
}

testProductDataOnly() {
	mkdir $TMPDIR/p
	../bin/tsdss-datagen -d $TMPDIR/p -t product
	assertEquals "create product data file" 0 $?

	if [[ -f $TMPDIR/p/$PRODUCTFILE ]]; then
		RC=1
	else
		RC=0
	fi
	assertEquals "Check $PRODUCTFILE exists" 1 $RC
}

testProductDataRows() {
	C=`wc -l $TMPDIR/$PRODUCTFILE | cut -d " " -f 1`
	assertEquals "Check number of rows in $PRODUCTFILE" 1 $C
}

testSalesDataExists() {
	if [[ -f $TMPDIR/$SALESFILE ]]; then
		RC=1
	else
		RC=0
	fi
	assertEquals "Check $SALESFILE exists" 1 $RC
}

testSalesDataOnly() {
	mkdir $TMPDIR/l
	../bin/tsdss-datagen -d $TMPDIR/l -t sales
	assertEquals "create sales data file" 0 $?

	if [[ -f $TMPDIR/l/$SALESFILE ]]; then
		RC=1
	else
		RC=0
	fi
	assertEquals "Check $SALESFILE exists" 1 $RC
}

testStoreDataExists() {
	if [[ -f $TMPDIR/$STOREFILE ]]; then
		RC=1
	else
		RC=0
	fi
	assertEquals "Check $STOREFILE exists" 1 $RC
}

testStoreDataOnly() {
	mkdir $TMPDIR/s
	../bin/tsdss-datagen -d $TMPDIR/s -t store
	assertEquals "create store data file" 0 $?

	if [[ -f $TMPDIR/s/$STOREFILE ]]; then
		RC=1
	else
		RC=0
	fi
	assertEquals "Check $STOREFILE exists" 1 $RC
}

testStoreDataRows() {
	C=`wc -l $TMPDIR/$STOREFILE | cut -d " " -f 1`
	assertEquals "Check number of rows in $STOREFILE" 50 $C
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
