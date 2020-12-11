#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//구단 선수

struct node {
    char position[20];
    char name[20];
    int gameScore;
    int comScore;
    struct node* next;
};

//현재 있는 선수
//	struct node* new_node;
//영입가능선수
//	struct node* come_node;

struct node* list_head = NULL;
char name[20];
char input = '0';
FILE* fp = NULL;
char filename[20];

//파일 열기
void openFile(char* filename) {

    fp = fopen(filename, "r+");
    if (fp == NULL) {
        printf("Cannot open file\n");
    }
}

void print_list(struct node*);

//파일내 텍스트 내용  삭제
void deleteNode(struct node* head_ptr,char* name){
	struct node* target_ptr=head_ptr->next;	
	struct node* prev=head_ptr;

	while(target_ptr!=NULL){
		if(strcmp(target_ptr->name,name)==0){
			break;
		}
		else{
			prev=target_ptr;
			target_ptr=target_ptr->next;
		}
	}
	if(target_ptr==NULL) return;

	prev->next=target_ptr->next;
	free(target_ptr);
//	print_list(new_node);
//	fp=fopen("player.txt","wb");
//	fwrite(&new_node,sizeof(new_node),1,fp);

//  fclose(fp);

}

int delplayer(struct node* head_ptr,void(*del)(struct node* head,char *name)){
	char name[20];
	printf("삭제할 선수를 입력하세요.");
	scanf("%s",name);
	del=deleteNode;
	del(head_ptr,name);
}

void print_list(struct node*);
//구조체에 내용넣고 출력
void readPlayer(char* filename, struct node* what_node) {
    openFile(filename);
    printf("===============================\n");
    printf("선수 출력\n");
    printf("===============================\n");
    printf("포지션 이름 개인게임성적 대회성적\n");
    while (!feof(fp)) {
        what_node = (struct node*)malloc(sizeof(struct node));
        fscanf(fp, "%s %s %d %d\n", what_node->position, what_node->name, &(what_node->gameScore), &(what_node->comScore));

        what_node->next = list_head;
        list_head=what_node;
    }
		print_list(what_node);
    printf("===============================\n");

    fclose(fp);
}

int perGame;
int perCom;

int setPer() {
    printf("공격력 평가 비율을 입력하세요");
    scanf("%d", &perGame);

    printf("방어력  평가 비율을 입력하세요");
    scanf("%d", &perCom);

    printf("공격력%d 방어력%d으로 설정되었습니다.\n ", perGame, perCom);
}

void print_list(struct node* what_node) {
		struct node* temp=what_node;
    while (temp!= NULL) {
        printf("%s %s %d %d\n", temp->position, temp->name, temp->gameScore, temp->comScore);
        temp = temp->next;
    }
    printf("\n");
}

void swap(struct node *a, struct node *b) 
{ 
    //char temp1[20] = a->position;
		int temp2 = a->gameScore;  
    //a->position=b->position;
		a->gameScore = b->gameScore;  
    //b->position=temp1;
		b->gameScore = temp2; 
}
 
void sortNode(char* filename,struct node* what_node) //what_node 지정해주며 시작
{ 
    openFile(filename);
    printf("===============================\n");
    printf("선수 출력\n");
    printf("===============================\n");
    printf("포지션 이름 개인게임성적 대회성적\n");
    while (!feof(fp)) {
        what_node = (struct node*)malloc(sizeof(struct node));
        fscanf(fp, "%s %s %d %d\n", what_node->position, what_node->name, &(what_node->gameScore), &(what_node->comScore));
        printf("%s %s %d %d\n", what_node->position, what_node->name, what_node->gameScore, what_node->comScore);

        what_node->next = list_head;
        list_head = what_node;
    }
		printf("sortnode 처음시작됨\n");    
    int swapped, i; 
    struct node *ptr1; 
    struct node *lptr = NULL; 
  
    
		  
    do //do while문 이용
    { 
        swapped = 0; //swapped=0으로 설정
        ptr1 = what_node; //ptr1에 what_node
        while (ptr1->next != lptr) //ptr1->next(2).lptr(NULL)
        { 
            if (ptr1->gameScore > ptr1->next->gameScore) 
            {  
                swap(ptr1, ptr1->next); //ptr1,ptr1->next
                swapped = 1; //swapped=1
            } 
            ptr1 = ptr1->next;//ptr1=(4)
        } 
        lptr = ptr1; //lptr=(4)
    } 
    while(swapped);

		struct node* temp=what_node;
    while (temp!= NULL) {
        printf("%s %s %d %d\n", temp->position, temp->name, temp->gameScore, temp->comScore);
        temp = temp->next;
    }
    printf("\n");

    fclose(fp);
}
 
   
void main() {
    int number;

//현재 있는 선수
	struct node* new_node;
//영입가능선수
	struct node* come_node;
    while (1) {

        printf("1.현재구단 선수 출력/2. 평가능력치 설정/3. 영입가능 선수 출력/4.선수추가,삭제 5. 종료\n");
        scanf("%d", &number);
        int tmp_gamescore = 0;

        if (number == 1) readPlayer("player.txt", new_node);
					
        else if (number == 2) setPer();
        else if (number == 3) sortNode("freeplayer.txt",come_node);
        else if (number == 4) delplayer(new_node,deleteNode);
				else if (number == 5) break;
        else printf("잘못 입력하셨습니다.\n");
    }
}
