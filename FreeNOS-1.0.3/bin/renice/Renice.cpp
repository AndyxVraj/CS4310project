
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

// Renice header(C:/FreeNOS-1.0.3/bin/renice/Renice.h)
#include "Renice.h"

// Libary implementation
// Renice system header(C:/FreeNOS-1.0.3/lib/libposix/sys/renice/Renice.h)
#include "sys/renice.h"
// Process client header(C:/FreeNOS-1.0.3/lib/libruntime/ProcessClient.h)
#include <ProcessClient.h>

// Declared variables within the scope
int setLevel;
int processID;

Renice::Renice(int argc, char** argv) : POSIXApplication(argc, argv)
{
	parser().setDescription("Renice for a state change within the process");
    parser().registerPositional("Priority", "The current set priority of the process");
	parser().registerPositional("PID", "The Process ID of the named process");
	parser().registerFlag('n', "priority", "Parameter that sets a new priority to the process");
    setLevel = atoi(argv[2]);
    processID = atoi(argv[3]);
}

Renice::~Renice()
{
	// Nothing
}

// Execution method, performs system call on renicePID using user-provided Process ID.
Renice::Result Renice::exec()
{
    printf("\nProcess ID is: %d\n", processID);
    printf("\nChanged Priority is: %d\n", setLevel);
    bool result;
    ProcessClient process;

    // If priority is set less than 1 or greater than 5 (invalid)
    if (setLevel < 1 || setLevel > 5)
	{
        result = false;
        printf("\nPriority value of %d is invalid. ", setLevel);
    }
	// If check is false (valid)
    else
	{
        process.setPriority(processID, setLevel);
        result = true;
        printf("\nPriority value of %d is valid. ", setLevel);
    }
    
    // Print result prompt after check
    if (result == true)
	{
        printf("Process %d priority changed.\n", processID);
    }
    else
	{
        printf("Process %d priority has NOT been changed.\n", processID);
    }

    return Success;
}
