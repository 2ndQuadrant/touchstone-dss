:s
:p
SELECT state, sum(units * unit_price)
FROM sales, store
WHERE sales.store_id = store.id
  AND cast(ts AS DATE) >= ':1'
  AND cast(ts AS DATE) < cast(':1' AS DATE) + INTERVAL '1 YEAR'
GROUP BY state
ORDER BY state;
:e
