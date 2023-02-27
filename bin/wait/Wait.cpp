/*
 * Copyright (C) 2009 Niek Linnenbank
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Wait.h"
#include <sys/wait.h>
#include <ProcessClient.h>



Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("It suspends the calling process until a child process ends or is stopped.");
    parser().registerPositional("PID", "Suspend execution until a child process ends or is stopped.");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    pid_t pid = atoi(arguments().get("PID"));

    const ProcessClient process;
    ProcessClient::Info info;


    const ProcessClient::Result result = process.processInfo(pid, info);

    if(waitpid(pid,0,0) == -1)
    {
        ERROR("Invalid PID " << strerror(errno));
        return IOError;
    }

    // Done
    return Success;
}