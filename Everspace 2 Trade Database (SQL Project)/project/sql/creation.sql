DROP TABLE IF EXISTS raw_prices, prices, traders, commodities, regions, systems;
CREATE TABLE systems (
	star_id INTEGER GENERATED ALWAYS AS IDENTITY PRIMARY KEY, 
	star_name TEXT UNIQUE NOT NULL
-- CETO / UNION / ZHARKOV / DRAKE / KHIONE / KHAIT NEBULA /
-- вроде бы нет торговли в системах: AETHON / KHAIT DOMINION / RHAK HOMEWORLDS / USHAK SANCTUARY
);

CREATE TABLE regions (
	star_id INTEGER NOT NULL REFERENCES systems (star_id), 
	region_id INTEGER GENERATED ALWAYS AS IDENTITY PRIMARY KEY, 
	region_name TEXT NOT NULL, 
	UNIQUE (star_id, region_name)
);

CREATE TABLE traders (
	trader_id INTEGER GENERATED ALWAYS AS IDENTITY PRIMARY KEY, 
	trader_name TEXT NOT NULL, 
	region_id INTEGER NOT NULL REFERENCES regions (region_id),
	UNIQUE (region_id, trader_name)
);

CREATE TABLE commodities (
	comm_id INTEGER GENERATED ALWAYS AS IDENTITY PRIMARY KEY, 
	comm_name TEXT UNIQUE NOT NULL
);
CREATE TABLE prices (
	trader_id INTEGER REFERENCES traders (trader_id), comm_id INTEGER REFERENCES commodities (comm_id), 
	price INTEGER NOT NULL CHECK(price >= 0), 
	PRIMARY KEY(trader_id, comm_id)
);
CREATE TABLE raw_prices (
	star_name	TEXT,	 
	region_name	TEXT,
	trader_name TEXT,
	comm_name	TEXT,
	price		INTEGER
);
