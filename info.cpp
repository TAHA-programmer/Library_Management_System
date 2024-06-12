#include<iostream>
#include<fstream>
#include<string>
int id_number = 0;//FOR INCREMENTING ID 
class Book
{
public:
	int Id;
	char Name[50];
	char Author[50];
};
const int SIZE = 100;
Book Record[SIZE];
//FUNCTIONS

void Add()//ADDING A RECORD
{
	if (id_number < SIZE)
	{
		Record[id_number].Id = id_number;
		std::cout << "Enter Name : ";
		std::cin >> Record[id_number].Name;
		std::cout << "Enter Author Name :";
		std::cin >> Record[id_number].Author;
		id_number++;
	}
	else
		std::cout << "Array is Full" << std::endl;
}

void print(const Book& book)//DISPLAYING A RECORD
{
	std::cout << "ID :" << book.Id << std::endl;
	std::cout << "Name :" << book.Name << std::endl;
	std::cout << "Author :" << book.Author << std::endl;
}

void printArray()//DISPLAYING ALL RECORDS
{
	for (int i = 0; i < id_number; i++)
		print(Record[i]);
}

void update()//UPDATING A RECORD

{
	int temp_id;
	std::cout << "Enter ID :";
	std::cin >> temp_id;
	if (temp_id < id_number && temp_id >= 0)
	{
		std::cout << "Enter new Book name :";
		std::cin >> Record[temp_id].Name;
		std::cout << "Enter new Author name :";
		std::cin >> Record[temp_id].Author;
	}
	else
		std::cout << "Invalid ID (out of range) :" << std::endl;
}

void Delete()//DELETING A RECORD
{
	int temp_id;
	std::cout << "Enter ID for deletion:";
	std::cin >> temp_id;
	if (temp_id < id_number && temp_id >= 0)
	{
		for (int i = temp_id; i < id_number - 1; i++)
		{
			Record[i] = Record[i + 1];
			Record[i].Id--;
		}
		id_number--;
	}
	else
		std::cout << "Invalid ID :" << std::endl;
}

void Search()//SEARCHING A RECORD
{
	int temp_id;
	std::cout << "Enter ID for searching :";
	std::cin >> temp_id;
	if (temp_id < id_number && temp_id >= 0)
	{
		print(Record[temp_id]);
	}
	else
		std::cout << "Record not found :" << std::endl;
}

void help()//FOR SHOWING ALL COMMANDS
{
	std::cout << "--------------------------------------------------------" << std::endl;
	std::cout << "add for addition of a record:" << std::endl;
	std::cout << "update for update of a record:" << std::endl;
	std::cout << "display for displaying all records:" << std::endl;
	std::cout << "search for searching of a record:" << std::endl;
	std::cout << "delete for deleting of a record:" << std::endl;
	std::cout << "import for importing all records from CSV to BINARY:" << std::endl;
	std::cout << "export for export all records from BINARY to CSV:" << std::endl;
	std::cout << "--------------------------------------------------------" << std::endl;
}

void write_file(std::string file)//WRITING ALL RECORDS
{
	std::ofstream fi(file, std::ios::binary | std::ios::trunc);
	if (fi.is_open())
	{
		fi.write((const char*)Record, sizeof(Book) * id_number);
		fi.close();
	}
	else
		std::cout << "file not opened :" << std::endl;
}

void read_file(std::string file)//READING ALL RECORDS
{
	std::ifstream fi;
	fi.open(file, std::ios::binary);
	if (fi.is_open())
	{
		fi.seekg(0, std::ios::end);
		int byte = fi.tellg();
		id_number = byte / sizeof(Book);
		fi.seekg(0, std::ios::beg);
		fi.read((char*)Record, sizeof(Book) * id_number);
		fi.close();
	}
	else
		std::cout << "file not opened :" << std::endl;
}

void importfile(std::string file)//IMPORT FUNCTION

{
	std::ifstream fi;
	fi.open(file);
	if (fi.is_open())
	{
		int i = 0;
		std::string temprary;
		while (fi.good())
		{
			fi >> Record[i].Id;
			fi.ignore(1);
			if (fi.eof())
				break;
			getline(fi, temprary, ',');
			temprary.copy(Record[i].Name, 50);
			Record[i].Name[temprary.size()] = '\0';
			getline(fi, temprary);
			temprary.copy(Record[i].Author, 50);
			Record[i].Author[temprary.size()] = '\0';
			i++;
		}
		id_number = i;
		fi.close();
	}
	else
		std::cout << "File not open " << std::endl;
}

void exportfile(std::string file)//EXPORT FUNCTION
{
	std::ofstream fi(file, std::ios::trunc);//for openning csv file
	if (fi.is_open())
	{
		for (int i = 0; i < id_number; i++)
		{
			fi << Record[i].Id << ",";
			fi << Record[i].Name << ",";
			fi << Record[i].Author << std::endl;
		}
		fi.close();
	}
	else
		std::cout << "Error while opening file" << std::endl;
}

//MAIN FILE

int main(int argc, char* argv[])
{
	//FOR ONE COMMAND 

	if (argc == 1)
	{
		//MENU
		std::cout << "MENU" << std::endl;
		help();
		std::string file;
		std::cout << "Enter file name (no spaces) :";
		std::cin >> file;
		read_file(file);
		std::string temp;
		std::cout << "Enter Command : ";
		std::cin >> temp;
		if (temp == "add")
			Add();
		else
			if (temp == "update")
				update();
			else
				if (temp == "delete")
					Delete();
				else
					if (temp == "search")
						Search();
					else
						if (temp == "display")
							printArray();
						else
							if (temp == "help")
								help();
							else
								std::cout << "invalid command" << std::endl;
		write_file(file);
	}
	//FOR TWO COMMANDS
	else
		if (argc == 2)
		{
			std::string file;
			std::cout << "Enter file name (no spaces) :";
			std::cin >> file;
			read_file(file);
			std::string temp = argv[1];
			if (temp == "add")
				Add();
			else
				if (temp == "update")
					update();
				else
					if (temp == "delete")
						Delete();
					else
						if (temp == "search")
							Search();
						else
							if (temp == "display")
								printArray();
							else
								if (temp == "help")
									help();
								else
									std::cout << "invalid command" << std::endl;
			write_file(file);
		}
	//FOR THREE COMMANDS
		else
			if (argc == 3)
			{
				std::string temp = argv[1];
				if (temp == "import")
				{
					temp = argv[2];
					importfile(temp);
					std::cout << "Enter new file name (binary) : ";
					std::cin >> temp;
					write_file(temp);
				}
				else
					if (temp == "export")
					{
						std::string file;
						std::cout << "Enter file name (no spaces) :";
						std::cin >> file;
						read_file(file);
						file = argv[2];
						exportfile(file);
					}
					else
						std::cout << "Invalid command" << std::endl;
			}
			else
				std::cout << "Invalid command" << std::endl;
	return 0;
}