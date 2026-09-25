# Write your MySQL query statement below
SELECT e.name
FROM Employee e
JOIN (
    SELECT managerId
    FROM Employee
    GROUP BY managerId
    HAVING COUNT(managerId) >= 5
) AS manager ON e.id = manager.managerId;