#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 50
#define FILENAME "students.dat"

typedef struct {
    int id;
    char name[50];
    int age;
    int score;
    char gender;
} Student;


void showMenu();

void addStudent(Student students[], int *count);

void showAllStudents(Student students[], int count);

void updateStudents(Student students[], int count);

int findStudentById(Student students[], int count, int id);

void deleteStudents(Student students[], int *count);

void calculateAverageScore(Student students[], int count);

void saveToFile(Student students[], int count);

void loadFromFile(Student students[], int *count);

int main() {
    Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;

    loadFromFile(students, &studentCount);
    printf("已从文件加载%d名学生信息\n", studentCount);

    while (1) {
        showMenu();
        printf("请输入您的选择：");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addStudent(students, &studentCount);
                saveToFile(students, studentCount);
                break;
            case 2:
                showAllStudents(students, studentCount);
                break;
            case 3:
                updateStudents(students, studentCount);
                saveToFile(students, studentCount);
                break;
            case 4:
                deleteStudents(students, &studentCount);
                saveToFile(students, studentCount);
                break;
            case 5:
                calculateAverageScore(students, studentCount);
                break;
            case 0:
                printf("感谢使用学生信息管理系统\n");
                return 0;
            default:
                printf("无效的选择，请重新输入!\n");
                break;
        }
        printf("\n按回车键继续...");
        getchar();
        getchar();
    }
    return 0;
}

void showMenu() {
    printf("==========学生信息管理系统 v3.0==========\n");
    printf("1. 添加学生\n");
    printf("2. 显示所有学生\n");
    printf("3. 修改学生信息\n");
    printf("4. 删除学生\n");
    printf("5. 计算平均成绩\n");
    printf("0. 退出系统\n");
    printf("=====================================\n");
}

int findStudentById(Student students[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}

void deleteStudents(Student students[], int *count) {
    printf("请输入你要删除的学生学号:");
    int id, index;
    scanf("%d", &id);

    index = findStudentById(students, *count, id);
    if (index == -1) {
        printf("未找到该学生！\n");
        return;
    }
    for (int i = index; i < *count - 1; i++) {
        students[i] = students[i + 1];
    }
    (*count)--;
    printf("学生删除成功!\n");
}

void addStudent(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("学生数量已达上限，无法添加！\n");
        return;
    }
    Student *s = &students[*count];

    printf("\n======添加学生========\n");

    printf("请输入学号:");
    scanf("%d", &s->id);

    printf("请输入姓名:");
    scanf("%s", &s->name);

    printf("请输入年龄:");
    scanf("%d", &s->age);

    printf("请输入成绩:");
    scanf("%d", &s->score);

    printf("请输入性别（m/f):");
    scanf(" %c", &s->gender);

    (*count)++;
    printf("学生添加成功，当前共有%d名学生!", *count);
}

void updateStudents(Student students[], int count) {
    int id, index;
    printf("请输入要修改的学生学号:");
    scanf("%d", &id);

    index = findStudentById(students, count, id);
    if (index == -1) {
        printf("未找到该学生！\n");
        return;
    }

    Student *s = &students[index];
    printf("\n当前学生信息:\n");
    printf("学号：%d\n", s->id);
    printf("姓名：%s\n", s->name);
    printf("年龄：%d\n", s->age);
    printf("成绩：%.2f\n", s->score);
    printf("性别：%c\n", s->gender);

    printf("\n请输入新的姓名（直接回车保持不变）：");
    char newName[50];
    getchar(); // 吸收换行符
    fgets(newName, sizeof(newName), stdin);
    if (newName[0] != '\n') {
        newName[strcspn(newName, "\n")] = '\0'; // 去掉换行符
        strcpy(s->name, newName);
    }

    printf("请输入新的年龄（0保持不变）:");
    int newAge;
    scanf("%d", &newAge);
    if (newAge != 0) {
        s->age = newAge;
    }

    printf("请输入新的成绩（-1保持不变）:");
    int newScore;
    scanf("%f", &newScore);
    if (newScore != -1) {
        s->score = newScore;
    }

    printf("学生信息修改成功!\n");
}

void showAllStudents(Student students[], int count) {
    if (count == 0) {
        printf("暂无学生信息!\n");
        return;
    }
    printf("\n==========所有学生信息============\n");
    printf("学号\t姓名\t年龄\t成绩\t性别\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%d\t%d\t%c\n",
               students[i].id, students[i].name, students[i].age, students[i].score, students[i].gender);
    }
}

void calculateAverageScore(Student students[], int count) {
    if (count == 0) {
        printf("暂无学生信息，无法计算平均成绩！\n");
        return;
    }

    int totalScore = 0;
    for (int i = 0; i < count; i++) {
        totalScore += students[i].score;
    }

    float average = (float) totalScore / count;
    printf("\n==========成绩统计============\n");
    printf("学生总数: %d\n", count);
    printf("总分: %d\n", totalScore);
    printf("平均成绩: %.2f\n", average);
}

void saveToFile(Student students[], int count) {
    FILE *fp = fopen(FILENAME, "wb");
    if (fp == NULL) {
        printf("无法打开文件保存数据！\n");
        return;
    }
    // 先写入学生数量
    fwrite(&count, sizeof(int), 1, fp);
    // 再写入所有学生数据
    fwrite(students, sizeof(Student), count, fp);

    fclose(fp);
    printf("数据已保存到文件\n");
}

void loadFromFile(Student students[], int *count) {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("数据文件不存在，将创建新文件\n");
        *count = 0;
        return;
    }

    // 先读取学生数量
    fread(count, sizeof(int), 1, fp);
    // 再读取所有学生数据
    fread(students, sizeof(students), *count, fp);
    fclose(fp);
}
