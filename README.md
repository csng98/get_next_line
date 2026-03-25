*This project has been created as part of the 42 curriculum by csekakul.*

# get_next_line

---

## Description

`get_next_line` is a C project where you implement a function that reads **one line at a time** from a file descriptor.

```c
char *get_next_line(int fd);
```

The function must:

- Return the next line including the `\n` (if present)
- Return the last line even if it does not end with `\n`
- Return `NULL` when EOF is reached or an error occurs
- Work with any `BUFFER_SIZE`
- Handle very large lines correctly

This project introduces:

- Static variables
- File descriptors
- The `read()` system call
- Memory management
- Persistent state between function calls

---

# How It Works

Since `read()` does not read “lines” but only raw bytes, we must:

1. Read chunks of size `BUFFER_SIZE`
2. Store them in persistent memory (called a **stash**)
3. Stop reading once a `\n` is found
4. Extract one line
5. Keep leftover characters for the next function call

---

# Core Concepts

## File Descriptors

When you open a file:

```c
int fd = open("file.txt", O_RDONLY);
```

You receive a **file descriptor** (an integer).  
Each descriptor has its own internal cursor (offset).

---

## `read()`

```c
ssize_t read(int fd, void *buf, size_t nbyte);
```

- Reads up to `nbyte` bytes
- Moves the file offset forward
- Returns:
  - `> 0` → bytes read
  - `0` → EOF
  - `-1` → error

`read()` remembers where it stopped thanks to the file descriptor offset.

---

## Static Variables

A static variable:

- Is initialized only once
- Keeps its value between function calls
- Lives until program termination

Example:

```c
int counter(void)
{
    static int i = 0;
    i++;
    return (i);
}
```

This is how `get_next_line` remembers leftover data between calls.

---

# Why We Need a “Stash”

Example with `BUFFER_SIZE = 4`  
File content:

```
Hello\n
```

`read()` behaves like:

```
"Hell"
"o\n"
```

Without storing previous reads, we would lose data.

So we use a **static stash** to accumulate content until a full line is available.

---

# My Implementation Approach

There are two common approaches.

---

## Option A — Stash as a Single String (My final approach)

```c
static char *stash;
```

You:

- Append buffer to stash
- Search for `\n`
- Extract line
- Keep the remainder

### Pros

- Simple design
- Easy to understand
- One growing string
- One extraction
- One cleanup

### Cons

- Multiple reallocations
- Repeated copying of large strings

---

## Option B — Stash as a Linked List (This was my first approach)

```c
typedef struct s_gnl_list
{
    char *content;
    struct s_gnl_list *next;
}   t_gnl_list;
```

Instead of continuously reallocating a large string:

- Each `read()` creates a new node
- Nodes are linked together
- When building the final line:
  - Calculate exact length
  - Allocate once
  - Copy data once

### Why I wated to choose this first:

- Fewer large reallocations
- Potentially faster for long lines
- Good practice with linked lists
- Better memory control

---

# Edge Cases Handled

- Empty file
- One-character file
- No newline at EOF
- Very long lines
- `BUFFER_SIZE = 1`
- Invalid file descriptor
- `read()` returning `-1`
- (Bonus) Multiple file descriptors

---

# Compilation

## Using Makefile

```bash
make
```

## Clean object files

```bash
make fclean
```

## Manual compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
```

If using a static library:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.a
```

---

# Instructions

## Example `main.c`

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int main(void)
{
    int		fd = open("test.txt", O_RDONLY);
    char *line;

    if (fd < 0)
	{
    	printf("Invalid file descriptor.\n");
		return (1);
	}
    line = get_next_line(fd);
	while (line != NULL)
	{
		printf("line -> %s", line);
		free(line);
		line = get_next_line(fd);
	}
    return (0);
}
```

## Example `main.c` with command line arguments
```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i = 1;

	if (argc != 2)
	{
		printf("Usage: ./a.out file\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}

	while ((line = get_next_line(fd)))
	{
		printf("Line %d: %s", i++, line);
		free(line);
	}
	close(fd);
}
```

## Example `main.c` for multiple file descriptors
```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int		fd1;
	int		fd2;
    char	*line1 = NULL;
    char	*line2 = NULL;

    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);
    if (fd1 < 0 || fd2 < 0)
    {
        perror("open");
        return 1;
    }
    while (1)
    {
        line1 = get_next_line(fd1);
        line2 = get_next_line(fd2);
        if (!line1 && !line2)
            break;
        if (line1)
        {
            printf("FD1: %s", line1);
            free(line1);
        }
        if (line2)
        {
            printf("FD2: %s", line2);
            free(line2);
        }
    }
    close(fd1);
    close(fd2);
    return 0;
}
```

---

## Test Different `BUFFER_SIZE` Values

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1  main.c get_next_line.c get_next_line_utils.c
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 main.c get_next_line.c get_next_line_utils.c
```

---

## Memory Leak Check

Using Valgrind:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./a.out
```

You want:

- No leaks
- No invalid reads/writes

---

# Libraries Used

In `get_next_line.h`:

- `<unistd.h>` → `read()`
- `<stdlib.h>` → `malloc()`, `free()`

In testing:

- `<fcntl.h>` → `open()`
- `<stdio.h>` → `printf()`
- `<unistd.h>` → `close()`

---

# Resources

- [Overview video](https://www.youtube.com/watch?v=-Mt2FdJjVno&t=2s)
- [42 GitBook (open & read)](https://42-cursus.gitbook.io/guide/1-rank-01/get_next_line/open-and-read)
- `man 2 read`
- [Static variables](https://en.wikipedia.org/wiki/Static_variable)
- [Static variables 2](https://www.geeksforgeeks.org/c/static-variables-in-c/)

---

# AI Usage

AI tools were used only for:

- Improving documentation clarity
- Reorganizing structure
- Explaining theoretical concepts

All implementation decisions, debugging, and testing were done manually.

---

# Final Result

`get_next_line`:

- Efficiently reads one line at a time
- Manages memory safely
- Handles edge cases
- Works with any buffer size
- Supports multiple file descriptors
