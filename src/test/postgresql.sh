#! /bin/sh
#
# Copyright 2016 PostgreSQL Global Development Group
#

export PGUSER="postgres"
export PGDATABASE="postgres"

oneTimeSetUp() {
	PGDATA=`mktemp -d`
	PSQL="psql -v ON_ERROR_STOP=1 -XAte -h $PGDATA -U $PGUSER"

	pg_ctl init -D $PGDATA -s -o "-U $PGUSER -A trust"
	assertEquals "create pgdata directory" "0" "$?"

	pg_ctl start -w -D $PGDATA -s -o "-c listen_addresses='' -c unix_socket_directories='$PGDATA' -c client_min_messages='debug1'" > /dev/null 2>&1
	assertEquals "start postgresql" 0 $?

	../bin/tsdss-datagen -d $PGDATA -f pgsql
	assertEquals "create data files" 0 $?
}

oneTimeTearDown() {
	pg_ctl stop -w -D $PGDATA -s
	assertEquals "stop postgresql" 0 $?

	rm -rf $PGDATA
}

setUp() {
	$PSQL -f ../../dbms/pgsql/create_tables.sql
	assertEquals "create tables" 0 $?
}

tearDown() {
	$PSQL -f ../../dbms/pgsql/drop_tables.sql
	assertEquals "drop tables" 0 $?
}

testPgsqlLoadProductTable() {
	$PSQL -c "COPY product FROM '$PGDATA/product.data';"
	assertEquals "COPY" 0 $?
}

testPgsqlLoadStoreTable() {
	$PSQL -c "COPY store FROM '$PGDATA/store.data';"
	assertEquals "COPY" 0 $?
}

testPgsqlLoadTimeTable() {
	COUNT=`wc -l $PGDATA/time.data | cut -f 1 -d " "`
	assertEquals "number of days" 365 $COUNT

	$PSQL -c "COPY time FROM '$PGDATA/time.data';"
	assertEquals "COPY" 0 $?
}

. `which shunit2`
