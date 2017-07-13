#! /bin/sh
#
# Copyright 2017 PostgreSQL Global Development Group
#

oneTimeSetUp() {
	export PATH=$PWD/../bin:$PWD/../scripts:$PWD/../scripts/pgsql:$PATH
}

setUp() {
	mkdir $SHUNIT_TMPDIR/r
}

testResultsAlreadyExists() {
	tsdss-run-workload -D pgsql -o $SHUNIT_TMPDIR/r
	assertEquals "Directory exists" 2 $?
}

testRequireDBMS() {
	tsdss-run-workload -o $SHUNIT_TMPDIR/r_dbms
	assertEquals "Specify DBMS" 1 $?
}

testRequireOutdir() {
	export PGDATA="$SHUNIT_TMPDIR/pgdata"
	export PGDATABASE="tsdss"

	tsdss-run-workload -D pgsql
	assertEquals "Specify output directory" 1 $?
}

testRequireTemplateDir() {
	export PGDATA="$SHUNIT_TMPDIR/pgdata"
	export PGDATABASE="tsdss"

	tsdss-run-workload -D pgsql -o $SHUNIT_TMPDIR/r_template1
	assertEquals "Specify template directory (all)" 4 $?

	tsdss-run-workload -D pgsql -o $SHUNIT_TMPDIR/r_template2 -2
	assertEquals "Specify template directory (power)" 4 $?
}

. `which shunit2`
