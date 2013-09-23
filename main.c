/*
 * Project 1: Simulation of Linux Shell
 * Written by: Yasha Prikhodko
 * Mon, Sep 23, 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

#define MAX_LENGTH 1024
#define DELIMS " \t\r\n\""

extern char **environ;

int main()
{
    char line[MAX_LENGTH];
    char *cmd;

    // Set SHELL environment variable
    char *name = "SHELL=";
    char *value = "/myshell";
    char str[100];
    strcpy(str, name);
    strcat(str, get_current_dir_name());
    strcat(str, value);
    putenv(str);

    // Start listening for the commands
    while (1) {
        printf("%s $ ", get_current_dir_name());
        if (!fgets(line, MAX_LENGTH, stdin)) break;

        // Parse and execute commands
        if ((cmd = strtok(line, DELIMS))) {
          // Clear errors
          errno = 0;

            // Implementation of cd command
            if (strcmp(cmd, "cd") == 0) {
                char *arg = strtok(0, DELIMS);

                if (!arg) fprintf(stderr, "%s: %s %s", "Current directory", get_current_dir_name(), "\n");
                else chdir(arg);

            // Implementation of dir command
            } else if (strcmp(cmd, "dir") == 0) {
                DIR *dp;
                struct dirent *ep;
                char *arg = strtok(0, DELIMS);

                if (!arg) {
                    arg = get_current_dir_name();
                }

                dp = opendir (arg);

                if (dp != NULL) {
                    while (ep = readdir (dp))
                        puts (ep->d_name);

                    (void) closedir (dp);
                }

            // Implementation of echo command
            } else if (strcmp(cmd, "echo") == 0) {
                char *arg = strtok(0, DELIMS);

                printf ("%s\n", arg);

            // Implementation of environ command
            } else if (strcmp(cmd, "environ") == 0) {
                int i = 0;
                while(environ[i]) {
                  printf("%s\n", environ[i++]);
                }
            // Implementation of help command
            } else if (strcmp(cmd, "help") == 0) {
                printf("here's your help\n"); //TODO: load a readme file and display the contents

            // Implementation of pause command
            } else if (strcmp(cmd, "pause") == 0) {
                printf("Hit Enter key to continue > ");
                getchar();

            // Implementation of clr command
            } else if (strcmp(cmd, "clr") == 0) {
                system("clear");

            // Implementation of quit command
            } else if (strcmp(cmd, "quit") == 0) {
                break;
            }

          if (errno) perror("Command failed");
        }

    }

    return 0;
}
