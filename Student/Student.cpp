#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>

class Student {
private:
    std::string name;
    std::string group;
    int age;

public:
    Student(const std::string& name, const std::string& group, int age)
        : name(name), group(group), age(age) {}

    std::string getName() const {
        return name;
    }

    std::string getGroup() const {
        return group;
    }

    int getAge() const {
        return age;
    }
};

class Journal {
private:
    std::vector<Student> students;
    std::string journalName;

public:
    Journal(const std::string& name) : journalName(name) {}

    void addStudent(const Student& student) {
        students.push_back(student);
    }

    const std::vector<Student>& getStudents() const {
        return students;
    }

    const std::string& getName() const {
        return journalName;
    }
};

void writeStudentsToFile(const Journal& journal) {
    std::ofstream outFile(journal.getName() + ".txt");
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing: " << journal.getName() << ".txt\n";
        return;
    }

    for (const auto& student : journal.getStudents()) {
        outFile << "Name: " << student.getName() << ", Group: " << student.getGroup() << ", Age: " << student.getAge() << std::endl;
    }

    outFile.close();
}

int main() {
    Journal journal1("Journal1");
    journal1.addStudent(Student("John", "A", 20));
    journal1.addStudent(Student("Alice", "B", 22));

    Journal journal2("Journal2");
    journal2.addStudent(Student("Bob", "A", 21));
    journal2.addStudent(Student("Eve", "C", 23));

    std::vector<Journal> journals = { journal1, journal2 };

    std::vector<std::thread> threads;
    for (const auto& journal : journals) {
        threads.emplace_back(writeStudentsToFile, std::ref(journal));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Data has been written to files.\n";

    return 0;
}
