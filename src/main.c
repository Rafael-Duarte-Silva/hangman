#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

const char *words[] = {
    "abacaxi",
    "astronauta",
    "biblioteca",
    "cachoeira",
    "dinossauro",
    "elefante",
    "foguete",
    "girassol",
    "hamburguer",
    "instrumento",
    "labirinto",
    "montanha",
    "oceano",
    "pirata",
    "quimica",
    "robô",
    "sorvete",
    "tempestade",
    "universo",
    "vulcao"};
const char *word = NULL;
int word_length = 0;
const int err_limit = 6;
int err_count = 0;
int hit_count = 0;
int *hit_positions = NULL;
char input_letter;

void clean_hit_positions()
{
    free(hit_positions);
    hit_positions = NULL;
}

int random_number(const int max)
{
    srand(time(NULL));
    return (rand() % (max + 1)); // min = 0
}

void random_word()
{
    int length = sizeof(words) / sizeof(words[0]);
    word = words[random_number(length - 1)];
}

bool calcule_hits()
{
    bool is_hit = false;
    for (int i = 0; i < word_length; i++)
    {
        if (input_letter == word[i])
        {
            hit_count++;
            is_hit = true;
            hit_positions[i] = true;
        }
    }

    return is_hit;
}

void display_score()
{
    printf(GREEN "hits: %d" RESET "\n", hit_count);
    printf(RED "errors: %d" RESET "\n", err_count);
}

void display_word()
{
    for (int i = 0; i < word_length; i++)
    {
        if (hit_positions[i])
        {
            printf(GREEN "%c" RESET, word[i]);
            continue;
        }

        printf("_");
    }
    printf("\n");
}

void display_infos()
{
    system("clear");
    display_word();
    display_score();
}

int main()
{
    random_word();
    word_length = strlen(word);
    hit_positions = calloc(word_length, sizeof(int));
    if (hit_positions == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    while (true)
    {
        display_infos();
        scanf(" %c", &input_letter);

        if (calcule_hits(input_letter))
        {
            if (hit_count == word_length)
            {
                display_infos();
                clean_hit_positions();
                return 0;
            }
            continue;
        }

        err_count++;
        if (err_count == err_limit)
        {
            display_infos();
            clean_hit_positions();
            return 0;
        }
    }

    clean_hit_positions();
    return 0;
}