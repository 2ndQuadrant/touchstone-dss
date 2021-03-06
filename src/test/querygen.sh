#! /bin/sh
#
# Copyright 2017 PostgreSQL Global Development Group
#

oneTimeSetUp() {
	export PATH=$PWD/../bin:$PATH
    export HOMEDIR=`dirname $0`
    export LD_LIBRARY_PATH="..;/usr/local/lib"
}

testQuerygenAnalyze() {
	tsdss-querygen -c ${HOMEDIR}/../../queries/pgsql/pgsql.conf -f pgsql \
			-i ${HOMEDIR}/../../queries/pgsql -o $SHUNIT_TMPDIR -a
	assertEquals "querygen analyze" 0 $?
}

testQuerygenDBMSpgsql() {
	tsdss-querygen -c ${HOMEDIR}/../../queries/pgsql/pgsql.conf -f pgsql \
			-i ${HOMEDIR}/../../queries/pgsql -o $SHUNIT_TMPDIR
	assertEquals "querygen pgsql" 0 $?
}

testQuerygenPlan() {
	tsdss-querygen -c ${HOMEDIR}/../../queries/pgsql/pgsql.conf -f pgsql \
			-i ${HOMEDIR}/../../queries/pgsql -o $SHUNIT_TMPDIR -p
	assertEquals "querygen plan" 0 $?
}

testQuerygenPlanAnalyzeConflict() {
	tsdss-querygen -c ${HOMEDIR}/../../queries/pgsql/pgsql.conf -f pgsql \
			-i ${HOMEDIR}/../../queries/pgsql -o $SHUNIT_TMPDIR -a -p
	assertEquals "querygen plan-analyze conflict" 4 $?
}

testQuerygenParamFormatUnkown() {
	tsdss-querygen -c ${HOMEDIR}/../../queries/pgsql/pgsql.conf -f a \
			-i ${HOMEDIR}/../../queries/pgsql
	assertEquals "querygen pgsql" 3 $?
}

testQuerygenParamIndir() {
	tsdss-querygen -c ${HOMEDIR}/../../queries/pgsql/pgsql.conf -f pgsql
	assertEquals "querygen indir" 4 $?
}

testQuerygenParamOutdir() {
	cd $SHUNIT_TMPDIR
	tsdss-querygen -c ${HOMEDIR}/../../queries/pgsql/pgsql.conf -f pgsql \
			-i ${HOMEDIR}/../../queries/pgsql
	assertEquals "querygen outdir" 0 $?
}

. `which shunit2`
