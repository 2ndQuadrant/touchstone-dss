#! /bin/sh
#
# Copyright 2016-2017 PostgreSQL Global Development Group
#

oneTimeSetUp() {
	export PATH=$PWD/../bin:$PWD/../scripts:$PWD/../scripts/pgsql:$PATH

	export PGUSER="postgres"
	export PGDATABASE="postgres"

	export PGHOST="$SHUNIT_TMPDIR/pgdata"

	PSQL="psql -v ON_ERROR_STOP=1 -XAte -h $PGHOST -U $PGUSER"

	pg_ctl init -D $PGHOST -s -o "-U $PGUSER -A trust"
	assertEquals "create pgdata directory" "0" "$?"

	PARAMS="-c listen_addresses='' -c unix_socket_directories='$PGHOST' "
	PARAMS="$PARAMS -c client_min_messages='debug1'"
	PARAMS="-o \"$PARAMS\""
	eval pg_ctl start -w -D $PGHOST -s $PARAMS
	assertEquals "start postgresql" 0 $?

	tsdss-datagen -d $SHUNIT_TMPDIR -f pgsql
	assertEquals "create data files" 0 $?
}

oneTimeTearDown() {
	pg_ctl stop -w -D $PGHOST -s
	assertEquals "stop postgresql" 0 $?
}

setUp() {
	tsdss-pgsql-create-tables
	assertEquals "create tables" 0 $?
}

tearDown() {
	tsdss-pgsql-drop-tables
	assertEquals "drop tables" 0 $?
}

testPgsqlLoadDatabase() {
	tsdss-pgsql-load-data -i $SHUNIT_TMPDIR
	assertEquals "tsdss-pgsql-load-data" 0 $?
}

testPgsqlLoadDatabaseChunked() {
	tsdss-datagen -d $SHUNIT_TMPDIR -f pgsql -t sales -c 2
	tsdss-pgsql-load-data -i $SHUNIT_TMPDIR -C 2
	assertEquals "tsdss-pgsql-load-data" 0 $?
}

testPgsqlLoadProductTable() {
	$PSQL -c "COPY fact FROM '$SHUNIT_TMPDIR/fact.data';"
	assertEquals "COPY" 0 $?
}

testPgsqlLoadProductTable() {
	$PSQL -c "COPY product FROM '$SHUNIT_TMPDIR/product.data';"
	assertEquals "COPY" 0 $?
}

testPgsqlLoadStoreTable() {
	$PSQL -c "COPY store FROM '$SHUNIT_TMPDIR/store.data';"
	assertEquals "COPY" 0 $?
}

testPgsqlLoadTimeTable() {
	COUNT=`wc -l $SHUNIT_TMPDIR/time.data | cut -f 1 -d " "`
	assertEquals "number of days" 365 $COUNT

	$PSQL -c "COPY time FROM '$SHUNIT_TMPDIR/time.data';"
	assertEquals "COPY" 0 $?
}

. `which shunit2`
