#include <stdio.h>

int main() {
    int id;
    char name[50];
    int age;
    float score;
    char gender;

    printf("====== 学生信息管理系统v1.0======\n");
    printf("请输入学生学号:");
    scanf("%d", &id);

    printf("请输入学生姓名:");
    scanf("%s", name); // 注意：不能输入带空格的姓名

    printf("请输入学生年龄:");
    scanf("%d", &age);

    printf("请输入学生成绩:");
    scanf("%f", &score);

    printf("请输入学生性别（M/F）:");
    scanf(" %c", &gender); // 注意前面的空格跳过换行符

    printf("\n======学生信息:=====\n");
    printf("学号: %d\n", id);
    printf("姓名: %s\n", name);
    printf("年龄: %d\n", age);
    printf("成绩: %.2f\n", score);

    if (gender == 'M' || gender == 'm') {
        printf("性别: 男\n");
    } else if (gender == 'F' || gender == 'f') {
        printf("性别: 女\n");
    } else {
        printf("性别输入错误\n");
    }

    printf("成绩等级:");
    switch ((int) score / 10) {
        case 10:
        case 9:
            printf("优秀\n");
            break;
        case 8:
            printf("良好\n");
            break;
        case 7:
            printf("中等\n");
            break;
        case 6:
            printf("及格\n");
            break;
        default:
            printf("不及格\n");
            break;
    }
    return 0;
}
