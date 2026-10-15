WITH NumberGroups AS (
    SELECT 
        num,
        id - ROW_NUMBER() OVER (PARTITION BY num ORDER BY id) AS island_id
    FROM Logs
)
SELECT DISTINCT num AS ConsecutiveNums
FROM NumberGroups
GROUP BY num, island_id
HAVING COUNT(*) >= 3;