#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//구단 선수

struct node {
    char position[20];
    char name[20];
    int gameScore;
    int comScore;
    int potenScore;
    struct node* next;
};
