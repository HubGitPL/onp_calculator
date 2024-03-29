#pragma once
#pragma warning(disable:4996)
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "myList.h"

#define SIZE_OF_CHAR_C 64
#define SIZE_OF_CHAR_C_SMALLER 32


#define PLUS "+"
#define MINUS "-"
#define MULTIPLY "*"
#define DIVIDE "/"
#define IF "IF"
#define MIN "MIN"
#define MAX "MAX"
#define N "N"
#define COMA ","
using namespace std;
/*
 źródła:
 wyklad: slajd o ONP (pseudokod i kroki algorytmu), slajd o stosie
 https://eduinf.waw.pl/inf/utils/010_2010/0410.php
 Thomas H Cormen Introducing to Alghorithms
 https://pl.wikipedia.org/wiki/Odwrotna_notacja_polska
 */
bool isLeftAssociative(const char character[]) {
    if (strcmp(character, PLUS) == 0 ||
        strcmp(character, MINUS) == 0 ||
        strcmp(character, MULTIPLY) == 0 ||
        strcmp(character, DIVIDE) == 0) {
        return true;
    } else {
        return false;
    }
}

bool isAnOperator(const char character[]){
    if(strcmp(character, PLUS) == 0 || strcmp(character, MINUS) == 0 || strcmp(character, MULTIPLY) == 0 || strcmp(character, DIVIDE) == 0 ||
       strcmp(character, MIN) == 0 || strcmp(character, MAX) == 0 || strcmp(character, N) == 0 || strcmp(character, "(") == 0 || strcmp(character, ")") == 0 ||
       strcmp(character, COMA) == 0 || strcmp(character, IF) == 0){
        return true;
    }
    else{
        return false;
    }
}
bool isFunction(const char character[]){
    if(strcmp(character, IF) == 0 || strcmp(character, MIN) == 0 || strcmp(character, MAX) == 0){
        return true;
    }
    else{
        return false;
    }
}
int priorityNumber(const char character[]){
    switch(character[0]){
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case 'I':
        case 'M':
        case 'N':
            return 3;
        default:
            return 0; // coma

    }
}
void coutPartialSolution(List *list,const char* sign){
    const int sizeVector = sizeList(list);
    printf("%s ", sign);
    for(int i=sizeVector-1; i>=0; i--){
        printf("%s ", getElement(list, i));
    }
    printf("\n");
}

void onpCalculation(List *list, int lengthOfAnswer){
    if(lengthOfAnswer == 0 && sizeList(list) == 0){
        return;
    }
    List *s = createList();
    char *a, *b, *c;
    int i=0, result;
    bool isFunctionMin = false, isFunctionMax = false;
    while(i<lengthOfAnswer) {
        if(strlen(getElement(list, i)) > 3){
            char znak = getElement(list, i)[2];
            if(znak == 'X'){
                isFunctionMax = true;
            }
            else if(znak == 'N'){
                isFunctionMin = true;
            }
        }
        if (!isAnOperator(getElement(list, i)) &&
        !isFunctionMin && !isFunctionMax){1
            pushBack(s, strdup(getElement(list, i)));
        } else {
            if (strcmp(getElement(list, i), PLUS) == 0) {
                coutPartialSolution(s, PLUS);
                a = getLastElement(s);
                popBack(s);
                b = getLastElement(s);
                popBack(s);
                result = atoi(a) + atoi(b);
                c = new char[SIZE_OF_CHAR_C_SMALLER];
                sprintf(c, "%d", result);
                pushBack(s, c);
                delete a;
                delete b;
            } else if (strcmp(getElement(list, i), MINUS) == 0) {
                coutPartialSolution(s, MINUS);
                a = getLastElement(s);
                popBack(s);
                b = getLastElement(s);
                popBack(s);
                result = atoi(b) - atoi(a);
                c = new char[SIZE_OF_CHAR_C_SMALLER];
                sprintf(c, "%d", result);
                pushBack(s, c);
            } else if (strcmp(getElement(list, i), MULTIPLY) == 0) {
                coutPartialSolution(s, MULTIPLY);
                a = getLastElement(s);
                popBack(s);
                b = getLastElement(s);
                popBack(s);
                result = atoi(a) * atoi(b);
                c = new char[SIZE_OF_CHAR_C_SMALLER];
                sprintf(c, "%d", result);
                pushBack(s, c);
                delete a;
                delete b;
            } else if (strcmp(getElement(list, i), DIVIDE) == 0) {
                coutPartialSolution(s, DIVIDE);
                a = getLastElement(s);
                popBack(s);
                b = getLastElement(s);
                popBack(s);
                if(atoi(a) == 0){
                    printf("ERROR\n");
                    destroyClearList(s);
                    delete a;
                    delete b;
                    return;
                }
                result = atoi(b) / atoi(a);
                c = new char[SIZE_OF_CHAR_C_SMALLER];
                sprintf(c, "%d", result);
                pushBack(s, c);
                delete a;
                delete b;
            }else if(strcmp(getElement(list, i), IF) == 0){
                coutPartialSolution(s, IF);
                a = getLastElement(s);
                popBack(s);
                b = getLastElement(s);
                popBack(s);
                c = getLastElement(s);
                popBack(s);
                if(atoi(c) > 0){
                    pushBack(s, b);
                }
                else{
                    pushBack(s, a);
                }
            }else if (strcmp(getElement(list, i), N) == 0) {
                coutPartialSolution(s, N);
                a = getLastElement(s);
                popBack(s);
                result = -atoi(a);
                c = new char[SIZE_OF_CHAR_C_SMALLER];
                sprintf(c, "%d", result);
                pushBack(s, c);
                delete a;
            } else if (isFunctionMin) {
                coutPartialSolution(s, getElement(list, i));
                //wyciagniecie tylko liczby z v[i] czyli z MINX tylko X
                char* number = new char[strlen(getElement(list, i)) - 3];
                for(int j=3; j<((int)strlen(getElement(list, i))); j++){
                    number[j-3] = getElement(list, i)[j];
                }
                int forCounter = atoi(number);
                int numberTemp;
                result = atoi(getLastElement(s));
                popBack(s);
                for(int j=1; j<forCounter; j++) {
                    if(sizeList(s) > 0) {
                        numberTemp = atoi(getLastElement(s));
                        popBack(s);
                        if(numberTemp < result){
                            result = numberTemp;
                        }
                    }
                }
                c = new char[SIZE_OF_CHAR_C_SMALLER];
                sprintf(c, "%d", result);
                pushBack(s, c);
                isFunctionMin = false;
                delete number;
            } else if (isFunctionMax) {
                coutPartialSolution(s, getElement(list, i));
                //wyciagniecie tylko liczby z v[i] czyli z MAXX tylko X
                char* number = new char[strlen(getElement(list, i)) - 3];
                for(int j=3; j<((int)strlen(getElement(list, i))); j++){
                    number[j-3] = getElement(list, i)[j];
                }
                int forCounter = atoi(number);
                int numberTemp;
                result = atoi(getLastElement(s));
                popBack(s);
                for(int j=1; j<forCounter; j++) {
                    if(sizeList(s) > 0) {
                        numberTemp = atoi(getLastElement(s));
                        popBack(s);
                    }
                    if(numberTemp > result){
                        result = numberTemp;
                    }
                }
                c = new char[SIZE_OF_CHAR_C_SMALLER];
                sprintf(c, "%d", result);
                pushBack(s, c);
                isFunctionMax = false;
                delete number;
            }
            else {
                pushBack(s, getElement(list, i));
            }
        }
        i++;
    }
    printf("%s\n", getLastElement(s));
    destroyClearList(s);
}
void toPostfix(){
    int loops;
    int priorityOfOperator, counterComas;
    scanf("%d", &loops);
    while(loops--) {
        counterComas = 0;
        List *list = createList();
        char **tab = new char *[1]{
            new char[SIZE_OF_CHAR_C]
        };
        List *s = createList();
        int i = 0;
        while (true) {
            scanf("%s", tab[i]);
            if (strcmp(tab[i], ".") == 0 || strcmp(tab[i], "\n") == 0){
                break;
            }
            i = 0;
            if (!isAnOperator(tab[i])) {
                pushBack(list, strdup(tab[i]));
            } else {
                if (strcmp(tab[i], "(") == 0) {
                    pushFront(s, strdup(tab[i]));
                }
                else if (strcmp(tab[i], ")") == 0) {
                    while (sizeList(s) > 0 && strcmp(getElement(s, 0), "(") != 0) {
                        if(strcmp(getElement(s, 0), COMA) == 0){
                            counterComas++;
                        }
                        else{
                            pushBack(list, strdup(getElement(s, 0)));
                        }
                        popFront(s);
                    }
                    if(sizeList(s) > 0){
                        if (strcmp(getElement(s, 0), "(") == 0) {
                            popFront(s);
                        }
                    }
                    if (sizeList(s) > 0 && isFunction(getElement(s, 0))) {
                        char* topChar = getElement(s, 0);
                        popFront(s);
                        if(strcmp(topChar, IF) == 0) {
                            pushBack(list, strdup(topChar));
                            counterComas = 0;
                        }else{
                            char* funcWithArgCounter = new char[SIZE_OF_CHAR_C_SMALLER];
                            sprintf(funcWithArgCounter, "%s%d", topChar, counterComas+1);
                            pushBack(list, strdup(funcWithArgCounter));
                            counterComas = 0;
                        }
                    }
                }
                else if (strcmp(tab[i], COMA) == 0) {
                    int counterC = 0;
                    while(sizeList(s) > 0 && strcmp(getElement(s, 0), "(") != 0) {
                        if (strcmp(getElement(s, 0), COMA) == 0) {
                            counterC++;
                        }
                        if (strcmp(getElement(s, 0), COMA) != 0) {
                            pushBack(list, strdup(getElement(s, 0)));
                        }
                        popFront(s);
                    }
                    while(counterC > 0){
                        pushFront(s, strdup(COMA));
                        counterC--;
                    }
                    pushFront(s, strdup(tab[i]));
                } else {
                    priorityOfOperator = priorityNumber(tab[i]);
                    while (sizeList(s) > 0 &&
                    strcmp(getElement(s, 0), "(") != 0 &&
                            (priorityNumber(getElement(s, 0)) > priorityOfOperator ||
                            (priorityNumber(getElement(s, 0)) == priorityOfOperator &&
                            isLeftAssociative(getElement(s, 0)) ) ) ) {
                        pushBack(list, strdup(getElement(s, 0)));
                        popFront(s);
                    }
                    pushFront(s, strdup(tab[i]));
                }
            }
        }
        while(sizeList(s) > 0){
            pushBack(list, getElement(s, 0));
            popFront(s);
        }
        destroyClearList(s);
        printList(list);
        printf("\n");
        onpCalculation(list, sizeList(list));
        destroyClearList(list);
        printf("\n");
        delete[] tab;
    }
}
int main() {
    toPostfix();
    return 0;
}


