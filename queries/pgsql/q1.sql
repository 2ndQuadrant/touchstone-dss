:s
:p
SELECT sum(units * unit_price), state
FROM sales, store
WHERE sales.store_id = store.id
GROUP BY state
ORDER BY state;
:e
