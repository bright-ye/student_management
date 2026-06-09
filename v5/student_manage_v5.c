#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 50
#define FILENAME "students.dat"

typedef struct StudentNode {
    int id;
    char name[50];
    int age;
    float score;
    char gender;
    struct StudentNode *next;
} StudentNode;

void showMenu();
StudentNode* createStudent(int id, char *name, int age, float score, char gender);
void addStudent(StudentNode **head);
void showAllStudents(StudentNode *head);
StudentNode* findStudentById(StudentNode *head, int id);
void updateStudent(StudentNode *head);
void deleteStudent(StudentNode **head);
void calculateAverageScore(StudentNode *head);
void saveToFile(StudentNode *head);
void loadFromFile(StudentNode **head);
void freeAllStudents(StudentNode **head);

int main() {
    StudentNode *head = NULL; // 链表头指针
    int choice;

    loadFromFile(&head);

    while (1) {
        showMenu();
        printf("请输入您的选择：");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addStudent(&head);
                saveToFile(head);
                break;
            case 2:
                showAllStudents(head);
                break;
            case 3:
                updateStudent(head);
                saveToFile(head);
                break;
            case 4:
                deleteStudent(&head);
                saveToFile(head);
                break;
            case 5:
                calculateAverageScore(head);
                break;
            case 0:
                freeAllStudents(&head);
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

// 创建新的学生节点
StudentNode* createStudent(int id, char *name, int age, float score, char gender) {
    StudentNode *node = (StudentNode*) malloc(sizeof(StudentNode));
    node->id = id;
    strcpy(node->name, name);
    node->age = age;
    node->score = score;
    node->gender = gender;
    node->next = NULL;
    return node;
}

void addStudent (StudentNode **head) {
    int id,age;
    char name[50];
    float score;
    char gender;

    printf("\n=======添加学生========\n");
    printf("请输入学号:");
    scanf("%d", &id);

    if (findStudentById(*head, id) != NULL) {
        printf("学号已存在!添加失败");
        return;
    }

    printf("请输入姓名：");
    scanf("%s", name);

    printf("请输入年龄：");
    scanf("%d", &age);

    printf("请输入成绩：");
    scanf("%f", &score);

    printf("请输入性别(M/F)：");
    scanf(" %c", &gender);

    StudentNode *newNode = createStudent(id, name, age, score, gender);
    if (*head == NULL) {
        *head = newNode;
    } else {
        StudentNode *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    printf("学生添加成功\n");
}

StudentNode* findStudentById(StudentNode *head, int id) {
    StudentNode *current = head;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void deleteStudent(StudentNode **head) {
    int id;
    printf("请输入要删除的学生学号:");
    scanf("%d", &id);

    StudentNode *current = *head;
    StudentNode *prev = NULL;

    while (current != NULL && current->id == id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("未找到该学生！\n");
        return;
    }

    // 如果是头结点
    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("学生删除成功! \n");
}

void updateStudent(StudentNode *head) {
    int id;
    printf("请输入要修改的学生学号:");
    scanf("%d", &id);

    StudentNode *student = findStudentById(head, id);
    if (student == NULL) {
        printf("未找到该学生！\n");
        return;
    }

    printf("\n当前学生信息:\n");
    printf("学号：%d\n", student->id);
    printf("姓名：%s\n", student->name);
    printf("年龄：%d\n", student->age);
    printf("成绩：%.2f\n", student->score);
    printf("性别：%c\n", student->gender);

    printf("\n请输入新的姓名（直接回车保持不变）：");
    char newName[50];
    getchar(); // 吸收换行符
    fgets(newName, sizeof(newName), stdin);
    if (newName[0] != '\n' && newName[0] != '\0') {
        newName[strcspn(newName, "\n")] = '\0'; // 去掉换行符
        strcpy(student->name, newName);
    }

    printf("请输入新的年龄（0保持不变）:");
    int newAge;
    scanf("%d", &newAge);
    if (newAge != 0) {
        student->age = newAge;
    }

    printf("请输入新的成绩（-1保持不变）:");
    float newScore;
    scanf("%f", &newScore);
    if (newScore != -1) {
        student->score = newScore;
    }

    printf("学生信息修改成功!\n");
}

void showAllStudents(StudentNode *head) {
    if (head == NULL) {
        printf("暂无学生信息\n");
        return;
    }
    printf("\n======== 所有学生信息 =========\n");
    printf("学号\t姓名\t年龄\t成绩\t性别\n");
    printf("--------------------------------\n");
    StudentNode *current = head;
    while (current != NULL) {
        printf("%d\t%s\t%d\t%.2f\t%c\n",
               current->id, current->name,
               current->age, current->score,
               current->gender);
        current = current->next;
    }
}

void calculateAverageScore(StudentNode *head) {
    if (head == NULL) {
        printf("暂无学生数据\n");
        return;
    }
    int count = 0;
    float sum = 0.0;
    StudentNode *current = head;
    while (current != NULL ) {
        count++;
        sum += current->score;
        current = current->next;
    }
    printf("班级平均成绩: %.2f \n", sum / count);
}

void saveToFile(StudentNode *head) {
    FILE *fp = fopen(FILENAME, "wb");
    if (fp == NULL) {
        printf("无法打开文件保存数据！\n");
        return;
    }
    
    // 先计算学生数量
    int count = 0;
    StudentNode *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    // 先写入学生数量
    fwrite(&count, sizeof(int), 1, fp);
    
    // 再写入所有学生数据
    current = head;
    while (current != NULL) {
        fwrite(current, sizeof(StudentNode) - sizeof(StudentNode*), 1, fp);
        current = current->next;
    }

    fclose(fp);
    printf("数据已保存到文件\n");
}

void loadFromFile(StudentNode **head) {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("数据文件不存在，将创建新文件\n");
        *head = NULL;
        return;
    }

    int count;
    if (fread(&count, sizeof(int), 1, fp) != 1) {
        printf("文件读取失败\n");
        fclose(fp);
        *head = NULL;
        return;
    }

    *head = NULL;
    StudentNode **current = head;
    for (int i = 0; i < count; i++) {
        StudentNode *newNode = (StudentNode *) malloc(sizeof(StudentNode));
        if (fread(newNode, sizeof(StudentNode) - sizeof(StudentNode*), 1, fp) != 1) {
            free(newNode);
            break;
        }
        newNode->next = NULL;
        *current = newNode;
        current = &newNode->next;
    }
    fclose(fp);
    printf("已从文件加载%d名学生信息\n", count);
}

void freeAllStudents(StudentNode **head) {
    StudentNode *current = *head;
    while (current != NULL) {
        StudentNode *next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}