# File Pointers

## fopen()

- Opens a file and returns a file pointer to it

`FILE* ptr = fopen(<filename>, <operation>);`

`<operation>` takes `"r"` for reading or `"w"` for writing, and `"a"` for appending. Append would go to the end of the file and add it from there.

## fclose()

- Closes the file pointed to by the given pointer

`fclose(<file pointer>);`

## fgetc()

- Generally translates to file, get character
- Reads and returns the next character from the file pointed to
- The pointer must be from `fopen(<filename>, "r")`, won't work if `"w"`

`char ch = fgetc(<file pointer>);`

Example use case:
```c
char c;
while ((ch = fgetc(ptr)) != EOF)
  printf("%c", ch);
```

This is essentially what a `cat` command in a terminal would do.

## fputc()

- Writes or appends the specified character to the appointed-to file 
- The pointer must be from `fopen(<filename>, "w")`, won't work if `"r"`

`fputc(<character>, <file pointer>);`

Example use case:
```c
char c;
while ((ch = fgetc(ptr)) != EOF)
  fputc(ch, ptr2);
```
Where ptr2 is a pointer to a second pointer to a second file. This is essentially the `cp` command on a terminal.

## fread()

- Reads `<qty>` units of size `<size>` from the file appointed to and stores them in memory in a buffer (usually and array) pointed by `<buffer>`
- The pointer must be from `fopen(<filename>, "r")`, won't work if `"w"`

`fread(<buffer>, <size>, <qty>, <file pointer>);`

Example:
```c
int arr[10];
fread(arr, sizeof(int), 10, ptr);
```
- Reading 40 bytes of information
- And we are storing them in an array called `arr`

Or,

```c
double* arr2 = malloc(sizeof(double) * 80);
fread(arr2, sizeof(double), 80, ptr);
```

Or,

```c
char c;
fread(&c, sizeof(char), 1, ptr);
```
Since we only want one character, we don't need an array.

## fwrite()

- Reads `<qty>` units of size `<size>` from the file appointed to and stores them in memory in a buffer (usually and array) pointed by `<buffer>`
- The pointer must be from `fopen(<filename>, "w" or "a")`, won't work if `"r"`

`fwrite(<buffer>, <size>, <qty>, <file pointer>);`

Example:
```c
int arr[10];
fwrite(arr, sizeof(int), 10, ptr);
```

Or,

```c
double* arr2 = malloc(sizeof(double) * 80);
fwrite(arr2, sizeof(double), 80, ptr);
```

Or,

```c
char c;
fwrite(&c, sizeof(char), 1, ptr);
```