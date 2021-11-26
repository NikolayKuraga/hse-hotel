/* stored functions PostgreSQL server */

-- check if a database with a given name exists
CREATE OR REPLACE FUNCTION check_db(dbname text) RETURNS BOOL AS $$
BEGIN
     RETURN (SELECT CASE
                        WHEN
                            (SELECT TRUE
                               FROM pg_database
                              WHERE datname=dbname)
                        THEN
                            TRUE
                        ELSE
                            FALSE
                        END);
END;
$$ LANGUAGE plpgsql;

-- create a database with a given name
-- with all necessary tables, triggers, trigger functions and an index
CREATE OR REPLACE FUNCTION create_db(dbname text) RETURNS VOID AS $$
BEGIN
    PERFORM dblink_exec('dbname=client port=5432 host=127.0.0.1 user=client password=client',
        'CREATE DATABASE ' || quote_ident(dbname));
    
    PERFORM dblink_exec('dbname=' || quote_ident(dbname) || ' port=5432 host=127.0.0.1 user=client password=client',
        'CREATE TABLE guest(
            guest_id serial PRIMARY KEY,
            last_name VARCHAR(30) NOT null,
            first_name VARCHAR(20) NOT null,
            patronimic VARCHAR(20),
            passport_series VARCHAR(4) NOT null
            CONSTRAINT valid_guest_passport_series 
            CHECK (passport_series ~ ''\d{4}''),
            passport_number VARCHAR(6) NOT null
            CONSTRAINT valid_guest_passport_number 
            CHECK (passport_number ~ ''\d{6}''),
            CONSTRAINT unique_guest_passport UNIQUE 
            (passport_series, passport_number),
            phone VARCHAR(10)
            CONSTRAINT valid_guest_phone_number 
            CHECK (phone ~ ''\d{10}''))');

    PERFORM dblink_exec('dbname=' || quote_ident(dbname) || ' port=5432 host=127.0.0.1 user=client password=client',
        'CREATE TABLE hotel_room(
            hotel_room_id INTEGER PRIMARY KEY,
            price_per_day NUMERIC(7, 2) NOT null
            CHECK (price_per_day > 0),
            number_of_rooms INTEGER DEFAULT 1
            CHECK (number_of_rooms > 0),
            area INTEGER NOT null
            CHECK (area > 0),
            service_class VARCHAR(8) DEFAULT ''standard''
            CONSTRAINT valid_service_class
            CHECK (service_class IN (''standard'', ''comfort'', ''luxury'')),
            kitchen BOOL DEFAULT FALSE)');

    PERFORM dblink_exec('dbname=' || quote_ident(dbname) || ' port=5432 host=127.0.0.1 user=client password=client',
        'CREATE TABLE booking(
            booking_id SERIAL PRIMARY KEY,
            arrival DATE NOT null,
            departure DATE NOT null
            CONSTRAINT valid_arrival_departure_dates 
            CHECK(departure > arrival),
            booking_date DATE DEFAULT CURRENT_DATE,
            CONSTRAINT valid_booking_date 
            CHECK(booking_date <= arrival),
            hotel_room_id INTEGER REFERENCES hotel_room
            ON DELETE CASCADE
            ON UPDATE CASCADE,
            CONSTRAINT valid_booking UNIQUE (arrival, departure, hotel_room_id),
            total_cost NUMERIC(8, 2)
            CHECK (total_cost > 0),
            bank_card VARCHAR(19)
            CONSTRAINT valid_card CHECK (bank_card ~ ''\d{13, 19}''))');

    PERFORM dblink_exec('dbname=' || quote_ident(dbname) || ' port=5432 host=127.0.0.1 user=client password=client',
        'CREATE TABLE booking_guest(
        booking_id INTEGER REFERENCES booking
        ON DELETE CASCADE,
        guest_id INTEGER REFERENCES guest
        ON DELETE CASCADE,
        PRIMARY KEY (booking_id, guest_id))');

    PERFORM dblink_exec('dbname=' || quote_ident(dbname) || ' port=5432 host=127.0.0.1 user=client password=client',
        'CREATE OR REPLACE FUNCTION is_room_available()
            RETURNS trigger
                LANGUAGE plpgsql
                AS $is_room_available$
            BEGIN
            IF EXISTS (SELECT booking_id FROM booking
                WHERE (NEW.hotel_room_id = booking.hotel_room_id AND
                    (NEW.arrival, NEW.departure) OVERLAPS (booking.arrival, booking.departure) AND
                    NEW.booking_id != booking.booking_id))
            THEN
                RAISE EXCEPTION ''booking dates cannot overlap for the same room'';
            END IF;
            RETURN NEW;
            END
            $is_room_available$;');

    PERFORM dblink_exec('dbname=' || quote_ident(dbname) || ' port=5432 host=127.0.0.1 user=client password=client',
        'CREATE TRIGGER available_room_trigger
        BEFORE INSERT OR UPDATE OF arrival, departure, hotel_room_id
        ON booking
        FOR EACH ROW
        EXECUTE PROCEDURE is_room_available();');

    PERFORM dblink_exec('dbname=' || quote_ident(dbname) || ' port=5432 host=127.0.0.1 user=client password=client',
        'CREATE OR REPLACE FUNCTION calc_cost()
        RETURNS trigger
        LANGUAGE plpgsql
        AS $calc_cost$
        BEGIN
        NEW.total_cost := (SELECT hotel_room.price_per_day *
                            (NEW.departure - NEW.arrival)
                            FROM hotel_room
                            WHERE NEW.hotel_room_id = hotel_room.hotel_room_id);
        RETURN NEW;
        END
        $calc_cost$;');

    PERFORM dblink_exec('dbname=' || quote_ident(dbname) || ' port=5432 host=127.0.0.1 user=client password=client',
        'CREATE TRIGGER cost_trigger
        BEFORE INSERT OR UPDATE OF arrival, departure, hotel_room_id
        ON booking
        FOR EACH ROW
        EXECUTE PROCEDURE calc_cost();');
        
    PERFORM dblink_exec('dbname=' || quote_ident(dbname) || ' port=5432 host=127.0.0.1 user=client password=client',
        'CREATE INDEX guest_name ON guest(last_name, first_name, patronimic);');

END;
$$ LANGUAGE plpgsql;

-- drop the database with a given name
CREATE OR REPLACE FUNCTION drop_db(dbname text) RETURNS VOID AS $$
BEGIN
     PERFORM dblink_exec('dbname=client port=5432 host=127.0.0.1 user=client password=client',
                         'DROP DATABASE ' || quote_ident(dbname));
END;
$$ LANGUAGE plpgsql;

-- query to find free rooms for dates specified by the user
CREATE OR REPLACE FUNCTION find_free_rooms(dbname text, arr text, dep text) RETURNS TABLE(
    hotel_room_id INTEGER,
    price_per_day NUMERIC(7, 2),
    number_of_rooms INTEGER,
    area INTEGER,
    service_class VARCHAR(8),
    kitchen BOOL) AS
$$
BEGIN
    PERFORM dblink_connect('connection', 'dbname=' || quote_ident(dbname) || ' port=5432 host=127.0.0.1 user=client password=client');
    RETURN QUERY SELECT * FROM dblink('connection', 
        'SELECT * FROM hotel_room AS r
        WHERE r.hotel_room_id NOT IN
        (SELECT b.hotel_room_id
        FROM booking AS b
        WHERE (' || quote_literal(arr) || '::DATE, ' || quote_literal(dep) || '::DATE)
        OVERLAPS (b.arrival, b.departure));') AS
        (hotel_room_id INTEGER,
        price_per_day NUMERIC(7, 2),
        number_of_rooms INTEGER,
        area INTEGER,
        service_class VARCHAR(8),
        kitchen BOOL);
    PERFORM dblink_disconnect('connection');
END;
$$ LANGUAGE plpgsql;

-- query to find a guest and their bookings 
-- by their last name and first name specified by the user
CREATE OR REPLACE FUNCTION find_guest(dbname text, 
    lst_name VARCHAR(30), frst_name VARCHAR(20)) RETURNS TABLE(
    last_name VARCHAR(30),
    first_name VARCHAR(20),
    patronimic VARCHAR(20),
    arrival DATE,
    departure DATE,
    hotel_room_id INTEGER,
    total_cost NUMERIC(8, 2)) AS
$$
BEGIN
    PERFORM dblink_connect('connection', 'dbname=' || quote_ident(dbname) || ' port=5432 host=127.0.0.1 user=client password=client');
    RETURN QUERY SELECT * FROM dblink('connection', 
        'SELECT guest.last_name, guest.first_name, guest.patronimic,
        booking.arrival, booking.departure, booking.hotel_room_id, booking.total_cost
        FROM guest, booking, booking_guest
        WHERE guest.guest_id = booking_guest.guest_id AND
        booking_guest.booking_id = booking.booking_id AND
        guest.last_name = ' || quote_literal(lst_name) || ' AND
        guest.first_name = ' || quote_literal(frst_name) || ';') AS
        (last_name VARCHAR(30),
        first_name VARCHAR(20),
        patronimic VARCHAR(20),
        arrival DATE,
        departure DATE,
        hotel_room_id INTEGER,
        total_cost NUMERIC(8, 2));
    PERFORM dblink_disconnect('connection');
END;
$$ LANGUAGE plpgsql;

-- query to delete a guest
-- by their last name and first name specified by the user
CREATE OR REPLACE FUNCTION delete_guest(dbname text, 
    lst_name VARCHAR(30), frst_name VARCHAR(20)) RETURNS VOID AS
$$
BEGIN
    PERFORM dblink_connect('connection', 'dbname=' || quote_ident(dbname) || ' port=5432 host=127.0.0.1 user=client password=client');
    PERFORM dblink('connection',
        'DELETE FROM guest
        WHERE guest.last_name = ' || quote_literal(lst_name) || ' AND
        guest.first_name = ' || quote_literal(frst_name) || ';');
    PERFORM dblink_disconnect('connection');
END;
$$ LANGUAGE plpgsql;
