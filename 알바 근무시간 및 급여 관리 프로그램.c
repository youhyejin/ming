#include <stdio.h>
#include <string.h> 
#include <time.h>

typedef struct IDPW{
	char id[10];
	char pw[10]; 
}IDPW;

typedef struct USER{
	char name[20];
	char phone[20];
	IDPW idpw;
	time_t startTime;
	time_t endTime;
	int duty;
	int salay;
	int state;
}USER;

void login_menu(); // 로그인 메뉴 (1. 관리자, 2. 사용자) 

void user_login(); // 사용자 로그인 
void user_main(); // 사용자 메인 

void is_come(); // 출퇴근 

void duty_salay_check(); // 근로 시간 및 급여

void admin_login(); //관리자 로그인 
void admin_main(); // 관리자 메인 

void admin_user_manage(); // 알바생 관리 
void user_add(); // 사용자 등록 
void user_list(); // 사용자 목록 

void admin_duty_salay_manage(); // 근로시간 및 급여 관리
void duty_salay_list(); // 근로시간 및 급여 목록 
void duty_salay_modify(); // 근로시간 및 급여 수정 
void duty_salay_delete(); // 근로시간 및 급여 삭제 

IDPW idpw; // 로그인한 아이디, 비밀번호 
USER user[30];

time_t start, end; // 출근시간, 퇴근시간

int main(void)
{
	login_menu(); 
	
	return 0;
}

// 로그인 메뉴(관리자, 사용자) 
void login_menu(){
	int menu;
	printf("1. 관리자 로그인\n");
	printf("2. 사용자 로그인\n"); 
	printf(">> ");
	scanf("%d", &menu);
	
	switch(menu){
		case 1:
			system("cls");
			admin_login();
			break;
		case 2:
			system("cls");
			user_login();
			break;
	}
}

// 사용자 로그인 
void user_login()
{
	FILE *fp;
	
	int i=0, j=0;
	
	fp = fopen("user.txt", "r");
	
	while(1){
		if(feof(fp))
			break;
		fscanf(fp, "%s %s %s %s %d %d %d %d %d\n", user[i].name, user[i].phone, user[i].idpw.id, user[i].idpw.pw, &user[i].startTime, &user[i].endTime, &user[i].duty, &user[i].salay, &user[i].state);
		i++; 
	}
	fclose(fp);

	printf("ID : ");
	scanf("%s", idpw.id);
	printf("PASSWARD : ");
	scanf("%s", idpw.pw);

	for(j=0; j<i; j++){
		if((strcmp(user[j].idpw.id, idpw.id) == 0) && (strcmp(user[j].idpw.pw, idpw.pw) == 0)){
			system("cls");
			user_main();
			break;
		}else if(j == i-1){
			system("cls");
			printf("아이디 또는 비밀번호가 다릅니다. 다시입력하세요.\n");
			user_login();
		}
	}

}

// 사용자 메인 
void user_main()
{
	int menu;
	
	printf("[  사용자 메뉴 ]\n");
	printf("1. 출퇴근\n");
	printf("2. 근로시간 및 급여 조회\n"); 
	printf("0. 뒤로가기\n");
	scanf("%d", &menu);
	
	switch(menu){
		case 1:
			system("cls");
			is_come();
			break;
		case 2:
			system("cls");
			duty_salay_check();
			break;
		case 0:
			system("cls");
			user_login();
			break;
	} 
	
}

// 출퇴근 
void is_come()
{
	FILE *fp;
	
	int i=0, j;
	int index;
	
	int come;
	
	printf("1. 출근\n");
	printf("2. 퇴근\n");
	printf("0. 뒤로가기\n"); 
	printf(">> ");
	scanf("%d", &come);
	
	fp = fopen("user.txt", "r");
	
	while(1){
		if(feof(fp))
			break;
		fscanf(fp, "%s %s %s %s %d %d %d %d %d\n", user[i].name, user[i].phone, user[i].idpw.id, user[i].idpw.pw, &user[i].startTime, &user[i].endTime, &user[i].duty, &user[i].salay, &user[i].state);
		i++;
	}
	fclose(fp);
	
	for(j=0; j<i; j++){
		if(strcmp(user[j].idpw.id, idpw.id) == 0){
			index = j;
			break;
		}
	}
	switch(come){
		case 1:
			if(user[index].state != 1){
				start = time(NULL);
				user[index].startTime = start;
				user[index].state = 1;
				
				fp = fopen("user.txt", "w");
				for(j=0; j<i; j++){
					fprintf(fp, "%s %s %s %s %d %d %d %d %d\n", user[j].name, user[j].phone, user[j].idpw.id, user[j].idpw.pw, user[j].startTime, user[j].endTime, user[j].duty, user[j].salay, user[j].state);
				}
				
				fclose(fp);
				
				printf("오늘도 화이팅!!!");
				printf("\nEnter");
				getchar();
				getchar(); 
				system("cls");
				user_main();
			} else{
				system("cls");
				printf("잘못입력하셨습니다. 다시 입력해주세요.");
				is_come();
			}
			break;
		case 2:
			if(user[index].state != 2){
				end = time(NULL);
				user[index].endTime = end;
				user[index].state = 2;	
				
				int duty = (end - start); /// 60 / 60; // 초를 시로 계산 
				int salay = 8720 * duty; // 급여 

				user[index].duty = user[index].duty + duty;
				user[index].salay = user[index].salay + salay;
				
				fp = fopen("user.txt", "w");
				for(j=0; j<i; j++){
					fprintf(fp, "%s %s %s %s %d %d %d %d %d\n", user[j].name, user[j].phone, user[j].idpw.id, user[j].idpw.pw, user[j].startTime, user[j].endTime, user[j].duty, user[j].salay, user[j].state);
				}
				fclose(fp);
				
				printf("오늘도 수고하셨습니다~~");
				printf("\nEnter");
				getchar();
				getchar(); 	
				system("cls");
				user_main();	
			} else{
				system("cls");
				printf("잘못입력하셨습니다. 다시 입력해주세요.");
				is_come();
			}
			break;
		case 0:
			system("cls");
			user_main();
			break;
		
	}
}

// 근로시간 및 급여 확인 
void duty_salay_check()
{
	FILE *fp;
	
	int i=0, j;
	int index;
	
	fp = fopen("user.txt", "r");
	
	while(1){
		if(feof(fp))
			break;
		fscanf(fp, "%s %s %s %s %d %d %d %d %d\n", user[i].name, user[i].phone, user[i].idpw.id, user[i].idpw.pw, &user[i].startTime, &user[i].endTime, &user[i].duty, &user[i].salay, &user[i].state);
		i++;
	}
	
	for(j=0; j<i; j++){
		if(strcmp(user[j].idpw.id, idpw.id) == 0){
			index = j;
			break;
		}
	}
	
	printf("%s(%s)님\n\n", user[index].name, user[index].idpw.id);
	printf("근로시간: %d 시간\n", user[index].duty);
	printf("급여 : %d 원\n\n", user[index].salay);
	printf("Enter");
	getchar();
	getchar();
	system("cls");
	user_main();
}

// 관리자 로그인 
void admin_login()
{
	FILE *fp;
	
	IDPW a_list[20];
	
	int i=0, j=0;
	
	fp = fopen("admin_idpw.txt", "r");
	
	while(1){
		if(feof(fp))
			break;
		fscanf(fp, "%s %s", a_list[i].id, a_list[i].pw);
		i++; 
	}
	
	fclose(fp);
	
	printf("ID : ");
	scanf("%s", idpw.id);
	printf("PASSWARD : ");
	scanf("%s", idpw.pw);
	
	for(j=0; j<i; j++){
		if((strcmp(a_list[j].id, idpw.id) == 0) && (strcmp(a_list[j].pw, idpw.pw) == 0)){
			system("cls");
			admin_main();
			break;
		}else if(j == i-1){
			system("cls");
			printf("아이디 또는 비밀번호가 다릅니다. 다시입력하세요.\n");
			admin_login();
		}
	}

	
} 

// 관리자 메인 
void admin_main(){
	int menu;
	printf("관리자\n");
	printf("1. 알바생 관리\n");
	printf("2. 근로 시간 및 급여 관리\n");
	printf("0. 뒤로가기\n");
	printf(">> "); 
	scanf("%d", &menu);
	
	switch(menu){
		case 1:
			system("cls");
			admin_user_manage(); 
			break;
		case 2:
			system("cls");
			admin_duty_salay_manage();
			break;
		case 0:
			system("cls");
			admin_login();
			break;
	}
}

// 알바생 관리 
void admin_user_manage()
{
	system("cls");
	int menu;
	
	printf("알바생 관리\n");
	printf("1. 알바생 등록\n");
	printf("2. 알바생 조회\n");
	printf("3. 알바생 수정\n");
	printf("4. 알바생 삭제\n");
	printf("0. 뒤로가기\n");
	scanf("%d", &menu);
	switch(menu){
		case 1:
			system("cls");
			user_add();
			break;
		case 2:
			system("cls");
			user_list();
			break;
		case 3:
			break;
		case 4:
			break;
		case 0:
			system("cls");
			admin_main();
			break;
	}
}
void user_add()
{
	FILE *fp;
	USER input;
	int i=0, j;
	
	fp = fopen("user.txt", "r");
	
	printf("[  알바생 등록 ]\n\n");
	printf("이름: ");
	scanf("%s", input.name);
	printf("전화번호: ");
	scanf("%s", input.phone);
	printf("아이디: ");
	scanf("%s", input.idpw.id);
	printf("비밀번호: ");
	scanf("%s", input.idpw.pw);
	
	while(1){
		if(feof(fp))
			break;
		fscanf(fp, "%s %s %s %s %d %d %d %d %d\n", user[i].name, user[i].phone, user[i].idpw.id, user[i].idpw.pw, &user[i].startTime, &user[i].endTime, &user[i].duty, &user[i].salay, &user[i].state);
		i++;
	}
	fclose(fp);
	
	strcpy(user[i].name, input.name);
	strcpy(user[i].phone,input.phone);
	strcpy(user[i].idpw.id, input.idpw.id);
	strcpy(user[i].idpw.pw, input.idpw.pw);
	user[i].startTime = 0;
	user[i].endTime = 0;
	user[i].duty = 0;
	user[i].salay = 0; 
	user[i].state = 2; // 퇴근 
	
	fp = fopen("user.txt", "a");

	fprintf(fp, "%s %s %s %s %d %d %d %d %d\n", user[i].name, user[i].phone, user[i].idpw.id, user[i].idpw.pw, user[i].startTime, user[i].endTime, user[i].duty, user[i].salay, user[i].state);
	
	fclose(fp);
	printf("등록이 완료되었습니다. \n");
	printf("Enter");
	getchar();
	getchar();
	system("cls");
	admin_user_manage();
}
void user_list()
{
	FILE *fp;
	USER input;
	char state;
	int i=0, j;
	
	fp = fopen("user.txt", "r");
	
	while(1){
		if(feof(fp))
			break;
		fscanf(fp, "%s %s %s %s %d %d %d %d %d\n", user[i].name, user[i].phone, user[i].idpw.id, user[i].idpw.pw, &user[i].startTime, &user[i].endTime, &user[i].duty, &user[i].salay, &user[i].state);
		i++;
	}
	fclose(fp);
	printf("[  알바생 목록 ]\n\n");
	printf("%-12s %-12s %-10s %-10s %-10s %-10s %-10s\n\n", "이름", "전화번호", "아이디", "비밀번호", "근무시간", "급여", "근무현황");
	for(j=0; j<i; j++){
		if(user[j].state == 1){
			state = 'O'; 
		}else if(user[j].state == 2){
			state = 'X';
		}
		printf("%-12s %-12s %-10s %-10s %-10d %-10d %-10c\n", user[j].name, user[j].phone, user[j].idpw.id, user[j].idpw.pw, user[j].duty, user[j].salay, state);
	}
	printf("\nEnter");
	getchar();
	getchar();
	system("cls");
	admin_user_manage();
}


void admin_duty_salay_manage()
{
	int menu;

	printf("[  근로 시간 및 급여 관리 ]\n");
	printf("1. 근로 시간 및 급여 조회\n");
	printf("2. 근로 시간 및 급여 수정\n");
	printf("3. 근로 시간 및 급여 삭제\n");
	printf("0. 뒤로가기\n");
	scanf("%d", &menu);
	
	switch(menu){
		case 1:
			system("cls");
			duty_salay_list();
			break;
		case 2:
			system("cls");
			duty_salay_modify();
			break;
		case 3:
			system("cls");
			duty_salay_delete();
			break;
		case 0:
			system("cls");
			admin_main();
			break;
	}
}

void duty_salay_list()
{
	FILE *fp;
	
	int i=0, j;
	int index;
	
	fp = fopen("user.txt", "r");
	
	while(1){
		if(feof(fp))
			break;
		fscanf(fp, "%s %s %s %s %d %d %d %d %d\n", user[i].name, user[i].phone, user[i].idpw.id, user[i].idpw.pw, &user[i].startTime, &user[i].endTime, &user[i].duty, &user[i].salay, &user[i].state);
		i++;
	}
	fclose(fp);
	
	printf("[  근로시간 및 급여 조회  ]\n\n");
	printf("%-12s %-12s %-10s %-10s\n\n", "이름", "전화번호", "근무시간", "급여");
	for(j=0; j<i; j++){
		printf("%-12s %-12s %-10d %-10d\n", user[j].name, user[j].phone, user[j].duty, user[j].salay);
	}
	printf("\nEnter");
	getchar();
	getchar();
	system("cls");
	admin_duty_salay_manage();
} 
 
void duty_salay_modify()
{
	FILE *fp;
	
	int i=0, j;
	int index;
	int input;
	
	int menu;
	char id[20];
	
	fp = fopen("user.txt", "r");
	
	while(1){
		if(feof(fp))
			break;
		fscanf(fp, "%s %s %s %s %d %d %d %d %d\n", user[i].name, user[i].phone, user[i].idpw.id, user[i].idpw.pw, &user[i].startTime, &user[i].endTime, &user[i].duty, &user[i].salay, &user[i].state);
		i++;
	}
	fclose(fp);
	
	printf("[  근로 시간 및 급여 수정  ]\n\n");

	printf("1. 근로 시간 수정\n");
	printf("2. 급여 수정\n");
	printf("0. 뒤로가기\n");
	scanf("%d", &menu);
	
	printf("수정할 사람의 아이디 입력 >> ");
	scanf("%s", id);
	
	for(j=0; j<i; j++){
		if(strcmp(user[j].idpw.id, id) == 0){
			index = j;
			break;
		}
	}
	switch(menu){
		case 1:
			system("cls");
			printf("[  근로 시간 수정  ]\n\n");
			printf("%s(%s)님 근로 시간 : %d\n", user[index].name, user[index].idpw.id, user[index].duty);
			printf("수정 시간 >> ");
			scanf("%d", &input);
			printf("%d 시간 -> %d 시간으로 변경\n", user[index].duty, input); 
			user[index].duty = input;
			break;
		case 2:
			system("cls");
			printf("[  급여 수정  ]\n\n");
			printf("%s(%s)님 급여 : %d\n", user[index].name, user[index].idpw.id, user[index].salay);
			printf("인센티브 >> ");
			scanf("%d", &input);
			printf("%d 원 -> %d 원으로 변경\n");
			user[index].salay = input;
			break;
	}
	fp = fopen("user.txt", "w");
	for(j=0; j<i; j++){
		fprintf(fp, "%s %s %s %s %d %d %d %d %d\n", user[j].name, user[j].phone, user[j].idpw.id, user[j].idpw.pw, user[j].startTime, user[j].endTime, user[j].duty, user[j].salay, user[j].state);
	}
	fclose(fp);
	printf("Enter");
	getchar();
	getchar();
	system("cls");
	admin_duty_salay_manage();
}

void duty_salay_delete()
{
	FILE *fp;
	
	int i=0, j;
	int index;
	int input;
	
	int menu;
	char id[20];
	
	fp = fopen("user.txt", "r");
	
	while(1){
		if(feof(fp))
			break;
		fscanf(fp, "%s %s %s %s %d %d %d %d %d\n", user[i].name, user[i].phone, user[i].idpw.id, user[i].idpw.pw, &user[i].startTime, &user[i].endTime, &user[i].duty, &user[i].salay, &user[i].state);
		i++;
	}
	fclose(fp);
	
	printf("[  근로 시간 및 급여 삭제  ]\n\n");

	printf("1. 근로 시간 삭제");
	printf("2. 급여 삭제\n");
	printf("0. 뒤로가기\n");
	scanf("%d", &menu);
	
	printf("삭제할 사람의 아이디 입력 >> ");
	scanf("%s", id);
	
	for(j=0; j<i; j++){
		if(strcmp(user[j].idpw.id, id) == 0){
			index = j;
			break;
		}
	}
	switch(menu){
		case 1:
			system("cls");
			printf("[  근로 시간 삭제  ]\n");
			printf("%s(%s)님 근로 시간 : %d\n", user[index].name, user[index].idpw.id, user[index].duty);
			printf("삭제하시겠습니까(YES:1, NO:0)>> ");
			scanf("%d", &input);
			if(input == 1){
				user[index].duty = 0;
			} else if(input == 0){
				admin_duty_salay_manage();
			}
			break;
		case 2:
			system("cls");
			printf("[  급여 삭제  ]\n");
			printf("%s(%s)님 급여 : %d\n", user[index].name, user[index].idpw.id, user[index].salay);
			printf("삭제하시겠습니까?(YES:1, NO:0)>> ");
			scanf("%d", &input);
			if(input == 1){
				user[index].salay = 0;
			} else if(input == 0){
				admin_duty_salay_manage();
			}
			break;
	}
	fp = fopen("user.txt", "w");
	for(j=0; j<i; j++){
		fprintf(fp, "%s %s %s %s %d %d %d %d %d\n", user[j].name, user[j].phone, user[j].idpw.id, user[j].idpw.pw, user[j].startTime, user[j].endTime, user[j].duty, user[j].salay, user[j].state);
	}
	fclose(fp);
	printf("삭제되었습니다.\n");
	printf("Enter");
	getchar();
	getchar(); 
	system("cls");
	admin_duty_salay_manage();
}

