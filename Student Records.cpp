#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

class Date {
private:
	int	D;
	int	M;
	int Y;
public:
	Date() {
		D = 1;
		M = 1;
		Y = 2018;
	};
	void	Read() {
		cout << "\n year:\t" << endl;
		cin >> Y;
		do {
			cout << "\n month:\t" << endl;
			cin >> M;
		} while (M > 12 || M < 1);
		do {
			cout << "\n day:\t" << endl;
			cin >> D;
		} while (D > 31 || D < 1);
	}
	void Print() {
		cout << D << "/" << M << "/" << Y << "\t" << endl;
	}
};

class Student {
private:
	char FName[50];
	char LName[50];
	Date	Dob;
	char	gender;
	char	Tel[8];
	float	overall;
	int	CT;
	Date	ES;

public:
	int ID;
	Student() {
		ID = -1;
		FName[0] = ' ';
		LName[0] = ' ';
		gender = 'o';
		*Tel = '\0';
		overall = 50;
		CT = 0;
	}
	void	New() {
		cout << "ID:" << endl;
		cin >> ID;
		cout << "\n First Name:\t" << endl;
		cin >> FName;
		cout << "\n Last Name:\t" << endl;
		cin >> LName;
		cout << "\n Date of Birth:" << endl;
		Dob.Read();
		cout << "\n gender \t" << endl;
		cin >> gender;
		cout << "\n Telephone Number:\t" << endl;
		cin >> Tel;
		cout << "\n overall:\t" << endl;
		cin >> overall;
		cout << "\n Number of Credits taken:\t" << endl;
		cin >> CT;
		cout << "\n Today's date:\n" << endl;
		ES.Read();
		
	}
	void Modify() {
		char i;
		cout << "Y or N" << endl;
		cout << "\n Modify ID ?\t" << endl;
		cin >> i;
		if (i == 'y')
			cin >> ID;
		cout << "\n Modify Name ?\t" << endl;
		cin >> i;
		if (i == 'y')
		{
			cout << "\n First Name:\t" << endl;
			cin >> FName;
			cout << "\n Last Name:\t" << endl;
			cin >> LName;
		}
		cout << "\n Modify Date of Birth ?\t" << endl;
		cin >> i;
		if (i == 'y')
			Dob.Read();
		cout << "\n Modify gender ?\t" << endl;
		cin >> i;
		if (i == 'y')
			cin >> gender;
		cout << "\n Modify overall ?\t" << endl;
		cin >> i;
		if (i == 'y')
			cin >> overall;
		cout << "\n Modify number of Credits taken ?\t" << endl;
		cin >> i;
		if (i == 'y')
			cin >> CT;
		cout << "\n Modify Date of enrolment ?\t" << endl;
		cin >> i;
		if (i == 'y')
			ES.Read();
	}
	void Write() {
		cout << "ID: \t"<< ID << endl;
		cout << "\n Name: \t" << FName << ' ' << LName <<"\n"<< endl;
		Dob.Print();
		cout << "\n gender: \t" << gender << endl;
		cout << "\n Overall: \t" << overall << endl;
		cout <<"\n Credits Taken: \t" << CT << "\n" << endl;
		ES.Print();
		cout << "\n" << endl;
	}

};

void Add(Student S) {
	ofstream f("StudentsRecords.txt", ios::out | ios::app);
	f.write((char*)&S, sizeof(Student));
	f.close();
};

void List() {
	Student S;
	ifstream f;
	f.open("StudentsRecords.txt");
	while (!f.eof()) {
		f.read((char*)&S, sizeof(Student));
		if (!f.eof())
		S.Write();
	}
	f.close();
};

Student Find(int id) {
	Student S;
	ifstream f;
	f.open("StudentsRecords.txt");
	while (!f.eof()) {
		f.read((char*)&S, sizeof(Student));
		if (S.ID == id)
			break;
	}
	f.close();
	if (S.ID == -1)
		cout << "Student " << id << " not found" << endl;
	else {
		S.Write();
	}
	return S;
}

void Renew(ifstream f1, ofstream *f) {
	Student S;
	while (f1.eof()) {
		f1.read((char*)&S, sizeof(Student));
		(*f).write((char*)&S, sizeof(Student));

	};
}

void Delet(int id) {
	Student S;
	ifstream f;
	ofstream f1;
	f.open("StudentsRecords.txt");
	f1.open("temp.txt");
	while (!f.eof()) {
		f.read((char*)&S, sizeof(Student));
		if (S.ID != id)
			f1.write((char*)&S, sizeof(Student));
	}
	f.close();
	f1.close();
	f1.open("StudentsRecords.txt");
	f.open("temp.txt");
	while (f1.eof()) {
		f.read((char*)&S, sizeof(Student));
		f1.write((char*)&S, sizeof(Student));

	};

}

void Modify(int id) {
	Student S;
	S = Find(id);
	if (S.ID == id) {
		Delet(id);
		S.Modify();
		Add(S);
	}
}

int main() {
	int i = 0;

	while (i != -1) {
		cout << "\n Options :\n" << endl;
		cout << "Add a New Student : \t 1 \n" << endl;
		cout << "Find a Student : \t 2 \n" << endl;
		cout << "Check the list of all Students : \t 3 \n" << endl;
		cout << "Modify a Student : \t 4 \n" << endl;
		cout << "Delet a Student : \t 5 \n" << endl;
		cout << "Exit : \t 6 \n \n" << endl;
		cin >> i;
		switch (i) {
		case 1: {
			Student S;
			S.New();
			Add(S);
			break;
		}
		case 2: {
			int id;
			cout << "id of the Student :\t" << endl;
			cin >> id;
			Find(id);
			break;
		}
		case 3: {
			List();
			break;
		}
		case 4: {
			int id;
			cout << "id of the Student :\t" << endl;
			cin >> id;
			Modify(id);
			break;
		}
		case 5: {
			int id;
			cout << "id of the Student :\t" << endl;
			cin >> id;
			Delet(id);
			break;
		}
		case 6: {
			i = -1;
			break;
		}		
		default:
			break;

		}
	}

}