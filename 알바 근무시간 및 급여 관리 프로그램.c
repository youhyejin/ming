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

void login_menu(); // �α��� �޴� (1. ������, 2. �����) 

void user_login(); // ����� �α��� 
void user_main(); // ����� ���� 

void is_come(); // ����� 

void duty_salay_check(); // �ٷ� �ð� �� �޿�

void admin_login(); //������ �α��� 
void admin_main(); // ������ ���� 

void admin_user_manage(); // �˹ٻ� ���� 
void user_add(); // ����� ��� 
void user_list(); // ����� ��� 

void admin_duty_salay_manage(); // �ٷνð� �� �޿� ����
void duty_salay_list(); // �ٷνð� �� �޿� ��� 
void duty_salay_modify(); // �ٷνð� �� �޿� ���� 
void duty_salay_delete(); // �ٷνð� �� �޿� ���� 

IDPW idpw; // �α����� ���̵�, ��й�ȣ 
USER user[30];

time_t start, end; // ��ٽð�, ��ٽð�

int main(void)
{
	login_menu(); 
	
	return 0;
}

// �α��� �޴�(������, �����) 
void login_menu(){
	int menu;
	printf("1. ������ �α���\n");
	printf("2. ����� �α���\n"); 
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

// ����� �α��� 
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
			printf("���̵� �Ǵ� ��й�ȣ�� �ٸ��ϴ�. �ٽ��Է��ϼ���.\n");
			user_login();
		}
	}

}

// ����� ���� 
void user_main()
{
	int menu;
	
	printf("[  ����� �޴� ]\n");
	printf("1. �����\n");
	printf("2. �ٷνð� �� �޿� ��ȸ\n"); 
	printf("0. �ڷΰ���\n");
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

// ����� 
void is_come()
{
	FILE *fp;
	
	int i=0, j;
	int index;
	
	int come;
	
	printf("1. ���\n");
	printf("2. ���\n");
	printf("0. �ڷΰ���\n"); 
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
				
				printf("���õ� ȭ����!!!");
				printf("\nEnter");
				getchar();
				getchar(); 
				system("cls");
				user_main();
			} else{
				system("cls");
				printf("�߸��Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���.");
				is_come();
			}
			break;
		case 2:
			if(user[index].state != 2){
				end = time(NULL);
				user[index].endTime = end;
				user[index].state = 2;	
				
				int duty = (end - start); /// 60 / 60; // �ʸ� �÷� ��� 
				int salay = 8720 * duty; // �޿� 

				user[index].duty = user[index].duty + duty;
				user[index].salay = user[index].salay + salay;
				
				fp = fopen("user.txt", "w");
				for(j=0; j<i; j++){
					fprintf(fp, "%s %s %s %s %d %d %d %d %d\n", user[j].name, user[j].phone, user[j].idpw.id, user[j].idpw.pw, user[j].startTime, user[j].endTime, user[j].duty, user[j].salay, user[j].state);
				}
				fclose(fp);
				
				printf("���õ� �����ϼ̽��ϴ�~~");
				printf("\nEnter");
				getchar();
				getchar(); 	
				system("cls");
				user_main();	
			} else{
				system("cls");
				printf("�߸��Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���.");
				is_come();
			}
			break;
		case 0:
			system("cls");
			user_main();
			break;
		
	}
}

// �ٷνð� �� �޿� Ȯ�� 
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
	
	printf("%s(%s)��\n\n", user[index].name, user[index].idpw.id);
	printf("�ٷνð�: %d �ð�\n", user[index].duty);
	printf("�޿� : %d ��\n\n", user[index].salay);
	printf("Enter");
	getchar();
	getchar();
	system("cls");
	user_main();
}

// ������ �α��� 
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
			printf("���̵� �Ǵ� ��й�ȣ�� �ٸ��ϴ�. �ٽ��Է��ϼ���.\n");
			admin_login();
		}
	}

	
} 

// ������ ���� 
void admin_main(){
	int menu;
	printf("������\n");
	printf("1. �˹ٻ� ����\n");
	printf("2. �ٷ� �ð� �� �޿� ����\n");
	printf("0. �ڷΰ���\n");
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

// �˹ٻ� ���� 
void admin_user_manage()
{
	system("cls");
	int menu;
	
	printf("�˹ٻ� ����\n");
	printf("1. �˹ٻ� ���\n");
	printf("2. �˹ٻ� ��ȸ\n");
	printf("3. �˹ٻ� ����\n");
	printf("4. �˹ٻ� ����\n");
	printf("0. �ڷΰ���\n");
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
	
	printf("[  �˹ٻ� ��� ]\n\n");
	printf("�̸�: ");
	scanf("%s", input.name);
	printf("��ȭ��ȣ: ");
	scanf("%s", input.phone);
	printf("���̵�: ");
	scanf("%s", input.idpw.id);
	printf("��й�ȣ: ");
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
	user[i].state = 2; // ��� 
	
	fp = fopen("user.txt", "a");

	fprintf(fp, "%s %s %s %s %d %d %d %d %d\n", user[i].name, user[i].phone, user[i].idpw.id, user[i].idpw.pw, user[i].startTime, user[i].endTime, user[i].duty, user[i].salay, user[i].state);
	
	fclose(fp);
	printf("����� �Ϸ�Ǿ����ϴ�. \n");
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
	printf("[  �˹ٻ� ��� ]\n\n");
	printf("%-12s %-12s %-10s %-10s %-10s %-10s %-10s\n\n", "�̸�", "��ȭ��ȣ", "���̵�", "��й�ȣ", "�ٹ��ð�", "�޿�", "�ٹ���Ȳ");
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

	printf("[  �ٷ� �ð� �� �޿� ���� ]\n");
	printf("1. �ٷ� �ð� �� �޿� ��ȸ\n");
	printf("2. �ٷ� �ð� �� �޿� ����\n");
	printf("3. �ٷ� �ð� �� �޿� ����\n");
	printf("0. �ڷΰ���\n");
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
	
	printf("[  �ٷνð� �� �޿� ��ȸ  ]\n\n");
	printf("%-12s %-12s %-10s %-10s\n\n", "�̸�", "��ȭ��ȣ", "�ٹ��ð�", "�޿�");
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
	
	printf("[  �ٷ� �ð� �� �޿� ����  ]\n\n");

	printf("1. �ٷ� �ð� ����\n");
	printf("2. �޿� ����\n");
	printf("0. �ڷΰ���\n");
	scanf("%d", &menu);
	
	printf("������ ����� ���̵� �Է� >> ");
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
			printf("[  �ٷ� �ð� ����  ]\n\n");
			printf("%s(%s)�� �ٷ� �ð� : %d\n", user[index].name, user[index].idpw.id, user[index].duty);
			printf("���� �ð� >> ");
			scanf("%d", &input);
			printf("%d �ð� -> %d �ð����� ����\n", user[index].duty, input); 
			user[index].duty = input;
			break;
		case 2:
			system("cls");
			printf("[  �޿� ����  ]\n\n");
			printf("%s(%s)�� �޿� : %d\n", user[index].name, user[index].idpw.id, user[index].salay);
			printf("�μ�Ƽ�� >> ");
			scanf("%d", &input);
			printf("%d �� -> %d ������ ����\n");
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
	
	printf("[  �ٷ� �ð� �� �޿� ����  ]\n\n");

	printf("1. �ٷ� �ð� ����");
	printf("2. �޿� ����\n");
	printf("0. �ڷΰ���\n");
	scanf("%d", &menu);
	
	printf("������ ����� ���̵� �Է� >> ");
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
			printf("[  �ٷ� �ð� ����  ]\n");
			printf("%s(%s)�� �ٷ� �ð� : %d\n", user[index].name, user[index].idpw.id, user[index].duty);
			printf("�����Ͻðڽ��ϱ�(YES:1, NO:0)>> ");
			scanf("%d", &input);
			if(input == 1){
				user[index].duty = 0;
			} else if(input == 0){
				admin_duty_salay_manage();
			}
			break;
		case 2:
			system("cls");
			printf("[  �޿� ����  ]\n");
			printf("%s(%s)�� �޿� : %d\n", user[index].name, user[index].idpw.id, user[index].salay);
			printf("�����Ͻðڽ��ϱ�?(YES:1, NO:0)>> ");
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
	printf("�����Ǿ����ϴ�.\n");
	printf("Enter");
	getchar();
	getchar(); 
	system("cls");
	admin_duty_salay_manage();
}

