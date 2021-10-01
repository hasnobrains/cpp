#ifdef MYENV

#include <iostream>
#include <map>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;


// Перечислимый тип для статуса задачи
enum class TaskStatus
{
    NEW,         // новая
    IN_PROGRESS, // в разработке
    TESTING,     // на тестировании
    DONE         // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

string GetStatusString(TaskStatus status)
{
    map<TaskStatus, string> m = {{TaskStatus::NEW, "NEW"},
                                 {TaskStatus::IN_PROGRESS, "IN_PROGRESS"},
                                 {TaskStatus::TESTING, "TESTING"},
                                 {TaskStatus::DONE, "DONE"}};

    return m[status];
}

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks)
{
    cout << "{";
    for (TasksInfo::iterator it = tasks.begin(); it != tasks.end(); it++)
    {
        cout << (it != tasks.begin() ? ", " : "") << "\""
             << GetStatusString(it->first) << "\": " << it->second;
    }
    cout << "}";
}

void PrintTasksStatuses(vector<TaskStatus> tasks)
{
    cout << "[";
    for (int i = 0; i < tasks.size(); ++i)
    {
        cout << (i != 0 ? ", " : "") << "\"" << GetStatusString(tasks[i])
             << "\"";
    }
    cout << "]" << endl;
}

#endif
#include <algorithm>
#include <vector>
class TeamTasks
{
  public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const
    {
        return tt.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person) { ++tt[person][TaskStatus::NEW]; }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person,
                                                   int task_count)
    {
        TasksInfo updated_tasks, untouched_tasks;
        TasksInfo& tasks = tt[person];

        vector<TaskStatus> task_statuses;

        for (auto& [status, count] : tasks)
        {
            for (int i = 0; i < count; ++i)
            {
                task_statuses.push_back(status);
            }
        }

        tasks.clear();

        sort(task_statuses.begin(), task_statuses.end(),
             [](TaskStatus x, TaskStatus y) {
                 return static_cast<int>(x) < static_cast<int>(y);
             });

        // PrintTasksStatuses(task_statuses);

        for (int i = 0; i < task_count && i < task_statuses.size(); ++i)
        {
            if (task_statuses[i] != TaskStatus::DONE)
            {
                SetNextStatus(task_statuses[i]);
                ++updated_tasks[task_statuses[i]];
            }
            ++tasks[task_statuses[i]];
        }
        for (int i = task_count; i < task_statuses.size(); ++i)
        {
            if (task_statuses[i] != TaskStatus::DONE)
            {
                ++untouched_tasks[task_statuses[i]];
            }
            ++tasks[task_statuses[i]];
        }

        // PrintTasksStatuses(task_statuses);


        return {updated_tasks, untouched_tasks};
    }

  private:
    void SetNextStatus(TaskStatus& status)
    {
        switch (status)
        {
            case TaskStatus::NEW:
                status = TaskStatus::IN_PROGRESS;
                break;
            case TaskStatus::IN_PROGRESS:
                status = TaskStatus::TESTING;
                break;
            case TaskStatus::TESTING:
                status = TaskStatus::DONE;
                break;
            case TaskStatus::DONE:
                break;
        }
    }

    map<string, TasksInfo> tt;
};

#ifdef MYENV

int main()
{
    TeamTasks tasks;

    string command;

    istringstream input("AddNewTasks Alice 5\n"
                        "PerformPersonTasks Alice 5\n"
                        "PerformPersonTasks Alice 5\n"
                        "PerformPersonTasks Alice 1\n"
                        "AddNewTasks Alice 5\n"
                        "PerformPersonTasks Alice 2\n"
                        "GetPersonTasksInfo Alice\n"
                        "PerformPersonTasks Alice 4\n"
                        "GetPersonTasksInfo Alice\n"
                        "PerformPersonTasks Alice 4\n"
                        "GetPersonTasksInfo Alice\n"
                        "PerformPersonTasks Alice 11\n"
                        "GetPersonTasksInfo Alice\n");

    while (getline(input, command))
    {
        istringstream ss(command);
        string command_code;
        ss >> command_code;

        if (command_code == "AddNewTasks")
        {
            string person;
            int count;
            ss >> person >> count;
            for (int i = 0; i < count; i++)
            {
                tasks.AddNewTask(person);
            }
            cout << "[]" << endl;
        }
        else if (command_code == "PerformPersonTasks")
        {
            string person;
            int count;
            ss >> person >> count;
            TasksInfo updated_tasks, untouched_tasks;
            tie(updated_tasks, untouched_tasks) =
                tasks.PerformPersonTasks(person, count);
            cout << "[";
            PrintTasksInfo(updated_tasks);
            cout << ", ";
            PrintTasksInfo(untouched_tasks);
            cout << "]" << endl;
        }
        else if (command_code == "GetPersonTasksInfo")
        {
            string person;
            ss >> person;
            PrintTasksInfo(tasks.GetPersonTasksInfo(person));
            cout << endl;
        }
    }

    return 0;
}

#endif
