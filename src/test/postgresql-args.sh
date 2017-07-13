#! /bin/sh
#
# Copyright 2016-2017 PostgreSQL Global Development Group
#

oneTimeSetUp() {
	export PATH=$PWD/../bin:$PWD/../scripts:$PWD/../scripts/pgsql:$PATH
}

setUp() {
	export PGDATA=$SHUNIT_TMPDIR
	export PGDATABASE=$USER
}

tearDown() {
	rm -rf $SHUNIT_TMPDIR/r
}

testPgsqlEnvPGDATA() {
	unset PGDATA
	tsdss-run-workload -D pgsql -o $SHUNIT_TMPDIR/r -t ../../queries/pgsql
	assertEquals "Missing PGDATA env" 3 $?
}

testPgsqlEnvPGDATABASE() {
	unset PGDATABASE
	tsdss-run-workload -D pgsql -o $SHUNIT_TMPDIR/r -t ../../queries/pgsql
	assertEquals "Missing PGDATABASE env" 3 $?
}

testPgsqlWorkloadParamTemplate() {
	tsdss-run-workload -D pgsql -o $SHUNIT_TMPDIR/r
	assertEquals "Template parameter" 4 $?
}

. `which shunit2`
