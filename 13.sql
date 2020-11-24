SELECT name FROM people
WHERE name != 'Kevin Bacon' AND people.id IN
(SELECT stars.person_id FROM stars
JOIN movies ON movies.id = stars.movie_id
WHERE stars.movie_id IN
(SELECT movies.id FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE people.id IN
(SELECT people.id FROM people
WHERE name = 'Kevin Bacon' AND birth = 1958)))