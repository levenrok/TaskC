# TaskC

TaskC is a command-line task management application built with C and SQLite. It provides a simple interface to add, view, and delete tasks, making it easier to manage your productivity from the terminal.

## Features

- **Show all tasks**: View a list of tasks that are yet to be completed.
- **Add task**: Add new tasks to the list.
- **Delete task**: Delete tasks by ID.
- **Exit**: Exit the application.

## Requirements

- **SQLite3**: Ensure that SQLite3 is installed on your system.
- **Clang Compiler**: Required to compile the C code.
- **Make**: Build system used in the project

## Setup

1. **Clone the repository**:
    ```bash
    git clone https://github.com/levenrok/task-c.git
    cd task-c
    ```

2. **Compile the code using Make**:
    ```bash
    make
    ```

3. **Run the program**:
    ```bash
    ./build/taskc
    ```

## Usage

- On running the program, you will see the following options:

    ```
    1. Show all tasks
    2. Add task
    3. Delete task
    4. Exit
    ```

- Select an option by entering the corresponding number.
- For adding tasks, enter a title for the task when prompted.
- For viewing all tasks, select "Show all tasks" to see a list of tasks marked as "not done."
- To delete a task, choose "Delete task".

## Code Overview

The code includes the following key functions:

- **retrive_tasks**: Queries the SQLite database for all tasks.
- **print_task**: Prints out each task to the terminal.
- **insert_task**: Inserts a new task into the database.
- **delete_task**: Deletes a task from the database using the task id.
- **Database setup**: On the first run, a `tasks.db` SQLite database will be created with a `Tasks` table.

## Future Enhancements

- Add feature to mark tasks as "done" or "incomplete."
- Improve program ui.
- Improve performance using threads.
- Improve error handling.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
