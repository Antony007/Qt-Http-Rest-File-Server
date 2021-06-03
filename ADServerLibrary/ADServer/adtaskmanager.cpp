#include "adtaskmanager.h"

using namespace AD;

void Task::SetID(int id)
{
    m_id = id;
}

ADTaskManager::ADTaskManager(QObject *parent) : QObject(parent)
{
    m_tasks.clear();
    m_index = 0;
}

int ADTaskManager::AddTask(Task *task)
{
    int index =m_index;
    m_index++;
    task->SetID(index);
    m_tasks.insert(index,task);
    if(StartTask(index))
        return index;
    else
        return 1;
}

bool ADTaskManager::RemoveTask(int id)
{
    if (m_tasks.contains(id))
    {
        Task* task = m_tasks.value(id);
        if(task->isRunning())
        {
            task->quit();
            task->wait();
        }
        m_tasks.remove(id);
        task->deleteLater();
        return true;
    }
    else
    {
        return false;
    }
}

QList<Task *> ADTaskManager::GetAllTasks()
{
    QList<Task*> taskLists;
    taskLists.clear();

    QMapIterator<int, Task* > i(m_tasks);
    while (i.hasNext()) {
        i.next();
        taskLists.append(i.value());
    }

    return taskLists;
}

Task *ADTaskManager::GetTask(int id)
{
    if (m_tasks.contains(id))
    {
        return m_tasks.value(id);
    }
    else
    {
        return NULL;
    }
}

bool ADTaskManager::StartTask(int id)
{
    if (m_tasks.contains(id))
    {
        Task* task = m_tasks.value(id);
        task->start();
        return true;
    }
    else
    {
        return false;
    }
}
