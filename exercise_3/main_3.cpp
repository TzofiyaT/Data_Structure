#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <functional>
#include "BTR.h"
#include "Treatment.h"

using namespace std;

//=============================================================
void main()
{

	char ch;
	BTree<Treatment> bt;
	vector<string> physicians;
	Treatment tr, tr2;
	string str, str2;
	vector<Treatment> keys;
	Treatment *p;

	cout << "\nChoose one of the following" << endl;
	cout << "1: add a new Physician" << endl;
	cout << "2: add an open date and time for a physician" << endl;
	cout << "3: add a new Appointment " << endl;
	cout << "4: print patient calendar " << endl;
	cout << "5: print physician calendar " << endl;
	cout << "6: print date reminders" << endl;
	cout << "7: exit:" << endl;
	do
	{
		cin >> ch;

		switch (ch)
		{
		case '1':
			cout << "Enter physician name ";
			cin >> str;
			physicians.push_back(str);
			break;
		case '2':cin >> tr;
			if (std::find(physicians.begin(), physicians.end(), tr.get_physician()) == physicians.end())
				cout << "ERROR" << endl;
			else
				bt.insert(tr);
			break;
		case '3':
			cin >> tr; //fix a new treatment. read treatment details.
			p = bt.search(tr);
			if (p == NULL)
				cout << "ERROR" << endl;
			else
			{
				cout << "Enter patient name ";
				cin >> str;

				if (p->get_patient() != "")
					cout << "USED" << endl;
				else
				{
					p->set_patient(str);
					cout << "treatement for " << str << " fixed at " << p->get_date() << " time " << p->get_time() << endl;
				}
			}
			break;
		case '4':cout << "Enter patient name ";
			cin >> str;
			bt.printAllKeys([str](Treatment a) {return (a.get_patient() == str); });
			break;
		case '5':cout << "Enter physician name ";
			cin >> str;
			bt.printAllKeys([str](Treatment a) {return (a.get_physician() == str && a.get_patient() != ""); });
			break;
		case '6':cout << "Enter date ";
			cin >> str;
			bt.printAllKeys([str](Treatment a) {return (a.get_date() == str && a.get_patient() != ""); });
			break;
		case '7':cout << "bye "; break;
		default: cout << "error ";  break;
		}//switch
	} while (ch != '7');

}

/*output  
Choose one of the following
1: add a new Physician
2: add an open date and time for a physician
3: add a new Appointment
4: print patient calendar
5: print physician calendar
6: print date reminders
7: exit:
1
Enter physician name dr-cohen
2
Enter physician year-month-day hour dr-cohen 2018-11-11 10
3
Enter physician year-month-day hour dr-cohen 2018-11-11 10
Enter patient name danni
treatement for danni fixed at 2018-11-11 time 10
2
Enter physician year-month-day hour dr-cohen 2018-11-11 11
3
Enter physician year-month-day hour dr-cohen 2018-11-11 11
Enter patient name yossi
treatement for yossi fixed at 2018-11-11 time 11
4
Enter patient name yossi
Treatement details: physician: dr-cohen patient: yossi date: 2018-11-11,11
5
Enter physician name dr-cohen
Treatement details: physician: dr-cohen patient: danni date: 2018-11-11,10
Treatement details: physician: dr-cohen patient: yossi date: 2018-11-11,11
6
Enter date 2018-11-11
Treatement details: physician: dr-cohen patient: danni date: 2018-11-11,10
Treatement details: physician: dr-cohen patient: yossi date: 2018-11-11,11
7
bye Press any key to continue . . .

*/
