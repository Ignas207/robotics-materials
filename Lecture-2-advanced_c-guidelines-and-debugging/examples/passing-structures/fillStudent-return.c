#include <stdio.h>
#include <string.h>

#define NAME_LEN 100U

typedef struct 
{
    char name[NAME_LEN];
    unsigned int age;
} Person;

Person FillStudentData(Person ctx);

int main(void)
{
    Person student;
    strncpy(student.name, "Bob", NAME_LEN);
    student.age = 20;
    printf("BeforeMain: Name: %s, age: %d\n", student.name, student.age);

    student = FillStudentData(student);

    printf("After: Name: %s, age: %d\n", student.name, student.age);
    return 0;
}

Person FillStudentData(Person ctx)
{
    printf("BeforeFill: Name: %s, age: %d\n", ctx.name, ctx.age);
    strncpy(ctx.name, "Alice", NAME_LEN);
    ctx.age = 30;
    printf("AfterFill: Name: %s, age: %d\n", ctx.name, ctx.age);
    return ctx;
}
