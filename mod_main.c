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


FILE* fp = NULL;

//파일 열기
void openFile(char* filename) {

    fp = fopen(filename, "r+");
    if (fp == NULL) {
        printf("Cannot open file\n");
    }
}

void print_list(struct node*);

//4번 기능 함수
//파일내 텍스트 내용  삭제, 추가

void deleteNode(struct node* head_ptr,struct node* head_ptr2,char* name){
	printf("\n");
	struct node* target_ptr=head_ptr;
	struct node* target_ptr2=head_ptr2->next;
	struct node* prev=head_ptr;
	struct node* temp_add=(struct node*)malloc(sizeof(head_ptr));

	if (name==head_ptr->name){
	
	struct node* head=(struct node*)malloc(sizeof(head_ptr));
	head->next=head_ptr;

	}

	while(head_ptr!=NULL){
		if(strcmp(head_ptr->name,name)==0){
break;
		}
		else{
			prev=head_ptr;
			head_ptr=head_ptr->next;
		}
	}
//	if(target_ptr==NULL) return;
	temp_add=head_ptr;
	prev->next=head_ptr->next;
	free(head_ptr);
	while(head_ptr2->next!=NULL){
		head_ptr2=head_ptr2->next;
		}
	temp_add->next=NULL;
	head_ptr2->next=temp_add;
//	head_ptr2=temp_add;

//	fp=fopen("player.txt","wb");
//	fwrite(&new_node,sizeof(new_node),1,fp);

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
	fp=fopen(file_name, "w" );
	if (what_node!=NULL)
	{
		char i;
		i=(what_node->position);
		fputs(i,fp);
		what_node=what_node->next;
	}
	printf("upload end\n");
	fclose(fp);
}

//
void print_list(struct node*);
//구조체에 내용넣고 출력
struct node* putStruct(struct node* what_node){
		what_node=NULL;
struct node* list_head = NULL;
    while (!feof(fp)) {
        what_node = (struct node*)malloc(sizeof(struct node));
        fscanf(fp, "%s %s %d %d\n", what_node->position, what_node->name, &(what_node->gameScore), &(what_node->comScore));

        what_node->next = list_head;
        list_head=what_node;
    }
		return what_node;

}
//1번 기능 실행 함수

struct node* readPlayer(char* filename, struct node* what_node) {

    openFile(filename);
		return putStruct(what_node);
 
    fclose(fp);
}

//2번 기능 실행 함수
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
}

void swap(struct node* head,struct node *a, struct node *b) 
{ 
		char temp0[20]; 
		strcpy(temp0,a->position);
		char temp1[20];
		strcpy(temp1,a->name);
		int temp2 = a->gameScore; 
		int temp3=a->comScore;
 
		strcpy(a->position,b->position);
		strcpy(a->name,b->name);
		a->gameScore=b->gameScore;
		a->comScore=b->comScore;

		strcpy(b->position,temp0); 
		strcpy(b->name,temp1); 
		b->gameScore = temp2;
		b->comScore=temp3; 
}

//3번 기능 실행 
 
void sortNode(struct node* what_node) //what_node 지정해주며 시작
{  

		
    printf("===============================\n");
		printf("sortnode 처음시작됨\n");    
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
            if ((ptr1->gameScore)+(ptr1->comScore) > (ptr1->next->gameScore)+(ptr1->next->comScore)) 
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
        printf("%s %s %d\n", temp->position, temp->name, (temp->gameScore)+(temp->comScore));
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

//파일 내용 넣어주기		
		new_node=readPlayer("player.txt", new_node);
		come_node=readPlayer("freeplayer.txt", come_node);

		while (1) {

        printf("1.현재구단 선수 출력/2. 평가능력치 설정/3. 영입가능 선수 출력/4.선수추가,삭제 5. 종료\n");
        scanf("%d", &number);
        int tmp_gamescore = 0;

        if (number == 1){
						print_list(new_node);
					}
        else if (number == 2) setPer();
        else if (number == 3) {
					print_list(come_node);
					sortNode(come_node);
					}
        else if (number == 4) {
					delplayer(come_node,new_node,deleteNode);
					print_list(come_node);
					uploadFile("freeplayer.txt",come_node);
					uploadFile("player.txt",new_node);
					}
				else if (number == 5) break;
        else printf("잘못 입력하셨습니다.\n");
    }
}
