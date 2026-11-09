\set ON_ERROR_STOP on

BEGIN;

\ir creation.sql

\copy raw_prices (star_name, region_name, trader_name, comm_name, price) FROM '../data/prices_import.csv' WITH (FORMAT csv, HEADER true)

\ir insertion.sql

COMMIT;