#ifndef KDMTASKMANAGER_H
#define KDMTASKMANAGER_H

#include "export.h"

#include <QThread>
#include <QMap>
#include <QPair>

namespace AD {

class ADTaskManager;

class  ADSERVERSHARED_EXPORT Task : public QThread
{
    Q_OBJECT

public:
    explicit Task(QObject* parent = 0): QThread(parent){}

public:
    virtual int percent() = 0;
    virtual int status() = 0;
    virtual QString text() = 0;

public:
    int GetID(){return m_id;}

private:
    void SetID(int id);

private:
    int m_id;

    friend class ADTaskManager;
};

class ADSERVERSHARED_EXPORT ADTaskManager : public QObject
{
    Q_OBJECT

public:
    explicit ADTaskManager(QObject * parent = 0);

public:
    int AddTask(Task* task);
    bool RemoveTask(int id);
    QList<Task*> GetAllTasks();
    Task* GetTask(int id);

private:
    bool StartTask(int id);

private:
    QMap<int, Task* > m_tasks;
    int m_index;
};

}

#endif // KDMTASKMANAGER_H
