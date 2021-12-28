--List the names of all people who starred in a movie in which Kevin Bacon also starred
SELECT DISTINCT name FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.id IN (
  SELECT movies.id FROM movies
  JOIN stars ON movies.id = stars.movie_id
  JOIN people ON stars.person_id = people.id
  WHERE people.name = "Kevin Bacon"
)
EXCEPT SELECT name FROM people 
WHERE name = "Kevin Bacon";