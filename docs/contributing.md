# Contributing to the R-Type

This document outlines the process for contributing to the Epitech R-Type project.

## Keep the code clean

1. **Naming & Case Conventions**

| Kind of identifier                                                | Case               | Example                                 |
| ---------------------------------------------------------------- | ------------------ | --------------------------------------- |
| **Variables / data members**                                     | `camelCase`        | `bufferSize`, `userCount`               |
| **Functions / methods / classes / structs / enums / namespaces** | `PascalCase`       | `RenderFrame()`, `AudioMixer`           |
| **Compile-time constants, macros, enum values**                  | `UPPER_SNAKE_CASE` | `MAX_RETRY_ATTEMPTS`, `FILE_OPEN_ERROR` |
| **Files and directories**                                        | `PascalCase`       | `AudioManager.cpp`, `NetworkUtils.h`    |

2. **Formatting**

- Indent with 4 spaces—never tabs.
- Insert a space around binary operators (`a + b`, `x != y`) and after commas.
- Put the opening brace on the same line as the declaration (`if (…) {`). Except for function definitions, where the opening brace should be on the next line.
- Keep line length reasonable (≈ 100 chars); wrap long expressions cleanly.

3. **Structure & Readability**

- Short, single-purpose functions. Aim for ≤ 40 lines; extract helper functions when a block starts to dominate.
- Return early to avoid pyramid-shaped code.
- Split deeply nested logic into separate functions.
- Replace literals with named `constexpr` values or `enum class` entries.
- Add comments only where intent isn’t obvious or when recording design rationale. Prefer `//` single-line comments; reserve `/* … */` for block explanations.
- You must code must be part of a class. You must not use global variables or functions. The variable member must be private.

4. **Consistency**

- Follow the existing style of the codebase. If you’re unsure, look at similar code or ask for guidance.
- The use of the keyword `using` is not allowed. Prefer `std::` or `namespace::` to avoid ambiguity.
- Use existing helper utilities and abstractions rather than introducing near-duplicates.

5. **Header Inclusion**

- Include exactly what you use.
- All `#include` directives appear at the very top of the file, before any code.
- Guard your own headers with `#pragma once`.
- No redundant includes. If a header is already included in a file, do not include it again.
- Local headers use double quotes `"Header.hpp"`. system or third-party headers use angle brackets `<header>`.
- List project local headers first, leave one blank line, then list system or third-party headers.

## Using Git

We are using Git for version control linked with Jira for task management. If you don't have access to Jira, please contact the [project manager](alan.cunin@epitech.eu).

1. **Use branches**

Jira create the branch for you. After that you can just checkout the branch with the name of your task.

```bash
git checkout -b <jira-task-name> # e.g. git checkout -b jira-1-initalize-repository
```

2. **Commit your changes**

You must follow the [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/) specification for your commit messages.

Each commit message consists of a short header, optional body and footer. The header has a special format that includes a type, an optional scope, and a subject. The header use the imperative, don't capitalize the first letter, as well as not dotting the end of the sentence. The footer must contain the Jira task linked to the branch you are working on.

The type of the header is one of the following:

| Type        | Description                                                                  |
| ----------- | ---------------------------------------------------------------------------- |
| `feat`      | A new feature                                                                |
| `fix`        | A bug fix                                                                     |
| `docs`      | Documentation only changes                                                   |
| `style`     | Changes that do not affect the meaning of the code (white-space, formatting) |
| `refactor`  | A code change that neither fixes a bug nor adds a feature                     |
| `test`      | Adding missing or correcting existing tests                                  |
| `build`     | Changes that affect the build system or external dependencies                |
| `ci`        | Changes to our CI configuration files and scripts                              |
| `chore`     | Other changes that don't modify src or test files                             |
| `revert`    | Reverts a previous commit                                                    |

Your commit message should be as descriptive as possible. Here is an example of a commit message:

```
feat: add new feature to the project

This commit adds a new feature to the project that allows users to do something amazing.

Jira task: JIRA-1234
```

Commit frequently and logically. For large changes, split your work into smaller commits—git add -p lets you stage hunks interactively.

3. **Submitting your changes**

Once you are done with your changes, you can create a pull request. The pull request must be linked to the Jira task you are working on. You can do this by adding the Jira task number in the title of the pull request.

The title of the pull request should resume the changes you made in a few words. Here is an example of a pull request title:

```
[JIRA-1234] Add new feature to the project
```

You must provide a description of the changes you made in the pull request. The description should be as descriptive as possible. Here is an example of a pull request description:

```
This pull request adds a new feature to the project that allows users to do something amazing.
```

The pull request must be reviewed by at least two other person before it can be merged, including the [technical lead](mael.bertocchi@epitech.eu).

4. **Merging your changes**

Once the pull request is approved, you can merge your changes into the main branch. The commit message must contain the Jira task number. Here is an example of a commit message:

```
[JIRA-1234] Merge pull request #123
```

You also can report the description of the pull request in the commit message description.

## Project Structure

The project is divided into several parts written in C++. Each part has its own directory and is responsible for a specific task.

- **Frontend**: This part is responsible for the user interface and the user experience.
- **Backend**: This part is responsible for the game logic and the game state.
- **Common**: This part holds the common code used by both the frontend and the backend.

The structure is duplicated in the `include` and `src` directories. The `include` directory contains the header files, while the `src` directory contains the source files.
