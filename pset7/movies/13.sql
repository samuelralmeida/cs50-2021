-- In 13.sql, write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.
-- Your query should output a table with a single column for the name of each person.
-- There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
-- Kevin Bacon himself should not be included in the resulting list.

SELECT p.name
FROM people AS p
JOIN stars AS s ON s.person_id = p.id
WHERE p.name != "Kevin Bacon" AND s.movie_id IN (
    SELECT m.id
    FROM movies AS m
    JOIN stars AS s ON s.movie_id = m.id
    JOIN people AS p ON p.id = s.person_id
    WHERE p.name = "Kevin Bacon"
);