#include "main.h"

class imp_res : public Restaurant
{
private:
	customer* first_cus; //first customer
	customer* x_cus; /// X customer

public:
	imp_res() {
		first_cus = nullptr;
		x_cus = nullptr;
	};

	void RED(string name, int energy)
	{

		if (energy == 0) {
			cout << "Khong nhan customer co energy bang 0";
			return;
		}

		cout << name << " |||.." << energy << endl;
		customer* cus = new customer(name, energy, nullptr, nullptr);

		//Check khach hang dau tien hay khong?
		if (!first_cus) {
			first_cus = cus;
			x_cus = cus;
			cout << "First customer: " << name << " " << energy << endl;
			return;
		}
		else {
			// neu la thuat su => add vao ben phai
			if (cus->energy >= x_cus->energy) {
				x_cus->next = cus;
				cus->prev = x_cus;


				x_cus = cus;
				first_cus->prev = cus;
				cus->next = first_cus;
			}
			else { // neu la oan linh => add vao ben trai
				cus->next = x_cus;
				cus->prev = x_cus->prev;

				x_cus->prev->next = cus;
				x_cus->prev = cus;

				x_cus = cus;
			}
		}
	}
	void BLUE(int num)
	{
		//func 2
		cout << "blue " << num << endl;
	}
	void PURPLE()
	{
		//func 3
		cout << "purple" << endl;
	}
	void REVERSAL()
	{
		//func 4
		cout << "reversal" << endl;
	}
	void UNLIMITED_VOID()
	{
		//func 5
		cout << "unlimited_void" << endl;
	}
	void DOMAIN_EXPANSION()
	{
		//func 6
		cout << "domain_expansion" << endl;
	}
	void LIGHT(int num)
	{
		//func 7
		cout << "light " << num << endl;
	}
};