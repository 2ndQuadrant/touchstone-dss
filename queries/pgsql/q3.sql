:s
:p
SELECT category, brand, count(DISTINCT state)
FROM sales, store, product
WHERE sales.store_id = store.id
  AND sales.product_id = product.id
  AND product.category <> ':1'
  AND product.brand NOT LIKE ':2%'
GROUP BY category, brand
ORDER BY category, brand;
:e
