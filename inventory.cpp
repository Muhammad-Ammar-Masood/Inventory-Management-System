// -------------------------INVENTORY MANAGEMENT SYSTEM BY FG SIR SYED COLLEGE----------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ostream>
#include <conio.h>
#include <windows.h>
#include <map>

using namespace std;

// Global variable
string prodName = "";
char check;
int billID;
string month = "";
int stockW = 0;
string MONTHS[12] = {"Jan" , "Feb" , "March" , "April" , "May" , "June" , "July" , "Aug" , "Sept" , "Oct" , "Nov" , "Dec"};

struct Product
{
	string name;
	string suppliers;
	int price;
	float weight;
	int buyPrice;
};

struct customer
{
	string name;
	int billId;
	string products;
	string date;
	int loan;
	bool paid;
};

struct Sales
{
	string month;
	float sales = 0;
	float profit = 0;
};

namespace std
{
	template <>
	struct hash<Product>
	{
		size_t operator()(const Product &key)
		{
			return hash<std::string>()(key.name);
		}
	};
}
namespace std
{
	template <>
	struct hash<customer>
	{
		size_t operator()(const customer &key)
		{
			return hash<int>()(key.billId);
		}
	};
	template <>
	struct hash<Sales>
	{
		size_t operator()(const Sales &key)
		{
			return hash<string>()(key.month);
		}
	};
}
map<string, Sales> mSales;
map<int, customer> mcustomer;
map<std::string, Product> mProducts;
vector<string> productsId;
string username = "admin";
string password = "1234";

// my functions
void login();
void signUp();
void addProducts();
void searchProduct();
void writeFile();
void readFile();
void displayProducts();
void alert();
void billGenerate();
void line(char);
void supply();
void suppliers();
void stock();
void sales();
void menu();
void updateProducts();
void displaycustomers();
void customerWriteFile();
void customerReadFile();
void fileMonthlySales();
void monthlySales();
void analytics();
void getMonth();

int main()
{
	getMonth();
	monthlySales();
	readFile();
	customerReadFile();
	system("cls");
	system("color B0");

	int m = 1;
	char ch = 31;
	char ch1 = 30;
	for (int i = 1; i <= 5; i++)
	{
		for (int k = 1; k < i; k++)
		{
			cout << " ";
		}
		for (int j = m; j <= 80; j++)
		{
			cout << ch;
		}
		m = m + 2;
		cout << endl;
		 Sleep(100);
	}

	cout << "\n\t\t\t INVENTORY MANAGEMENT SYSTEM\n\n";

	 Sleep(100);

	m = m - 2;
	for (int i = 1; i <= 5; i++)
	{
		for (int k = 5; k > i; k--)
		{
			cout << " ";
		}
		for (int j = m; j <= 80; j++)
		{
			cout << ch1;
		}
		m = m - 2;
		cout << endl;
		 Sleep(100);
	}

	 Sleep(1500);

	system("cls");
	line(30);

	cout << "\t\t\t        INVENTORY MANAGEMENT SYSTEM \n";
	line(31);
	cout << endl;
	cout << endl;
	if (username == "" || password == "")
	{
		signUp();
	}
	login();
	getch();

	cout << "\t\t\t-----------------------------------------\n";
	cout << endl;
	line('-');
	cout << " Press Any Key to continue...\n";
	getche();
	system("cls");
	menu();

	return 0;
}

// -------------------------INVENTORY MANAGEMENT SYSTEM BY FG SIR SYED COLLEGE----------------------------

void signUp()
{
	cout << "Set username : ";
	cin >> username;
	cout << "Set password : ";
	cin >> password;
}
void login()
{
	string tmpU;
	string tmpP;
	char c;

	cout << "\t\t\t LOG IN :- \n";
	cout << "\t\t\t-----------------------------------------\n";
	cout << "\t\t\t\tEnter username : ";
	cin >> tmpU;

	cout << "\t\t\t\tEnter password : ";

	for (int i = 1; i <= 4; i++)
	{
		c = getch();
		tmpP += c;
		cout << "*";
	}

	cout << endl;

	// getch();

	if (username == tmpU && password == tmpP)
	{
		return;
	}
	else
	{
		system("cls");
		cout << "Invalid credentials ! \n";
		cout << "please try again \n";
		login();
	}
}
// Function MENU
void menu()
{
	char c = 16;
	system("cls");
	cout << endl;

	line('*');
	int menunum;
	cout << " \t\t\t\t\t    MENU                  \n";
	line('*');

	cout << "\n\t\t" << c << "[1]-Supply";
	cout << "\t\t" << c << "[2]-Stock";
	cout << "\t\t" << c << "[3]-Sales\n\n";
	cout << "\t\t" << c << "[4]-Customers";
	cout << "\t\t" << c << "[5]-Analytics";
	cout << "\t\t" << c << "[6]-Exit\n\n";
	line('_');
	cout << "Enter your choice here:\n";
	cin >> menunum;
	line('_');

	switch (menunum)
	{
	case 1:
		system("cls");
		supply();
		break;
	case 2:
		system("cls");
		stock();
		break;
	case 3:
		system("cls");
		sales();
		break;
	case 4:
		system("cls");
		displaycustomers();
		break;
	case 5:
		system("cls");
		analytics();
	case 6:
		system("cls");
		break;
	default:
		system("cls");
		cout << "Invalid entry";
		getch();
		menu();
	}
}

void addProducts()
{
	system("cls");
	string tmpN;
	string tmpSup;
	int tmpP;
	int tmpB;
	float tmpW;

	do
	{
		line('=');
		cout << "Enter product name : ";
		cin >> tmpN;
		for (int i = 0; tmpN[i] != '\0'; i++)
		{
			if (tmpN[i] >= 'A' && tmpN[i] <= 'Z')
			{
				tmpN[i] += 32;
			}
		}

		if (mProducts.find(tmpN) != mProducts.end())
		{
			line('_');
			cout << "already exist : ";
			getch();
			supply();
			break;
		}

		cout << "Enter supplier name : ";
		cin >> tmpSup;

		cout << "Enter product Quantity (kg/L/Pcs) : ";
		cin >> tmpW;

		cout << "Enter product selling price : ";
		cin >> tmpP;

		cout << "Enter product purchase price : ";
		cin >> tmpB;
		cout << endl;

		mProducts[tmpN] = Product{tmpN, tmpSup, tmpP, tmpW, tmpB};
		productsId.push_back(tmpN);
		line('-');
		cout << "Do you want to enter another product (y/n) : ";
		cin >> check;

	} while (check == 'y');
	writeFile();
	line('-');
	cout << "Product successfully added to the Stock !\n";
	cout << "Press any key to go back\n";
	line('-');
	getch();
	supply();
}
void writeFile()
{
	fstream myFile;
	myFile.open("stock.txt", ios::out); // write
	if (myFile.is_open())
	{
		for (auto i = productsId.begin(); i != productsId.cend(); ++i)
		{
			myFile << mProducts.at(*i).name << "," << mProducts.at(*i).suppliers << "," << mProducts.at(*i).price << "," << mProducts.at(*i).weight << "," << mProducts.at(*i).buyPrice << ",";
		}
	}
	myFile.close();
}

void displayProducts()
{
	system("cls");
	cout << endl;
	line('*');
	cout << "\t\t\t\t\tSTOCK                 \n";
	line('*');
	cout << "ProductID \t\t"
		 << "Products \t\t"
		 << "Quantity(kg/L/pcs)	\t "
		 << "Unit Price (Rs)" << endl;
	line('-');

	int k = 1;
	for (auto i = productsId.begin(); i != productsId.cend(); ++i)
	{

		cout << k << "\t\t\t" << mProducts.at(*i).name << "\t\t\t" << mProducts.at(*i).weight << "\t\t\t\t " << mProducts.at(*i).price << endl;

		k++;
	}
	line('-');

	alert();
	getche();
	menu();
}

// -------------------------INVENTORY MANAGEMENT SYSTEM BY FG SIR SYED COLLEGE----------------------------

void searchProduct()
{

	system("cls");
	cout << endl;
	line('*');
	cout << "\t\t\t\t\tSEARCH                 \n";
	line('*');
	string Tname;
	cout << endl;
	cout << "Enter item to find : ";
	cin >> Tname;
	if(mProducts.find(Tname) == mProducts.end())
	{
		cout << "Invalid entry !\n";
		cout << "Please try again ! \n";
		getch();
		searchProduct();
	}
	system("cls");

	cout << endl;
	line('=');
	cout << "\t\t\t\t\tSTOCK                 \n";
	line('=');
	cout << "ProductID\t\t"
		 << "Products"
		 << "\t"
		 << "Quanitity(Kg/ltr/pcs)"
		 << "\t\t"
		 << "\tUnit Price" << endl;
	line('-');
	cout << "1"
		 << "\t\t\t" << mProducts.at(Tname).name << "\t\t\t" << mProducts.at(Tname).weight << "\t\t\t\t\t " << mProducts.at(Tname).price << " Rs " << endl;
	getche();
	stock();
}

void readFile()
{
	fstream myFile;
	vector<string> tmp;
	myFile.open("stock.txt", ios::in);
	if (myFile.is_open())
	{
		string line;
		while (getline(myFile, line, ','))
		{
			tmp.push_back(line);
		}
	}
	myFile.close();

	for (int i = 0; i < tmp.size(); i += 5)
	{
		productsId.push_back(tmp[i]);
		mProducts[tmp[i]] = Product{tmp[i], tmp[i + 1], stoi(tmp[i + 2]), stof(tmp[i + 3]), stoi(tmp[i + 4])};
	}
	return;
}

// Function for Supply menu
void supply()
{
	system("Cls");
	int supplychoice;
	cout << endl;
	line('*');
	cout << "\t\t\t\t\t Supply \n";
	line('*');

	cout << "\n\t\t\t[1]- Add Products\n";
	cout << "\t\t\t[2]- Suppliers list\n";
	cout << "\t\t\t[3]- Update Stock\n";
	cout << "\t\t\t[4]- Back to menu\n";

	cout << endl;
	line('=');
	cout << "Enter your choice here:\n";
	cin >> supplychoice;
	line('=');

	if (supplychoice == 1)
		addProducts();
	else if (supplychoice == 2)
	{
		suppliers();
	}
	else if (supplychoice == 3)
	{
		updateProducts();
	}
	else if (supplychoice == 4)
		menu();
}

// Function for STOCKS Menu
void stock()
{
	system("cls");
	cout << endl;
	line('*');
	cout << "\t\t\t\t\t STOCK \n";
	line('*');
	int choice;
	cout << "\n\t\t[1]- Display Current Stock\n";
	cout << "\t\t[2]- Search Item in Stock\n";
	cout << "\t\t[3]- Go to menu  \n\n";
	line('=');
	cout << "Enter here: ";
	cin >> choice;
	if (choice == 1)
	{
		system("cls");
		displayProducts();
	}
	else if (choice == 2)
	{
		system("cls");
		searchProduct();
	}
	else if (choice == 3)
	{
		menu();
	}
	else
	{
		cout << "invalid entry";
	}
}

// Function for SALES Menu
void sales()
{
	system("cls");
	cout << endl;
	line('*');
	cout << "\t\t\t\t\t SALES \n";
	line('*');
	int choice;

	cout << "\n\t[1]-Generate Bill of sales \n";
	cout << "\t[2]-Go to menu\n\n";

	line('=');
	cout << "Enter here: ";
	cin >> choice;
	if (choice == 1)
	{
		system("cls");
		billGenerate();
	}

	else if (choice == 2)
	{
		system("cls");
		line('=');
		menu();
	}
	else
	{
		menu();
	}
}

// Function to Export data to file for printing
void billGenerate()
{
	char exit;
	int itembought;
	int totalPrice = 0;
	int discount;
	int payment;
	int change;
	string name;
	string filename;
	ofstream file;

	fstream billIdFile;

	billIdFile.open("billId.txt", ios::in);
	if (billIdFile.is_open())
	{
		string tmpB;
		while (getline(billIdFile, tmpB))
		{
			billID = stoi(tmpB);
		}
	}
	billIdFile.close();
	billID++;
	filename = "Bill ";
	filename = filename + to_string(billID);
	line('-');
	system("cls");
	file.open(string(filename + ".txt").c_str());
	line('=');

	cout << "Enter your Name : ";
	cin >> name;

	string tmpN;
	int tmpP;
	float tmpW;
	vector<string> tmpV;
	vector<float> Vweight;
	system("cls");

	cout << endl;
	line('=');
	cout << "\t\t\t\t\tSTOCK                 \n";
	line('=');
	cout << "ProductID\t\t"
		 << "Products"
		 << "\t"
		 << "Quantity(Kg/ltr/pcs)"
		 << "\t\t"
		 << "\tUnit Price" << endl;
	line('-');
	int l = 1;
	for (auto i = productsId.begin(); i != productsId.cend(); ++i)
	{

		cout << l << "\t\t\t" << mProducts.at(*i).name << "\t\t\t" << mProducts.at(*i).weight << "\t\t\t\t\t " << mProducts.at(*i).price << endl;
		l++;
	}
	do
	{
		line('=');
		cout << "Enter product name : ";
		cin >> tmpN;
		for (int i = 0; tmpN[i] != '\0'; i++)
		{
			if (tmpN[i] >= 'A' && tmpN[i] <= 'Z')
			{
				tmpN[i] += 32;
			}
		}
		cout << "Enter product Quantity (kg/L/Pcs) : ";
		cin >> tmpW;

		cout << endl;
		if (tmpW > mProducts.at(tmpN).weight)
		{
			cout << mProducts.at(tmpN).weight << '\n';
			cout << "Out of stock \n";
			getch();
			continue;
		}
		mProducts.at(tmpN).weight -= tmpW;
		Vweight.push_back(tmpW);
		tmpP = tmpW * mProducts.at(tmpN).price;
		totalPrice += tmpP;
		tmpV.push_back(tmpN);
		cout << "Any other product bought(y/n) : ";
		cin >> check;
		tolower(check);
	} while (check == 'y');

	line('-');

	cout << "Discount(%) : ";
	cin >> discount;

	cout << "Payment : ";
	cin >> payment;

	line('-');
	cout << "Preparing  Bill...\n";
	cout << "Done...\n";
	file << "**********************************************************************************\n";
	file << "\t\t\t\tBILL\n";
	file << "**********************************************************************************\n";

	string d = __DATE__;
	string date = "";
	string da = "";
	int x ;
	for(int i =0 ; d[i] != ' ' ; i++)
	{
		date += d[i];
	}
	int size = sizeof(d)/sizeof(string);
	for (int i =0 ; i< size ; i++)
	{
		if (d[i] >= '0' && d[i] <= 9)
		{
			da += d[i];
		}
	}
	cout << size;
	cout << da;
	for (int j=0 ; j < 12;j++)
	{
		if(MONTHS[j] == date)
		{
			x  = j+1;
		}
	}
	cout << x;
	file << "Bill ID. : #" << billID << "\t\t\t\t\t              Date : " << x << " " << da << endl;
	file << "Name : " << name << "\t\t\t\t\t              TIME : " << __TIME__ << endl;
	file << "==================================================================================\n";

	file << "ProductID\t\t"
		 << "Products"
		 << "\t"
		 << "Quantity(Kg/ltr/pcs)"
		 << "\t\t"
		 << "Unit Price" << endl;

	file << "---------------------------------------------------------------------------------\n";
	line('-');
	int discount1 = totalPrice * discount / 100;
	int grandTotal = totalPrice - discount1;
	int k = 0;
	int j = 0;
	prodName = "";
	float tmpPro = 0;
	for (auto i = tmpV.begin(); i != tmpV.cend(); ++i)
	{

		file << j << "\t\t\t" << mProducts.at(*i).name << "\t\t\t" << Vweight[k] << "\t\t\t" << mProducts.at(*i).price << endl;
		prodName = prodName.append(mProducts.at(*i).name);

		tmpPro += (mProducts.at(*i).price - mProducts.at(*i).buyPrice);
		tmpPro *= Vweight[k];
		k++;
		j++;
	}
	writeFile();
	file << "----------------------------------------------------------------------------------\n";
	file << "                                                     Total Amount : " << totalPrice << endl;
	file << "                                                     Payment : " << payment << endl;
	file << "                                                     Discount : " << discount1 << endl;
	file << "                                                     Grand Total : " << grandTotal << endl;
	file << "                                                     Change : " << payment - grandTotal << endl;
	file << "==================================================================================\n";
	file << "\nThank You for shopping!";
	cout << "\nDone! Bill Printed ";
	file.close();

	cout << "----------------------------------------------------------------------------------\n";
	cout << "                                                     Total Amount : " << totalPrice << endl;
	cout << "                                                     Payment : " << payment << endl;
	cout << "                                                     Discount : " << discount1 << endl;
	cout << "                                                     Grand Total : " << grandTotal << endl;
	cout << "                                                     Change : " << payment - grandTotal << endl;
	cout << "==================================================================================\n";
	cout << "\nThank You for shopping!";
	getch();
	system("cls");
	cout << endl;

	cout << endl;
	line('-');
	fstream file_1;
	file_1.open("billId.txt", ios::out);
	if (file_1.is_open())
	{
		cout << "Bill Id file is open\n";
		file_1 << billID;
	}
	file_1.close();
	int loan = 0;
	if (payment < grandTotal)
	{
		loan = grandTotal - payment;
	}

	mcustomer[billID] = customer{name, billID, prodName, __DATE__, loan, (loan == 0) ? true : false};

	getMonth();

	mSales.at(month).month = month;
	mSales.at(month).sales += grandTotal;
	mSales.at(month).profit += tmpPro;
	line('-');

	fileMonthlySales();
	customerWriteFile();

	cout << endl;
	cout << "Finished\n";
	line('-');
	cout << "Press any key to skip to menu";
	getch();
	menu();
}

void suppliers()
{
	system("cls");

	line('=');
	cout << "\t\t\t\t\tSuppliers                 \n";
	line('=');
	cout << "ProductID\t | \t"
		 << "Products"
		 << "\t | \t"
		 << "Suppliers"
		 << endl;
	line('-');
	int k = 1;
	for (auto i = productsId.begin(); i != productsId.cend(); ++i)
	{
		cout << k << "\t\t\t" << mProducts.at(*i).name << "\t\t\t" << mProducts.at(*i).suppliers << endl;
		k++;
	}
	line('-');
	writeFile();
	cout << "Press any key to go back to menu";
	getch();
	menu();
}

void alert()
{
	cout << endl;
	line('*');
	cout << " *Stock Alert!*";
	for (auto i = productsId.begin(); i != productsId.cend(); ++i)
	{
		if (mProducts.at(*i).weight < 15)
		{
			cout << "\n\t";
			cout << "      *" << mProducts.at(*i).name << " is getting out of stock " << endl;
		}
	}
}

void line(char ch)
{
	for (int j = 0; j < 100; j++)
		cout << ch;
	cout << endl;
}

void updateProducts()
{
	system("cls");
	string tmpN;
	int tmpP;
	float tmpW;
	int cho;
	cout << endl;
	line('*');
	cout << "\t\t\t\t\tUpdate Product\n";
	line('*');
	cout << "Enter name of product : ";
	cin >> tmpN;

	if(mProducts.find(tmpN) == mProducts.end())
	{
		cout << "Invalid entry !\n";
		cout << "Please try agin\n";
		getch();
		updateProducts();
	}

	cout << endl;
	cout << "What do you want to update : \n";
	cout << "[1]-Price\n";
	cout << "[2]-Quantity\n";
	line('-');
	cin >> cho;
	cout << "-------------------------------\n";
	switch (cho)
	{
	case 1:
		cout << "Enter new price : ";
		cin >> tmpP;
		mProducts.at(tmpN).price = tmpP;
		line('-');
		cout << "Stock Updated !";
		getch();
		supply();
		break;
	case 2:
		cout << "Add Quantity (kg/ltr/pcs) : ";
		cin >> tmpW;

		mProducts.at(tmpN).weight += tmpW;
		line('-');
		cout << "Stock Updated !";
		writeFile();
		getch();
		supply();
	default:
		break;
	}
}
// -------------------------INVENTORY MANAGEMENT SYSTEM BY FG SIR SYED COLLEGE----------------------------
void displaycustomers()
{
	customerReadFile();
	system("cls");

	cout << endl;
	line('*');
	cout << "\t\t\t\t\tCUSTOMERS                \n";
	line('*');
	cout << "Bill Id \t\t"
		 << "Name \t\t\t"
		 << "loan\t\t\t"
		 << "Paid" << endl;
	line('-');

	for (int i = 0; i <= billID; i++)
	{
		if (mcustomer.find(i) != mcustomer.end())
		{
			cout << mcustomer.at(i).billId << "\t\t\t" << mcustomer.at(i).name << "\t\t\t" << mcustomer.at(i).loan;
			if (mcustomer.at(i).paid)
			{
				cout << "\t\t\tpaid \n";
			}
			else
			{
				cout << "\t\t\tNot paid \n";
			}
		}
	}
	line('_');
	cout << "Do you want to update customers(Y/N) ?";
	cin >> check;
	if(check == 'Y' || check == 'y')
	{
		int id;
		int x;
		cout << "Enter bill id of the customer : ";
		cin >> id;
		if(mcustomer.find(id) != mcustomer.end())
		{
			cout << "Enter amount paid : ";
			cin >> x;

			if(mcustomer.at(id).loan - x >= 0)
			{
				mcustomer.at(id).loan -= x;
				cout << "Data updated !\n";
				if(mcustomer.at(id).loan == 0)
				{
					mcustomer.at(id).paid = true;
				}
			}
			else 
			{ 
				mcustomer.at(id).loan = 0;
				mcustomer.at(id).paid = true;
			}
		}
	}
	
	customerWriteFile();
	getch();
	menu();
}

void customerWriteFile()
{
	fstream myFile;
	myFile.open("customer.txt", ios::out); // write
	if (myFile.is_open())
	{
		for (auto i = 0; i <= billID; i++)
		{
			if (mcustomer.find(i) != mcustomer.end())
			{
				myFile << mcustomer.at(i).billId << "," << mcustomer.at(i).name << "," << mcustomer.at(i).products << "," << mcustomer.at(i).date << "," << mcustomer.at(i).loan << "," << mcustomer.at(i).paid << ",";
			}
		}
	}
	myFile.close();
}

void customerReadFile()
{

	fstream billIdFile;

	billIdFile.open("billId.txt", ios::in);
	if (billIdFile.is_open())
	{
		string tmpB;
		while (getline(billIdFile, tmpB))
		{
			billID = stoi(tmpB);
		}
	}
	billIdFile.close();

	vector<string> Vinput;
	fstream myFile;
	string line;
	myFile.open("customer.txt", ios::in);
	if (myFile.is_open())
	{
		while (getline(myFile, line, ','))
		{
			Vinput.push_back(line);
		}
	}
	myFile.close();

	for (auto i = Vinput.begin(); i != Vinput.cend(); i += 6)
	{
		bool t = stoi(*(i + 5));
		mcustomer[stoi(*i)] = customer{*(i + 1), stoi(*i), *(i + 2), *(i + 3), stoi(*(i + 4)), t};
	}
	myFile.close();
}

void monthlySales()
{
	mSales["Jan"];
	mSales["Feb"];
	mSales["March"];
	mSales["April"];
	mSales["May"];
	mSales["June"];
	mSales["July"];
	mSales["Aug"];
	mSales["Sept"];
	mSales["Oct"];
	mSales["Nov"];
	mSales["Dec"];
	getMonth();
	vector<string> tmpVa;
	string line;
	fstream myFile;
	myFile.open("sales.txt", ios::in);
	if (myFile.is_open())
	{
		while (getline(myFile, line, ','))
		{
			tmpVa.push_back(line);
		}
	}

	for (auto i = tmpVa.begin(); i != tmpVa.cend(); i += 3)
	{
		mSales[*i] = Sales{*i, stof(*(i + 1)), stof(*(i + 2))};
	}
}

void fileMonthlySales()
{
	getMonth();
	fstream myFile;
	myFile.open("sales.txt", ios::out);
	if (myFile.is_open())
	{
		myFile << mSales.at(month).month << ',' << mSales.at(month).sales << ',' << mSales.at(month).profit << ',';
	}
}

void analytics()
{
	getMonth();
	monthlySales();

	stockW = 0;
	for (auto i = productsId.begin(); i != productsId.cend(); ++i)
		{
			stockW += mProducts.at(*i).buyPrice*mProducts.at(*i).weight ;
		}


	system("cls");
	char ch1 = 16;
	char ch2 = 26;
	cout << endl;
	line('*');
	cout << "\t\t\t\t\tANALYTICS                \n";
	line('*');
	cout << endl;
	line('=');
	cout << " " << ch1 << "Present Stock" << endl;
	line('-');
	cout  << "\t      "<< ch2 << " Total Cost of Stock : " << stockW << " Rs" << endl;

	line('_');

	cout << endl;

	line('=');
	for(int i =0 ; i < 12 ; i++)
		{
			if(mSales.find(MONTHS[i]) != mSales.end() && mSales.at(MONTHS[i]).sales > 0)
			{
				cout << " " << ch1 << "Month : " << mSales.at(MONTHS[i]).month << endl;
				line('-');
				cout  << "\t      "<< ch2 << " Sales : " << mSales.at(MONTHS[i]).sales << " Rs" << endl;
				cout  << "\t      "<< ch2 << " Profit : " << mSales.at(MONTHS[i]).profit << " Rs" << endl;
			}
		}
	line('_');
	
	
	getch();
	menu();
}

void getMonth()
{
	string date = __DATE__;
	month = "";
	for (int i = 0; date[i] != ' '; i++)
	{
		month += date[i];
	}
}

// -------------------------INVENTORY MANAGEMENT SYSTEM BY FG SIR SYED COLLEGE----------------------------
