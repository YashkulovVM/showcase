--Все торговцы и что они продают
SELECT region_name AS Регион, trader_name AS Торговец, comm_name AS Товар, price AS Цена
FROM(
prices p
JOIN traders t ON
t.trader_id = p.trader_id
JOIN commodities c ON
c.comm_id = p.comm_id
JOIN regions r ON r.region_id = t.region_id
)
ORDER BY region_name, trader_name, comm_name, price DESC;

--Где самая высокая цена на Small Arms?
SELECT s.star_name System, r.region_name region, t.trader_name trader, c.comm_name as commodity, p.price 
FROM prices p
JOIN commodities c ON c.comm_id = p.comm_id 
JOIN traders t ON t.trader_id = p.trader_id
JOIN regions r ON r.region_id = t.region_id
JOIN systems s ON s.star_id = r.star_id
WHERE comm_name = 'Small Arms'
ORDER BY price DESC;

--Разброс цен для каждого товара в системе Drake
SELECT
    c.comm_name AS commodity,
    MIN(p.price) AS min_price,
    MAX(p.price) AS max_price,
    MAX(p.price) - MIN(p.price) AS price_spread
FROM prices p
JOIN commodities c ON c.comm_id = p.comm_id
JOIN traders t ON t.trader_id = p.trader_id 
JOIN regions r ON t.region_id = r.region_id
JOIN systems s ON r.star_id = s.star_id
WHERE s.star_name = 'DRAKE'
GROUP BY c.comm_id, c.comm_name
ORDER BY price_spread DESC, commodity;

--Чем выгоднее торговать? Разница в процентах и в кредитах (внутренняя валюта в игре)
SELECT
    c.comm_name,
    MIN(p.price) AS min_price,
    MAX(p.price) AS max_price,
    MAX(p.price) - MIN(p.price) AS price_difference,
    ROUND(
        100.0 * (MAX(p.price) - MIN(p.price))
        / NULLIF(MIN(p.price), 0),
        1
    ) AS difference_percent
FROM prices p
JOIN commodities c ON c.comm_id = p.comm_id
GROUP BY c.comm_id, c.comm_name
ORDER BY difference_percent DESC NULLS LAST;


--Где товар Mining Equipment дешевле своей средней цены (повсюду) хотя бы на 10%?
SELECT
    s.star_name,
    r.region_name,
    t.trader_name,
    c.comm_name,
    p.price,
    ROUND(a.avg_price, 1) AS avg_price,
    ROUND(
        100.0 * (a.avg_price - p.price)
        / NULLIF(a.avg_price, 0),
        1
    ) AS below_average_percent
FROM prices p
JOIN commodities c ON c.comm_id = p.comm_id
JOIN traders t ON t.trader_id = p.trader_id
JOIN regions r ON r.region_id = t.region_id
JOIN systems s ON s.star_id = r.star_id
JOIN (
    SELECT comm_id, AVG(price) AS avg_price
    FROM prices
    GROUP BY comm_id
) a ON a.comm_id = p.comm_id
WHERE p.price <= a.avg_price * 0.9 AND c.comm_name = 'Mining Equipment'
ORDER BY below_average_percent DESC;

--Где достигается минимальная цена каждого товара?
SELECT
    c.comm_name,
    s.star_name,
    r.region_name,
    t.trader_name,
    p.price
FROM prices p
JOIN commodities c ON c.comm_id = p.comm_id
JOIN traders t ON t.trader_id = p.trader_id
JOIN regions r ON r.region_id = t.region_id
JOIN systems s ON s.star_id = r.star_id
WHERE p.price = (
    SELECT MIN(p2.price)
    FROM prices p2
    WHERE p2.comm_id = p.comm_id
)
ORDER BY c.comm_name, s.star_name, t.trader_name;


--У каких товаров внутри одной системы разброс цен больше 20%?
SELECT
    s.star_name,
    c.comm_name,
    COUNT(*) AS traders_count,
    MIN(p.price) AS min_price,
    MAX(p.price) AS max_price,
    ROUND(
        100.0 * (MAX(p.price) - MIN(p.price))
        / NULLIF(MIN(p.price), 0),
        1
    ) AS difference_percent
FROM prices p
JOIN commodities c ON c.comm_id = p.comm_id
JOIN traders t ON t.trader_id = p.trader_id
JOIN regions r ON r.region_id = t.region_id
JOIN systems s ON s.star_id = r.star_id
GROUP BY
    s.star_id,
    s.star_name,
    c.comm_id,
    c.comm_name
HAVING
    COUNT(*) > 1
    AND MAX(p.price) > MIN(p.price) * 1.2
ORDER BY difference_percent DESC NULLS LAST;


/* У меня в трюме:
 * 25 единиц Camdon Enzyme,
 * 150 единиц Ramen,
 * 50 единиц Cybernetic Implants.
 * Хочу найти топ-3 мест, где мне профитнее всего продать всё одновременно
 */

WITH cargo_value AS (
    SELECT
        s.star_name,
        r.region_name,
        t.trader_id,
        t.trader_name,
        SUM(
            CASE c.comm_name
                WHEN 'Camdon Enzyme' THEN p.price * 25
                WHEN 'Ramen' THEN p.price * 150
                WHEN 'Cybernetic Implants' THEN p.price * 50
            END
        ) AS total_revenue
    FROM prices p
    JOIN commodities c ON c.comm_id = p.comm_id
    JOIN traders t ON t.trader_id = p.trader_id
    JOIN regions r ON r.region_id = t.region_id
    JOIN systems s ON s.star_id = r.star_id
    WHERE c.comm_name IN (
        'Camdon Enzyme',
        'Ramen',
        'Cybernetic Implants'
    )
    GROUP BY
        s.star_name,
        r.region_name,
        t.trader_id,
        t.trader_name
    HAVING COUNT(*) = 3
)
SELECT
    star_name,
    region_name,
    trader_name,
    total_revenue,
    ROUND(
        100.0 * (
            total_revenue
            / NULLIF((SELECT AVG(total_revenue) FROM cargo_value), 0)
            - 1
        ),
        2
    ) AS above_average_percent
FROM cargo_value
WHERE ROUND(
        100.0 * (
            total_revenue
            / NULLIF((SELECT AVG(total_revenue) FROM cargo_value), 0)
            - 1
        ),
        2
    ) > 0
ORDER BY total_revenue DESC
LIMIT 3;