#include <stdio.h>
#include <string.h>

#define NAME_LEN 100U

#define FILL_STUDENT_OK 0
#define FILL_STUDENT_FAILED 1

// #define DEBUG_TEST_INVALID

typedef struct 
{
    char name[NAME_LEN];
    unsigned int age;
} Person;

// Function accepts a POINTER (*)
int FillStudentData(Person *ctx);

int main(void)
{
    Person student;
    strncpy(student.name, "Bob", NAME_LEN);
    student.age = 20;
    printf("BeforeMain: Name: %s, age: %d\n", student.name, student.age);

    // We pass an ADDRESS (& operator)
    int status = FillStudentData(&student);
    if(status == FILL_STUDENT_OK)
    {
        printf("Function completed succesfully!\n");
    }
    else
        printf("Function failled!\n");

    printf("After: Name: %s, age: %d\n", student.name, student.age);
    return 0;
}

int FillStudentData(Person *ctx)
{
#ifndef DEBUG_TEST_INVALID
    int fillAge = 30;
#else
    int fillAge = -30;
#endif

    // We are accessing a POINTER, thus we use (->)
    printf("BeforeFill: Name: %s, age: %d\n", ctx->name, ctx->age);
    if(fillAge < 0)
    {
        printf("Error: Invalid age!\n");
        return FILL_STUDENT_FAILED;
    }
    ctx->age = fillAge;
    strncpy(ctx->name, "Alice", NAME_LEN);
    printf("AfterFill: Name: %s, age: %d\n", ctx->name, ctx->age);

    return FILL_STUDENT_OK;
}
