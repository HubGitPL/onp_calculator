#include <iostream>
#include <stdio.h>
#include <stack>
#include <queue>
#include <string>

#define LENGTHOFINPUT 1000
/*
 źródła:
 wyklad: slajd o ONP (pseudokod i kroki algorytmu), slajd o stosie
 https://eduinf.waw.pl/inf/utils/010_2010/0410.php
 Thomas H Cormen Introducing to Alghorithms
 https://pl.wikipedia.org/wiki/Odwrotna_notacja_polska
 */


using namespace std;

int priorityNumber(char character){
    if(character == '+' || character == '-'){
        return 1;
    }
    else if(character == '*' || character == '/'){
        return 2;
    }
    else if(character == 'I' || character == 'M' || character == 'N'){
        //TODO: take care of others letters
        return 3;
    }
    else{
        return 0; // paretensis
    }
}

bool isAnOperator(char character){
    if(character == '+' || character == '-' || character == '*' || character == '/' ||
       character == 'I' || character == 'M' || character == 'N' || character == '(' || character == ')'){
        return true;
    }
    else{
        return false;
    }
}
int main() {
    stack <char> characters;
    stack<char> answer;
    char* expression = new char[LENGTHOFINPUT];
    char sign;
    int licznik =0;
    while((sign = fgetc(stdin)) != EOF && sign != '.'){
        expression[licznik] = sign;
        licznik++;
    }
    expression[licznik] = '\0';
    char* array = new char[LENGTHOFINPUT];
    int arrayCounter = 0;
    int counter = 0;
    int priorityOfCharacter;
    char word;
    while(licznik > counter){
        word = expression[counter];
        counter++;

        if(word == '.'){
            continue;
        }else if (word == ' '){
            if(array[arrayCounter-1] != ' ' && arrayCounter > 0){
                array[arrayCounter] = ' ';
                arrayCounter++;
            }

            continue;
        }

        if(!isAnOperator(word)){
            array[arrayCounter] = word;
            arrayCounter++;
        }else{
            if(word == '(') {
                characters.push(word);
            }
            else if(word == ')'){
                while(characters.top() != '(' ){
                    array[arrayCounter] = characters.top();
                    arrayCounter++;
                    characters.pop();
                }
                characters.pop();
            }
            else{
                priorityOfCharacter = priorityNumber(word);
                while(!characters.empty()){
                    if(priorityNumber(characters.top()) == '(' || priorityNumber(characters.top()) < priorityOfCharacter){
                        break;
                    }
                    array[arrayCounter] = characters.top();
                    arrayCounter++;
                    characters.pop();
                }
                characters.push(word);
            }
        }
    }

    while(!characters.empty()){
        array[arrayCounter] = characters.top();
        arrayCounter++;
        array[arrayCounter] = ' ';
        arrayCounter++;
        characters.pop();
    }

    for(int i = 0; i < arrayCounter; i++) {
        cout << array[i];
    }
    delete [] array;
}
/*
 * stack <char> characters;
    string wyrazenie = "4 - 3 - 6 + 6 / 7 / 4.";
    string result = "";

    while(wyrazenie.length() > 0){
        char character = wyrazenie[0];
        wyrazenie.erase(0, 1);
        if(character == ' ' || character == '.'){
            continue;
        }
        if(isAnOperator(character)){
            while(!characters.empty() && priorityNumber(characters.top()) >= priorityNumber(character)){
                result += characters.top();
                characters.pop();
            }
            characters.push(character);
        }
        else if(character == '('){
            characters.push(character);
        }
        else if(character == ')'){
            while(characters.top() != '('){
                result += characters.top();
                characters.pop();
            }
            characters.pop();
        }
        else{
            result += character;
        }
    }
    while(!characters.empty()){
        result += characters.top();
        characters.pop();
    }

    cout << result << endl;
 */