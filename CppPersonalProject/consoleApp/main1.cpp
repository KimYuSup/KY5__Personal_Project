	
	////////////////////////////////////////★	
	//										//	
	//		FTP NAS서버 접속 더치페이		//	
	//										//	
	//		ftp://ARTOAnas.ipdisk.co.kr		//	
	//										//	2014.12.13 make...
	//					20111974 김유섭		//////////////////////#	
	//										//	
	//////////////////////////////////////////	
			//		
			//		ver1.0	++	payAdd_mode 기능 추가			- 회원추가
			//		ver1.1	++	Search_mode 기능 추가			- 회원검색
			//		ver1.2	++	Change_mode 기능 추가			- 회원수정
			//		ver1.3	++	DUTCH_pay_mode 기능 추가		- 페이기능
			//		ver1.4	++	DUTCH__CLS_mode 기능 추가		- 페이정산
			//		ver2.0	_&	각 함수별 알고리즘 정리			- 최적화 한참 많이 필요하다 생각듬. 
			//		ver3.0	_+	ftp 접속 프로토콜 도입			- 파일 암호화를 통하여 데이터 암호필요성 느낌.
			//		ver3.1	--	ftp 접속 프로토콜 수정			- 불 필요 부분 수정.
			//		
			//		ver4.0	$$	Win_API							- 진행중...#################
			//		ver9.0	$$	Android_APP						- 구상중...
			//		
			//////////////////////////////////////////////#	
	
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define __MEMBER_Su__ 100	// 최대 멤버수, 메크로 상수로 최종버전에 설정할것. 처리시 주석문 지울것.

struct DUTCH{
	int pay_id_number;	// 결제자 회원번호 인덱스
	string name;		// 결제자 이름
	string phone_num;	// 결제자 연락처			<<<< = 연락처 대신에 " 그룹 " 으로 해주는건 어떨지... 
};

struct DUTCH_DATA{
	//int pay_id_number;	// 결제자 회원번호 인덱스 [DUTCH 구조체와 동일]
	//string name;		// 결제자 이름 [DUTCH 구조체와 동일]
	double pay_money[100]; // 더치페이 금액을 저장할 배열
	//string pay_money_data[100][1000000];		// 어디에서 무엇을 먹었는지 저장할 공간.... [맴버인덱스] [어디서무엇을먹었는지의데이터] 추후 넣을 기능.
};

	//////////////////////////////////////////
	//		FTP NAS서버 접속 클라이언트		//
	//		ftp://ARTOAnas.ipdisk.co.kr		//
	//////////////////////////////////////////
void artoa_nas()	// 비공개
{
	//nas ID
	//nas PW
	//nas 접속
	//nas > HDD1 > Personal__Project > KY5__pro > 2014 > cpp > dutch_pay
	//DUTCHPay_member.txt	copy it !
	//DUTCHPay_data.txt		copy it !
	//copy to > [ C:\ ]...
}
void artoa_nas_exit()
{
	//DUTCHPay_member.txt	copy it !
	//DUTCHPay_data.txt		copy it !
	//nas ID
	//nas PW
	//nas 접속
	//nas > HDD1 > Personal__Project > KY5__pro > 2014 > cpp > dutch_pay
	//DUTCHPay_member.txt	send it !
	//DUTCHPay_data.txt		send it !
}

//회원추가	 
int add_mode()	// 새로운 회원의 정보를 입력받아 추가로 저장 할 수 있는 함수. 
{
	//==========================================================================	ㄱ		회원정보를 가져오기위한 init부분,
	cout << "서버로부터 더치페이 기존회원의 정보를 가져오는 중 입니다..." <<endl;

	int no;
	bool u_no[100] = {false};

	DUTCH ph[100];
	ifstream fin;
	fin.open("DUTCHPay_member.txt");
	fin >> no;
	while(fin){
		u_no[no] = true;
		ph[no].pay_id_number = no;
		fin >> ph[no].name;
		fin >> ph[no].phone_num;
		fin >> no;
	}
	fin.close();

	DUTCH_DATA ph_data[100];
	ifstream fin_data;
	fin_data.open("DUTCHPay_data.txt");
	fin_data >> no;
	while(fin_data){
		u_no[no] = true;
		ph[no].pay_id_number = no;
		fin_data >> ph[no].name;
		for(int i=0; i!=100; i++)
			fin_data >> ph_data[no].pay_money[i];
		fin_data >> no;
	}
	fin_data.close();
	cout << "서버로부터 더치페이 기존회원의 정보를 받아왔습니다." <<endl<<endl;
	//===============================================================================================================	ㄱ 

	char s_sw, d_sw, c_sw;
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
		cin >> ph[no].phone_num;


		cout << " 저장하시겠습니까(Y/N) ? ";
		cin >> s_sw;
		if(s_sw == 'Y'||s_sw == 'y')
		{
			ph[no].pay_id_number = no;

			////////////////////////////////////////////////////// 추가로 입력한 정보를 저장.
			ofstream fout;
			fout.open("DUTCHPay_member.txt", ios::ios_base::app);
			if(!fout) cout <<"* 파일 오픈에 실패하였습니다."<<endl; 
			else
			{
				int i = no;
				if(ph[i].pay_id_number < 0) continue;
				fout << ph[i].pay_id_number << '	';
				fout << ph[i].name <<'	';
				fout << ph[i].phone_num <<'	'<<endl;
			}
			fout.close();


			ofstream fout_data;
			fout_data.open("DUTCHPay_data.txt", ios::ios_base::app);
			if(!fout_data) cout <<"* 파일 오픈에 실패하였습니다."<<endl; 
			else
			{
				int i = no;
				if(ph[i].pay_id_number < 0) continue;
				fout_data << ph[i].pay_id_number << '	';
				fout_data << ph[i].name <<'	';
				for(int ii=0; ii!=10; ii++)									//  <<  10명의 데이터라고했는데 그렇게가 아니라 100 명으로 설정할것.
					ph_data[i].pay_money[ii]=0;
				for(int ii=0; ii!=10; ii++)		
					fout_data << ph_data[i].pay_money[ii]<<'	';
				fout_data <<'	'<<endl;
			}
			fout_data.close();
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
//회원검색
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
		fin >> ph[no].phone_num;
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
			cout << " 휴 대 폰 : " << ph[no].phone_num << endl<< endl;
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
//회원수정
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
		fin >> ph[no].phone_num;
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
			cout << " 휴대폰 : " << ph[no].phone_num << endl;
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
				cin >> ph[no].phone_num;
				ph[no].pay_id_number = no;

				u_no[no] = true;
				c_sw = 1;
	}

	ofstream fout;
	fout.open("DUTCHPay_member.txt");
	for(int i=0; i<100; i++){
		if(u_no[i] == false) continue;
		ph[i].pay_id_number = i;
		fout << ph[i].pay_id_number << '	';
		fout << ph[i].name <<'	';
		fout << ph[i].phone_num <<'	';
	}
	fout.close();
	system("cls");
	return 0;
}
//더치페이 모드
int DUTCH_pay_mode()	// [   int DUTCH_pay_mode()   ]  더치페이 실질적인 기능 구현중...
{
	//==========================================================================	ㄱ		회원정보를 가져오기위한 init부분,
	cout << "서버로부터 더치페이 회원의 정보를 가져오는 중 입니다..." <<endl;

	DUTCH ph[100];
	int no;
	bool u_no[100] = {false};

	ifstream fin;
	fin.open("DUTCHPay_member.txt");
	fin >> no;
	while(fin){
		u_no[no] = true;
		ph[no].pay_id_number = no;
		fin >> ph[no].name;
		fin >> ph[no].phone_num;
		fin >> no;
	}
	fin.close();
	cout << "서버로부터 더치페이 회원의 정보를 받아왔습니다." <<endl<<endl;
	//===============================================================================================================	ㄱ 
	//==========================================================================	ㄴ		금액정보를 가져오기위한 init부분,
	cout << "서버로부터 더치페이 금액정보를 가져오는 중 입니다..." <<endl;

	DUTCH_DATA ph_data[100];
	ifstream fin_data;
	fin_data.open("DUTCHPay_data.txt");
	fin_data >> no;
	while(fin_data){
		u_no[no] = true;
		ph[no].pay_id_number = no;
		fin_data >> ph[no].name;		// 결제자가 누구인지 알아야 하는데 이 정보는 [ DUTCH ] 회원정보 클레스 에서 받아와야할지 생각해봐야됨.
		for(int i=0; i!=100; i++)
			fin_data >> ph_data[no].pay_money[i];	// 이부분에 [ __MEMBER_Su__ ]에 해당하는 배열을 가지고 있어야 회원 정보에 누가 누구한테 돈을 줄 지 알 수 있음.
		fin_data >> no;
	}
	fin.close();
	cout << "더치페이 금액정보를 받아왔습니다." <<endl<<endl;
	//===============================================================================================================	ㄴ

	int index_id;
	cout << "결제자의 회원번호를 입력하세요 : " ;
	cin >> index_id;

	double money_all;
	cout << "총 결제금액을 입력하세요 : " ;
	cin >> money_all;



	int member_count = 1;
	int member_id[ 10 ] = {0,};					//			<<<<  10의 데이터를 100명분의 데이터로 해줄것
	for (int i =0; i!=10; i++)
	{
		cout << "함께한 맴버의 회원번호를 입력하세요 (종료는 -1)   : " ;
		cin >> member_id[i];
		if(member_id[i] >= 0) member_count++;	//    <<<<     3항 연산자로 수정할것.		( member_id[i] > 0 ) ? ( member_count++구문 ) : ( break구문 ) ;
		else {member_id[i]=0; break;}
	}


	cout << endl;
	cout << endl;

	for (int i =0; i!=10; i++)
	{
		cout << (member_id[i]) <<endl;
	}
	cout << endl;
	cout << endl;

	double pay_moneydata  = ( (double)money_all / (double)member_count ) ;
	for(int i=0; i!=10; i++)									//			<<<<  10의 데이터를 100명분의 데이터로 해줄것
		ph_data[index_id].pay_money[member_id[i]] = pay_moneydata ;

	cout <<"\n\n 결제자는 : [" << index_id << "]번 ID [" <<  ph[index_id].name << "] 님 입니다." <<endl;
	cout <<" 총 결제금액은 ["<< money_all << "]원 이며" <<endl;
	cout <<" 총 맴버는 ["<< member_count << "]명 으로 " <<endl;
	cout <<" 더치페이의 가격은 각각 ["<< pay_moneydata <<"]원 이 나왔으며"<<endl;
	cout << "["<<ph[index_id].name << "]님 에게 ["<< pay_moneydata << "]원을 주시면 됩니다."<<endl;

	for(int i=0; i!=10; i++)									//			<<<<  10의 데이터를 100명분의 데이터로 해줄것
		cout << ph_data[index_id].pay_money[member_id[i]] <<endl; ;


	ph[no].pay_id_number = no;
	ofstream fout_data;
	fout_data.open("DUTCHPay_data.txt");	//덮어씌우기
	if(!fout_data) cout <<"* 파일 오픈에 실패하였습니다."<<endl; 
	else
	{
		fout_data << "회원num	성명";
		for(int i=0; i!=10; i++) fout_data << ph[i].name <<"	";
		fout_data << "	" <<endl;
		for(int i=1; i<100; i++){
			if(ph[i].pay_id_number < 0) continue;
			fout_data << ph[i].pay_id_number << '	';
			fout_data << ph[i].name <<'	';
			for(int ii=0; ii!=10; ii++)									//  <<  10명의 데이터라고했는데 그렇게가 아니라 100 명으로 설정할것.
				/**/			ph_data[i].pay_money[ii]=0;
			for(int i=0; i!=10; i++)									//			<<<<  10의 데이터를 100명분의 데이터로 해줄것
				ph_data[index_id].pay_money[member_id[i]] += pay_moneydata ;
			for(int ii=1; ii!=10; ii++)		
				fout_data << ph_data[i].pay_money[ii]<<'	';
			fout_data <<'	'<<endl;
		}
	}
	fout_data.close();
	cout << "저장에성공했습니다."<<endl;
	system("pause");
	return 0;
}
//페이정산 초기화 모드
int DUTCH__CLS_mode(){

	//==========================================================================	ㄱ		회원정보를 가져오기위한 init부분,
	cout << "서버로부터 더치페이 기존회원의 정보를 가져오는 중 입니다..." <<endl;

	int no;
	bool u_no[100] = {false};

	DUTCH ph[100];
	ifstream fin;
	fin.open("DUTCHPay_member.txt");
	fin >> no;
	while(fin){
		u_no[no] = true;
		ph[no].pay_id_number = no;
		fin >> ph[no].name;
		fin >> ph[no].phone_num;
		fin >> no;
	}
	fin.close();

	DUTCH_DATA ph_data[100];
	ifstream fin_data;
	fin_data.open("DUTCHPay_data.txt");
	fin_data >> no;
	while(fin_data){
		u_no[no] = true;
		ph[no].pay_id_number = no;
		fin_data >> ph[no].name;
		for(int i=0; i!=100; i++)
			fin_data >> ph_data[no].pay_money[i];
		fin_data >> no;
	}
	fin_data.close();
	cout << "서버로부터 더치페이 기존회원의 정보를 받아왔습니다." <<endl<<endl;
	//===============================================================================================================	ㄱ
	ph[no].pay_id_number = no;

	////////////////////////////////////////////////////// 추가로 입력한 정보를 저장.
	ofstream fout;
	fout.open("DUTCHPay_member.txt", ios::ios_base::app);
	if(!fout) cout <<"* 파일 오픈에 실패하였습니다."<<endl; 
	else
	{
		int i = no;
		if(ph[i].pay_id_number < 0) return 0;//continue;
		fout << ph[i].pay_id_number << '	';
		fout << ph[i].name <<'	';
		fout << ph[i].phone_num <<'	'<<endl;
	}
	fout.close();


	ofstream fout_data;
	fout_data.open("DUTCHPay_data.txt", ios::ios_base::app);
	if(!fout_data) cout <<"* 파일 오픈에 실패하였습니다."<<endl; 
	else
	{
		int i = no;
		if(ph[i].pay_id_number < 0) return 0;//continue;
		fout_data << ph[i].pay_id_number << '	';
		fout_data << ph[i].name <<'	';
		for(int ii=0; ii!=10; ii++)									//  <<  10명의 데이터라고했는데 그렇게가 아니라 100 명으로 설정할것.
			ph_data[i].pay_money[ii]=0;
		for(int ii=0; ii!=10; ii++)		
			fout_data << ph_data[i].pay_money[ii]<<'	';
		fout_data <<'	'<<endl;
	}
	fout_data.close();
	cout << "저장에성공했습니다."<<endl;
	system("pause");
	//////////////////////////////////////////////////////



	return 0;
}

//main메뉴
int main ()	// 메인 메뉴가 되는 main, //  최종적으로 실험시엔, main()으로 만들어줄것.
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
		cout << "5. 정산완료" <<endl;

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
			DUTCH_pay_mode();
			break;

		case 5:
			system("cls");
			cout << "DUTCH__CLS_mode 입니다.\n 정산완료를 원하시면 Y혹은 y를 두번 입력하세요. " <<endl;
			char yes;
			cin >> yes;
			if(yes == 'y' || yes == 'Y') cin >> yes;
			if(yes == 'y' || yes == 'Y') DUTCH__CLS_mode();
			system("cls");
			break;

		default: system("cls"); cout << " * 잘못된 선택입니다. *" <<endl;
			break;
		}
	}
	system("cls");
	cout << "\n프로그램이 비 정상적으로 종료됩니다." << endl; 
	cout << "\nError Log를 추출하여 서버에 전송하겠습니다." << endl; 
	//
	// Error log save to Send Server Code...(Add)
	//
	system("pause");
	return 0;
} 



