#pragma once
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
https://pl.wikipedia.org/wiki/Odwrotna_notacja_polska
corrected version of toPostfix function
https://en.m.wikipedia.org/wiki/Shunting_yard_algorithm
books:
Thomas H Cormen Introducing to Alghorithms
stack implementation: Learn C the Hard Way: Practical Exercises on the Computational Subjects You Keep Avoiding (Like C) Zed A. Shaw
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
void handlingPlus(List *s){
    int result;
    char *a, *b, *c = new char[SIZE_OF_CHAR_C_SMALLER];
    coutPartialSolution(s, PLUS);
    a = getLastElement(s);
    popBack(s);
    b = getLastElement(s);
    popBack(s);
    result = atoi(a) + atoi(b);
    snprintf(c, SIZE_OF_CHAR_C_SMALLER, "%d", result);
    pushBack(s, strdup(c));
    delete a;
    delete b;
    delete [] c;
}
void handlingMinus(List *s){
    int result;
    char *a, *b, *c = new char[SIZE_OF_CHAR_C_SMALLER];
    coutPartialSolution(s, MINUS);
    a = getLastElement(s);
    popBack(s);
    b = getLastElement(s);
    popBack(s);
    result = atoi(b) - atoi(a);
    snprintf(c, SIZE_OF_CHAR_C_SMALLER, "%d", result);
    pushBack(s, strdup(c));
    delete a;
    delete b;
    delete [] c;
}
void handlingMuliplay(List *s){
    int result;
    char *a, *b , *c = new char[SIZE_OF_CHAR_C_SMALLER];
    coutPartialSolution(s, MULTIPLY);
    a = getLastElement(s);
    popBack(s);
    b = getLastElement(s);
    popBack(s);
    result = atoi(a) * atoi(b);
    snprintf(c, SIZE_OF_CHAR_C_SMALLER, "%d", result);
    pushBack(s, strdup(c));
    delete a;
    delete b;
    delete [] c;
}
void handlingIF(){
    //TODO
}
void handlingMIN(){
    //TODO
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
            !isFunctionMin && !isFunctionMax){
            pushBack(s, getElement(list, i));
        } else {
            c = new char[SIZE_OF_CHAR_C_SMALLER];
            if (strcmp(getElement(list, i), PLUS) == 0) {
                handlingPlus(s);
            } else if (strcmp(getElement(list, i), MINUS) == 0) {
                handlingMinus(s);
            } else if (strcmp(getElement(list, i), MULTIPLY) == 0) {
                handlingMuliplay(s);
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
                sprintf(c, "%d", result);
                pushBack(s, strdup(c));
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
                    delete a;
                }
                else{
                    pushBack(s, a);
                    delete b;
                }
            }else if (strcmp(getElement(list, i), N) == 0) {
                coutPartialSolution(s, N);
                a = getLastElement(s);
                popBack(s);
                result = -atoi(a);
                snprintf(c, SIZE_OF_CHAR_C_SMALLER, "%d", result);
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
                sprintf(c, "%d", result);
                pushBack(s, c);
                isFunctionMin = false;
                delete [] number;
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
                        if(numberTemp > result){
                            result = numberTemp;
                        }
                    }
                }
                sprintf(c, "%d", result);
                pushBack(s, c);
                isFunctionMax = false;
                delete [] number;
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
                            pushBack(list, topChar);
                            counterComas = 0;
                        }else{
                            char* funcWithArgCounter = new char[SIZE_OF_CHAR_C_SMALLER];
                            sprintf(funcWithArgCounter, "%s%d", topChar, counterComas+1);
                            pushBack(list, strdup(funcWithArgCounter));
                            counterComas = 0;
                            delete [] funcWithArgCounter;
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
        delete[] tab[0];
        delete[] tab;
        onpCalculation(list, sizeList(list));
        destroyClearList(list);
        printf("\n");
    }
}
int main() {
    toPostfix();
    return 0;
}
