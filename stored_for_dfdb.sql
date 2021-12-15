/* stored functions for PostgreSQL server's default database */

-- check if a database with a given name exists
CREATE OR REPLACE FUNCTION check_db(dbname text) RETURNS BOOL AS $check_db$
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
$check_db$ LANGUAGE plpgsql;

-- create a database with a given name with all necessary tables, functions, triggers and an index
CREATE OR REPLACE FUNCTION create_db(dbname text) RETURNS VOID AS $create_db$
BEGIN
    PERFORM dblink_exec('dbname=client port=5432 host=127.0.0.1 user=client password=client',
        'CREATE DATABASE ' || quote_ident(dbname));
    PERFORM dblink_connect('myconn', 'dbname=' || quote_ident(dbname) || ' port=5432 host=127.0.0.1 user=client password=client');
    PERFORM dblink_exec('myconn','BEGIN');
    PERFORM dblink_exec('myconn',
        'CREATE TABLE guest(
            guest_id SERIAL PRIMARY KEY,
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
    PERFORM dblink_exec('myconn',
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
    PERFORM dblink_exec('myconn',
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
            ON DELETE SET NULL
            ON UPDATE CASCADE,
            CONSTRAINT valid_booking UNIQUE (arrival, departure, hotel_room_id),
            total_cost NUMERIC(8, 2)
            CHECK (total_cost > 0),
            bank_card VARCHAR(19)
            CONSTRAINT valid_card CHECK (bank_card ~ ''\d{13,19}''));');
    PERFORM dblink_exec('myconn',
        'CREATE TABLE booking_guest(
            booking_id INTEGER REFERENCES booking
            ON DELETE CASCADE
            ON UPDATE CASCADE,
            guest_id INTEGER REFERENCES guest
            ON DELETE CASCADE
            ON UPDATE CASCADE,
            PRIMARY KEY (booking_id, guest_id));');
    PERFORM dblink_exec('myconn',
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
    PERFORM dblink_exec('myconn',
        'CREATE TRIGGER available_room_trigger
        BEFORE INSERT OR UPDATE OF arrival, departure, hotel_room_id
        ON booking
        FOR EACH ROW
        EXECUTE PROCEDURE is_room_available()');
    PERFORM dblink_exec('myconn',
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
        $calc_cost$');
    PERFORM dblink_exec('myconn',
        'CREATE TRIGGER cost_trigger
        BEFORE INSERT OR UPDATE OF arrival, departure, hotel_room_id
        ON booking
        FOR EACH ROW
        EXECUTE PROCEDURE calc_cost()');
    PERFORM dblink_exec('myconn',
         'CREATE INDEX guest_name ON guest(last_name, first_name, patronimic)');
    PERFORM dblink_exec('myconn',
         'CREATE OR REPLACE FUNCTION find_free_rooms(arr text, dep text) RETURNS TABLE(
		hotel_room_id INTEGER,
		price_per_day NUMERIC(7, 2),
		number_of_rooms INTEGER,
		area INTEGER,
		service_class VARCHAR(8),
		kitchen BOOL) AS
		$find_free_rooms$
		BEGIN
			IF arr::DATE < dep::DATE
			THEN
				RETURN QUERY SELECT * FROM hotel_room AS r
					WHERE r.hotel_room_id NOT IN
					(SELECT b.hotel_room_id
					FROM booking AS b
					WHERE (arr::DATE, dep::DATE)
					OVERLAPS (b.arrival, b.departure));
			ELSE
				RAISE EXCEPTION ''The arrival date must be earlier than the departure date!'';
			END IF;
		END;
		$find_free_rooms$ LANGUAGE plpgsql;');
    PERFORM dblink_exec('myconn',
         'CREATE OR REPLACE FUNCTION find_guest(
			lst_name VARCHAR(30), frst_name VARCHAR(20))
			RETURNS TABLE(
			guest_id INTEGER,
			last_name VARCHAR(30),
			first_name VARCHAR(20),
			patronimic VARCHAR(20),
			passport_series VARCHAR(4),
			passport_number VARCHAR(6),
			phone VARCHAR(10),
			booking_id INTEGER,
			arrival DATE,
			departure DATE,
			booking_date DATE,
			hotel_room_id INTEGER,
			total_cost NUMERIC(8, 2),
			bank_card VARCHAR(19),
			price_per_day NUMERIC(7, 2),
			number_of_rooms INTEGER,
			area INTEGER,
			service_class VARCHAR(8),
			kitchen BOOL) AS
			$find_guest$
			BEGIN
				RETURN QUERY SELECT guest.guest_id, guest.last_name, guest.first_name, 
					guest.patronimic, guest.passport_series, guest.passport_number, guest.phone,
					booking.booking_id, booking.arrival, booking.departure, booking.booking_date, 
					booking.hotel_room_id, booking.total_cost, booking.bank_card,
					hotel_room.price_per_day, hotel_room.number_of_rooms, hotel_room.area, 
					hotel_room.service_class, hotel_room.kitchen
				FROM guest, hotel_room, booking, booking_guest
				WHERE guest.last_name = lst_name AND guest.first_name = frst_name AND 
					hotel_room.hotel_room_id = booking.hotel_room_id AND 
					booking.booking_id = booking_guest.booking_id AND 
					guest.guest_id = booking_guest.guest_id;
			END;
			$find_guest$ LANGUAGE plpgsql;');
    PERFORM dblink_exec('myconn',
        'CREATE FUNCTION insert_guest(v_last_name VARCHAR(30),
                                     v_first_name VARCHAR(20),
                                     v_patronimic VARCHAR(20),
                                     v_passport_series VARCHAR(4),
                                     v_passport_number VARCHAR(6),
                                     v_phone VARCHAR(10)) RETURNS VOID AS $insert_guest$
        BEGIN
             INSERT INTO guest(last_name, first_name, patronimic, passport_series, passport_number, phone)
             VALUES (v_last_name, v_first_name, v_patronimic, v_passport_series, v_passport_number, v_phone);
        END;
        $insert_guest$ LANGUAGE plpgsql');
    PERFORM dblink_exec('myconn',
        'CREATE FUNCTION insert_hotel_room(
            v_hotel_room_id INTEGER,
            v_price_per_day NUMERIC(7, 2),
            v_number_of_rooms INTEGER,
            v_area INTEGER,
            v_service_class VARCHAR(8),
            v_kitchen BOOL) RETURNS VOID AS $insert_hotel_room$
        BEGIN
            INSERT INTO hotel_room(hotel_room_id, price_per_day, number_of_rooms, area, service_class, kitchen)
            VALUES (v_hotel_room_id, v_price_per_day, v_number_of_rooms, v_area, v_service_class, v_kitchen);
        END;
        $insert_hotel_room$ LANGUAGE plpgsql');
    PERFORM dblink_exec('myconn',
        'CREATE FUNCTION insert_booking(
            v_arrival DATE,
            v_departure DATE,
            v_hotel_room_id INTEGER,
            v_bank_card VARCHAR(19)) RETURNS VOID AS $insert_booking$
        BEGIN
            INSERT INTO booking(arrival, departure, hotel_room_id, bank_card)
            VALUES (v_arrival, v_departure, v_hotel_room_id, v_bank_card);
        END;
        $insert_booking$ LANGUAGE plpgsql');
    PERFORM dblink_exec('myconn',
        'CREATE FUNCTION insert_booking_guest(
            v_booking_id INTEGER,
            v_guest_id INTEGER) RETURNS VOID AS $insert_booking_guest$
        BEGIN
            INSERT INTO booking_guest(booking_id, guest_id)
            VALUES (v_booking_id, v_guest_id);
        END;
        $insert_booking_guest$ LANGUAGE plpgsql');

    /* function print_table() should be called like
    SELECT * FROM print_table(NULL::guest);
    SELECT * FROM print_table(NULL::hotel_room);*/
    PERFORM dblink_exec('myconn', 
        'CREATE OR REPLACE FUNCTION print_table(_tbl anyelement)
        RETURNS SETOF anyelement AS
        $print_table$
        BEGIN
            RETURN QUERY EXECUTE ''SELECT * FROM '' || pg_typeof(_tbl);
        END;
        $print_table$ LANGUAGE plpgsql;');

    /* The function delete_row() returns TRUE, if the deletion was successfull
    Otherwise it returns FALSE.
    Example of how it should be called:
    SELECT delete_row('guest', 'guest_id', 1);*/
    PERFORM dblink_exec('myconn',
        'CREATE OR REPLACE FUNCTION delete_row(_tbl regclass, key_col text, key_val INTEGER)
        RETURNS BOOL AS
        $delete_row$
        DECLARE 
        success BOOL;
        BEGIN
            EXECUTE format(''
                DELETE FROM %s
                WHERE %I = $1
                RETURNING TRUE'', _tbl, key_col)
            USING key_val
            INTO success;
            IF success IS TRUE
            THEN
                RETURN TRUE;
            ELSE
                RETURN FALSE;
            END IF;
        END;
        $delete_row$ LANGUAGE plpgsql;');

    /* The function delete_guest_by_name() returns TRUE, if the deletion was successfull.
    Otherwise it returns FALSE.
    Example of how it should be called:
    SELECT delete_guest_by_name('Ivanov', 'Ivan');*/
    PERFORM dblink_exec('myconn',
        'CREATE OR REPLACE FUNCTION delete_guest_by_name(
        lst_name VARCHAR(30), frst_name VARCHAR(20))
        RETURNS BOOL AS
        $delete_guest_by_name$
        DECLARE
        success BOOL;
        BEGIN
            EXECUTE format(''DELETE FROM guest
                WHERE guest.last_name = $1 AND
                guest.first_name = $2
                RETURNING TRUE'')
            USING lst_name, frst_name
            INTO success;
            IF success IS TRUE
            THEN
                RETURN TRUE;
            ELSE
                RETURN FALSE;
            END IF;
        END;
        $delete_guest_by_name$ LANGUAGE plpgsql;');
    
    /* The function delete_booking_guest() returns TRUE, if the deletion was successfull.
	Otherwise (if the table had been empty before the deletion) it returns FALSE.
	Example of how it should be called:
	SELECT delete_booking_guest(3, 5);
	Here 3 is a booking id, 5 is a guest id.*/
	PERFORM dblink_exec('myconn',
        'CREATE OR REPLACE FUNCTION delete_booking_guest(
		v_booking_id INTEGER, v_guest_id INTEGER)
		RETURNS BOOL AS
		$delete_booking_guest$
		DECLARE
		success BOOL;
		BEGIN
			EXECUTE format(''DELETE FROM booking_guest
				WHERE booking_guest.booking_id = $1 AND
				booking_guest.guest_id = $2
				RETURNING TRUE'')
			USING v_booking_id, v_guest_id
			INTO success;
			IF success IS TRUE
			THEN
				RETURN TRUE;
			ELSE
				RETURN FALSE;
			END IF;
		END;
		$delete_booking_guest$ LANGUAGE plpgsql;');

    /* The function delete_guest_by_passport() returns TRUE, if the deletion was successfull.
    Otherwise it returns FALSE.
    Example of how it should be called:
    SELECT delete_guest_by_passport('1111', '1111111');*/
    PERFORM dblink_exec('myconn',
        'CREATE OR REPLACE FUNCTION delete_guest_by_passport(
        v_passport_series VARCHAR(4), v_passport_number VARCHAR(6))
        RETURNS BOOL AS
        $delete_guest_by_passport$
        DECLARE
        success BOOL;
        BEGIN
            EXECUTE format(''DELETE FROM guest
                WHERE guest.passport_series = $1 AND
                guest.passport_number = $2
                RETURNING TRUE'')
            USING v_passport_series, v_passport_number
            INTO success;
            IF success IS TRUE
            THEN
                RETURN TRUE;
            ELSE
                RETURN FALSE;
            END IF;
        END;
        $delete_guest_by_passport$ LANGUAGE plpgsql;');

    /* The function delete_booking_by_dates_and_room() returns TRUE, if the deletion was successfull.
    Otherwise it returns FALSE.
    Example of how it should be called:
    SELECT delete_row('2021-12-27', '2021-12-29', 1);*/
    PERFORM dblink_exec('myconn',
        'CREATE OR REPLACE FUNCTION delete_booking_by_dates_and_room(
        v_arrival DATE, v_departure DATE, v_hotel_room_id INTEGER)
        RETURNS BOOL AS
        $delete_booking_by_dates_and_room$
        DECLARE
        success BOOL;
        BEGIN
            EXECUTE format(''DELETE FROM booking
                WHERE booking.arrival = $1 AND
                booking.departure = $2 AND
                booking.hotel_room_id = $3
                RETURNING TRUE'')
            USING v_arrival, v_departure, v_hotel_room_id
            INTO success;
            IF success IS TRUE
            THEN
                RETURN TRUE;
            ELSE
                RETURN FALSE;
            END IF;
        END;
        $delete_booking_by_dates_and_room$ LANGUAGE plpgsql;');
    
    /* The function clear_table() returns TRUE, if the deletion was successfull.
    Otherwise (if the table had been empty before the deletion) it returns FALSE.
    Example of how it should be called:
    SELECT clear_table('booking');*/
    PERFORM dblink_exec('myconn',
        'CREATE OR REPLACE FUNCTION clear_table(_tbl regclass)
        RETURNS BOOL AS
        $clear_table$
        DECLARE
        success BOOL;
        BEGIN
            EXECUTE format(''DELETE FROM %I
                RETURNING TRUE'', _tbl)
            INTO success;
            IF success IS TRUE
            THEN
                RETURN TRUE;
            ELSE
                RETURN FALSE;
            END IF;
        END;
        $clear_table$ LANGUAGE plpgsql;');
    PERFORM dblink_exec('myconn',
        'CREATE OR REPLACE FUNCTION print_full_info()
		RETURNS TABLE(
		guest_id INTEGER,
		last_name VARCHAR(30),
		first_name VARCHAR(20),
		patronimic VARCHAR(20),
		passport_series VARCHAR(4),
		passport_number VARCHAR(6),
		phone VARCHAR(10),
		booking_id INTEGER,
		arrival DATE,
		departure DATE,
		booking_date DATE,
		hotel_room_id INTEGER,
		total_cost NUMERIC(8, 2),
		bank_card VARCHAR(19),
		price_per_day NUMERIC(7, 2),
		number_of_rooms INTEGER,
		area INTEGER,
		service_class VARCHAR(8),
		kitchen BOOL) AS
		$print_full_info$
		BEGIN
			RETURN QUERY SELECT guest.guest_id, guest.last_name, guest.first_name, 
				guest.patronimic, guest.passport_series, guest.passport_number, guest.phone,
				booking.booking_id, booking.arrival, booking.departure, booking.booking_date, 
				booking.hotel_room_id, booking.total_cost, booking.bank_card,
				hotel_room.price_per_day, hotel_room.number_of_rooms, hotel_room.area, 
				hotel_room.service_class, hotel_room.kitchen
			FROM hotel_room
			JOIN booking
			ON hotel_room.hotel_room_id = booking.hotel_room_id
			JOIN booking_guest
			ON booking.booking_id = booking_guest.booking_id
			JOIN guest
			ON guest.guest_id = booking_guest.guest_id;
		END;
		$print_full_info$ LANGUAGE plpgsql;');
	PERFORM dblink_exec('myconn',
        'CREATE OR REPLACE FUNCTION update_booked_room(key_val INTEGER, new_room INTEGER)
		RETURNS BOOL AS
		$update_booked_room$
		DECLARE
		booking_exists BOOL;
		unchanged BOOL;
		BEGIN
			EXECUTE format(''SELECT EXISTS (
				SELECT 1 FROM booking
				WHERE booking_id = $1)'')
				USING key_val INTO booking_exists;
			IF booking_exists
			THEN
				EXECUTE format(''SELECT EXISTS (
					SELECT 1 FROM booking
					WHERE booking_id = $1 AND hotel_room_id = $2)'')
				USING key_val, new_room INTO unchanged;
				IF unchanged
				THEN
					RETURN FALSE;
				ELSE
					EXECUTE format(''UPDATE booking
						SET hotel_room_id = $1
						WHERE booking_id = $2;'')
					USING new_room, key_val;
					RETURN TRUE;
				END IF;
			ELSE
				RAISE EXCEPTION ''A booking with such an ID does not exist!'';
			END IF;                                                      
		END;
		$update_booked_room$ LANGUAGE plpgsql;');
    PERFORM dblink_exec('myconn','COMMIT');
     
END;
$create_db$ LANGUAGE plpgsql;

-- drop the database with a given name
CREATE OR REPLACE FUNCTION drop_db(dbname text) RETURNS VOID AS $drop_db$
BEGIN
     PERFORM dblink_exec('dbname=client port=5432 host=127.0.0.1 user=client password=client',
                         'DROP DATABASE ' || quote_ident(dbname));
END;
$drop_db$ LANGUAGE plpgsql;
