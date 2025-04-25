
#include <iostream>

int main()
{
	int choice;
	do
	{
		std::cout << "Choose your lab (-1 for exit): ";
		std::cin >> choice;

		switch (choice)
		{
		case -1:
			std::cout << "Have a nice day!";
			break;
		case 1:
			system("\"C:/Desktop/БГУИР/2 семестр/ООПиП/lab_launcher/launcher/x64/Debug/lab1.exe\"");
			system("pause");
			system("cls");
			break;
		case 2:
			system("\"C:/Desktop/БГУИР/2 семестр/ООПиП/lab_launcher/launcher/x64/Debug/lab2.exe\"");
			system("pause");
			system("cls");
			break;
		case 3:
			system("\"C:/Desktop/БГУИР/2 семестр/ООПиП/lab_launcher/launcher/x64/Debug/lab3.exe\"");
			system("pause");
			system("cls");
			break;
		case 4:
			system("\"C:/Desktop/БГУИР/2 семестр/ООПиП/lab_launcher/launcher/x64/Debug/lab4.exe\"");
			system("pause");
			system("cls");
			break;
		case 5:
			system("\"C:/Desktop/БГУИР/2 семестр/ООПиП/lab_launcher/launcher/x64/Debug/lab5.exe\"");
			system("pause");
			system("cls");
			break;
		case 6:
			system("\"C:/Desktop/БГУИР/2 семестр/ООПиП/lab_launcher/launcher/x64/Debug/lab6.exe\"");
			system("pause");
			system("cls");
			break;
		case 7:
			system("\"C:/Desktop/БГУИР/2 семестр/ООПиП/lab_launcher/launcher/x64/Debug/lab7.exe\"");
			system("pause");
			system("cls");
			break;
		case 8:
			system("\"C:/Desktop/БГУИР/2 семестр/ООПиП/lab_launcher/launcher/x64/Debug/lab8.exe\"");
			system("pause");
			system("cls");
			break;
		default:
			std::cout << "Wrong lab number!\n";
		}
	} while (choice != -1);

	return 0;
}