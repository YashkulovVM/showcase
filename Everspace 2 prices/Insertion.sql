TRUNCATE prices, traders, commodities, regions, systems RESTART IDENTITY;

INSERT INTO
	systems (star_name)
VALUES ('CETO'),('UNION'),('DRAKE'),('ZHARKOV'),('KHAIT NEBULA'),('KHIONE');

INSERT INTO
	regions (star_id, region_name)
SELECT s.star_id, r.region_name
FROM(
VALUES
	('CETO', 'Ceto Orbit'),('CETO', 'Siren''s Sea'),('CETO', 'Nemertes'),('CETO', 'Alcyone Station'),('CETO', 'Charybdis Bowl'),('CETO', 'Nepthys Plains'),('CETO', 'Planetary Debris'),('CETO', 'Union Bridge')
	) AS r(star_name, region_name)
JOIN systems s ON
s.star_name = r.star_name;

INSERT INTO
	traders (trader_name, region_id)
SELECT t.trader_name, r.region_id
FROM(
VALUES
	('Colonial Research Station', 'CETO', 'Ceto Orbit'),('Flying Dutchess', 'CETO', 'Siren''s Sea'),('Trading Outpost', 'CETO', 'Union Bridge'),('Main Station', 'CETO', 'Alcyone Station'),('Refinery', 'CETO', 'Alcyone Station'),('G&B Scrapyard', 'CETO', 'Charibdys Bowl')
) AS t(trader_name, star_name, region_name)
JOIN systems s ON
t.star_name = s.star_name
JOIN regions r ON
t.region_name = r.region_name
AND s.star_id = r.star_id;

SELECT *
FROM systems;

SELECT *
FROM regions;

SELECT *
FROM traders;