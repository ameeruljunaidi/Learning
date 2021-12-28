--Returns the average energy of songs that are by Drake
SELECT AVG(energy) from songs
JOIN artists ON songs.artist_id = artists.id
WHERE artists.name = "Drake";