/**
 * Copyright (C) 2024 Yanderemine54
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

#include <stdlib.h>
#include "stack.h"

stack_t* init_stack(void) {
    stack_t* stack = calloc(1, sizeof(stack_t));
    stack->top = -1;
    stack->array = calloc(512, sizeof(int));
    return stack;
}

int push(stack_t* stack, int element) {
    if (stack->top == 512 - 1) {
        return 0;
    }

    stack->top++;
    stack->array[stack->top] = element;
}

int pop(stack_t* stack) {
    int element;

    if (stack->top == -1) {
        return -1;
    }

    element = stack->array[stack->top];
    stack->top--;
    return element;
}
