#! /bin/sh
#
# Copyright 2016-2017 PostgreSQL Global Development Group
#

oneTimeSetUp() {
	export PATH=$PWD/../bin:$PWD/../scripts:$PWD/../scripts/pgsql:$PATH
	export PGDATA="$SHUNIT_TMPDIR/pgdata"
	export PGDATABASE="tsdss"
	export PGHOST=$PGDATA
}

testPgsqlSimpleTest() {
	PARAMS="-c listen_addresses='' -c unix_socket_directories='$PGDATA' "
	PARAMS="$PARAMS -c client_min_messages='debug1'"
	PARAMS="-P \"$PARAMS\""

	eval tsdss-run-workload -g -D pgsql -o $SHUNIT_TMPDIR/r  \
			-t ../../queries/pgsql -i $SHUNIT_TMPDIR $PARAMS
	assertEquals "Workload" 0 $?
}

. `which shunit2`
