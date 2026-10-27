DROP TABLE IF EXISTS prices, traders, commodities, regions, systems;
create table systems (
	star_id		INTEGER generated always as identity primary key,
	star_name 	TEXT unique NOT NULL -- CETO / UNION / ZHARKOV / DRAKE / KHIONE / KHAIT NEBULA /
	 -- вроде бы нет торговли в системах: AETHON / KHAIT DOMINION / RHAK HOMEWORLDS / USHAK SANCTUARY
);

create table regions (
	star_id		INTEGER not null  references systems (star_id),
	region_id 	INTEGER generated always as identity primary key,
	region_name	TEXT not null,
	unique (star_id, region_name)
);

create table traders (
	trader_id	INTEGER generated always as identity primary key,
	trader_name	TEXT NOT NULL,
	region_id	INTEGER not null references regions (region_id)
);

create table commodities (
	comm_id		INTEGER generated always as identity primary key,
	comm_name	TEXT unique NOT NULL
);
create table prices (
	trader_id 	INTEGER references traders (trader_id),
	comm_id	  	INTEGER references commodities (comm_id),
	price	 	INTEGER NOT null check(price >= 0),
	primary key(trader_id, comm_id)
);


