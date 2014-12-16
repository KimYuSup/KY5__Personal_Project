#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct DUTCH{
	int pay_id_number;
	string name;
	string m_phone;
	int pay_member[100];
	int pay_money[100];
};

int add_mode()	// 새로운 회원의 정보를 입력받아 추가로 저장 할 수 있는 함수. 
{
	DUTCH ph[100];
	int no;
	bool u_no[100] = {false};
	char s_sw, d_sw, c_sw;

	ifstream fin;
	fin.open("DUTCHPay_member.txt");
	fin >> no;
	while(fin){
		u_no[no] = true;
		ph[no].pay_id_number = no;
		fin >> ph[no].name;
		fin >> ph[no].m_phone;
		fin >> no;
	}
	fin.close();

	//for(int i=0; i<100; i++)
	//	ph[i].pay_id_number = -1;

	cout << "  * 회원등록 모드입니다. *\n\n";

	while(1){
		cout << " 신규등록하시겠습니까(Y/N) ? ";
		cin >> c_sw;
		if(c_sw == 'N' || c_sw == 'n')  break;
		while(1){
			cout << " 회원번호 : ";
			cin >> no;
			if(no < 0 || no > 99)
				cout << " 회원번호는 0부터 99까지입니다. 다시 입력해주세요.\n";
			else if( ph[no].pay_id_number > -1){
				cout << " 회원번호 중복입니다. 계속하시면 덮어씁니다 계속하시겠습니까? (Y/N) : ";
				cin >> d_sw;
				if(d_sw == 'Y' || d_sw == 'y')break;
			}
			else
				break;
		}
		cout << " 이    름 : ";
		cin >> ph[no].name;
		cout << " 연 락 처 : ";
		cin >> ph[no].m_phone;

		cout << " 저장하시겠습니까(Y/N) ? ";
		cin >> s_sw;
		if(s_sw == 'Y'||s_sw == 'y')
		{
			ph[no].pay_id_number = no;

			////////////////////////////////////////////////////// 추가 설정한 부분에 대해 저장.
			ofstream fout;
			fout.open("DUTCHPay_member.txt", ios::ios_base::app);
			if(!fout)
			{
				cout <<"* 파일 오픈에 실패하였습니다."<<endl;
			}
			else
			{
				//for(int i=0; i<100; i++){
				int i = no;
					if(ph[i].pay_id_number < 0) continue;
					fout << ph[i].pay_id_number << ' ';
					fout << ph[i].name <<' ';
					fout << ph[i].m_phone <<' '<<endl;
				//}
			}
			fout.close();
			cout << "저장에성공했습니다."<<endl;
			system("pause");
			//////////////////////////////////////////////////////
		}
		//else { cout << "올바른선택이 아닙니다."<<endl; }
	}
	// 최종저장이 아니라. 저장할지의 여부를 따라 위에서 저장하게 만듬
	system("cls");
	return 0;
}

int search_mode()	//회원 정보를 검색할 수 있는 함수
{
	DUTCH ph[100];
	bool u_no[100] = {false};
	int no;
	char ch_in[11];

	ifstream fin;
	fin.open("DUTCHPay_member.txt");
	fin >> no;
	while(fin){
		u_no[no] = true;
		ph[no].pay_id_number = no;
		fin >> ph[no].name;
		fin >> ph[no].m_phone;
		fin >> no;
	}
	fin.close();

	cout << "  * 회원번호검색 *\n\n";

	cout << " 회원번호 또는 이름을 입력하세요 : ";
	cin >> ch_in;
	while(1){
		no = 999;
		if(ch_in[0] >= '0' && ch_in[0] <= '9')
			no = atoi(ch_in);
		else
			for(int i=0; i<99; i++){
				if(u_no[i] == false) continue;
				if(ch_in != ph[i].name) continue;
				no = i;
				break;
			}
			if(u_no[no] == false || no < 0 || no > 99){
				cout << "  ->  없는 회원번호, 이름입니다.\n";
				goto contine_A;
			}
			cout << " ==================================== " << endl;
			cout << "\n 회원번호 : " << ph[no].pay_id_number << endl;
			cout << " 이    름 : " << ph[no].name << endl;
			cout << " 휴 대 폰 : " << ph[no].m_phone << endl<< endl;
			cout << " ==================================== " << endl;

contine_A:
			cout << "\n 검색을 원하시면 회원번호 또는 이름을 입력하세요 취소(-1) : ";
			cin >> ch_in;

			if( atoi(ch_in) == -1 )
			{
				system("cls");
				break;
			}
	}
	system("cls");
	return 0;
}

int change_mode()	//회원정보를 검색하여 기존의 정보를 수정하는 함수, 새로운 추가도 가능.
{
	DUTCH ph[100];
	bool u_no[100] = {false};
	int no, c_sw = 1;
	char d_sw, ch_in[11];

	ifstream fin;
	fin.open("DUTCHPay_member.txt");
	fin >> no;
	while(fin){
		u_no[no] = true;
		ph[no].pay_id_number = no;
		fin >> ph[no].name;
		fin >> ph[no].m_phone;
		fin >> no;
	}
	fin.close();

	cout << "  * 회원번호검색(수정) *\n\n";

	while(c_sw == 1){
		cout << " 단축번호 또는 이름을 입력하세요 : ";
		cin >> ch_in;
		no = 999;
		if(ch_in[0] >= '0' && ch_in[0] <= '9')
			no = atoi(ch_in);
		else
			for(int i=0; i<99; i++){
				if(u_no[i] == false) continue;
				if(ch_in != ph[i].name) continue;
				no = i;
				break;
			}
			if(u_no[no] == false || no < 0 || no > 99){
				cout << "  ->  없는 번호, 이름입니다.\n";
				continue;
			}

			cout << "\n 단축번호 : " << ph[no].pay_id_number << endl;
			cout << " 이  름 : " << ph[no].name << endl;
			cout << " 휴대폰 : " << ph[no].m_phone << endl;
			cout << "\n 계속검색1,  정보수정2,  새로추가3,  끝내기0  : ";
			cin >> c_sw;
			if(c_sw != 2 && c_sw != 3) continue;
			if(c_sw == 3)
				while(1){
					cout << " 단축번호: ";
					cin >> no;
					if(no < 0 || no > 99)
						cout << " 번호는 0부터 99까지, 다시 입력해주세요.\n";
					else if( u_no[no] == true){
						cout << " 단축번호 중복입니다. 계속하시겠습니까(Y/N) ? ";
						cin >> d_sw;
						if(d_sw == 'Y' || d_sw == 'y')break;
					}
					else
						break;
				}

				cout << " 이  름 : ";
				cin >> ph[no].name;
				cout << " 휴대폰 : ";
				cin >> ph[no].m_phone;
				ph[no].pay_id_number = no;

				u_no[no] = true;
				c_sw = 1;
	}

	ofstream fout;
	fout.open("DUTCHPay_member.txt");
	for(int i=0; i<100; i++){
		if(u_no[i] == false) continue;
		ph[i].pay_id_number = i;
		fout << ph[i].pay_id_number << ' ';
		fout << ph[i].name <<' ';
		fout << ph[i].m_phone <<' ';
	}
	fout.close();
	system("cls");
	return 0;
}

int main ()	// 메인 메뉴가 되는 main
{
	int mode_sel=0;

	cout << "" <<endl;
	while(mode_sel>=0)
	{
		cout << "0. 종료" <<endl;
		cout << "1. 추가" <<endl;
		cout << "2. 검색" <<endl;
		cout << "3. 수정" <<endl;
		cout << "4. 더치페이" <<endl;

		if( cin>>mode_sel<=0 ) break;

		switch (mode_sel)
		{
		case 0:
			system("cls");
			cout << " 정상적으로 프로그램을 종료합니다." <<endl;
			exit(1);
			break;

		case 1:
			system("cls");
			cout << "add mode 입니다." <<endl;
			add_mode();
			break;

		case 2:
			system("cls");
			cout << "search mode 입니다." <<endl;
			search_mode();
			break;

		case 3:
			system("cls");
			cout << "change mode 입니다." <<endl;
			change_mode();
			break;

		case 4:
			system("cls");
			cout << "DUTCH_pay_mode 입니다." <<endl;
			//DUTCH_pay_mode();
			break;

		default: system("cls"); cout << "잘못된 선택입니다." <<endl;
			break;
		}
	}
	system("cls");
	cout << "\n프로그램이 비 정상적으로 종료됩니다." << endl; 
	cout << "\nError Log를 추출하여 서버에 전송하겠습니다." << endl; 
	//
	// Error log save to send Code...(Add)
	//
	system("pause");
	return 0;
}

/*
int main()
{

add_mode();
DUTCH ph[100];
bool u_no[100] = {false};
int no, c_sw = 1;
char ch_in[11];
int count=0;
int pay=0;

int pay_1=0;	//결재자
int pay_2=0;	//갤재금액
int pay_3=0;	//맴버
int m_cout=0;


ifstream fin;
fin.open("DUTCHPay_member.txt");
fin >> no;
while(fin){
u_no[no] = true;
ph[no].pay_id_number = no;
fin >> ph[no].name;
fin >> ph[no].m_phone;
//fin >> ph[no].pay_member[no];
//fin >> ph[no].pay_money[no];
fin >> no;
}
fin.close();


ifstream fin_pay;
fin_pay.open("DUTCHPay_pay.txt");
fin_pay >> no;
while(fin){
u_no[no] = true;
ph[no].pay_id_number = no;
fin_pay >> ph[no].pay_member[no];
fin_pay >> ph[no].pay_money[no];
fin_pay >> no;
}
fin_pay.close();

cout << "  * 더치페이모드 입니다. *\n\n";

cout << " 결재자의 회원번호를 입력하세요 : " ;
cin >> pay_1;
cout << " 결재금액을 입력하세요 : ";
cin >> pay_2;
while(pay_3>0)
{
cout << " 페이멤버 회원번호를 입력하세요 : ";
cin >> pay_3;
m_cout ++;
}

ofstream fout;
fout.open("DUTCHPay_member.txt", ios::ios_base::app);
for(int i=0; i<100; i++){
if(u_no[i] == false) continue;
ph[i].pay_id_number = i;
// fout << setw(2) << ph[i].pay_id_number << ' ';
fout << ph[i].pay_id_number << ' ';
fout << ph[i].name <<' ';
fout << ph[i].m_phone <<' ';
for(int i=0; i<100; i++){
fout << ph[i].pay_member[i] <<' ';
fout << ph[i].pay_money[i] <<' ';
}
}
fout.close();

return 0;
}*/