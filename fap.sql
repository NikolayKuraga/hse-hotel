/* (stored) functions and procedures for PostgreSQL server */

-- check database 'clientdb' for existense
CREATE OR REPLACE FUNCTION check_db() RETURNS BOOL AS $$
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
$$ LANGUAGE plpgsql;

-- create database 'clientdb'
CREATE OR REPLACE PROCEDURE create_db() AS $$
BEGIN
     PERFORM dblink_exec('dbname=client port=5432 host=127.0.0.1 user=client password=client',
                         'CREATE DATABASE clientdb;');
END;
$$ LANGUAGE plpgsql;

-- drop procedure
CREATE OR REPLACE PROCEDURE drop_db() AS $$
BEGIN
     PERFORM dblink_exec('dbname=client port=5432 host=127.0.0.1 user=client password=client',
                         'DROP DATABASE clientdb;');
END;
$$ LANGUAGE plpgsql;
