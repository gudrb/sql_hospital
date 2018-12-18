#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

//#define _CRT_SECURE_NO_WARNINGS

void login(void);  //�ǻ����� ��ȣ������ ȯ������ �����ؼ� ��ȣ�� ��ȯ�Ѵ�.
void join(void);  //ȯ�ڰ� ȸ�������� �� �� �ְ� ���� �Լ�.
void patient_view(char *patient_ID);   //ȯ�� �並 �����ش�.
void doctor_view(char *doctor_ID);    //�ǻ� �並 �����ش�.
void insert_result();                
void Doctor_R_R(char *doctor_ID);     //����� ȯ�� ����� �����ش�.
void Patient_R_R(char *doctor_ID);    //ȯ�ڰ� �ǻ��� ���� �ð��� ����.
void Room_R_R(char *room_num);        //ȯ�ڰ� �� �Կ� ��Ȳ�� ����.
void nurse_view(char *nurse_ID);     //��ȣ�� �並 �����ش�.
void insert_bill();                  //�˻��� �Է�.
void insert_Hbill();                  //�Կ���� �Է�.
char *compare_exist(char *ID);        //���̵� �����ϴ��� ���ϴ� �Լ�
void patient_view1(void); 
void patient_view2(char *patient_ID);// ȯ���� �� �ι�° �Լ� ���� �ð� Ȯ��
void patient_view3(char *patient_ID);
void patient_view4(char *patient_ID);
void patient_view5(char *patient_ID);
void patient_view8(char *patient_ID);
void patient_view9(char *patient_ID);
void treat_res(char *doctor_ID);   //ȯ�ڰ� ���� �����ϴ� �Լ�
void hospital_res(char *room_num);  //ȯ�ڰ� �Կ����� �����ϴ� �Լ�

MYSQL mysql;

int main(void) {
	//MYSQL mysql;
	int login_num;
	char *host = "localhost";
	char *user = "root";
	char *pwd = "-awawa45097";
	char *db = "cheil_hospital";

	while (1) {
	
		mysql_init(&mysql);
		
		if (!mysql_real_connect(&mysql, host, user, pwd, db, 3306, NULL, 0)) {

			printf("****************���� ����****************\n");
		}
		else {
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\t\t\t************cheil hospital ************\n");
			printf("\t\t\t1. �α���\n");
			printf("\t\t\t2. ȸ�� ����\n");
			printf("\t\t\t3. ���� \n");
			printf("\t\t\t���ϴ� �޴��� �����ϼ��� : ");
			scanf("%d", &login_num);
	
			switch (login_num) {
			case 1:
				system("cls");
				login();
			case 2:
				join();
				break;
			case 3:
				printf("****************��    ��****************\n");
				exit(1);
			}
		}
		printf("****************��    ��****************\n");
		exit(1);
	}

	mysql_close(&mysql);
	return 0;
}
void join(void) {
	int row_length, cloum_length;
	int i = 0;
	char *qry;
	char ch;
	char qry_[150];
	char qry_ID[150];
	char qry_name[150];
	char qry_sex[150];
	char qry_disease[150];
	char qry_age[150];
	char qry_END[200];
	
	printf("ID �� �Է��Ͻÿ�(����1�� �����ϴ� 10�ڸ� ��): ");
	scanf("%s", qry_ID);
	printf("�̸��� �Է��Ͻÿ�(���� �̸�): ");
	scanf("%s", qry_name);
	printf("������ (����: W, ����: M): ");
	scanf("%s", qry_sex);
	printf("������ �Է��Ͻÿ�(���� ����): ");
	scanf("%s", qry_disease);
	printf("���� �� �Է��Ͻÿ�: ");
	scanf("%s", qry_age);
	
	
	qry = "insert patient values(";

	sprintf(qry_END, "%s%s, '%s', '%s', '%s', %s)", qry, qry_ID, qry_name, qry_sex, qry_disease, qry_age);
	printf("%s", qry_END);
	if (mysql_real_query(&mysql, qry_END, strlen(qry_END))) {
		printf("send query err");
	}

	printf("���ư����� x �� �Է��Ͻÿ� :");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
	}
} 
void login(void) {
	char *compare_ID;
	char *ID;
	
	while (1) {

		system("cls");
		printf("\n");
		printf("\n");
		printf("\n");

		printf("\t\t\t****************�α��� ȭ��****************\n");
		printf("\t\t\tID �� �Է��Ͻÿ� : ");
		compare_ID = (char *)malloc(sizeof(char) * 20);
		ID = (char *)malloc(sizeof(char) * 20);
		scanf("%s", ID);
		compare_ID = compare_exist(ID);

		if (ID != "0") {
			break;
		}
	}
	
	while (1) {
		if(compare_ID[0] == '2') {
			system("cls");
			doctor_view(ID);
		}
		else if (compare_ID[0] == '3') {
			system("cls");
			nurse_view(ID);
		}
		else if (compare_ID[0] == '1') {
			system("cls");
			patient_view(ID);
		}
	}
}
void patient_view(char *patient_ID) {
	int choice_num;   //ȯ�ڰ� �޴��� ������ �� �����ϴ� ����
	char *qry;
	char ch;
	char qry2[150];
	int row_length, cloum_length;
	char *ID;
	qry = "select P_name from patient where patient_ID = ";
	sprintf(qry2, "%s %s", qry, patient_ID);    //ȯ���̸��� ������

	if (mysql_real_query(&mysql, qry2, strlen(qry2))) {
		printf("send query err");
	}

	MYSQL_RES *res = mysql_store_result(&mysql);
	MYSQL_ROW row;

	cloum_length = mysql_num_fields(res);
	row_length = mysql_num_rows(res);

	while (row = mysql_fetch_row(res)) {
		ID = row[0];
	}
	
	while (1) {
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\t\t\t************ %s ************\n", ID);   //~~�� ȯ���մϴ�.��� �߰� ȯ���̸� �޾ƿ;���
		printf("\t\t\t1. �ǻ� ��� ���� �ð� Ȯ�� �� ����\n");
		printf("\t\t\t2. �Կ� ���� ���� �� Ȯ�� �� ����\n");
		printf("\t\t\t3. �ǻ� ��� ���� ��ȸ\n");
		printf("\t\t\t4. �Կ� ���� ��ȸ\n");
		printf("\t\t\t5. �˻� ��� Ȯ�� \n");
		printf("\t\t\t6. ���� ��� Ȯ�� \n");
		printf("\t\t\t7. �Կ� ��� Ȯ�� \n");
		printf("\t\t\t8. ���� \n");
		printf("\t\t\t���ϴ� �޴��� �����ϼ��� : ");
		scanf("%d", &choice_num);
		switch (choice_num) {
		case 1:
			system("cls");
			patient_view1();//�ǻ� ������ �̾Ƴ��� ������ ���� �Լ�
			break;
		case 2:
			system("cls");
			patient_view9(patient_ID);   //�Կ� ���� ������ ���� �� �� �ִ�.���൵ ����
			break;
		case 3:
			system("cls");
			patient_view2(patient_ID);   //���� �ð� Ȯ���ϴ� �Լ�
			break;
		case 4:
			system("cls");
			patient_view8(patient_ID);     //�Կ� ���� Ȯ��
			break;
		case 5:
			system("cls");
			patient_view3(patient_ID);//ȯ���� �˻� ��� �����ͼ� ����ϴ� �Լ�
			break;
		case 6:
			system("cls");
			patient_view4(patient_ID);//ȯ���� ������ �����ͼ� ����ϴ� �Լ�
			break;
		case 7:
			system("cls");
			patient_view5(patient_ID);//ȯ���� �Կ� ����� �����ͼ� ����ϴ� �Լ�
			break;
		case 8:
			exit(1);
		}

	}
}
void patient_view1(){
	int row_length, cloum_length;
	int i = 0;
	char *qry;
	char *doc_choice_ID[20];
	char ch;
	char qry2[150];
	int doc_choice;
	qry = "select D_name, dept_name, doctor_ID from doctor";

	if (mysql_real_query(&mysql, qry, strlen(qry))) {
		printf("send query err");
	}

	MYSQL_RES *res = mysql_store_result(&mysql);
	MYSQL_ROW row;

	//cloum_length = mysql_num_fields(res);
	//row_length = mysql_num_rows(res);
	system("cls");
	printf("***  �ǻ� �̸�   ***   �����   ***\n");
	while (row = mysql_fetch_row(res)) {
		printf("***  %d.   %5s           ***    %10s    ***\n",i, row[0], row[1]);
		doc_choice_ID[i] = row[2];
		i++;
	}
	while (1) {
		printf("�ǻ縦 �����Ͻÿ� (������ = 9): ");
		scanf("%d", &doc_choice);
		if (doc_choice == 9) {
			system("cls");
			break;
		}
			Patient_R_R(doc_choice_ID[doc_choice]);   //�ǻ縦 �����ؼ� ���೻���� Ȯ���� ���ִ�.
		}
}
void patient_view2(char *patient_ID){
	char *qry;
	char ch;
	char qry2[150];
	int row_length, cloum_length;
	char *ID;
	qry = "select start_time, end_time, D_name from treat, doctor where treat.doctor_ID = doctor.doctor_ID and patient_ID = ";
	
	sprintf(qry2, "%s %s", qry, patient_ID);    

	if (mysql_real_query(&mysql, qry2, strlen(qry2))) {
		printf("send query err");
	}

	MYSQL_RES *res = mysql_store_result(&mysql);
	MYSQL_ROW row;

	cloum_length = mysql_num_fields(res);
	row_length = mysql_num_rows(res);

	system("cls");
	printf("***  ���� ���� �ð�   ***   ����  ����  �ð�   ***   �ǻ� �̸�   ***\n");
	while (row = mysql_fetch_row(res)) {
		printf("***   %5s           ***   %10s         ***   %10s    ***\n", row[0], row[1], row[2]);
	}
	printf("���ư����� x �� �Է��Ͻÿ� :");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
	}

}
void patient_view3(char *patient_ID){
	char *qry;
	int ch;
	char qry2[150];
	int row_length, cloum_length;
	char *ID;
	qry = "select disease, inspection_result from patient, medical_certification where medical_certification.patient_ID = patient.patient_ID and patient.patient_ID = ";

	sprintf(qry2, "%s %s", qry, patient_ID);

	if (mysql_real_query(&mysql, qry2, strlen(qry2))) {
		printf("send query err");
	}

	MYSQL_RES *res = mysql_store_result(&mysql);
	MYSQL_ROW row;

	cloum_length = mysql_num_fields(res);
	row_length = mysql_num_rows(res);

	system("cls");
	printf("***  �˻� ���   ***  ġ�� �ʿ� ����  ***\n");
	while (row = mysql_fetch_row(res)) {
		printf("***   %5s      ***   %5s   ***\n", row[0], row[1]);
	}
	while (1) {
		printf("���ư����� 9 �� �Է��Ͻÿ� : ");
		scanf("%d", &ch);
		if (ch == 9) {
			break;
		}
	}

}
void patient_view4(char *patient_ID){
	char *qry;
	char ch;
	char qry2[150];
	int row_length, cloum_length;
	char *ID;
	qry = "select inspection_bill from medical_certification where patient_ID = ";

	sprintf(qry2, "%s %s", qry, patient_ID);

	if (mysql_real_query(&mysql, qry2, strlen(qry2))) {
		printf("send query err");
	}

	MYSQL_RES *res = mysql_store_result(&mysql);
	MYSQL_ROW row;

	cloum_length = mysql_num_fields(res);
	row_length = mysql_num_rows(res);

	system("cls");
	printf("***   ������  ***\n");
	while (row = mysql_fetch_row(res)) {
		printf("***   %5s��    ***\n", row[0]);
	}
	printf("���ư����� x �� �Է��Ͻÿ� :");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
	}
}
void patient_view5(char *patient_ID){
	char *qry;
	char ch;
	char qry2[150];
	int row_length, cloum_length;
	char *ID;
	qry = "select hospitalization_bills from medical_certification where patient_ID = ";

	sprintf(qry2, "%s %s", qry, patient_ID);

	if (mysql_real_query(&mysql, qry2, strlen(qry2))) {
		printf("send query err");
	}

	MYSQL_RES *res = mysql_store_result(&mysql);
	MYSQL_ROW row;

	//cloum_length = mysql_num_fields(res);
	//row_length = mysql_num_rows(res);

	system("cls");
	printf("***   �Կ���  ***\n");
	while (row = mysql_fetch_row(res)) {
		printf("***   %5s��    ***\n", row[0]);
	}
	printf("���ư����� x �� �Է��Ͻÿ� :");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
	}
}
void patient_view8(char *patient_ID) {
	char *qry;
	char ch;
	char qry2[150];
	int row_length, cloum_length;
	char *ID;
	qry = "select start_date, end_date, room_num from assigned_room where patient_ID = ";

	sprintf(qry2, "%s %s", qry, patient_ID);

	if (mysql_real_query(&mysql, qry2, strlen(qry2))) {
		printf("send query err");
	}

	MYSQL_RES *res = mysql_store_result(&mysql);
	MYSQL_ROW row;

	//cloum_length = mysql_num_fields(res);
	//row_length = mysql_num_rows(res);

	system("cls");
	printf("***  ���� ���� ��¥   ***   ����  ����  ��¥   ***   �� ��ȣ   ***\n");
	while (row = mysql_fetch_row(res)) {
		printf("***   %5s           ***   %10s         ***   %10s    ***\n", row[0], row[1], row[2]);
	}
	printf("���ư����� x �� �Է��Ͻÿ� :");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
	}

	
}
void patient_view9(char *patient_ID) {
	int row_length, cloum_length;
	int i = 0;
	char *qry;
	char *room_choice_ID[20];
	char *room_num;
	char ch;
	char qry2[150];
	int doc_choice;
	room_num = (char *)malloc(sizeof(char) * 20);
	qry = "select room_num, building from hospital_room";

	if (mysql_real_query(&mysql, qry, strlen(qry))) {
		printf("send query err");
	}

	MYSQL_RES *res = mysql_store_result(&mysql);
	MYSQL_ROW row;

	//cloum_length = mysql_num_fields(res);
	//row_length = mysql_num_rows(res);
	system("cls");
	printf("***  �� ��ȣ   ***   �ǹ� ��ȣ   ***\n");
	while (row = mysql_fetch_row(res)) {
		printf("***  %d.   %5s           ***    %10s    ***\n", i, row[0], row[1]);
		room_choice_ID[i] = row[0];
		i++;
	}
	printf("���� �����Ͻÿ� : ");
	scanf("%d", &doc_choice);
	room_num = room_choice_ID[doc_choice];
	Room_R_R(room_choice_ID[doc_choice]);    //�ش� ���� ������Ȳ�������ش�.

	printf("���ư����� x �� �Է��Ͻÿ� :");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
	}
}
void doctor_view(char *doctor_ID) {
	int choice_num;   //�ǻ簡 �޴��� ������ �� �����ϴ� ����
	char *qry;
	char ch;
	char qry2[150];
	int row_length, cloum_length;
	char *ID;
	qry = "select D_name from doctor where doctor_ID = ";
	sprintf(qry2, "%s %s", qry, doctor_ID);    //�ǻ� ���̵� ���Ͽ� �ǻ� �̸��� �������� ����

	if (mysql_real_query(&mysql, qry2, strlen(qry2))) {
		printf("send query err");
	}

	MYSQL_RES *res = mysql_store_result(&mysql);
	MYSQL_ROW row;

	cloum_length = mysql_num_fields(res);
	row_length = mysql_num_rows(res);

	while (row = mysql_fetch_row(res)) {
		ID = row[0];
	}
	while (1) {
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\t\t\t************ %s ************\n", ID);   //�ǻ� ���̵� �ǻ� �̸� �̾ƿͼ� ����ϱ�
		printf("\t\t\t1. ȯ�� ���� ��� �Է�\n");
		printf("\t\t\t2. ȯ�� ���� ���� Ȯ��\n");
		printf("\t\t\t3. ���� \n");
		printf("\t\t\t���ϴ� �޴��� �����ϼ��� : ");
		scanf("%d", &choice_num);
		switch (choice_num) {
		case 1:
			system("cls");
			insert_result();    //ȯ���� ���� ����� �Է��ϴ� �Լ�
		case 2:
			system("cls");
			Doctor_R_R(doctor_ID);    //�ش� �ǻ��� ȯ�� ���� ������ ����ϴ� �Լ�
		case 3:
			exit(1);
		}
	}
}
void insert_result() {
	int row_length, cloum_length;
	int i = 0;
	char *qry;
	char ch;
	char *qry_bill;
	char *qry_result;
	char *qry_Hbill;
	char *qry_PID;
	char *qry_END;
	qry_bill = (char *)malloc(sizeof(char) * 100);
	qry_result = (char *)malloc(sizeof(char) * 100);
	qry_Hbill = (char *)malloc(sizeof(char) * 100);
	qry_PID = (char *)malloc(sizeof(char) * 100);
	qry_END = (char *)malloc(sizeof(char) * 100);

	qry_bill = "0";
	printf("ġ�� �ʿ� ���θ� �Է��ϼ��� :");
	scanf("%s", qry_result);
	qry_Hbill = "0";
	printf("ȯ�� ���̵� �Է��ϼ��� : ");
	scanf("%s", qry_PID);
	


	
	qry = "insert into medical_certification values(";
	
	sprintf(qry_END, "%s%s, '%s', %s, %s)", qry, qry_bill, qry_result, qry_Hbill, qry_PID);

	if (mysql_real_query(&mysql, qry_END, strlen(qry_END))) {
		printf("send query err");
	}

	printf("���ư����� x �� �Է��Ͻÿ� :");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
	}
}
void Doctor_R_R(char *doctor_ID) {  //�ڽſ��� ����� ȯ�� ���
	int row_length, cloum_length;
	int i = 0;
	char *qry;
	char ch;
	char qry2[150];
	qry = "select start_time, end_time, patient_ID from treat where doctor_ID = ";
	
	sprintf(qry2, "%s %s", qry, doctor_ID);

	if (mysql_real_query(&mysql, qry2, strlen(qry2))) {
		printf("send query err");
	}

	MYSQL_RES *res = mysql_store_result(&mysql);
	MYSQL_ROW row;

	cloum_length = mysql_num_fields(res);
	row_length = mysql_num_rows(res);
	system("cls");
	printf("***  ���� ���� �ð�   ***   ����  ����  �ð�   ***   ȯ�� ���̵�   ***\n");
	while (row = mysql_fetch_row(res)) {
		printf("***   %5s           ***   %10s         ***   %10s    ***\n", row[0], row[1], row[2]);
	}
	printf("���ư����� x �� �Է��Ͻÿ� :");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
	}
}
void Patient_R_R(char *doctor_ID) {
	int row_length, cloum_length;
	int i = 0;
	char *qry;
	char ch;
	char qry2[150];
	qry = "select start_time, end_time from treat where doctor_ID = ";

	sprintf(qry2, "%s %s", qry, doctor_ID);

	if (mysql_real_query(&mysql, qry2, strlen(qry2))) {
		printf("send query err");
	}

	MYSQL_RES *res = mysql_store_result(&mysql);
	MYSQL_ROW row;

	cloum_length = mysql_num_fields(res);
	row_length = mysql_num_rows(res);
	//system("cls");
	printf("***  ���� ���� �ð�   ***   ����  ����  �ð�   ***\n");
	while (row = mysql_fetch_row(res)) {
		printf("***   %5s           ***      %10s         ***\n", row[0], row[1]);
	}
	printf("�����Ͻ÷��� 1, ���ư����� x �� �Է��Ͻÿ� : ");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
		else if (ch == '1') {
			treat_res(doctor_ID);
			break;
		}
	}
}
void treat_res(char *doctor_ID) {
	char *qry;
	char ch;
	char qry_[150];
	char qry_ID[20];
	//char *qry_D_ID;
	int qry_start_time;
	int qry_end_time;
	char qry_END[150];
	
	//qry_ID = (char *)malloc(sizeof(char) * 100);
	//qry_D_ID = (char *)malloc(sizeof(char) * 100);


	printf("�ڽ��� ���̵� �Է��Ͻÿ� : ");
	scanf("%s", qry_ID);
	//qry_D_ID = doctor_ID;
	printf("���� �ð��� �Է��Ͻÿ� :");
	scanf("%d", &qry_start_time);
	qry_end_time = qry_start_time + 1;


	qry = "insert treat values(";

	sprintf(qry_END, "%s%d, %d, '%s', '%s')", qry, qry_start_time, qry_end_time, qry_ID, doctor_ID);
	printf("%s", qry_END);
	if (mysql_real_query(&mysql, qry_END, strlen(qry_END))) {
		printf("send query err");
	}

	printf("���ư����� x �� �Է��Ͻÿ� :");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
	}
}
void hospital_res(char *room_num) {
	char *qry;
	char ch;
	char qry_[150];
	char qry_ID[20];
	//char *qry_D_ID;
	int qry_start_time;
	int qry_end_time;
	char qry_END[150];

	//qry_ID = (char *)malloc(sizeof(char) * 100);
	//qry_D_ID = (char *)malloc(sizeof(char) * 100);


	printf("�ڽ��� ���̵� �Է��Ͻÿ� : ");
	scanf("%s", qry_ID);
	//qry_D_ID = doctor_ID;
	printf("���� ��¥�� �Է��Ͻÿ� :");
	scanf("%d", &qry_start_time);
	printf("������ �Կ� ��¥�� �Է��Ͻÿ� :");
	scanf("%d", &qry_end_time);


	qry = "insert assigned_room values(";

	sprintf(qry_END, "%s%d, %d, '%s', '%s')", qry, qry_start_time, qry_end_time, qry_ID, room_num);
	printf("%s", qry_END);
	if (mysql_real_query(&mysql, qry_END, strlen(qry_END))) {
		printf("send query err");
	}

	printf("���ư����� x �� �Է��Ͻÿ� :");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
	}
}
void Room_R_R(char *room_num) {
	int row_length, cloum_length;
	int i = 0;
	char *qry;
	char ch;
	char qry2[150];
	qry = "select start_date, end_date from assigned_room where room_num = ";

	sprintf(qry2, "%s %s", qry, room_num);

	if (mysql_real_query(&mysql, qry2, strlen(qry2))) {
		printf("send query err");
	}

	MYSQL_RES *res = mysql_store_result(&mysql);
	MYSQL_ROW row;

	cloum_length = mysql_num_fields(res);
	row_length = mysql_num_rows(res);
	
	system("cls");
	printf("***  ���� ���� ��¥   ***   ����  ����  ��¥   ***\n");
	while (row = mysql_fetch_row(res)) {
		printf("***   %5s           ***      %10s         ***\n", row[0], row[1]);
	}
	printf("���� �Ͻ÷��� 1, ���ư����� x �� �Է��Ͻÿ� :");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
		else if (ch == '1') {
			system("cls");
			hospital_res(room_num);    //�ش� �濡���� ������ �� �� �ְ� ���ִ� �Լ�
			break;
		}
	}
}
void nurse_view(char *nurse_ID) {
	int choice_num;   //ȯ�ڰ� �޴��� ������ �� �����ϴ� ����
	char *qry;
	char ch;
	char qry2[150];
	int row_length, cloum_length;
	char *ID;
	qry = "select N_name from nulse where nulse_ID = ";
	
	sprintf(qry2, "%s %s", qry, nurse_ID);    //��ȣ�� ���̵� ���Ͽ� ��ȣ�� �̸��� �������� ����

	if (mysql_real_query(&mysql, qry2, strlen(qry2))) {
		printf("send query err");
	}

	MYSQL_RES *res = mysql_store_result(&mysql);
	MYSQL_ROW row;

	cloum_length = mysql_num_fields(res);
	row_length = mysql_num_rows(res);

	while (row = mysql_fetch_row(res)) {
		ID = row[0];
	}
	while (1) {
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\t\t\t************ %s ************\n", ID);   //��ȣ�� id ��ȣ���̸� �޾ƿͼ� ����
		printf("\t\t\t1. ȯ�� �˻��� �Է�\n");
		printf("\t\t\t2. ȯ�� �Կ���� �Է� \n");
		printf("\t\t\t3. ���� \n");
		printf("\t\t\t���ϴ� �޴��� �����ϼ��� : ");
		scanf("%d", &choice_num);

		switch (choice_num) {
		case 1:
			insert_bill();      //ȯ���� ���� ��� �Է��ϴ� �Լ�.
			break;
		case 2:
			insert_Hbill();     //ȯ���� �Կ� ����� �Է��ϴ� �Լ�.
		case 3:
			exit(1);
		}
	}
}
void insert_bill() {
//	int row_length, cloum_length;
	int i = 0;
	char *qry;
	char ch;
	char qry_[150];
	char *qry_PID;
	char *qry_bill;
	char qry_END[200];
	qry_PID = (char *)malloc(sizeof(char) * 20);
	qry_bill = (char *)malloc(sizeof(char) * 20);

	printf("ȯ�� ���̵� �Է��Ͻÿ� : ");
	scanf("%s", qry_PID);

	printf("�˻� ����� �Է��Ͻÿ� : ");
	scanf("%s", qry_bill);
	
	


	qry = "update medical_certification set inspection_bill = ";

	sprintf(qry_END, "%s %s where patient_ID = %s",qry, qry_bill, qry_PID);
	if (mysql_real_query(&mysql, qry_END, strlen(qry_END))) {
		printf("send query err");
	}

	printf("���ư����� x �� �Է��Ͻÿ� :");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
	}
}
void insert_Hbill() {
	int row_length, cloum_length;
	int i = 0;
	char *qry;
	char ch;
	char qry_[150];
	char *qry_PID;
	char *qry_Hbill;
	char qry_END[200];
	qry_PID = (char *)malloc(sizeof(char) * 20);
	qry_Hbill = (char *)malloc(sizeof(char) * 20);

	printf("ȯ�� ���̵� �Է��Ͻÿ� : ");
	scanf("%s", qry_PID);

	printf("�Կ� ����� �Է��Ͻÿ� : ");
	scanf("%s", qry_Hbill);




	qry = "update medical_certification set hospitalization_bills = ";

	sprintf(qry_END, "%s %s where patient_ID = %s", qry, qry_Hbill, qry_PID);
	if (mysql_real_query(&mysql, qry_END, strlen(qry_END))) {
		printf("send query err");
	}

	printf("���ư����� x �� �Է��Ͻÿ� :");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
	}
}
char *compare_exist(char *ID) {
	
	int row_length;
	int i = 0;
	
	char *qry = (char *)malloc(sizeof(char) * 100);

	if (ID[0] == '1') {
		qry = "select patient_ID from patient";
	}
	else if (ID[0] == '2') {
		qry = "select doctor_ID from doctor";
	}
	else if (ID[0] == '3') {
		qry = "select nulse_ID from nulse";
	}
	
	if (mysql_real_query(&mysql, qry, strlen(qry))) {
		printf("send query err");
	}
	
	MYSQL_RES *res = mysql_store_result(&mysql);
	MYSQL_ROW row;

	row_length = mysql_num_fields(res);

	while (row = mysql_fetch_row(res)) {
		for (i = 0; i<row_length; i++) {
		//	printf("%s   ", row[i]);
			if (strcmp(ID, row[i]) == 0)     //���̵� �����ϴ��� ���ϴ� �κ�
				return row[i];
		}
	}
	mysql_free_result(res);

	printf("ID �� �ùٸ��� �ʽ��ϴ�.\n");
	return "0";
}   //�α��� �Ҷ� �����ͺ��̽� �ȿ� �ش� ���̵� �ִ��� ���ϴ� �Լ�.
