-- Copyright 2016, PostgreSQL Global Development Group

CREATE TABLE time (
    id BIGINT NOT NULL,
    date DATE NOT NULL,
    day SMALLINT NOT NULL,
    day_of_week SMALLINT NOT NULL,
    month SMALLINT NOT NULL,
    month_name VARCHAR(9) NOT NULL,
    quarter SMALLINT NOT NULL,
    quarter_name CHAR(2) NOT NULL,
    year SMALLINT NOT NULL
);
