-- In 12.sql, write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Johnny Depp.
-- You may assume that there is only one person in the database with the name Helena Bonham Carter.

SELECT m.title
FROM movies AS m
JOIN stars AS s ON s.movie_id = m.id
JOIN people AS p ON p.id = s.person_id
WHERE p.name = "Johnny Depp" AND m.id IN (
    SELECT m.id
    FROM movies AS m
    JOIN stars AS s ON s.movie_id = m.id
    JOIN people AS p ON p.id = s.person_id
    WHERE p.name = "Helena Bonham Carter"
);
