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

#include <stdbool.h>
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

void command_loop(bool interactive);

int main(int argc, const char** argv) {
    if (isatty(STDIN_FILENO) == 1) {
        /* Interactive shell */
        command_loop(true);
    } else {
        /* Non-interactive shell */
        command_loop(false);
    }
    return 0;
}

void command_loop(bool interactive) {
    char* buffer = calloc(512, sizeof(char));
    char** cmd_argv = calloc(512, sizeof(char*));
    char* token;
    int i = 0;
    int ret;
    bool background = false;
    while (1) {
        if (interactive)
            printf("$ ");
        fgets(buffer, 512, stdin);
        for (size_t j = 0; j < strlen(buffer); j++) {
            if (buffer[j] == '\n') {
                buffer[j] = '\0';
            }
        }
        token = strtok(buffer, " ");
        while (token != NULL) {
            if (strncmp("&", token, 2) == 0)
                background = true;
            
            cmd_argv[i] = strdup(token);
            token = strtok(NULL, " ");
            i++;
        }
        cmd_argv[i] = NULL;
        if (strncmp("exit", cmd_argv[0], 4) == 0) {
            break;
        }
        if (strncmp("echo", cmd_argv[0], 5) == 0) {
            if (strncmp("$?", cmd_argv[1], 3) == 0) {
                printf("%d\n", ret);
                goto reset;
            }
            for (int arg = 1; arg < i; arg++) {
                printf("%s ", cmd_argv[arg]);
            }
            printf("\n");
            goto reset;
        }
        if (strncmp("fg", cmd_argv[0], 3)) {
            wait(NULL);
            goto reset;
        }
        ret = fork();
        if (ret == 0) {
            execvp(cmd_argv[0], cmd_argv);
            exit(0);
        }
        if (!background)
            wait(&ret);
reset:
        i = 0;
        background = false;
    }
    if (interactive)
        puts("Exiting...");
    free(buffer);
    free(cmd_argv);
}
