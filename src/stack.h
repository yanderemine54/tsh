// Copyright (C) 2024 Yanderemine54
// 
// This file is part of tsh.
// 
// tsh is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// tsh is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with tsh.  If not, see <http://www.gnu.org/licenses/>.

#ifndef TSH_STACK_H
#define TSH_STACK_H
typedef struct {
    int top;
    int* array;
} stack_t;
stack_t* init_stack(void);
int push(stack_t* stack, int element);
int pop(stack_t* stack);
#endif