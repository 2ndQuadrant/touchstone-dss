% Touchstone Decision Support Systems

Table of Contents
=================

* [Table Descriptions](#table-descriptions)
  * [Product Dimension Table](#product-dimension-table)
  * [Sales Fact Table](#sales-fact-table)
  * [Store Dimension Table](#store-dimension-table)
  * [Time Dimension Table](#time-dimension-table)

Table Descriptions
==================

![Schema Diagram](schema.png)

Product Dimension Table
-----------------------

The **product** table consists of a variable number of products.  This is specified to the data generator.

: Product Dimension Table

-------------------------------------------------------------------------------
Name      Type      Description
--------- --------- -----------------------------------------------------------
id        BIGINT    Primary key, a serially generated number

ean       CHAR(13)  International Article Number
                    [https://en.wikipedia.org/wiki/International_Article_Number](https://en.wikipedia.org/wiki/International_Article_Number)

name      CHAR(20)  Product name, randomly generated string

brand     CHAR(20)  Product brand, randomly generated string

category  CHAR(20)  Product category, randomly generated string
-------------------------------------------------------------------------------

Sales Fact Table
----------------

The **sales** table consists of a variable number of rows.  It generates rows until a specified number of gibibytes is reached.

: Sales Fact Table

------------------------------------
Name        Type     Description
----------- -------- ---------------
product_id  BIGINT   Foreign Key

store_id    BIGINT   Foreign Key

time_id     BIGINT   Foreign Key

units       INTEGER  Units sold

unit_price  NUMERIC  Price per unit
------------------------------------

Store Dimension Table
---------------------

The **store** table consists of a fixed number of store locations.  They represent a physical location where there will be a store in each of the 50 states in the United States.

: Store Dimension Table

---------------------------------------------------------------------
Name          Type         Description
------------  ------------ ------------------------------------------
id            BIGINT       Primary key, a serially generated number

store_number  BIGINT       Matches id for ease of testing

state         VARCHAR(14)  Name of the state

state_abbr    CHAR(2)      Two letter abbreviation of the state name
---------------------------------------------------------------------

Time Dimension Table
--------------------

The **time** table consists of dates with the granularity of days.  A whole calendar year is generated at a time, always starting in the year 2001.  How many years of dates can be specified.

: Time Dimension Table

-------------------------------------------------------------------------------
Name          Type        Description
------------- ----------- -----------------------------------------------------
id            BIGINT      Primary key, the GMT epoch (or ctime) requivalent of
                          the date

date          DATE        The actual date

day           SMALLINT    Day of the month

day_of_week   SMALLINT    Day of the week

month         SMALLINT    The numerical value of the month (1-12)

month_name    VARCHAR(9)  The name of the month

quarter       SMALLINT    The quarter of the year (1-4)

quarter_name  CHAR(2)     The name of the query (e.g. Q1)

year          SMALLINT    The year
-------------------------------------------------------------------------------
