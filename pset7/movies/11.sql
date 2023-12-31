-- In 11.sql, write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Chadwick Boseman.

SELECT title
FROM movies AS m
JOIN ratings AS r ON r.movie_id = m.id
JOIN stars AS s ON s.movie_id = m.id
JOIN people AS p ON p.id = s.person_id
WHERE p.name = "Chadwick Boseman"
ORDER BY r.rating DESC
LIMIT 5;