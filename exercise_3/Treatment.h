#pragma once
#include <iostream>
#include <string>
using namespace std;

class Treatment
{
private:
	string physician;
	string patient;
	string date;
	string time;
public:
	//constractor
	Treatment(string physi = "", string patie = "", string d = "0000-00-00", string t = "00")
	{
		physician = physi; 
		patient = patie;
		date = d;
		time = t;
	}

	//get and set
	void set_physician(string s) { physician = s; }
	void set_patient(string s) { patient = s; }
	void set_date(string s) { date = s; }
	void set_time(string s) { time = s; }
	string get_physician()const;
	string get_patient()const { return patient; }
	string get_date()const { return date; }
	string get_time()const { return time; }

	//operators
	bool operator==(Treatment other)const;
	bool operator<(Treatment other)const;
	bool operator>(Treatment other)const;
	bool operator<=(Treatment other)const;
	bool operator>=(Treatment other)const;

	//cout<< and cin>>
	friend istream& operator>>(istream& is, Treatment& t);
	friend ostream& operator<<(ostream& os, Treatment& t);
};

bool Treatment::operator==(Treatment other) const
{
	if (physician == other.get_physician() && date == other.get_date() && time == other.get_time())
		return true;
	return false;
}

bool Treatment::operator<(Treatment other)const
{
	if (date < other.get_date())
		return true;
	else if (date == other.get_date())
		if (time < other.get_time())
			return true;
		else if (time == other.get_time())
			if (physician < other.get_physician())  // same time
				return true;
	return false;
}

bool Treatment::operator>(Treatment other) const
{
	return !this->operator==(other) && !this->operator<(other);
}

bool Treatment::operator>=(Treatment other) const
{
	return this->operator==(other) || this->operator>(other);
}

bool Treatment::operator<=(Treatment other) const
{
	return this->operator==(other) || this->operator<(other);
}


istream& operator>>(istream& is, Treatment& t)
{
	cout << "Enter physician year-month-day hour ";
	is >> t.physician >> t.date >> t.time;
	t.patient = string("");
	return is;
}

ostream& operator<<(ostream& os, Treatment& t)
{
	os << "Treatement details: physician: " << t.physician << " patient: " << t.patient << " date: " << t.date << "," << t.time << endl;
	return os;
}

string Treatment::get_physician() const
{
	return physician;
}