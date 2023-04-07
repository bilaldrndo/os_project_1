# Operating Systems - Project 1: Shell (5th Topic)

## Basic Infomation:

### Members:
- Bilal Drndo
- Dželila Tinjak

### Files:
```
    .
    ├── project_code.c          
    ├── project_compiled                
    ├── sample_text.txt
    ├── [OS][Shell Project] 5.pdf
    └── README.md
```

*Note: `sample_text.txt` file is there in order to test the `cat()` function*

### Outline:
In this project, we have created a custom terminal app in C programming language where we implemented all of the required requirements that were given to us in the `[OS][Shell Project] 5.pdf` file.

### Instructions for Compiling:
1. Make sure that You have installed a C compiler on Your Computer. If not, You can download it by following [this](https://itsourcecode.com/c-tuts/environment-setup-in-c-programming-language/) tutorial.
2. Open a new Terminal Window and change Your working directory to this project. Example: `cd /path/to/this/directory/`.
3. Compile the project by typing in `gcc -o project_compiled project_code.c`.
4. Run the project by typing in `./project_compiled`.
5. Have Fun!

### Sources/Tutorials that we have used:
- https://learning.ibu.edu.ba/pluginfile.php/113346/mod_resource/content/1/shell-skeleton.txt
- https://brennan.io/2015/01/16/write-a-shell-in-c/
- https://www.geeksforgeeks.org/making-linux-shell-c/

---

## Answers to Questions:

### Task 1.1: The shell
***Advanced: The prompt should look like this: machinename@username:~$***
```c
char username[1024];
char machinename[1024];
getlogin_r(username, sizeof(username));
gethostname(machinename, sizeof(machinename));

printf("\033[0;32m%s@%s:\033[0m\033[0;34m~\033[0m$ ", machinename, username);
```

### Task 1.2: Shell programs/commands
***Basic: Implement the basic functionality of the following programs: rm, cat, clear, cowsay.***
```c
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
```

***Intermediate: Provide a few options and/or arguments for at least two programs. Additional points for creativity (e.g. implementing something that does not exist in bash, or differently than it is done in bash).***
```c
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
```

### Task 1.3: System calls
***Basic: Within the C-programming example of your choice, implement the following system calls: fork(), wait(), and exec().***
```c
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
```

***Intermediate: Within the C-programming example of your choice, implement kill(), execv().***
```c
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
```

***Additionally: Carefully explore and then implement the forkbomb.***
```c
int forkbomb()
{
    printf("Forkbombing....\n");
    while (1)
    {
        fork(); // Create unlimited number of forks
    }
    return 0;
}
```

### Task 1.4:
***Add some colors to your shell and name***
```c
printf("\033[0;32m%s@%s:\033[0m\033[0;34m~\033[0m$ ", machinename, username);
// and
printf("\033[0;31mError: Command not found: %s\033[0m\n", tokens[0]);
```

### Task 1.5:
***Provide a concise and descriptive answer to the following questions.***

**Question 1: What does the `mmap()` function do?**

*In Unix-based operating systems, the mmap() function is a system call that enables a process to map a file or a section of a file into its own address space. This enables speedy and adaptable I/O operations by giving processes a mechanism to access files as if they were in the process' own memory. The mmap() method allows you to access memory from the operating system as well. By providing the appropriate options, mmap() can enable your program to establish an anonymous memory region that is linked to swap space rather than a specific file. The memory can then be handled and treated similarly to a stack. A program can allocate memory that is the size of a page using the mmap() system function.*

**Question 2: What happens during a context switch? Do we want the OS to perform many or few context switches? Explain.**

*A context switch is the process by which the operating system saves the state of a running process and restores the state of a different process so that it can run on the CPU. When the OS has regained control, a decision has to be made: whether to continue running the currently-running process, or switch to a different one. This decision is made by a part of the operating system known as the scheduler which has two parts: policy - to pick which process to run & mechanism - to switch to that process.
If the decision is made to switch, the OS then executes a low-level piece of code which we refer to as a context switch. All the OS has to do is save a few register values for the currently-executing process and restore a few for the soon-to-be-executing process. By doing this, the OS makes sure that when the return-from-trap instruction is ultimately issued, the system restarts execution of a different process rather than going back to the one that was already executing. To save the context of the currently-running process, the OS will execute some low-level assembly code to save the general purpose registers, PC, and the kernel stack pointer of the currently-running process, and then restore said registers, PC, and switch to the kernel stack for the soon-to-be-executing process. By switching stacks, the kernel enters the call to the switch code in the context of one process (the one that was interrupted) and returns in the context of another (the soon-to-be-executing one). When the OS then finally executes a return-from-trap instruction, the soon-to-be-executing process becomes the currently-running process. And therefore the context switch is complete.
How long does something like a context switch take? There is a tool called lmbench that measures exactly those things, as well as a few other performance measures.
Given that each switch adds a minor overhead in terms of time and resources, the OS should ideally conduct as few context switches as possible. However, context switches are necessary to make sure that numerous processes may share a CPU in a fair and effective manner and to stop one rogue process from controlling the CPU.
Therefore, while reducing context shifts is preferred, it's also crucial to balance responsiveness and efficiency.*


