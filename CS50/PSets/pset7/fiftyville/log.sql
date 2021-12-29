-- The theft took place on July 28, 2020 and that it took place on Chamberlin Street
SELECT description FROM crime_scene_reports
WHERE year = 2020 AND month = 7 AND day = 28 AND street = "Chamberlin Street";

-- Interviews were conducted today with three witnesses who were present at the time 
-- Each of their interview transcripts mentions the courthouse
-- Let's see what we can get from the interview table
SELECT name, transcript FROM interviews
WHERE year >= 2020 AND month >= 7 AND day >= 28;

-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. 
-- Let's see what we can get from the courthouse_security_logs table
-- There's probably a 5 min window for perp to leave the premise
SELECT name FROM people 
WHERE license_plate IN
(
  SELECT license_plate FROM courthouse_security_logs
  WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 
  AND minute >= 15 AND minute <= 20 AND activity = "exit"
);


-- Let's look at the ATM data (atm_transactions, bank_accounts)
-- Eugene said it was earlier that morning, at Fifer St.
SELECT name FROM people
WHERE id IN
(
  SELECT person_id FROM bank_accounts
  WHERE account_number IN
  (
    SELECT account_number FROM atm_transactions
    WHERE year = 2020 AND month = 7 AND day = 28
    AND atm_location = "Fifer Street"
  )
);

-- Let's take a look at the flight data
-- Earliest flight out of fiftyville tomorrow
SELECT name FROM people
WHERE passport_number IN
(
  SELECT passport_number FROM passengers
  where flight_id IN
    (
      SELECT flights.id FROM flights
      JOIN airports ON flights.origin_airport_id = airports.id
      WHERE flights.year = 2020 AND flights.month = 7 AND flights.day = 29
      AND flights.hour < 12 AND airports.city = "Fiftyville"
    )
);


SELECT city, full_name FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
JOIN passengers ON flights.id = passengers.flight_id
JOIN people ON passengers.passport_number = people.passport_number
WHERe people.name = "Ernest";

-- Thief asked person on the other end to purchase flight ticket
-- They spoke for less than 1 minute
SELECT name FROM people
WHERE phone_number IN
(
  SELECT caller FROM phone_calls
  WHERE year = 2020 AND month = 7 AND day = 28
  AND duration < 60
);

-- Get Union
SELECT suspects.name, COUNT(*)
FROM
(
  SELECT name FROM people 
  WHERE license_plate IN
  (
    SELECT license_plate FROM courthouse_security_logs
    WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 
    AND minute >= 15 AND minute <= 20 AND activity = "exit"
  )
  UNION ALL
  SELECT name FROM people
  WHERE id IN
  (
    SELECT person_id FROM bank_accounts
    WHERE account_number IN
    (
      SELECT account_number FROM atm_transactions
      WHERE year = 2020 AND month = 7 AND day = 28
      AND atm_location = "Fifer Street"
    )
  )
  UNION ALL
  SELECT name FROM people
  WHERE passport_number IN
  (
    SELECT passport_number FROM passengers
    where flight_id IN
      (
        SELECT flights.id FROM flights
        JOIN airports ON flights.origin_airport_id = airports.id
        WHERE flights.year = 2020 AND flights.month = 7 AND flights.day = 29
        AND flights.hour < 12 AND airports.city = "Fiftyville"
      )
  )
  UNION ALL
  SELECT name FROM people
  WHERE phone_number IN
  (
    SELECT caller FROM phone_calls
    WHERE year = 2020 AND month = 7 AND day = 28
    AND duration < 60
    UNION
    SELECT receiver FROM phone_calls
    WHERE year = 2020 AND month = 7 AND day = 28
    AND duration < 60
  ) 
) AS suspects
GROUP BY name
ORDER BY count(name) DESC LIMIT 5;

-- The accomplice is
SELECT name FROM people
WHERE phone_number IN
(
  SELECT receiver FROM phone_calls
  WHERE caller = "(367) 555-5533" AND year = 2020 AND month = 7 AND day = 28
  AND duration < 60
);