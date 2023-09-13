-- Keep a log of any SQL queries you execute as you solve the mystery.

-- read description about crime
SELECT * FROM crime_scene_reports WHERE day = 28 AND month = 7 AND year = 2020 AND street = "Chamberlin Street";

-- the crime report said three witnesses were inteviewed and all them mentions the couthouse
SELECT * FROM interviews WHERE day = 28 AND month = 7 AND year = 2020 AND transcript LIKE "%courthouse%";

-- first witness saw the thief in the courthouse park within ten minutes after the theft
SELECT * FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND year = 2020 AND hour = 10 AND minute > 15 AND minute < 25;

-- second witness saw the thief withdrawing money in the ATM on "Fifer Street"
SELECT * FROM atm_transactions WHERE day = 28 AND month = 7 AND year = 2020 AND atm_location = "Fifer Street";

-- third witness saw the thief calling someone for less than one minute
SELECT * FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2020 AND duration < 60;

-- searching for people intersaction between caller, atm transaction and license plate. the result was 2 suspects. IDs (514354, 686048)
SELECT *
FROM people AS p
JOIN bank_accounts AS ba ON p.id = ba.person_id
WHERE ba.account_number IN (
    SELECT account_number
    FROM atm_transactions
    WHERE day = 28 AND month = 7 AND year = 2020 AND atm_location = "Fifer Street"
) AND p.phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE day = 28 AND month = 7 AND year = 2020 AND duration < 60
) AND p.license_plate IN (
    SELECT license_plate
    FROM courthouse_security_logs
    WHERE day = 28 AND month = 7 AND year = 2020 AND hour = 10 AND minute > 15 AND minute < 25
);

-- according to third witness the plan of thief was to take the earliest flight out of Fiftyville tomorrow
SELECT * FROM flights AS f JOIN airports AS a ON a.id = f.origin_airport_id WHERE a.city = "Fiftyville" AND f.day = 29 AND f.month = 7 AND f.year = 2020 ORDER BY f.hour ASC, f.minute ASC;

-- the id of earliest flight out of Fiftyville on July 29, 2020 is 36. so check if suspects was in the flight
SELECT *
FROM passengers AS ps
JOIN people AS p ON p.passport_number = ps.passport_number
WHERE p.id IN (514354, 686048) AND ps.flight_id = 36;

-- ANSWER 1: THIEF
-- id       | name      | phone_number      | passport_number   | license_plate
-- 686048   | Ernest    | (367) 555-5533    | 5773159633        | 94KL13X

-- find destination
SELECT *
FROM airports AS a
WHERE a.id IN (
    SELECT destination_airport_id FROM flights WHERE id = 36
);

-- ANSWER 2: ESCAPED TO
-- id   | abbreviation  | full_name         | city
-- 4    | LHR           | Heathrow Airport  | London

-- find the reciever of calling to know who sis the accomplice
SELECT *
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls AS pc
    WHERE caller = "(367) 555-5533" AND day = 28 AND month = 7 AND year = 2020 AND duration < 60
);

-- ANSWER 3: ACCOMPLICE
-- id       | name      | phone_number      | passport_number   | license_plate
-- 864400   | Berthold  | (375) 555-8161    |                   | 4V16VO0