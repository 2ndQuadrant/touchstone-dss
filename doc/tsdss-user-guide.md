% Touchstone Decision Support Systems Workload User Guide

Using the Test Kit
==================

### PostgreSQL Environment Variables

* *PGDATABASE=tsdss* - This is the database name to use.
* *PGDATA=/tmp/pgdata* - This defines where the PostgreSQL instance will be
  created.

Quick Start
===========

Only one command needs to be issued to run a complete test:

    tsdss-run-workload -D pgsql -o /tmp/results -t queries/pgsql -g

This will run the generate the data files (`-g`) for a default sized 1GB scale
factor database load with PostgreSQL and record the results of the test in
_/tmp/results_.  The templates in _queries/pgsql_ will also be used for the
query power test.

Database Management Systems Specific Notes
==========================================

Environment variables are used to test specific DBMS features instead of adding
addition command line flags.

PostgreSQL
----------

### Table Partitioning

Use table inheritance to partition the **sales** fact table by month, set the
following environment variable:

    export PG_PARTITION="inheritance"

Use native declarative partitioning to partition the **sales** fact table by
month, set the following environment variable, requires version 10:

    export PG_PARTITION="native"
