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

int add_mode()
{
	DUTCH ph[100];
	int no;
	char s_sw, d_sw, c_sw;

	for(int i=0; i<100; i++)
		ph[i].pay_id_number = -1;

	cout << "  * ȸ����� ����Դϴ�. *\n\n";

	while(1){
		cout << " �űԵ���Ͻðڽ��ϱ�(Y/N) ? ";
		cin >> c_sw;
		if(c_sw == 'N' || c_sw == 'n') break;

		while(1){
			cout << " ȸ����ȣ : ";
			cin >> no;
			if(no < 0 || no > 99)
				cout << " ȸ����ȣ�� 0���� 99�����Դϴ�. �ٽ� �Է����ּ���.\n";
			else if( ph[no].pay_id_number > -1){
				cout << " ȸ����ȣ �ߺ��Դϴ�. ����Ͻø� ����ϴ� ����Ͻðڽ��ϱ�? (Y/N) : ";
				cin >> d_sw;
				if(d_sw == 'Y' || d_sw == 'y')break;
			}
			else
				break;
		}
		cout << " ��    �� : ";
		cin >> ph[no].name;
		cout << " �� �� ó : ";
		cin >> ph[no].m_phone;

		cout << " �����Ͻðڽ��ϱ�(Y/N) ? ";
		cin >> s_sw;
		if(s_sw == 'Y'||s_sw == 'y')
		{
			ph[no].pay_id_number = no;
			cout << "���忡�����߽��ϴ�."<<endl;
		}
		//		else
		//		{
		//			cout << "�ùٸ������� �ƴմϴ�."<<endl;
		//		}
	}
	ofstream fout;
	fout.open("DUTCHPay_member.txt", ios::ios_base::app);
	if(!fout)
	{
		cout <<"* ���� ���¿� �����Ͽ����ϴ�."<<endl;
	}
	else
	{
		for(int i=0; i<100; i++){
			if(ph[i].pay_id_number < 0) continue;
			fout << ph[i].pay_id_number << ' ';
			fout << ph[i].name <<' ';
			fout << ph[i].m_phone <<' '<<endl;
		}
	}
	fout.close();

	return 0;
}

int search_mode()
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

	cout << "  * ȸ����ȣ�˻� *\n\n";

	cout << " ȸ����ȣ �Ǵ� �̸��� �Է��ϼ��� : ";
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
				cout << "  ->  ���� ȸ����ȣ, �̸��Դϴ�.\n";
				goto contine_A;
			}
			cout << " ==================================== " << endl;
			cout << "\n ȸ����ȣ : " << ph[no].pay_id_number << endl;
			cout << " ��    �� : " << ph[no].name << endl;
			cout << " �� �� �� : " << ph[no].m_phone << endl<< endl;
			cout << " ==================================== " << endl;

			contine_A:
			cout << "\n �˻��� ���Ͻø� ȸ����ȣ �Ǵ� �̸��� �Է��ϼ��� ���(-1) : ";
			cin >> ch_in;
			
			if( atoi(ch_in) == -1 )
			{
				system("cls");
				break;
			}
	}

	return 0;
}

int change_mode()
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

	cout << "  * ȸ����ȣ�˻�(����) *\n\n";

	while(c_sw == 1){
		cout << " �����ȣ �Ǵ� �̸��� �Է��ϼ��� : ";
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
				cout << "  ->  ���� ��ȣ, �̸��Դϴ�.\n";
				continue;
			}

			cout << "\n �����ȣ : " << ph[no].pay_id_number << endl;
			cout << " ��  �� : " << ph[no].name << endl;
			cout << " �޴��� : " << ph[no].m_phone << endl;
			cout << "\n ��Ӱ˻�1,  ��������2,  �����߰�3,  ������0  : ";
			cin >> c_sw;
			if(c_sw != 2 && c_sw != 3) continue;
			if(c_sw == 3)
				while(1){
					cout << " �����ȣ: ";
					cin >> no;
					if(no < 0 || no > 99)
						cout << " ��ȣ�� 0���� 99����, �ٽ� �Է����ּ���.\n";
					else if( u_no[no] == true){
						cout << " �����ȣ �ߺ��Դϴ�. ����Ͻðڽ��ϱ�(Y/N) ? ";
						cin >> d_sw;
						if(d_sw == 'Y' || d_sw == 'y')break;
					}
					else
						break;
				}

				cout << " ��  �� : ";
				cin >> ph[no].name;
				cout << " �޴��� : ";
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

	return 0;
}

int main ()
{
	int mode_sel=0;
	
		cout << "" <<endl;
	while(mode_sel>=0)
	{
		cout << "0. ����" <<endl;
		cout << "1. �߰�" <<endl;
		cout << "2. �˻�" <<endl;
		cout << "3. ����" <<endl;
		cout << "4. ��ġ����" <<endl;

		if( cin>>mode_sel<=0 ) break;
		
		switch (mode_sel)
		{
		case 0:
			system("cls");
			cout << " ���������� ���α׷��� �����մϴ�." <<endl;
			exit(1);
			break;

		case 1:
			system("cls");
			cout << "add mode �Դϴ�." <<endl;
			add_mode();
			break;

		case 2:
			system("cls");
			cout << "search mode �Դϴ�." <<endl;
			search_mode();
			break;

		case 3:
			system("cls");
			cout << "change mode �Դϴ�." <<endl;
			change_mode();
			break;

		case 4:
			system("cls");
			cout << "DUTCH_pay_mode �Դϴ�." <<endl;
			//DUTCH_pay_mode();
			break;

		default: system("cls"); cout << "�߸��� �����Դϴ�." <<endl;
			break;
		}
	}
	system("cls");
	cout << "\n���α׷��� �� ���������� ����˴ϴ�." << endl; 
	cout << "\nError Log�� �����Ͽ� ������ �����ϰڽ��ϴ�." << endl; 
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
	
	int pay_1=0;	//������
	int pay_2=0;	//����ݾ�
	int pay_3=0;	//�ɹ�
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

	cout << "  * ��ġ���̸�� �Դϴ�. *\n\n";

	cout << " �������� ȸ����ȣ�� �Է��ϼ��� : " ;
	cin >> pay_1;
	cout << " ����ݾ��� �Է��ϼ��� : ";
	cin >> pay_2;
	while(pay_3>0)
	{
		cout << " ���̸�� ȸ����ȣ�� �Է��ϼ��� : ";
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