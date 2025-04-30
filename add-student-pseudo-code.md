FUNC add_student(db)
  IF db IS NULL THEN
    RETURN NULL_CONNECTION
  END IF

  ALLOCATE memory for student.register_id WITH size 5
  ALLOCATE memory for student.name WITH size 50

  IF malloc failed THEN
    PRINT err msg
    RETURN SQLITE_ERROR
  END IF

  DO
    PROMPT user to enter register ID
    READ input into student.register_id

    CHECK if register_id already exist in db
    IF checking fails THEN
      PRINT err msg
      FREE student's memory
      RETURN SQLITE_ERROR
    ELSE IF register_id exists THEN
      PRINT "Register ID already exists"
    END IF
  WHILE register_id already exists

  PROMPT user to enter name
  READ input into student.name

  PROMPT user to enter age
  READ input into student.age

  IF inputs are invalid THEN
    PRINT err msg
    CLEAR input buffer
    FREE student's memory
    RETURN SQLITE_ERROR
  END IF

  PREPARE SQL STATEMENT: INSERT INTO students VALUES (?, ?, ?)

  IF preparation fails THEN
    PRINT err msg
    FREE student's memory
    RETURN err code
  END IF

  BIND values:
    register_id → parameter 1
    name → parameter 2
    age → parameter 3

  EXECUTE the prepared statement
  IF execution fails THEN
    PRINT err msg
    FINALIZE statement
    FREE student's memory
    RETURN err code
  END IF

  FINALIZE the statement
  FREE allocated memory (student)

  PRINT "Student added successfully."
  RETURN SQLITE_OK
END FUNC