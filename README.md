# SIMPLE SHELL

This is a simple shell that mimics the normal functioning of the already developed ones such as bash, c-shell, z-shell, sh-shell amongst others with minimal functionalities. The main functionalities are traced from /*sh*/ that can be located within /bin/sh directory  
## HOW MY SHELL WORKS
* On compilation and execution of the shell executable, just like a normal shell, the user will be prompted for user input. This is made possible with the `getline` fuctions that comes defined with the system. 
> We will see the use of a variety of system calls to enable our interaction with the system kernel successful
* The user input is then stored in a buffer that is allocated to the heap memory so that it can exist throughout it's required lifetime.
> It will be fed to the `execve` system call that will execute a command input by a user.
* The input string is then tokenised so as to store the commands seperately using the strtok() function that seperates with the space delimiter (the scope of the project requirements). The strtok() function will provide pointers to the commands of which I copy in the heap memory using strdup() function.  
> I duplicate the pointer to the initial user input since strtok() breaks/destroys the string that it tokenizes. It will also be observed in future operations when using the function. The duplicate string also has to be freed to avoid memory leaks after successful tokenization.  
* The pointer to the tokens is then fed to the execute function so as it may be executed by the appropriate command executables.  
> The command executable will be the command in the [0] index of the tokens from the tokenizer function.  
`NOTE`: All commands in the systems are either build-in or executables that can be located within the 'PATH' environmental variable, and the `comand_path and check_path` function utilize the PATH to find the executable. Absolute commands entries, like /bin/ls, are executed by the check_path function while single line commands, like ls and pwd, are handled by command_path.  
* If the command is found, **using the stat() system call**, then a child process will be created with `fork system call`.  
* This ends up using `execve system call` with the command as the 1st paramenter, the tokens as the second, and env, as the third, of which handles the environmental variable.  


With my implementation, I am able to:
### Accept user input
* using getline() function
* implemented in the shell.c file

### Tokenize the input to seperate the commands
* Using strtok() function
* implemented in the tokenizer.c file

### Establish if the command is available
* Using the stat() function
* implemented in the parser.c file
> for absolute path commands(paths to the actual exe file), as well as execution of files in current diecetory, the check_path() function handles that. 
> For shorthand commands like ls/pwd, command_path() function is alterd to use PATH to find the binary executable file to it.

### Fork a child process to execute a command and invoke the parent to wait for the child process
* using the wait() function  

### Handle memory leaks withing the system to prevent reachable memory or any leaks of any sort
* made possible by using free() function


##All are welcomed to contribute to the project and offer further improvements.

