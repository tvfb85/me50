#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // initialize variable called 'name' which can hold data of type string, and set it to the return value of get_string()
    string name = get_string("What is your name?\n");

    // print to the console
    printf("hello, %s\n", name);
}