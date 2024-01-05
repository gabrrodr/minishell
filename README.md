# minishell
<p align="center">
  <a href="https://github.com/maiadegraaf">
    <picture>
    <img alt="philosophers" src="https://user-images.githubusercontent.com/68693691/193606493-2969e425-6bad-44ce-97af-89fec62bee22.gif" width=500>
    </picture>
  </a>
</p>

*A mini recreation of bash.  Implementing previously learned concepts like file descriptors and processes.  Made with [Alfred Polycarpe](https://github.com/Alfredpoly).*

## Table of Contents
- [The Challenge](#the-challenge)
  - [What Is Bash and How Does It Work?](#what-is-bash-and-how-does-it-work)
- [Implementation](#implementation)
- [My Take Away](#my-take-away)
- [Installation](#installation)

## The Challenge
This is the biggest project I've done so far, and the first one I did in a group.  The goal was to create a version of bash.  We had to learn how bash takes arguments, parses them, and executes them. We also had to incorporate the following features, among others:
- Display a promt while waiting for a new commmand.
- Have a working history.
- Find and launch executables (using the `PATH` variable or an absolute path).
- Handle `'` (single) and `"` (double) **quotes** like in bash.
- Implement **redirections** such as:
  - `<` redirect input.
  - `>` redirect output.
  - `<<` heredoc (doesn't affect history).
  - `>>` redirect output in append mode.
- Implement `|` (**pipes**).
- Handle **environment variables**.
- Handle `$?`.
- `ctrl-C`, `ctrl-D`, and `ctrl-\` should behave like in bash.
- Recreate the following **builtins**:
  - `echo` with option `-n`.
  - `cd` with only a relative or absolute path.
  - `pwd` (no flags).
  - `export` (no flags).
  - `unset` (no flags).
  - `env` (no flags or arguments).
  - `exit` (no flags).

We didn't have to implement && and ||, or wildcards, as well as any special symbols that weren't specifically asked for in the subject.  We were also told that when in doubt, take bash as a reference.  This sometimes led to discussions on wether or not we had to implement something, the result of which was usually "probably??? 🤷‍♀️".

### What Is Bash and How Does It Work?
The shell is a program that the user can use to interact with an operating system's services. Bash is the GNU shell, and is currently the most common shell program.  We took the challenge of recreating bash very literally, so the first thing we did was learn how bash actually works.  Essentially it breaks down the process into 4 steps: `lexer` → `parser` → `expander` → `executor`, which we replicated in our project. 

![bash steps](https://user-images.githubusercontent.com/68693691/193665518-0c0c7fec-38a9-4f6c-91ca-fef606abfb0d.png)

## My Take Away
As previously mentioned, this was the first project I did in a group, which for me was an overall joyful experience.  This is a huge and daunting project and doing it alone would have been a massive challenge and it wouldn't have taken only a couple months. I think we divided up the different parts of the project very well, while also supporting each other if we ran into issues.  Although we each wrote most of our parts, we both contributed in every single function of the program, either when we were first writing them or when it was time to fix bugs and leaks.

By far the hardest part of this project was handling all the edge cases.  Before handing in the project we had done our best to manage all of the ones we we're aware of, which was a considerably long list.  Often by solving one case, we would break another part of our code.

## Installation
### Clone the repository:
``` 
git clone https://github.com/gabrrodr/minishell.git
cd minishell
make
```
### Run Minishell
```
./minishell
```
