#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Initialize the logging interface
    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);
    
    // Check for the correct number of arguments
    if (argc < 3) {
        syslog(LOG_ERR, "Insufficient arguments provided");
        closelog(); // Close the log
        exit(EXIT_FAILURE);
    }

    // Attempt to open the specified file for writing
    FILE *file = fopen(argv[1], "w");
    if (!file) {
        syslog(LOG_ERR, "Failed to open file: %s", argv[1]);
        closelog(); // Close the log
        exit(EXIT_FAILURE);
    }

    // Write the specified content to the file
    fprintf(file, "%s", argv[2]);
    fclose(file); // Close the file

    // Log the successful write operation
    syslog(LOG_INFO, "Successfully wrote '%s' to %s", argv[2], argv[1]);
    closelog(); // Close the log
    
    return EXIT_SUCCESS;
}
