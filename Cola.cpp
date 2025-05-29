#include<iostream>
using namespace std;

#define MAX 5
Nodo cola[MAX];

int frente = -1;
int final = -1;

struct Nodo{
    int id;
    string proceso;
    int priority;
};