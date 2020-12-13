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

FILE* fp = NULL;
int perGame;
int perCom;
int perPoten;

int setPer();
void openFile(char*);
int delplayer(struct node* ,struct node* ,void(*del)(struct node* ,struct node* ,char *));
void print_list(struct node*);
void swap(struct node* ,struct node* , struct node*);
void sortNode(struct node*);
void deleteNode(struct node*,struct node*,char*);
struct node* readPlayer(char*, struct node*);
struct node* putStruct(struct node*);
void uploadFile(char*,struct node*);

void main() {

    int number;

//현재 있는 선수
  struct node* new_node;
//영입가능선수
  struct node* come_node;

//파일 내용 넣어주기
    new_node=readPlayer("player.dat", new_node);
    come_node=readPlayer("freeplayer.dat", come_node);

    while (1) {
        printf("\n1. 현재구단 선수 출력\n2. 영입가능 선수 출력\n3. 평가비
율 설정하여 정렬\n4. 선수추가,삭제\n5. 종료\n");
        scanf("%d", &number);
        int tmp_gamescore = 0;

        if (number == 1){
            print_list(new_node);
          }
        else if (number == 2) {
            print_list(come_node);
          }
        else if (number == 3) {
            setPer();
            sortNode(come_node);
          }
        else if (number == 4) {
          delplayer(come_node,new_node,deleteNode);
          print_list(come_node);
        //  uploadFile("freeplayer.dat",come_node);
          uploadFile("player.dat",new_node);
          }
        else if (number == 5) break;
        else printf("잘못 입력하셨습니다.\n");
    }
}

//파일 열기
void openFile(char* filename) {

    fp = fopen(filename, "r+");
    if (fp == NULL) {
        printf("Cannot open file\n");
    }
}

//4번 기능 함수
//파일내 텍스트 내용  삭제, 추가

void deleteNode(struct node* head_ptr,struct node* head_ptr2,char* name){
  printf("\n");
  struct node* target_ptr=head_ptr;
  struct node* target_ptr2=head_ptr2->next;
  struct node* prev=head_ptr;
  struct node* temp_add;

  while(head_ptr!=NULL){
      head_ptr=head_ptr->next;
    }
  }

  printf("%s\n",temp_add->position);
  prev->next=head_ptr->next;
  free(head_ptr);
  while(head_ptr2->next!=NULL){
    head_ptr2=head_ptr2->next;
    }
  temp_add->next=NULL;
  head_ptr2->next=temp_add;
  fclose(fp);
}

int delplayer(struct node* head_ptr,struct node* head_ptr2,void(*del)(struct node* head,struct node* head2,char *name)){
  char name[20];
  printf("추가할 선수를 입력하세요.");
  scanf("%s",name);
  del(head_ptr,head_ptr2,name);
}

//텍스트 파일에 업로드
void uploadFile(char* file_name,struct node* what_node ){
    fp=fopen(file_name,"w");
    struct node* list_head=NULL;
    while (what_node!=NULL) {
        fprintf(fp, "%s %s %d %d %d\n", what_node->position, what_node->name, (what_node->gameScore), (what_node->comScore),what_node->potenScore);
        list_head=what_node->next;
        what_node=list_head;
    }
  printf("\n player.dat upload end\n");
  fclose(fp);
}

struct node* putStruct(struct node* what_node){
    what_node=NULL;
    struct node* list_head = NULL;
    while (!feof(fp)) {
        what_node = (struct node*)malloc(sizeof(struct node));
        fscanf(fp, "%s %s %d %d %d\n", what_node->position, what_node->name, &(what_node->gameScore), &(what_node->comScore),&(what_node->potenScore));
        what_node->next = list_head;
        list_head=what_node;
    }
    return what_node;
}

//1번 기능 실행 함수

struct node* readPlayer(char* filename, struct node* what_node) {
    struct node* k;
    openFile(filename);
    k=putStruct(what_node);
    fclose(fp);
    return k;
}


//2번 기능 실행 함수

int setPer() {
    printf("\n 게임 성적 평가 비율을 입력하세요");
    scanf("%d", &perGame);

    printf(" 대회 성적 평가 비율을 입력하세요");
    scanf("%d", &perCom);

    printf(" 잠재력 평가 비율을 입력하세요");
    scanf("%d", &perPoten);

    printf("\n 솔로게임 평가 비율  %d\n 대회 게임 평가 비율 %d\n 잠재력 >평가비율%d\n 으로 설정되었습니다.\n ", perGame, perCom,perPoten);
}

void print_list(struct node* what_node) {
    struct node* temp=what_node;
    printf("포지션 이름 게임성적 대회성적 잠재력\n");
    while (temp!= NULL) {
printf("%s %7s %7d %7d %7d\n", temp->position, temp->name, temp->gameScore, temp->comScore,temp->potenScore);
        temp = temp->next;
    }
}

void swap(struct node* head,struct node *a, struct node *b)
{
    char temp0[20];
    strcpy(temp0,a->position);
    char temp1[20];
    strcpy(temp1,a->name);
    int temp2 = a->gameScore;
    int temp3=a->comScore;
    int temp4=a->potenScore;

    strcpy(a->position,b->position);
    strcpy(a->name,b->name);
    a->gameScore=b->gameScore;
    a->comScore=b->comScore;
    a->potenScore=b->potenScore;

    strcpy(b->position,temp0);
    strcpy(b->name,temp1);
    b->gameScore = temp2;
    b->comScore=temp3;
    b->potenScore=temp4;
}

//3번 기능 실행

void sortNode(struct node* what_node) //what_node 지정해주며 시작
{
    printf("\n==================================\n");
    printf("영입 가능한 선수 능력치 순으로 출력\n\n");

//평가비율을 반영하여 능력치 합 정렬 시작
    int swapped, i;
    struct node *ptr1;
    struct node *lptr = NULL;
    struct node *head=what_node;

    do //do while문 이용
    {
        swapped = 0; //swapped=0으로 설정
        ptr1 = what_node; //ptr1에 what_node
        while (ptr1->next != lptr) //ptr1->next(2).lptr(NULL)
        {
           if ((0.01*perGame)*(ptr1->gameScore)+(0.01*perCom)*(ptr1->comScore)+(0.01*perPoten)*(ptr1->potenScore) > (0.01*perGame)*(ptr1->next->gameScore)+(0.01*perCom)*(ptr1->next->comScore)+(0.01*perPoten)*(ptr1->next->potenScore))
            {
                swap(head,ptr1, ptr1->next); //ptr1,ptr1->next
                swapped = 1; //swapped=1
            }
            head=ptr1;
            ptr1 = ptr1->next;//ptr1=(4)
        }
        lptr = ptr1; //lptr=(4)
    }
    while(swapped);

    struct node* temp=what_node;
    while (temp!= NULL) {
        printf("%s %s %0.1f\n", temp->position, temp->name, ((0.01*perGame)*(temp->gameScore)+(0.01*perCom)*(temp->comScore)+(0.01*perPoten)*(temp->potenScore))/3);
        temp = temp->next;
    }
    printf("\n");

    fclose(fp);
}
