```
FUNCTION prompt_and_input(ADDRESS OF input)
    PRINT menu options
    SCAN INTO input
    IF input is invalid
        SET input = -1
    ENDIF
END

FUNCTION main()
    DECLARE ADDRESS OF db
    INITIALIZE db
    IF db initialization fails
        PRINT "Failed to initialize database"
        CLOSE db
        EXIT FAILURE
    ENDIF

    DECLARE err = 0
    DECLARE choice = -1
    DECLARE program_cycle = 1

    WHILE program_cycle = 1
        prompt_and_input(ADDRESS OF choice)

        IF choice is add student
            add_student(db)
            IF function fails
                PRINT error message
                CLOSE db
                EXIT FAILURE
            ENDIF

        ELSE IF choice is find student
            find_student(db)
            IF function fails
                PRINT error message
                CLOSE db
                EXIT FAILURE
            ENDIF

        ELSE IF choice is delete student
            delete_student(db)
            IF function fails
                PRINT error message
                CLOSE db
                EXIT FAILURE
            ENDIF

        ELSE IF choice is exit
            PRINT "Exiting..."
            program_cycle = 0

        ELSE
            PRINT "Invalid choice. Please try again"

        ENDIF
    ENDWHILE

    CLOSE db
    EXIT SUCCESS
END
```