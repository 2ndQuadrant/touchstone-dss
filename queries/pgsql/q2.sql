:s
:p
SELECT state, year, sum(units * unit_price)
FROM sales, store, time, product
WHERE sales.store_id = store.id
  AND sales.product_id = product.id
  AND sales.time_id = time.id
  AND product.category = ':1'
GROUP BY state, year
ORDER BY state, year;
:e
