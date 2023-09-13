-- In 10.sql, write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.
-- Your query should output a table with a single column for the name of each person.
-- If a person directed more than one movie that received a rating of at least 9.0, they should only appear in your results once.

SELECT DISTINCT(name)
FROM people AS p
JOIN directors AS d ON d.person_id = p.id
JOIN movies AS m ON m.id = d.movie_id
JOIN ratings AS r ON r.movie_id = m.id
WHERE r.rating >= 9;