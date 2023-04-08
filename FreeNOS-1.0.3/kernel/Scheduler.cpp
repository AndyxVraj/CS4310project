/*
 * Copyright (C) 2015 Niek Linnenbank
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Log.h>
#include "Kernel.h"
#include "Scheduler.h"

Scheduler::Scheduler()
{
    DEBUG("");
}

Size Scheduler::count() const
{
    return m_queue.count();
}

Scheduler::Result Scheduler::enqueue(Process *proc, bool ignoreState)
{

    if (proc->getState() != Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " not in Ready state");
        return InvalidArgument;
    }

    //m_queue.push(proc);
    int pri = proc->getPriority();
    Scheduler::Result result;

    switch(pri)
    {
        case 1:
            m_queue.push(proc);
            result = Success;
            break;
        case 2:
            m_queue2.push(proc);
            result = Success;
            break;
        case 3:
            m_queue3.push(proc);
            result = Success;
            break;
        case 4:
            m_queue4.push(proc);
            result = Success;
            break;
        case 5:
            m_queue5.push(proc);
            result = Success;
            break;
    }

    return Success;
}

Scheduler::Result Scheduler::dequeue(Process *proc, bool ignoreState)
{
    if (proc->getState() == Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " is in Ready state");
        return InvalidArgument;
    }

    Size count = m_queue.count();
    Size count2 = m_queue2.count();
    Size count3 = m_queue3.count();
    Size count4 = m_queue4.count();
    Size count5 = m_queue5.count();


    // Traverse the Queue to remove the Process
    for (Size i = 0; i < count; i++)
    {
        Process *p = m_queue.pop();


        if (p == proc)
            return Success;
        else
            m_queue.push(p);
    }

    for (Size i = 0; i < count2; i++)
    {
        Process *p = m_queue2.pop();
        

        if (p == proc)
            return Success;
        else
            m_queue2.push(p);
    }

     for (Size i = 0; i < count3; i++)
    {
        Process *p = m_queue3.pop();
        

        if (p == proc)
            return Success;
        else
            m_queue3.push(p);
    }

     for (Size i = 0; i < count4; i++)
    {
        Process *p = m_queue4.pop();
        

        if (p == proc)
            return Success;
        else
            m_queue4.push(p);
    }

    for (Size i = 0; i < count5; i++)
    {
        Process *p = m_queue5.pop();


        if (p == proc)
            return Success;
        else
            m_queue5.push(p);
    }

    


    FATAL("process ID " << proc->getID() << " is not in the schedule");
    return InvalidArgument;
}

Process * Scheduler::select()
{
    if (m_queue5.count() > 0)
    {
        Process *p = m_queue4.pop();
        m_queue5.push(p);

        return p;
    }

    if (m_queue4.count() > 0)
    {
        Process *p = m_queue4.pop();
        m_queue4.push(p);

        return p;
    }

    if (m_queue3.count() > 0)
    {
        Process *p = m_queue3.pop();
        m_queue3.push(p);

        return p;
    }

    if (m_queue2.count() > 0)
    {
        Process *p = m_queue2.pop();
        m_queue2.push(p);

        return p;
    }

    if (m_queue.count() > 0)
    {
        Process *p = m_queue.pop();
        m_queue.push(p);

        return p;
    }


    return (Process *) NULL;
}
