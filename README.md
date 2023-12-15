# SIMPLE SHELL

This is a simple shell that mimics the normal functioning of the already developed ones such as bash, c-shell, z-shell, sh-shell amongst others with minimal functionalities.  
## HOW MY SHELL WORKS
* Just like the normal shell, one execution of my shell executable, the user will be prompted for user input. This is made possible with the getline fuctions that comes defined with the system. (~we will see the use of a variety of system calls to enable our interaction with the system kernel successful as a means of accessing the kernel~)
* The user input is then stored in a buffer that is allocated to the heap for further operation
* The input string is then tokenised so as to store the commands seperately using the strtok function that seperates with the space delimiter (the scope of the project requirements). The strtok() function will provide pointers to the commands separated bu the space delimeter of which I later store in the heap memory using strdup() function.  
NOTE: I duplicate the pointer to the initial user input since strtok() breaks/ destroys the string that it tokenizes. It will also be observed in future operations. The duplicate string also has to be freed to avoid memory leaks.
* The pointer to the tokens is then fed to the execute function so as it may be executed by the appropriate command executables.
NOTE: All commands in the systems are either build-in or executables tht can be located within the 'PATH' environmental variable.
