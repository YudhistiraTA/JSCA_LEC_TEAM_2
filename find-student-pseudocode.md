FUNCTION find_student(db):
    IF db is NULL THEN
        RETURN error for no connection

    PRINT "Enter student's name to search: "
    GET input and store in variable 'name'

    IF input is not valid THEN
        PRINT "Invalid input"
        RETURN error

    ADD "%" to the beginning and end of 'name'
    STORE result in variable 'search_name'

    SET SQL query to:
        "SELECT register_id, name, age FROM students WHERE name LIKE ?"

    PREPARE statement using the SQL query

    IF statement failed to prepare THEN
        PRINT "Failed to prepare statement"
        RETURN error

    BIND 'search_name' to the SQL statement at position 1

    SET found to false

    WHILE getting rows from the result:
        IF there is a row THEN
            SET found to true
            PRINT "Student found:"
            PRINT "Register ID:", register_id from row
            PRINT "Name:", name from row
            PRINT "Age:", age from row

    IF found is false THEN
        PRINT "No student found with that name"

    IF error happened during row reading THEN
        PRINT "Error while getting results"

    FINALIZE the statement

    RETURN success
