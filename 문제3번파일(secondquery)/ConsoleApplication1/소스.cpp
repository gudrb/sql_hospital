#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

//#define _CRT_SECURE_NO_WARNINGS

void login(void);  //의사인지 간호사인지 환자인지 구분해서 번호를 반환한다.
void join(void);  //환자가 회원가입을 할 수 있게 만든 함수.
void patient_view(char *patient_ID);   //환자 뷰를 보여준다.
void doctor_view(char *doctor_ID);    //의사 뷰를 보여준다.
void insert_result();                
void Doctor_R_R(char *doctor_ID);     //예약된 환자 목록을 보여준다.
void Patient_R_R(char *doctor_ID);    //환자가 의사의 예약 시간을 본다.
void Room_R_R(char *room_num);        //환자가 방 입원 현황을 본다.
void nurse_view(char *nurse_ID);     //간호사 뷰를 보여준다.
void insert_bill();                  //검사비용 입력.
void insert_Hbill();                  //입원비용 입력.
char *compare_exist(char *ID);        //아이디가 존재하는지 비교하는 함수
void patient_view1(void); 
void patient_view2(char *patient_ID);// 환자의 뷰 두번째 함수 예약 시간 확인
void patient_view3(char *patient_ID);
void patient_view4(char *patient_ID);
void patient_view5(char *patient_ID);
void patient_view8(char *patient_ID);
void patient_view9(char *patient_ID);
void treat_res(char *doctor_ID);   //환자가 진료 예약하는 함수
void hospital_res(char *room_num);  //환자가 입원실을 예약하는 함수

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

			printf("****************연결 실패****************\n");
		}
		else {
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\t\t\t************cheil hospital ************\n");
			printf("\t\t\t1. 로그인\n");
			printf("\t\t\t2. 회원 가입\n");
			printf("\t\t\t3. 종료 \n");
			printf("\t\t\t원하는 메뉴를 선택하세요 : ");
			scanf("%d", &login_num);
	
			switch (login_num) {
			case 1:
				system("cls");
				login();
			case 2:
				join();
				break;
			case 3:
				printf("****************종    료****************\n");
				exit(1);
			}
		}
		printf("****************종    료****************\n");
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
	
	printf("ID 를 입력하시오(숫자1로 시작하는 10자리 수): ");
	scanf("%s", qry_ID);
	printf("이름을 입력하시오(영어 이름): ");
	scanf("%s", qry_name);
	printf("성별을 (여자: W, 남자: M): ");
	scanf("%s", qry_sex);
	printf("증상을 입력하시오(영어 증상): ");
	scanf("%s", qry_disease);
	printf("나이 를 입력하시오: ");
	scanf("%s", qry_age);
	
	
	qry = "insert patient values(";

	sprintf(qry_END, "%s%s, '%s', '%s', '%s', %s)", qry, qry_ID, qry_name, qry_sex, qry_disease, qry_age);
	printf("%s", qry_END);
	if (mysql_real_query(&mysql, qry_END, strlen(qry_END))) {
		printf("send query err");
	}

	printf("돌아가려면 x 를 입력하시오 :");
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

		printf("\t\t\t****************로그인 화면****************\n");
		printf("\t\t\tID 를 입력하시오 : ");
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
	int choice_num;   //환자가 메뉴를 선택할 때 저장하는 변수
	char *qry;
	char ch;
	char qry2[150];
	int row_length, cloum_length;
	char *ID;
	qry = "select P_name from patient where patient_ID = ";
	sprintf(qry2, "%s %s", qry, patient_ID);    //환자이름을 가져옴

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
		printf("\t\t\t************ %s ************\n", ID);   //~~님 환영합니다.라고 뜨게 환자이름 받아와야함
		printf("\t\t\t1. 의사 상담 가능 시간 확인 및 예약\n");
		printf("\t\t\t2. 입원 예약 가능 날 확인 및 예약\n");
		printf("\t\t\t3. 의사 상담 예약 조회\n");
		printf("\t\t\t4. 입원 예약 조회\n");
		printf("\t\t\t5. 검사 결과 확인 \n");
		printf("\t\t\t6. 진단 비용 확인 \n");
		printf("\t\t\t7. 입원 비용 확인 \n");
		printf("\t\t\t8. 종료 \n");
		printf("\t\t\t원하는 메뉴를 선택하세요 : ");
		scanf("%d", &choice_num);
		switch (choice_num) {
		case 1:
			system("cls");
			patient_view1();//의사 예약목록 뽑아내는 쿼리를 가진 함수
			break;
		case 2:
			system("cls");
			patient_view9(patient_ID);   //입원 예약 가능한 날을 볼 수 있다.예약도 가능
			break;
		case 3:
			system("cls");
			patient_view2(patient_ID);   //예약 시간 확인하는 함수
			break;
		case 4:
			system("cls");
			patient_view8(patient_ID);     //입원 예약 확인
			break;
		case 5:
			system("cls");
			patient_view3(patient_ID);//환자의 검사 결과 가져와서 출력하는 함수
			break;
		case 6:
			system("cls");
			patient_view4(patient_ID);//환자의 병원비를 가져와서 출력하는 함수
			break;
		case 7:
			system("cls");
			patient_view5(patient_ID);//환자의 입원 비용을 가져와서 출력하는 함수
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
	printf("***  의사 이름   ***   진료과   ***\n");
	while (row = mysql_fetch_row(res)) {
		printf("***  %d.   %5s           ***    %10s    ***\n",i, row[0], row[1]);
		doc_choice_ID[i] = row[2];
		i++;
	}
	while (1) {
		printf("의사를 선택하시오 (나가기 = 9): ");
		scanf("%d", &doc_choice);
		if (doc_choice == 9) {
			system("cls");
			break;
		}
			Patient_R_R(doc_choice_ID[doc_choice]);   //의사를 선택해서 예약내역을 확인할 수있다.
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
	printf("***  예약 시작 시간   ***   예약  종료  시간   ***   의사 이름   ***\n");
	while (row = mysql_fetch_row(res)) {
		printf("***   %5s           ***   %10s         ***   %10s    ***\n", row[0], row[1], row[2]);
	}
	printf("돌아가려면 x 를 입력하시오 :");
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
	printf("***  검사 결과   ***  치료 필요 여부  ***\n");
	while (row = mysql_fetch_row(res)) {
		printf("***   %5s      ***   %5s   ***\n", row[0], row[1]);
	}
	while (1) {
		printf("돌아가려면 9 를 입력하시오 : ");
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
	printf("***   병원비  ***\n");
	while (row = mysql_fetch_row(res)) {
		printf("***   %5s원    ***\n", row[0]);
	}
	printf("돌아가려면 x 를 입력하시오 :");
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
	printf("***   입원비  ***\n");
	while (row = mysql_fetch_row(res)) {
		printf("***   %5s원    ***\n", row[0]);
	}
	printf("돌아가려면 x 를 입력하시오 :");
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
	printf("***  예약 시작 날짜   ***   예약  종료  날짜   ***   방 번호   ***\n");
	while (row = mysql_fetch_row(res)) {
		printf("***   %5s           ***   %10s         ***   %10s    ***\n", row[0], row[1], row[2]);
	}
	printf("돌아가려면 x 를 입력하시오 :");
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
	printf("***  방 번호   ***   건물 번호   ***\n");
	while (row = mysql_fetch_row(res)) {
		printf("***  %d.   %5s           ***    %10s    ***\n", i, row[0], row[1]);
		room_choice_ID[i] = row[0];
		i++;
	}
	printf("방을 선택하시오 : ");
	scanf("%d", &doc_choice);
	room_num = room_choice_ID[doc_choice];
	Room_R_R(room_choice_ID[doc_choice]);    //해당 방의 예약현황을보여준다.

	printf("돌아가려면 x 를 입력하시오 :");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
	}
}
void doctor_view(char *doctor_ID) {
	int choice_num;   //의사가 메뉴를 선택할 때 저장하는 변수
	char *qry;
	char ch;
	char qry2[150];
	int row_length, cloum_length;
	char *ID;
	qry = "select D_name from doctor where doctor_ID = ";
	sprintf(qry2, "%s %s", qry, doctor_ID);    //의사 아이디를 비교하여 의사 이름을 가져오는 쿼리

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
		printf("\t\t\t************ %s ************\n", ID);   //의사 아이디 의사 이름 뽑아와서 출력하기
		printf("\t\t\t1. 환자 진단 결과 입력\n");
		printf("\t\t\t2. 환자 예약 내역 확인\n");
		printf("\t\t\t3. 종료 \n");
		printf("\t\t\t원하는 메뉴를 선택하세요 : ");
		scanf("%d", &choice_num);
		switch (choice_num) {
		case 1:
			system("cls");
			insert_result();    //환자의 진단 결과를 입력하는 함수
		case 2:
			system("cls");
			Doctor_R_R(doctor_ID);    //해당 의사의 환자 예약 내역을 출력하는 함수
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
	printf("치료 필요 여부를 입력하세요 :");
	scanf("%s", qry_result);
	qry_Hbill = "0";
	printf("환자 아이디를 입력하세요 : ");
	scanf("%s", qry_PID);
	


	
	qry = "insert into medical_certification values(";
	
	sprintf(qry_END, "%s%s, '%s', %s, %s)", qry, qry_bill, qry_result, qry_Hbill, qry_PID);

	if (mysql_real_query(&mysql, qry_END, strlen(qry_END))) {
		printf("send query err");
	}

	printf("돌아가려면 x 를 입력하시오 :");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
	}
}
void Doctor_R_R(char *doctor_ID) {  //자신에게 예약된 환자 출력
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
	printf("***  예약 시작 시간   ***   예약  종료  시간   ***   환자 아이디   ***\n");
	while (row = mysql_fetch_row(res)) {
		printf("***   %5s           ***   %10s         ***   %10s    ***\n", row[0], row[1], row[2]);
	}
	printf("돌아가려면 x 를 입력하시오 :");
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
	printf("***  예약 시작 시간   ***   예약  종료  시간   ***\n");
	while (row = mysql_fetch_row(res)) {
		printf("***   %5s           ***      %10s         ***\n", row[0], row[1]);
	}
	printf("예약하시려면 1, 돌아가려면 x 를 입력하시오 : ");
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


	printf("자신의 아이디를 입력하시오 : ");
	scanf("%s", qry_ID);
	//qry_D_ID = doctor_ID;
	printf("예약 시간을 입력하시오 :");
	scanf("%d", &qry_start_time);
	qry_end_time = qry_start_time + 1;


	qry = "insert treat values(";

	sprintf(qry_END, "%s%d, %d, '%s', '%s')", qry, qry_start_time, qry_end_time, qry_ID, doctor_ID);
	printf("%s", qry_END);
	if (mysql_real_query(&mysql, qry_END, strlen(qry_END))) {
		printf("send query err");
	}

	printf("돌아가려면 x 를 입력하시오 :");
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


	printf("자신의 아이디를 입력하시오 : ");
	scanf("%s", qry_ID);
	//qry_D_ID = doctor_ID;
	printf("예약 날짜를 입력하시오 :");
	scanf("%d", &qry_start_time);
	printf("마지막 입원 날짜를 입력하시오 :");
	scanf("%d", &qry_end_time);


	qry = "insert assigned_room values(";

	sprintf(qry_END, "%s%d, %d, '%s', '%s')", qry, qry_start_time, qry_end_time, qry_ID, room_num);
	printf("%s", qry_END);
	if (mysql_real_query(&mysql, qry_END, strlen(qry_END))) {
		printf("send query err");
	}

	printf("돌아가려면 x 를 입력하시오 :");
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
	printf("***  예약 시작 날짜   ***   예약  종료  날짜   ***\n");
	while (row = mysql_fetch_row(res)) {
		printf("***   %5s           ***      %10s         ***\n", row[0], row[1]);
	}
	printf("예약 하시려면 1, 돌아가려면 x 를 입력하시오 :");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
		else if (ch == '1') {
			system("cls");
			hospital_res(room_num);    //해당 방에대한 예약을 할 수 있게 해주는 함수
			break;
		}
	}
}
void nurse_view(char *nurse_ID) {
	int choice_num;   //환자가 메뉴를 선택할 때 저장하는 변수
	char *qry;
	char ch;
	char qry2[150];
	int row_length, cloum_length;
	char *ID;
	qry = "select N_name from nulse where nulse_ID = ";
	
	sprintf(qry2, "%s %s", qry, nurse_ID);    //간호사 아이디를 비교하여 간호사 이름을 가져오는 쿼리

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
		printf("\t\t\t************ %s ************\n", ID);   //간호사 id 간호사이름 받아와서 띄우기
		printf("\t\t\t1. 환자 검사비용 입력\n");
		printf("\t\t\t2. 환자 입원비용 입력 \n");
		printf("\t\t\t3. 종료 \n");
		printf("\t\t\t원하는 메뉴를 선택하세요 : ");
		scanf("%d", &choice_num);

		switch (choice_num) {
		case 1:
			insert_bill();      //환자의 진료 비용 입력하는 함수.
			break;
		case 2:
			insert_Hbill();     //환자의 입원 비용을 입력하는 함수.
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

	printf("환자 아이디를 입력하시오 : ");
	scanf("%s", qry_PID);

	printf("검사 비용을 입력하시오 : ");
	scanf("%s", qry_bill);
	
	


	qry = "update medical_certification set inspection_bill = ";

	sprintf(qry_END, "%s %s where patient_ID = %s",qry, qry_bill, qry_PID);
	if (mysql_real_query(&mysql, qry_END, strlen(qry_END))) {
		printf("send query err");
	}

	printf("돌아가려면 x 를 입력하시오 :");
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

	printf("환자 아이디를 입력하시오 : ");
	scanf("%s", qry_PID);

	printf("입원 비용을 입력하시오 : ");
	scanf("%s", qry_Hbill);




	qry = "update medical_certification set hospitalization_bills = ";

	sprintf(qry_END, "%s %s where patient_ID = %s", qry, qry_Hbill, qry_PID);
	if (mysql_real_query(&mysql, qry_END, strlen(qry_END))) {
		printf("send query err");
	}

	printf("돌아가려면 x 를 입력하시오 :");
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
			if (strcmp(ID, row[i]) == 0)     //아이디가 존재하는지 비교하는 부분
				return row[i];
		}
	}
	mysql_free_result(res);

	printf("ID 가 올바르지 않습니다.\n");
	return "0";
}   //로그인 할때 데이터베이스 안에 해당 아이디가 있는지 비교하는 함수.
