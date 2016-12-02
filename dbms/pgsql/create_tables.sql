-- Copyright 2016 2ndQuadrant, Ltd.
-- Copyright 2016 Mark Wong
--
-- This file is part of Touchstone-DSS.
--
-- Touchstone-DSS is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
--
-- Touchstone-DSS is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with Touchstone-DSS.  If not, see <http://www.gnu.org/licenses/>.

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
