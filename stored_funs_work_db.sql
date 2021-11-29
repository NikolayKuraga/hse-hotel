-- create stored function for inserting guests
CREATE FUNCTION insert_guest(v_last_name VARCHAR(30),
                             v_first_name VARCHAR(20),
                             v_patronimic VARCHAR(20),
                             v_passport_series VARCHAR(4),
                             v_passport_number VARCHAR(6),
                             v_phone VARCHAR(10)) RETURNS VOID AS $insert_guest$
BEGIN
     INSERT INTO guest(last_name, first_name, patronimic, passport_series, passport_number, phone)
     VALUES (v_last_name, v_first_name, v_patronimic, v_passport_series, v_passport_number, v_phone);
END;
$insert_guest$ LANGUAGE plpgsql;
