#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "define.h"

int check_last_token();
static int get_token();
static int unget_token();
static bool get_token_state = true;

extern int yylex();
extern int yylineno;

int P();
static int LD();
static int LD_prime();
static int D();
static int LV();
static int LV_prime();
static int LS();
static int LS_prime();
static int S();
static int LP();
static int LP_prime();
static int PAR();

int get_token(void)
{
    static int token = 0;
    if (get_token_state == true)
        token = yylex();
    else
        get_token_state = true;

    return token;
}

static int unget_token(void)
{
    get_token_state = false;
    return EXIT_SUCCESS;
}

int check_last_token(void)
{
    return get_token();
}

int P(void)
{
    int token = 0;
    token = get_token();
    if (token == PROGRAM)
    {
        LD();
        LS();
        token = get_token();
        if (token == END)
            return EXIT_SUCCESS;
        else
        {
            fprintf(stderr, "tdl: expecting 'END' at line %d.\n", yylineno);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        fprintf(stdout, "tdl: syntax error at line %d.\n", yylineno);
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

static int LD(void)
{
    D();
    LD_prime();
    return EXIT_SUCCESS;
}

static int LD_prime(void)
{
    int token = 0;
    token = get_token();
    if (token == INT || token == REAL)
    {
        unget_token();
        D();
        LD_prime();
    }
    else
        unget_token();
    return EXIT_SUCCESS;
}

static int D(void)
{
    int token = 0;
    token = get_token();
    if (token == INT || token == REAL)
    {
        LV();
        token = get_token();
        if (token == ';')
            return EXIT_SUCCESS;
        else
        {
            fprintf(stderr, "tdl: expecting ';' at line %d.\n", yylineno);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        fprintf(stdout, "tdl: syntax error at line %d.\n", yylineno);
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

static int LV(void)
{
    int token = 0;
    token = get_token();
    if (token == IDENTIFIER)
        LV_prime();
    else{
        fprintf(stderr, "tdl: expecting IDENTIFIER at line %d.\n", yylineno);
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

static int LV_prime(void)
{
    int token = 0;
    token = get_token();
    if (token == ',')
    {
        token = get_token();
        if (token == IDENTIFIER)
        {
            LV_prime();
        }
        else
        {
            fprintf(stderr, "tdl: expecting ',' at line %d.\n", yylineno);
            exit(EXIT_FAILURE);
        }
    }
    else
        unget_token();
    return EXIT_SUCCESS;
}

static int LS(void)
{
    S();
    LS_prime();
    return EXIT_SUCCESS;
}

static int LS_prime(void)
{
    int token = 0;
    token = get_token();
    if (token == READ || token == WRITE || token == WRITELN)
    {
        unget_token();
        S();
        LS_prime();
    }
    else
    {
        unget_token();
    }
    return EXIT_SUCCESS;
}

static int S(void)
{
    int token = 0;
    token = get_token();
    if (token == READ)
    {
        token = get_token();
        if (token == IDENTIFIER)
        {
            token = get_token();
            if (token == ';')
                return EXIT_SUCCESS;
            else
            {
                fprintf(stderr, "tdl: expected ';' at line %d.\n", yylineno);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            fprintf(stderr, "tdl: expected IDENTIFIER at line %d.\n", yylineno);
            exit(EXIT_FAILURE);
        }
    }
    else if (token == WRITE)
    {
        LP();
        token = get_token();
        if (token == ';')
            return EXIT_SUCCESS;
        else
        {
            fprintf(stderr, "tdl: expected ';' at line %d.\n", yylineno);
            exit(EXIT_FAILURE);
        }
    }
    else if (token == WRITELN)
    {
        token = get_token();
        if (token == ';')
            return EXIT_SUCCESS;
        else
        {
            fprintf(stderr, "tdl: expected ';' at line %d.\n", yylineno);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        fprintf(stdout, "tdl: syntax error at line %d.\n", yylineno);
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

static int LP(void)
{
    PAR();
    LP_prime();
    return EXIT_SUCCESS;
}

static int LP_prime(void)
{
    int token = 0;
    token = get_token();
    if (token == ',')
    {
        PAR();
        LP_prime();
    }
    else
        unget_token();
    return EXIT_SUCCESS;
}

static int PAR(void)
{
    int token = 0;
    token = get_token();

    if (token == IDENTIFIER ||
        token == CONST_INT ||
        token == CONST_REAL ||
        token == STRING)
    {
        return EXIT_SUCCESS;
    }
    else
    {
        fprintf(stderr, "tdl: invalid parameter at line %d.\n", yylineno);
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
