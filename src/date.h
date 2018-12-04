/*** Developed by Polina Shlepakova ***/

#ifndef _DATE_H_
#define _DATE_H_

#include <iostream>
#include <string>

constexpr int nFormats = 12;
constexpr int formatLen = 10;
constexpr char formatStrings[nFormats][formatLen + 1] =
        {"DD MM YYYY", "DD.MM.YYYY", "DD-MM-YYYY", "DD/MM/YYYY",
         "YYYY MM DD", "YYYY.MM.DD", "YYYY-MM-DD", "YYYY/MM/DD",
         "MM DD YYYY", "MM.DD.YYYY", "MM-DD-YYYY", "MM/DD/YYYY"};

class Date {
public:
	enum Month {jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};
	
	// Formats of dates
	// First part of the name specifies the order of components, 
	// the second one - the separators between components.
	// For example, 03 Dec 2018 in format ymd_slash would be 2018/12/03
	enum Format {dmy_space, dmy_period, dmy_hyphen, dmy_slash,
				 ymd_space, ymd_period, ymd_hyphen, ymd_slash,
				 mdy_space, mdy_period, mdy_hyphen, mdy_slash};
	
	Date(int day = 1, Month month = jan, int year = 0);
	Date(int day, int month, int year);
	Date(const Date& date);
	~Date();

	int day() const;
	Month month() const;
	int year() const;

	void setDay(int day);
	void setMonth(int month);
	void setYear(int year);

	// returns number of days passed from 00/00/0000
	operator int() const;

	static void setFormat(std::ios_base& s, Format f);
	static Format getFormat(std::ios_base& s);

private:
	int _day, _month, _year;

	bool leapYear(int y) const;
	bool validate(int d, Month m, int y);
	int numberOfDays(int month = 0) const;

	static long& flag(std::ios_base& s);
};

// returns the difference in days
int operator-(const Date& d1, const Date& d2);

bool operator<(const Date& d1, const Date& d2);
bool operator>(const Date& d1, const Date& d2);
bool operator<=(const Date& d1, const Date& d2);
bool operator>=(const Date& d1, const Date& d2);

bool operator==(const Date& d1, const Date& d2);
bool operator!=(const Date& d1, const Date& d2);

std::ostream& operator<<(std::ostream& os, const Date& d);
std::istream& operator>>(std::istream& is, Date& d);

// manipulators
std::ostream& dmy_space(std::ostream& os);
std::ostream& dmy_period(std::ostream& os);
std::ostream& dmy_hyphen(std::ostream& os);
std::ostream& dmy_slash(std::ostream& os);
std::ostream& ymd_space(std::ostream& os);
std::ostream& ymd_period(std::ostream& os);
std::ostream& ymd_hyphen(std::ostream& os);
std::ostream& ymd_slash(std::ostream& os);
std::ostream& mdy_space(std::ostream& os);
std::ostream& mdy_period(std::ostream& os);
std::ostream& mdy_hyphen(std::ostream& os);
std::ostream& mdy_slash(std::ostream& os);

#endif // _DATE_H_
