#include <iostream>
#include <vector>
#include <algorithm>

struct Task {
    std::string title;
    int priority;
    std::string description;
    std::string deadline;

    static bool sortByPriority(const Task& a, const Task& b) {
        return a.priority < b.priority;
    }

    static bool sortByDeadline(const Task& a, const Task& b) {
        return a.deadline < b.deadline;
    }

    static bool isDeadlineWithinRange(const Task& task, const std::string& start, const std::string& end) {
        return task.deadline >= start && task.deadline <= end;
    }

    static bool isSameDay(const Task& task, const std::string& day) {
        return task.deadline.substr(0, 10) == day;
    }

    void addTask();
    void deleteTask();
    void editTask();
    void searchTasks();
    void displayTasksForDay();
    void displayTasksForWeek();
    void displayTasksForMonth();
    void displaySortedTasksByPriority();
    void displaySortedTasksByDeadline();
};

std::vector<Task> tasks;

void Task::addTask() {
    Task newTask;
    std::cout << "Enter task title: ";
    std::cin >> newTask.title;
    std::cout << "Enter task priority (1-5): ";
    std::cin >> newTask.priority;
    std::cout << "Enter task description: ";
    std::cin >> newTask.description;
    std::cout << "Enter task deadline (YYYY-MM-DD HH:MM): ";
    std::cin >> newTask.deadline;

    tasks.push_back(newTask);
    std::cout << "Task added successfully.\n";
}

void Task::deleteTask() {
    if (tasks.empty()) {
        std::cout << "No tasks to delete.\n";
        return;
    }

    int index;
    std::cout << "Enter the index of the task to delete: ";
    std::cin >> index;

    if (index >= 0 && index < tasks.size()) {
        tasks.erase(tasks.begin() + index);
        std::cout << "Task deleted successfully.\n";
    }
    else {
        std::cout << "Invalid index.\n";
    }
}

void Task::editTask() {
    if (tasks.empty()) {
        std::cout << "No tasks to edit.\n";
        return;
    }

    int index;
    std::cout << "Enter the index of the task to edit: ";
    std::cin >> index;

    if (index >= 0 && index < tasks.size()) {
        Task& taskToEdit = tasks[index];
        std::cout << "Enter new task title: ";
        std::cin >> taskToEdit.title;
        std::cout << "Enter new task priority (1-5): ";
        std::cin >> taskToEdit.priority;
        std::cout << "Enter new task description: ";
        std::cin >> taskToEdit.description;
        std::cout << "Enter new task deadline (YYYY-MM-DD HH:MM): ";
        std::cin >> taskToEdit.deadline;

        std::cout << "Task edited successfully.\n";
    }
    else {
        std::cout << "Invalid index.\n";
    }
}

void Task::searchTasks() {
    std::string searchTerm;
    std::cout << "Enter search term: ";
    std::cin >> searchTerm;

    std::vector<Task> results;
    for (const Task& task : tasks) {
        if (task.title.find(searchTerm) != std::string::npos ||
            task.description.find(searchTerm) != std::string::npos) {
            results.push_back(task);
        }
    }

    if (results.empty()) {
        std::cout << "No matching tasks found.\n";
    }
    else {
        std::cout << "Matching tasks:\n";
        for (const Task& result : results) {
            std::cout << result.title << " (Priority: " << result.priority << ")\n";
        }
    }
}

void Task::displayTasksForDay() {
    std::string day;
    std::cout << "Enter day (YYYY-MM-DD): ";
    std::cin >> day;

    std::cout << "Tasks for " << day << ":\n";
    for (const Task& task : tasks) {
        if (isSameDay(task, day)) {
            std::cout << task.title << " (Priority: " << task.priority << ")\n";
        }
    }
}

void Task::displayTasksForWeek() {
    std::string startDay, endDay;
    std::cout << "Enter start day (YYYY-MM-DD): ";
    std::cin >> startDay;
    std::cout << "Enter end day (YYYY-MM-DD): ";
    std::cin >> endDay;

    std::cout << "Tasks for the week:\n";
    for (const Task& task : tasks) {
        if (isDeadlineWithinRange(task, startDay, endDay)) {
            std::cout << task.title << " (Priority: " << task.priority << ")\n";
        }
    }
}

void Task::displayTasksForMonth() {
    std::string month;
    std::cout << "Enter month (YYYY-MM): ";
    std::cin >> month;

    std::cout << "Tasks for " << month << ":\n";
    for (const Task& task : tasks) {
        if (task.deadline.substr(0, 7) == month) {
            std::cout << task.title << " (Priority: " << task.priority << ")\n";
        }
    }
}

void Task::displaySortedTasksByPriority() {
    std::vector<Task> sortedTasks = tasks;
    std::sort(sortedTasks.begin(), sortedTasks.end(), sortByPriority);

    std::cout << "Tasks sorted by priority:\n";
    for (const Task& task : sortedTasks) {
        std::cout << task.title << " (Priority: " << task.priority << ")\n";
    }
}

void Task::displaySortedTasksByDeadline() {
    std::vector<Task> sortedTasks = tasks;
    std::sort(sortedTasks.begin(), sortedTasks.end(), sortByDeadline);

    std::cout << "Tasks sorted by deadline:\n";
    for (const Task& task : sortedTasks) {
        std::cout << task.title << " (Deadline: " << task.deadline << ")\n";
    }
}

int main() {
    Task taskManager;

    int choice;
    do {
        std::cout << "1. Add Task\n"
            << "2. Delete Task\n"
            << "3. Edit Task\n"
            << "4. Search Tasks\n"
            << "5. Display Tasks for Day\n"
            << "6. Display Tasks for Week\n"
            << "7. Display Tasks for Month\n"
            << "8. Display Sorted Tasks by Priority\n"
            << "9. Display Sorted Tasks by Deadline\n"
            << "0. Exit\n"
            << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            taskManager.addTask();
            break;
        case 2:
            taskManager.deleteTask();
            break;
        case 3:
            taskManager.editTask();
            break;
        case 4:
            taskManager.searchTasks();
            break;
        case 5:
            taskManager.displayTasksForDay();
            break;
        case 6:
            taskManager.displayTasksForWeek();
            break;
        case 7:
            taskManager.displayTasksForMonth();
            break;
        case 8:
            taskManager.displaySortedTasksByPriority();
            break;
        case 9:
            taskManager.displaySortedTasksByDeadline();
            break;
        case 0:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    
}
