/* stored functions PostgreSQL server */

-- check database 'clientdb' for existense
CREATE OR REPLACE FUNCTION check_db() RETURNS BOOL AS $check_db$
BEGIN
     RETURN (SELECT CASE
                        WHEN
                            (SELECT TRUE
                               FROM pg_database
                              WHERE datname='clientdb')
                        THEN
                            TRUE
                        ELSE
                            FALSE
                        END);
END;
$check_db$ LANGUAGE plpgsql;

-- create database 'clientdb'
CREATE OR REPLACE FUNCTION create_db() RETURNS VOID AS $create_db$
BEGIN
     PERFORM dblink_exec('dbname=client port=5432 host=127.0.0.1 user=client password=client',
                         'CREATE DATABASE clientdb;');
     PERFORM dblink_exec('dbname=clientdb port=5432 host=127.0.0.1 user=client password=client',
                         'CREATE TABLE guest(
                          guest_id SERIAL PRIMARY KEY,
                          last_name VARCHAR(30) NOT NULL,
                          first_name VARCHAR(20) NOT NULL,
                          patronimic VARCHAR(20),
                          passport_series VARCHAR(4) NOT NULL
                            CONSTRAINT valid_guest_passport_series CHECK (passport_series ~ ''\d{4}''),
                          passport_number VARCHAR(6) NOT NULL
                            CONSTRAINT valid_guest_passport_number CHECK (passport_number ~ ''\d{6}''),
                          CONSTRAINT unique_guest_passport UNIQUE (passport_series, passport_number),
                          phone VARCHAR(10)
                            CONSTRAINT valid_guest_phone_number CHECK (phone ~ ''\d{10}''));');
     PERFORM dblink_exec('dbname=clientdb port=5432 host=127.0.0.1 user=client password=client',
                         'CREATE FUNCTION insert_guest(v_last_name VARCHAR(30),
                                                       v_first_name VARCHAR(20),
                                                       v_patronimic VARCHAR(20),
                                                       v_passport_series VARCHAR(4),
                                                       v_passport_number VARCHAR(6),
                                                       v_phone VARCHAR(10)) RETURNS VOID AS $$
                          BEGIN
                               INSERT INTO guest(last_name, first_name, patronimic, passport_series, passport_number, phone)
                               VALUES (v_last_name, v_first_name, v_patronimic, v_passport_series, v_passport_number, v_phone);
                          END;
                          $$ LANGUAGE plpgsql;');
END;
$create_db$ LANGUAGE plpgsql;

-- drop database 'clientdb'
CREATE OR REPLACE FUNCTION drop_db() RETURNS VOID AS $drop_db$
BEGIN
     PERFORM dblink_exec('dbname=client port=5432 host=127.0.0.1 user=client password=client',
                         'DROP DATABASE clientdb;');
END;
$drop_db$ LANGUAGE plpgsql;
