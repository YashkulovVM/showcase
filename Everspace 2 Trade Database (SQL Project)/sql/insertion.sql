BEGIN;

TRUNCATE
    prices, traders, commodities, regions, systems
RESTART IDENTITY;

INSERT INTO
	systems (star_name)
VALUES ('CETO'),('UNION'),('DRAKE'),('ZHARKOV'),('KHAIT NEBULA'),('KHIONE');

INSERT INTO
	regions (star_id, region_name)
SELECT DISTINCT s.star_id, r.region_name
FROM raw_prices r
LEFT JOIN systems s ON
	s.star_name = r.star_name;

INSERT INTO
	traders (trader_name, region_id)
SELECT DISTINCT t.trader_name, r.region_id
FROM raw_prices t
LEFT JOIN systems s ON
	t.star_name = s.star_name
LEFT JOIN regions r ON
	t.region_name = r.region_name
AND s.star_id = r.star_id;


INSERT INTO
	commodities (comm_name)
VALUES
	('Nano Fibers'), ('Ramen'),('Seeds'),('Small Arms'),('Clothing'),('Solar Panels'),('Mining Equipment'),('Medicine'),('Liquor'),('Earth Wine'),('Cybernetic Implants'),('Camdon Enzyme');

INSERT INTO
	prices (trader_id, comm_id, price)
SELECT t.trader_id, c.comm_id, p.price
FROM raw_prices p
LEFT JOIN systems s ON
s.star_name = p.star_name
LEFT JOIN regions r ON
r.region_name = p.region_name
AND s.star_id = r.star_id
LEFT JOIN traders t ON
	p.trader_name = t.trader_name
AND r.region_id = t.region_id
LEFT JOIN commodities c ON
	p.comm_name = c.comm_name;

COMMIT;