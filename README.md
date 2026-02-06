*This project has been created as part of the 42 curriculum by csekakul.*

# Description

TODO: clean up this section, because it's chaotic

My approach of this challange is the following:
- I am going to open a file referenced by the file descriptor using `open()`.
- Start scanning through the file with `read()`, reading nbyte characters at a time (let's say 5). The size of the buffer will be defined at compilation, so the size can vary. It is at compilation when you will directly tell `read` how much you want to read in the file at once.
- You can imagine the `read` function as the cursor, `read` remembers the position of the cursor, it associates it with the file descriptor.
- At each call to the function *get_next_line*, `read` returns either 5 (the size of the buffer, characters read), a smaller number in case there aren't 5 characters left or 0 if we reached the end of the file.
- We put the scanned characters in a variable called *buffer* and use *strjoin* to store the value in a **static variable** called *stash*. Using a static variable ensures that we don't loose the value between function calls. We have to do this, because otherwise *buffer* would be overwritten each time.
- Then in each function call, we need to check *stash*. Need to check if ther is a "\n" indicatinig the end of the line. In case we indeed found a "\n", we copy the content of *stash* into the variable *line*, but only until the "\n" cahracter. The rest of the characters we leave in the *stash*, and it won't get lost thanks to being a static variable.
- Here come the **linked lists** into the picture. We could also save our *stash* in a single variable as a string, but using linked lists has certain advantages in terms of execution speed. And I also want to practice them. 
- *get_next_line* returns a character string which corresponds to the line which is read in the file. This character string will be our variable *line*.
- After saving a line in *line*, we need to clean up *stash* with `free`. But only the exact same thing we just saved in *line*, the rest we leave for the next round.

-> So *stash* is a static variable and also a linked list? What are the elements of the linked list?
-> *line* is just a simple char *?

## `read()`

- Prototype: ssize_t read(int fildes, void *buf, size_t nbyte);
- Description: read() attempts to read nbyte bytes of data from the object referenced by the descriptor fildes into the buffer pointed to by buf. On objects capable of seeking, the read() starts at a position given by the pointer associated with fildes. Upon return from read(), the pointer is incremented by the number of bytes actually read.
- Returns: If successful, the number of bytes actually read is returned. Upon reading end-of-file, zero is returned. Otherwise, a -1 is returned and the global variable errno is set to indicate the error.

## `open()`

- Prototype: int open (const char* path, int flags [, int mode ]);
- Path corresponds to the title of the file that I want to open/create. Or it can also refer to the file's lovation, if I am not working in the same directory as the file, I can provide an absolute path with "/".
- Flags: I have to tell my function what kind of access I want, this is done with flags.
	- O_RDONLY: In read-only mode, open the file.
	- O_WRONLY: In a write-only mode, open the file
	- O_RDWR: Open the file in reading and write mode
	- O_CREAT: This flag is applied to create a file if it doesn’t exist in the specified path or directory
	- O_EXCL: Prevents the file creation if it already exists in the directory or location.
- Return value: The return value of open() is a file descriptor, a small, nonnegative integer that is an index to an entry in the process' table of open file descriptors. If there is an error somewhere, the function will return -1 as a synonym of faliure.
- Example
	```C
	int main()
	{
    	int fd;
    	fd = open("text.txt", O_RDONLY);
	}
	```
## static variables
- A static variable is declared using static keyword and have the property of retaining their value between multiple function calls. It is initialized only once and is not destroyed when the function returns a value. It extends the lifetime of the variable till the end of the program.
- Example
```C
int fun()
{
	static int count = 0;
	count++;
	return count;
}

int main()
{
    printf("%d ", fun());
	printf("%d ", fun());
	return 0;
}
```
- Global static variables: Static variables are generally declared inside functions, but they can also be declared outside functions (at the global scope). Global static variables have their scope limited to the file they are defined in (internal linkage). It means that they cannot be accessed outside the current translation unit (C source file).
- Example
```C
static int globalVar = 5;

void display()
{
	printf("%d\n", globalVar);
}
int main()
{
	display();  
 	globalVar = 10;
 	display();  
	return 0;
}
```
### Local vs Static Local Variables

|Local Variable|Static Variable|
| :------: | :-----: |
|Local to hte function or block|Local to the function or block|
Exits only during function execution|Exits throughout the program execution|
|Reinitialized each time function is called|Initialized only once|
|Stored in the stack|Stored in the data segment|

### Important properties
1. Uninitialized Static Variables have 0 value.
2. Static local variables are initialized only once and stay throughout the program's life.
3. Static local variables have internal linkage.

# Instructions

# Resources
- [Overview of the project](https://www.youtube.com/watch?v=-Mt2FdJjVno&t=157s)
- [Gitbook guide](https://42-cursus.gitbook.io/guide/1-rank-01/get_next_line/open-and-read)
- [Static variables](https://www.geeksforgeeks.org/c/static-variables-in-c/)
- [GNL guide](https://yannick.eu/gnl/)
- man 2 read
