#include "main.h"


class imp_res : public Restaurant
{
private:

	customer* first_cus; //first customer
	customer* x_cus; /// X customer
	int count;

	//LL queue
	customer* fqueue_cus;
	customer* tqueue_cus;
	//LL record customer
	customer* fr;
	customer* tr;

public: //ham bo tro
	void print_List_Cus() {
		customer* cur = first_cus;
		cout << "Customers in table: ";
		for (int i = 0; i < count; i++) {
			cout << cur->name << " " << cur->energy << " <=> ";
			cur = cur->next;
		}
		cout << endl;

		if (fqueue_cus) {
			customer* qcur = fqueue_cus;
			cout << "Customers in queue: ";
			while (qcur->next) {
				cout << qcur->name << " " << qcur->energy << " -> ";
				qcur = qcur->next;
			}
			cout << tqueue_cus->name << " " << tqueue_cus->energy;
			cout << endl;
		}
		else {
			cout << "Customers in queue: 0" << endl;
		}


		customer* rcur = fr;
		cout << "Order of customers entering the table: ";
		while (rcur->next) {
			cout << rcur->name << " " << rcur->energy << " -> ";
			rcur = rcur->next;
		}
		cout << tr->name << " " << tr->energy;
		cout << endl;
	}

	bool is_name_duplicated(string name) {
		customer* cur = first_cus;
		for (int i = 0; i < count; i++) {
			if (name == cur->name) {
				return true;
			}
			cur = cur->next;
		}
		return false;
	}

	void arrange_seat(customer* cus) {
		customer* current = first_cus->next;
		customer* x_cus = first_cus;
		int RES = cus->energy - first_cus->energy;
		//int index = 0;

		for (int i = 1; i < count; i++) {
			int temp_RES = cus->energy - current->energy;
			if (abs(temp_RES) > abs(RES)) {
				RES = temp_RES;
				//index = i;
				x_cus = current;
			}
			current = current->next;
		}

		if (RES < 0) { // add to left 
			if (count == 1) {
				cus->next = x_cus;
				cus->prev = x_cus;

				x_cus->prev = cus;
				x_cus->next = cus;
			}
			else {
				cus->next = x_cus;
				cus->prev = x_cus->prev;

				x_cus->prev->next = cus;
				x_cus->prev = cus;
			}

		}
		else { //add to right
			if (count == 1) {
				cus->next = x_cus;
				cus->prev = x_cus;

				x_cus->prev = cus;
				x_cus->next = cus;
			}
			else {
				cus->next = x_cus->next;
				x_cus->next->prev = cus;

				x_cus->next = cus;
				cus->prev = x_cus;
			}
		}
	}

public:
	imp_res() {
		first_cus = nullptr;
		x_cus = nullptr;
		count = 0;

		fqueue_cus = nullptr;
	};

	void RED(string name, int energy)
	{

		if (energy == 0) {
			cout << "Khong nhan customer co energy bang 0" << endl;
			return;
		}



		if (is_name_duplicated(name)) {
			cout << "Ten khach moi trung" << endl;
			return;
		}


		cout << name << " " << energy << endl;
		customer* cus = new customer(name, energy, nullptr, nullptr);

		if (count >= MAXSIZE) {
			cout << "So luong khach vuot qua MAXSIZE, add to queue" << endl;
			if (fqueue_cus == nullptr) {
				fqueue_cus = cus;
				tqueue_cus = cus;
			}
			else {
				tqueue_cus->next = cus;
				tqueue_cus = cus;
			}

			return;
		}

		//Check khach hang dau tien hay khong?
		if (!first_cus) {
			first_cus = cus;
			x_cus = cus;
			//cout << "First customer: " << name << " " << energy << endl;
		}
		else {
			//Count >= MAXSIZE/2 thi sap xep theo chien luoc khac
			if (count >= MAXSIZE / 2) {
				arrange_seat(cus);
			}
			else {
				if (count == 1) {
					cus->next = x_cus;
					cus->prev = x_cus;

					x_cus->next = cus;
					x_cus->prev = cus;
				}
				else {
					// neu la thuat su => add vao ben phai
					if (cus->energy >= x_cus->energy) {
						cus->next = x_cus->next;
						cus->prev = x_cus;

						x_cus->next->prev = cus;
						x_cus->next = cus;
						x_cus = cus;
						//x_cus->next = cus;
						/*cus->prev = x_cus;
						x_cus = cus;
						first_cus->prev = cus;
						cus->next = first_cus;*/
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

		}
		++count;

		//record customer
		customer* temp = new customer(cus->name, cus->energy, nullptr, nullptr);
		if (fr == nullptr) {
			fr = temp;
			tr = temp;
		}
		else {
			tr->next = temp;
			tr = temp;
		}
	}
	void BLUE(int num)
	{
		//func 2
		//cout << "blue " << num << endl;
		if (num >= count || num >= MAXSIZE) {
			cout << "Duoi het khach hang ve" << endl;
			// remove
			for (int i = 0; i < count; i++) {
				customer* rev = first_cus;
				if (first_cus->next) {
					first_cus = first_cus->next;

					rev->next = nullptr;
					rev->prev = nullptr;
					delete rev;
				}
				else {
					delete first_cus; //co 1 node
					first_cus = nullptr;

				}
				count--;
			}

			//giai phong toan bo record
			cout << "Giai phong all record" << endl;
			customer* rev = fr;
			while (fr->next) {
				fr = fr->next;

				rev->next = nullptr;
				delete rev;
			}
			if (fr == tr) delete fr;
		}
		else {
			for (int i = 0; i < num; i++) {

				customer* rev = first_cus; //remove
				customer* rrev = fr; //record remove

				//find customer 2
				if (fr->next) {
					fr = fr->next;
					while (first_cus->name != fr->name) {
						first_cus = first_cus->next;
					}
				}

				//Delete customer out
				rrev->next = nullptr;
				delete rrev;

				if (count != 1) {
					rev->next->prev = rev->prev;
					rev->prev->next = rev->next;
					rev->next = nullptr;
					rev->prev = nullptr;
					delete rev;
				}
				else {
					delete first_cus;
					first_cus = nullptr;
				}
				count--;
			}

		}

		//Chon cho ngoi cho khach if queue != nullptr
		while (fqueue_cus && count < MAXSIZE) {
			customer* newcus = fqueue_cus;
			if (fqueue_cus->next) fqueue_cus = fqueue_cus->next;

			RED(newcus->name, newcus->energy);
			//giai phong node trong queue
			newcus->next = nullptr;
			delete newcus;
		}
	}

	void PURPLE()
	{
		//func 3
		//cout << "purple" << endl;
	}
	void REVERSAL()
	{
		//func 4
		//cout << "reversal" << endl;
	}
	void UNLIMITED_VOID()
	{
		//func 5
		//cout << "unlimited_void" << endl;
	}
	void DOMAIN_EXPANSION()
	{
		//func 6
		//cout << "domain_expansion" << endl;
	}
	void LIGHT(int num)
	{
		//func 7
		//cout << "light " << num << endl;
	}
};