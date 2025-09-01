# Minishell: A Bash Shell Implementation

## Overview

The **Minishell** project is a simplified implementation of a UNIX shell written in C. It replicates basic shell behavior such as executing commands, handling redirections, and managing processes. The project helps understand how shells work under the hood, including parsing, process management, and file descriptors. 🐚⚙️🖥️

## Features

* Command execution with `execve`.
* Built-in commands:

  * `echo` (with `-n` option)
  * `cd` (with relative/absolute paths and `~`)
  * `pwd`
  * `export`
  * `unset`
  * `env`
  * `exit`
* Pipes (`|`) for inter-process communication.
* Input/output redirections (`<`, `>`, `>>`, `<<`).
* Environment variable expansion (`$VAR`).
* Signal handling (`Ctrl-C`, `Ctrl-\`, `Ctrl-D`) similar to bash.
* Robust error handling and exit codes matching bash behavior.

## Program Details

* **Program Name:** `minishell`
* **Usage:**

  ```bash
  ./minishell
  ```
* Minishell provides an interactive prompt where users can type commands and see results, just like a regular shell.

## Running the Program

1. Clone the repository:

   ```bash
   git clone https://github.com/MohammadHusssein/42-minishell.git
   cd 42-minishell
   ```
2. Compile the program:

   ```bash
   make
   ```
3. Run the shell:

   ```bash
   ./minishell
   ```

## Acknowledgements
A huge thank you to my partner [Razane Traoui](https://github.com/RznTr) for her dedication, teamwork, and countless hours spent debugging and building this project together, couldn’t have done it without you! 🙌👩‍💻👨‍💻


## License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT). Feel free to use, modify, and distribute with proper attribution. 📜🔓✨
