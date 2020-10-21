#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

// function declarations
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
void print_grade(int grade);

int main(void)
{
    // Ask user for text input
    string text = get_string("Text: ");

    // Save return values after counting letters, words and sentences
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Calculate letters and sentences per 100 words and cast to float
    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;

    // Add calculated values to Coleman-Liau formula
    double index = 0.0588 * L - 0.296 * S - 15.8;

    // Round grade level to nearest whole number and print
    print_grade(round(index));
}

// Count letters by iterating over string and incrementing the letters count for alphabetic characters only
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

// Count words by iterating over string and checking for whitespaces
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

    // Return words count plus one to account for no whitespace after the last word
    return words + 1;
}

// Count sentences by iterating over string and checking for periods, exclamation points and question marks
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

// Check for lower than grade one and higher than grade 16 before outputting the result
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