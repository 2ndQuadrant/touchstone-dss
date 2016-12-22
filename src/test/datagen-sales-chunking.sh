#! /bin/sh
#
# Copyright 2016 PostgreSQL Global Development Group
#

oneTimeSetUp() {
	export PATH=$PWD/../bin:$PATH

	tsdss-datagen -d $SHUNIT_TMPDIR -t sales -S 0
	assertEquals "create single data file" 0 $?

	tsdss-datagen -d $SHUNIT_TMPDIR -t sales -S 0 -c 2
	assertEquals "create multiple data files" 0 $?
}

oneTimeTearDsetUp() {
	cd $SHUNIT_TMPDIR
}

testLineCount() {
	C0=`wc -l $SHUNIT_TMPDIR/sales.data | cut -f 1 -d " "`
	C1=`wc -l $SHUNIT_TMPDIR/sales.data.* | tail -n 1 | awk '{print $1}'`
	assertEquals "Equal Lines" $C0 $C1
}

testFirstLine() {
	L0=`head -n 1 $SHUNIT_TMPDIR/sales.data`
	L1=`head -n 1 $SHUNIT_TMPDIR/sales.data.1`
	assertEquals "Equal First Lines" "$L0" "$L1"
}

testMidLine1() {
	L0=`tail -n 1 $SHUNIT_TMPDIR/sales.data.1`

	C=`wc -l $SHUNIT_TMPDIR/sales.data.1 | cut -f 1 -d " "`
	L1=`head -n $C $SHUNIT_TMPDIR/sales.data | tail -n 1`
	assertEquals "Equal Middle Line 1" "$L0" "$L1"
}

testMidLine2() {
	L0=`head -n 1 $SHUNIT_TMPDIR/sales.data.2`

	C=`wc -l $SHUNIT_TMPDIR/sales.data.1 | cut -f 1 -d " "`
	L1=`head -n $(($C + 1)) $SHUNIT_TMPDIR/sales.data | tail -n 1`
	assertEquals "Equal Middle Line 2" "$L0" "$L1"
}

testLastLine() {
	L0=`tail -n 1 $SHUNIT_TMPDIR/sales.data`
	L1=`tail -n 1 $SHUNIT_TMPDIR/sales.data.2`
	assertEquals "Equal Last Lines" "$L0" "$L1"
}

. `which shunit2`
