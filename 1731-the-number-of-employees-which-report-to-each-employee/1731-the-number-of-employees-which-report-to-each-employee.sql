# Write your MySQL query statement below
SELECT mgr.employee_id,
        mgr.name,
        COUNT(sub.reports_to) AS reports_count,
        ROUND(AVG(sub.age)) AS average_age
FROM Employees mgr 
JOIN Employees sub
    ON mgr.employee_id = sub.reports_to
GROUP BY mgr.employee_id , mgr.name
ORDER BY mgr.employee_id;