/*
! Võ Tiến ..............
* Võ Tiến ..............
~ Võ Tiến ..............
& Võ Tiến ..............
TODO Võ Tiến ..............
*/

#include "main.h"
#include "restaurant.cpp"

const int startProgam = 401;
const int endProgam = 600;

void simulate(string filename)
{
	solution.flush();
	//* nhập file
	ifstream ss(filename);
	if (ss.fail())
	{
		cout << "ERROR: " << filename << endl;
		return;
	}

	
	string str, name;
	int num, i = 1;
	
	ss >> str;
	ss >> MAXSIZE; //* nhập maxsize đầu tiên
	JJK_RESTAURANT_OPERATIONS* NOT_LIKE_CODE = new JJK_RESTAURANT_OPERATIONS();
	// //* xử lí file
	while (ss >> str)
	{
		if (str == "LAPSE") // LAPSE <NAME>
		{
			ss >> name;
			solution << "LAPSE : LINE " << i << "\n";
			NOT_LIKE_CODE->LAPSE(name);
		}
		else if (str == "KOKUSEN") // KOKUSEN
		{
			NOT_LIKE_CODE->KOKUSEN();
		}
		else if (str == "KEITEIKEN") // KEITEIKEN <NUM>
		{
			ss >> num;
			solution << "KEITEIKEN " + to_string(num) +" : LINE " << i << "\n";
			NOT_LIKE_CODE->KEITEIKEN(num);
			solution << '\n';
		}
		else if (str == "HAND") // HAND
		{
			solution << "HAND : LINE " << i << "\n";
			NOT_LIKE_CODE->HAND();
			solution << '\n';
		}		
		else if (str == "LIMITLESS") // LIMITLESS <NUM>
		{
			ss >> num;
			solution << "LIMITLESS " + to_string(num) +" : LINE " << i << "\n";
			NOT_LIKE_CODE->LIMITLESS(num);
			solution << '\n';
		}		
		else if (str == "CLEAVE") // CLEAVE <NUM>
		{
			ss >> num;
			solution << "CLEAVE " + to_string(num) +" : LINE " << i << "\n";
			NOT_LIKE_CODE->CLEAVE(num);
			solution << '\n';
		}				
		i++;
	}
	delete NOT_LIKE_CODE;
}


void copyFile(const std::string& sourcePath, const std::string& destinationPath) {
    std::ifstream sourceFile(sourcePath, std::ios::binary);
    std::ofstream destinationFile(destinationPath, std::ios::binary);

    if (!sourceFile) {
        std::cerr << "Error opening source file: " << sourcePath << std::endl;
        return;
    }

    if (!destinationFile) {
        std::cerr << "Error opening destination file: " << destinationPath << std::endl;
        return;
    }

    destinationFile << sourceFile.rdbuf();

    if (!destinationFile) {
        std::cerr << "Error copying data from " << sourcePath << " to " << destinationPath << std::endl;
    }
}

void printTestFail(int i)
{
    //copy
    copyFile("test/solution_you/output" + to_string(i) + ".txt", "test_fail/solution_you.txt");
    copyFile("test/solution/output" + to_string(i) + ".txt", "test_fail/solution.txt");
    copyFile("test/input/input" + to_string(i) + ".txt", "test_fail/input_fail.txt");

	string file_solution_you = "test/solution_you/output" + to_string(i) + ".txt";
	string file_solution = "test/solution/output" + to_string(i) + ".txt";
	ifstream read_solution_you(file_solution_you);
	ifstream read_solution(file_solution);
	string s1, s2;
	int k = 1;
	while (read_solution_you >> s1 && read_solution >> s2)
	{
		if (s1 != s2)
		{
			cout << "\nfail test " << i << " " << "https://www.diffchecker.com/text-compare/"; // << " : line " << k <<" in ouput"  << endl;
			return;
		}
		k++;
	}
	if (read_solution_you >> s1 || read_solution >> s2)
	{
		cout << "fail test " << i << " line " << k << endl;
	}
}

void comparefile(int start, int end)
{
	string folder_solution_you = "test/solution_you/output";
	string folder_solution = "test/solution/output";
	vector<int> result;
	for (int i = start; i <= end; i++)
	{
		string file_solution_you = folder_solution_you + to_string(i) + ".txt";
		string file_solution = folder_solution + to_string(i) + ".txt";

		ifstream read_solution_you(file_solution_you);
		ifstream read_solution(file_solution);
		if (read_solution_you.fail() || read_solution.fail())
		{
			cout << "Error reading file\n"
				 << end;
			return;
		}
		string s1, s2;
		while (read_solution_you >> s1 && read_solution >> s2)
		{
			if (s1 != s2)
			{
				result.push_back(i);
				break;
			}
		}
		if (read_solution_you >> s1 || read_solution >> s2)
		{
			if (result.size() == 0 || result.size() > 0 && result[result.size() - 1] != i)
				result.push_back(i);
		}
	}

	if (result.size() == 0)
	{
		cout << "Success: test " << start << " to " << end << endl;
	}
	else
	{
		cout << "percent success : " << (1 - result.size() * 1.0 / (end - start + 1)) * 100 << "%" << endl;
		cout << "Fail : test [";
		for (int i = 0; i < result.size() - 1; i++)
		{
			cout << result[i] << ", ";
		}
		cout << result[result.size() - 1] << "]\n";
		printTestFail(result[0]);
	}
}

//* ./main red; ./main blue; ./main reversel; ./main unlimited_void; ./main domain_expansion
int main(int argc, char *argv[])
{
	cout << "Start program" << endl;
	string folder_input = "test/input/input";
	string folder_solution_you = "test/solution_you/output";
	string folder_solution = "test/solution/output";

	if (argc < 2)
	{
		cout << "checking : ";
		for (int i = startProgam; i <= endProgam; i++)
		{
			cout << i << " ";
			solution.open(folder_solution_you + to_string(i) + ".txt");
			simulate(folder_input + to_string(i) + ".txt");
			solution.close();
		}
		cout << "\nOK: runs without errors\n"
				<< endl;
		comparefile(startProgam, endProgam);
	}
	else if (argc == 2)
	{
		string s = argv[1];
		cout << "checking : ";
		if(s == "me")
		{
			for (int i = startProgam; i <= endProgam; i++)
			{
				cout << i << " ";
				solution.open(folder_solution + to_string(i) + ".txt");
				simulate(folder_input + to_string(i) + ".txt");
				solution.close();
			}
			cout << "\nOK: runs without errors code me !!!!!!!!!\n" << endl;		
		}
		else
		{	
			int i = stoi(s);
			cout << i << " ";
			solution.open(folder_solution_you + to_string(i) + ".txt");
			simulate(folder_input + to_string(i) + ".txt");
			
			solution.close();
			cout << "\nOK: runs without errors\n" << endl;
			comparefile(stoi(s), stoi(s));
		}
	}
	else if (argc == 3)
	{
		cout << "checking : ";
		string s1 = argv[1], s2 = argv[2];
		int start = stoi(s1);
		int end = stoi(s2);
		for (int i = start; i <= end; i++)
		{
			cout << i << " ";
			solution.open(folder_solution_you + to_string(i) + ".txt");
			simulate(folder_input + to_string(i) + ".txt");
			solution.close();
		}
		cout << "\nOK: runs without errors\n" << endl;
		comparefile(start, end);
	}


	// if (COUNTDELETE == 0)
	// {
	// 	cout << "\nOK: NO leak mermory \n"
	// 		 << endl;
	// }
	// else if (COUNTDELETE)
	// {
	// 	cout << "\nOK: leak mermory Please fix the bug, No 10\% test deduction\n"
	// 		 << endl;
	// }
}