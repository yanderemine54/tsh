/**
 * Copyright (C) 2023 Yanderemine54
 * 
 * This file is part of tsh.
 * 
 * tsh is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * tsh is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with tsh.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#if !(_XOPEN_SOURCE >= 500 || _POSIX_C_SOURCE >= 200809L || _BSD_SOURCE || _SVID_SOURCE)
char *strdup(const char *s) {
    size_t size = strlen(s) + 1;
    char *p = malloc(size);
    if (p) {
        memcpy(p, s, size);
    }
    return p;
}
#endif


int main(int argc, const char** argv) {
    char buffer[512];
    char* cmd_argv[256];
    char* token;
    int i = 0;
    int ret;
    if (isatty(STDIN_FILENO)) {
        /* Interactive shell */
        while (1) {
            printf("$ ");
            fgets(buffer, 512, stdin);
            for (size_t j = 0; j < strlen(buffer); j++) {
                if (buffer[j] == '\n') {
                    buffer[j] = '\0';
                }
            }
            token = strtok(buffer, " ");
            while (token != NULL) {
                cmd_argv[i] = strdup(token);
                token = strtok(NULL, " ");
                i++;
            }
            cmd_argv[i] = NULL;
            if (strncmp("exit", cmd_argv[0], 4) == 0) {
                break;
            }
            ret = fork();
            if (ret <= 0) {
                execvp(cmd_argv[0], cmd_argv);
                exit(0);
            }
            wait(NULL);
            i = 0;
        }
        puts("Exiting...");
    } else {
        /* Non-interactive shell */
    }
    return 0;
}
