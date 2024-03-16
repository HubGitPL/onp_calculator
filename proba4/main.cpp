#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <stack>

#define SIZE_OF_CHAR_C 100
using namespace std;
/*
 źródła:
 wyklad: slajd o ONP (pseudokod i kroki algorytmu), slajd o stosie
 https://eduinf.waw.pl/inf/utils/010_2010/0410.php
 Thomas H Cormen Introducing to Alghorithms
 https://pl.wikipedia.org/wiki/Odwrotna_notacja_polska
 */

bool isAnOperator(const char character[]){
    if(strcmp(character, "+") == 0 || strcmp(character, "-") == 0 || strcmp(character, "*") == 0 || strcmp(character, "/") == 0 ||
       strcmp(character, "MIN") == 0 || strcmp(character, "MAX") == 0 || strcmp(character, "N") == 0 || strcmp(character, "(") == 0 || strcmp(character, ")") == 0 ||
       strcmp(character, ",") == 0 || strcmp(character, "IF") == 0){
        return true;
    }
    else{
        return false;
    }
}
bool isFunction(const char character[]){
    if(strcmp(character, "IF") == 0 || strcmp(character, "MIN") == 0 || strcmp(character, "MAX") == 0){
        return true;
    }
    else{
        return false;
    }
}
int priorityNumber(const char character[]){
    if((strcmp(character, "+") == 0) || strcmp(character, "-") == 0){
        return 1;
    }
    else if(strcmp(character, "*") == 0 || strcmp(character, "/") == 0){
        return 2;
    }
    else if(strcmp(character, "IF") == 0 || strcmp(character, "MIN") == 0 ||
            strcmp(character, "N") == 0 || strcmp(character, "MAX") == 0){
        return 3;
    }
    else{
        return 0; // coma
    }
}
void coutPartialSolution(vector<char*> v,const char* sign){
    const int sizeVector = v.size();
    printf("%s ", sign);
    for(int i=sizeVector-1; i>=0; i--){
        printf("%s ", v[i]);
    }
    printf("\n");
}

void onpCalculation(vector<char*>& v,const int lengthOfAnswer){
    vector <char*> s;
    char *a, *b, *c;
    int i=0, result;
    while(i<lengthOfAnswer) {
        if (!isAnOperator(v[i])) {
            s.push_back(v[i]);
        } else {
            if (strcmp(v[i], "+") == 0) {
                coutPartialSolution(s, "+");
                a = s.back();
                s.pop_back();
                b = s.back();
                s.pop_back();
                result = atoi(a) + atoi(b);
                c = new char[SIZE_OF_CHAR_C];
                sprintf(c, "%d", result);
                s.push_back(c);
            } else if (strcmp(v[i], "-") == 0) {
                coutPartialSolution(s, "-");
                a = s.back();
                s.pop_back();
                b = s.back();
                s.pop_back();
                result = atoi(b) - atoi(a);
                c = new char[SIZE_OF_CHAR_C];
                sprintf(c, "%d", result);
                s.push_back(c);
            } else if (strcmp(v[i], "*") == 0) {
                coutPartialSolution(s, "*");
                a = s.back();
                s.pop_back();
                b = s.back();
                s.pop_back();
                result = atoi(a) * atoi(b);
                c = new char[SIZE_OF_CHAR_C];
                sprintf(c, "%d", result);
                s.push_back(c);
            } else if (strcmp(v[i], "/") == 0) {
                coutPartialSolution(s, "/");
                a = s.back();
                s.pop_back();
                b = s.back();
                s.pop_back();
                if(atoi(a) == 0){
                    printf("ERROR\n");
                    return;
                }
                result = atoi(b) / atoi(a);
                c = new char[SIZE_OF_CHAR_C];
                sprintf(c, "%d", result);
                s.push_back(c);
            } else if (strcmp(v[i], "MIN") == 0) {
                a = s.back();
                s.pop_back();
                b = s.back();
                s.pop_back();
                result = atoi(a) < atoi(b) ? atoi(a) : atoi(b);
                c = new char[SIZE_OF_CHAR_C];
                sprintf(c, "%d", result);
                s.push_back(c);
            } else if (strcmp(v[i], "MAX") == 0) {
                a = s.back();
                s.pop_back();
                b = s.back();
                s.pop_back();
                result = atoi(a) > atoi(b) ? atoi(a) : atoi(b);
                c = new char[SIZE_OF_CHAR_C];
                sprintf(c, "%d", result);
                s.push_back(c);
            }else if (strcmp(v[i], "N") == 0) {
                coutPartialSolution(s, "N");
                a = s.back();
                s.pop_back();
                result = -atoi(a);
                c = new char[SIZE_OF_CHAR_C];
                sprintf(c, "%d", result);
                s.push_back(c);
            }else if(strcmp(v[i], "IF")){
                coutPartialSolution(s, "IF");
                a = s.back();
                s.pop_back();
                b = s.back();
                s.pop_back();
                c = s.back();
                s.pop_back();
                if(atoi(c) > 0){
                    s.push_back(b);
                }
                else{
                    s.push_back(a);
                }
            }
            else {
                s.push_back(v[i]);
            }
        }
        i++;
    }

    printf("%s\n", s.back());
}
int main() {
    int loops;
    int priorityOfOperator, counterComas;
    scanf("%d", &loops);
    while(loops--) {
        counterComas = 0;
        vector<char *> v;
        char **tab = new char *[1];
        for (int i = 0; i < 1; i++) {
            tab[i] = new char[SIZE_OF_CHAR_C];
        }
        stack<char *> s;
        int i = 0;
        while (true) {
            scanf("%99s", tab[i]);
            if (strcmp(tab[i], ".") == 0) {
                break;
            }
            i = 0;
            if (!isAnOperator(tab[i])) {
                v.push_back(strdup(tab[i]));
            } else {
                if (strcmp(tab[i], "(") == 0) {
                    s.push(strdup(tab[i]));
                } else if (strcmp(tab[i], ")") == 0) {
                    while (strcmp(s.top(), "(") != 0) {
                        v.push_back(strdup(s.top()));
                        s.pop();
                    }
                    s.pop();
                    if (!s.empty()) {
                        if (isFunction(s.top())) {
                            v.push_back(strdup(s.top()));
                            s.pop();
                        }
                    }
                } else if (strcmp(tab[i], ",") == 0) {
                    counterComas++;
                    continue;
                } else {
                    priorityOfOperator = priorityNumber(tab[i]);
                    while (!s.empty()) {
                        if (priorityOfOperator == 3 && priorityNumber(s.top()) == 3) {
                            break;
                        }
                        if (priorityNumber(s.top()) == '(' ||
                            priorityNumber(s.top()) < priorityOfOperator) {
                            break;
                        }
                        v.push_back(s.top());
                        s.pop();
                    }
                    s.push(strdup(tab[i]));
                }
            }
        }
        while(!s.empty()){
            v.push_back(s.top());
            s.pop();
        }
        for(auto j : v) {
            printf("%s ", j);
        }
        printf("\n");
        onpCalculation(v, v.size());
        printf("\n");
        delete[] tab;
    }
}


