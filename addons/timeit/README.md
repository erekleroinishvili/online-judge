# Timeing Program Execution on Windows

## Utility for Competitive Programming

## Description

Windows doesn’t provide a convenient way to measure the execution time of a program—especially when it involves reading from and writing to standard input and output. `timeit` solves this problem for me, and I find it especially useful in competitive programming.

## Usage

1. Save the code in a text file with a `.bat` extension (e.g., `timeit.bat`).
**Note:** Do **not** name it `time.bat`, as `time` is an existing Windows command with different functionality.

2. Place `timeit.bat` somewhere in your system's `%PATH%`, so it can be accessed from any directory.

3. Now you can run `timeit`, and it will display three different usage options:

    - One of the options lets you provide input data directly on the command line. Your program will receive it through standard input!

    - For example, if you run the following command, `add.exe` will receive `2 4 5` via standard input:
      ```shell
      timeit add.exe 2 4 5
      ```

    - This might even work if you manually enter 200,000 positive integers from the keyboard (though I haven’t tested that 😉).

## Background

### macOS, Unix, Linux, Ubuntu

If you’re on macOS or another Unix-like system, you’re probably smiling right now. That's because you have access to a handy little utility called `time`. Problem solved!

The `time` utility does exactly what we need, and it’s easy to use—provided you're comfortable with input redirection:

```shell
time mytask < in.txt
```

### Windows

Windows Server 2003—released two years before I was born—apparently included a similar utility called `timeit`. Unfortunately, Microsoft removed it from later versions of Windows. It was replaced with the more complex and less convenient `Measure-Command` in PowerShell.

### Goal

I wanted to re-create the original `timeit` experience on Windows: a simple tool that lets you send input data to a compiled `.exe` file, measure its execution time with precision, show its output, and report the program’s exit code.

For example, if I have a program `add.cpp` that reads three numbers from standard input and adds them, I want to be able to time its execution like this:

```shell
timeit add.exe 2 4 5
```
