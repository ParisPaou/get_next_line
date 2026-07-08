# Get Next Line

## Description

Get Next Line is a project from the 42 curriculum that focuses on creating a function capable of reading a file descriptor one line at a time.

The goal is to implement:

char *get_next_line(int fd);

The function reads and returns a single line from a file descriptor each time it is called. It includes the newline character (\n) when it exists and returns NULL when there is nothing more to read or when an error occurs.

The project introduces the use of static variables to store remaining data between function calls, allowing efficient reading without loading the entire file into memory.

---

## Features

- Reads files line by line.
- Works with regular files and standard input.
- Supports different BUFFER_SIZE values.
- Returns one line per function call.
- Keeps leftover data between calls using a static variable.
- Uses dynamic memory allocation.
- Handles end-of-file conditions correctly.

---

## Function Prototype

char *get_next_line(int fd);

### Parameters

fd:
The file descriptor to read from.

### Return Value

The function returns:

- The next line read from the file descriptor.
- NULL if there is nothing left to read or if an error occurs.

---

## Compilation

The project supports compilation with a custom BUFFER_SIZE value.

Example:

cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c

Different buffer sizes can be tested:

-D BUFFER_SIZE=1

-D BUFFER_SIZE=100

-D BUFFER_SIZE=9999

The function must work correctly regardless of the chosen buffer size.

---

## Project Structure

.
├── get_next_line.c
├── get_next_line_utils.c
└── get_next_line.h


### get_next_line.c

Contains the main implementation of the get_next_line() function.

### get_next_line_utils.c

Contains helper functions used for string operations, memory allocation, and data management.

### get_next_line.h

Contains the required includes and the function prototype.

---

## How It Works

The function uses the read() system call to retrieve data from the file descriptor.

Since read() may return only part of a line, the remaining data is stored in a static variable. This stored data is reused during the next function call.

The process:

1. Read data from the file descriptor into a buffer.
2. Append the buffer content to stored data.
3. Search for a newline character.
4. Extract the current line.
5. Save the remaining characters for the next call.
6. Return the extracted line.

This allows the program to read files efficiently without reading the entire file at once.

---

## Example

File:

Hello World
This is Get Next Line
42 School


Code:

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;

    fd = open("example.txt", O_RDONLY);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);

    return (0);
}


Output:

Hello World
This is Get Next Line
42 School

---

## Allowed Functions

Only the following external functions are allowed:

- read
- malloc
- free

---

## Forbidden

The following are not allowed:

- lseek()
- Global variables
- Using libft

---

## Concepts Learned

This project helps develop understanding of:

- File descriptors
- System calls
- Static variables
- Dynamic memory allocation
- Buffer management
- String manipulation
- Memory leak prevention

---

## Notes

get_next_line() should work correctly with:

- Very small buffer sizes, such as BUFFER_SIZE=1
- Large buffer sizes, such as BUFFER_SIZE=10000000
- Files ending with or without a newline
- Standard input

The function should read only the required amount of data and avoid unnecessary file reads.

---

## Author

Paris Paouleanou
