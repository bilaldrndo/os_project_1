#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_COMMAND_LENGTH 1024

// Task 1.2
// Basic: Implement the basic functionality of the following programs: rm, cat, clear, cowsay.
int rm(char *filename)
{
    // Remove a file
    if (unlink(filename) == -1)
    {
        printf("Error:");
        perror("rm");
        return -1;
    }
    return 0;
}
int cat(char *filename)
{
    // Display the contents of a file
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("cat");
        return -1;
    }

    char line[1024];
    while (fgets(line, 1024, fp) != NULL)
    {
        printf("%s", line);
    }

    printf("\n");

    fclose(fp);
    return 0;
}
void clear()
{
    // Clear the terminal screen
    printf("\033[2J\033[H");
}
int cowsay(char *message)
{
    // Display a cow saying a message
    printf("< %s >                    \n", message);
    printf("       \\    ^__^ \n");
    printf("        \\   (oo)\\_______ \n");
    printf("            (__)\\       )\\/\\ \n");
    printf("                ||----w | \n");
    printf("                ||     || \n");
    return 0;
}

// Task 1.2
// Intermediate: Provide a few options and/or arguments for at least two programs.
// Additional points for creativity (e.g. implementing something that does not exist in bash, or differently than it is done in bash)
int displayACowboyRobot(char *message)
{
    // Display a cowboy robot with ot without a hat
    if (strcmp(message, "hat") == 0)
    {
        printf("     __________     \n");
        printf("_____|        |_____\n");
        printf("|__________________|\n");
        printf("    |         |    \n");
        printf("    |  _   _  |    \n");
        printf("    |         |    \n");
        printf("    |  _____  |    \n");
        printf("    |_________|    \n");
    }
    else if (strcmp(message, "nohat") == 0)
    {

        printf("    ___________\n");
        printf("    |         |    \n");
        printf("    |  _   _  |    \n");
        printf("    |         |    \n");
        printf("    |  _____  |    \n");
        printf("    |_________|    \n");
    }
    return 0;
}
int cd(char *path)
{
    // Change directory
    if (chdir(path) == -1)
    {
        printf("\033[0;31mError: %s directory not found\033[0m\n", path);
    }
    return 0;
}

// Task 1.3
// Basic: Within the C-programming example of your choice, implement the following system calls: fork(), wait(), and exec().
int forkWaitExecProgramExampleToGetCurrenDirecotyList()
{
    pid_t pid;
    int status;

    pid = fork(); // Create a new child process
    if (pid < 0)
    {
        // Error occurred
        printf("Fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        // Child process
        printf("This is the child process, process ID is %d\n", getpid());
        execlp("/bin/ls", "ls", NULL); // Execute the ls command
        perror("execlp");              // Only reached if execv fails
        exit(1);
    }
    else
    {
        // Parent process
        wait(&status); // Wait for child to exit
        printf("Child process has finished executing.\n");
    }

    return 0;
}

// Task 1.3
// Basic: Within the C-programming example of your choice, implement kill(), execv().
int implementKillExecvAndCreateANewDirectory(char *dirName)
{
    pid_t pid;
    int status;

    pid = fork(); // Create a new child process
    if (pid < 0)
    {
        // Error occurred
        printf("Fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        // Child process
        printf("This is the child process, process ID is %d\n", getpid());
        char *args[] = {"-p", dirName, NULL};
        execv("/bin/mkdir", args); // Execute the cd command
        perror("execv");           // Only reached if execv fails
        exit(1);
    }
    else
    {
        // Parent process
        kill(pid, SIGINT); // Send SIGINT signal to child process
        wait(&status);     // Wait for child to exit
        printf("Child process has finished executing.\n");
    }

    return 0;
}

// Task 1.3: Carefully explore and then implement the forkbomb
// Definition: A forkbomb is a type of denial-of-service attack that involves rapidly creating new processes until the system becomes overwhelmed and crashes.
// HIGHLY IMPORTANT: DO NOT RUN THIS PROGRAM SINCE IT WILL CRASH YOUR SYSTEM i.e. don't type forkbomb command in the terminal prompt
int forkbomb()
{
    printf("Forkbombing....\n");
    while (1)
    {
        fork(); // Create unlimited number of forks
    }
    return 0;
}

int main(int argc, char *argv[])
{
    printf("****************************\n");
    printf("Welcome to the magic console\n");
    printf("Made by: Bilal & Dzelila \n");
    printf("****************************\n");

    char username[1024];
    char machinename[1024];
    getlogin_r(username, sizeof(username));        // Get username
    gethostname(machinename, sizeof(machinename)); // Get hostname

    while (1)
    {
        char command[MAX_COMMAND_LENGTH]; // Initialize command

        // Task 1.1 & 1.4
        // The shell name: machinename@username:~$
        // Add some colors to your shell and name
        printf("\033[0;32m%s@%s:\033[0m\033[0;34m~\033[0m$ ", machinename, username);

        fgets(command, MAX_COMMAND_LENGTH, stdin);

        // Remove newline character from command
        int length = strlen(command);
        if (command[length - 1] == '\n')
        {
            command[length - 1] = '\0';
        }

        // Tokenize command string
        char *tokens[MAX_COMMAND_LENGTH];
        char *token = strtok(command, " ");
        int token_count = 0;

        while (token != NULL)
        {
            tokens[token_count] = token;
            token_count++;
            token = strtok(NULL, " ");
        }
        tokens[token_count] = NULL;

        if (tokens[0] == NULL)
        {
            // If no command was entered, continue to next prompt
            continue;
        }
        else if (strcmp(tokens[0], "exit") == 0)
        {
            // If exit command was entered, it will end the program
            return 0;
        }
        else if (strcmp(tokens[0], "rm") == 0)
        {
            // If rm command was entered, it will remove the file that has been specified
            if (token_count < 2)
            {
                printf("Usage: rm [filename]\n");
            }
            else
            {
                rm(tokens[1]);
            }
        }
        else if (strcmp(tokens[0], "cat") == 0)
        {
            // If cat command was entered, it will print out the file that it has been specified
            if (token_count < 2)
            {
                printf("Usage: cat [filename]\n");
            }
            else
            {
                cat(tokens[1]);
            }
        }
        else if (strcmp(tokens[0], "clear") == 0)
        {
            // If clear command was entered, it will clear the previous prompt
            clear();
        }
        else if (strcmp(tokens[0], "cowsay") == 0)
        {
            // If cowsay command was entered, it will display that text in a way where the cow will say it
            if (token_count < 2)
            {
                printf("Usage: cowsay [message]\n");
            }
            else
            {

                // Combine all of from words from tokens array except the one in the 0th place tokens[0] into one
                char message[MAX_COMMAND_LENGTH] = "";
                for (int i = 1; i < token_count; i++)
                {
                    strcat(message, tokens[i]);
                    if (i != token_count - 1)
                    {
                        strcat(message, " ");
                    }
                }

                // Pass the full message to the cowsay() function
                cowsay(message);
            }
        }
        else if (strcmp(tokens[0], "displayacowboyrobot") == 0)
        {
            // If displayacowboyrobot command was entered, it will display a cowboy robot
            if (token_count < 2)
            {
                printf("Usage: displayacowboyrobot [parameter hat or nohat]\n");
            }
            else
            {
                displayACowboyRobot(tokens[1]);
            }
        }
        else if (strcmp(tokens[0], "cd") == 0)
        {
            // If cd command was entered, it will change the directory to the requested path
            char *path;
            if (token_count < 2)
            {
                // If there is no parameter, it will automatically set path to the default HOME path
                path = getenv("HOME");
            }
            else
            {
                path = tokens[1];
            }

            cd(path);
        }
        else if (strcmp(tokens[0], "ls") == 0)
        {
            // If ls command was entered, it will list all of the files in the current working directory
            forkWaitExecProgramExampleToGetCurrenDirecotyList();
        }
        else if (strcmp(tokens[0], "mkdir") == 0)
        {
            // If mkdir command was entered, it will create a new directory with a name that user specifies in the current working directory
            if (token_count < 2)
            {
                printf("Usage: mkdir [dicrectory name]\n");
            }
            else
            {
                implementKillExecvAndCreateANewDirectory(tokens[1]);
            }
        }
        // HIGHLY IMPORTANT: DO NOT RUN THIS PROGRAM SINCE IT WILL CRASH YOUR SYSTEM i.e. don't type forkbomb command in the terminal prompt
        else if (strcmp(tokens[0], "forkbomb") == 0)
        {
            // If forkbomb command was entered, it will spawn fork() function endlessly and crash the computer
            forkbomb();
        }
        else
        {
            // Task 1.4
            // Add some colors to your shell and name.
            printf("\033[0;31mError: Command not found: %s\033[0m\n", tokens[0]);
        }
    }
}