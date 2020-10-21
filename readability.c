#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
void print_grade(int grade);

int main(void)
{
    string text = get_string("Text: ");

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    int L = (float) letters / words * 100;
    int S = (float) sentences / words * 100;

    double index = 0.0588 * L - 0.296 * S - 15.8;

    print_grade(round(index));
}

int count_letters(string text)
{
    int letters = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }

    return letters;
}

int count_words(string text)
{
    int words = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isspace(text[i]))
        {
            words++;
        }
    }

    return words + 1;
}

int count_sentences(string text)
{
    int sentences = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences++;
        }
    }

    return sentences;
}

void print_grade(int grade)
{
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}