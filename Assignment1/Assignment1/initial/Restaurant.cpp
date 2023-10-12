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

	//LL record customer (ghi lai thu tu cua customer vao cua hang, de delete)
	customer* fr; //first record
	customer* tr; //tail record

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
				cout << qcur->name << qcur->energy << " -> ";
				qcur = qcur->next;
			}
			cout << tqueue_cus->name << tqueue_cus->energy;
			cout << endl;
		}
		else {
			cout << "Customers in queue: 0" << endl;
		}



		customer* rcur = fr;
		cout << "Order of customers entering the table: ";
		while (rcur->next) {
			cout << rcur->name << rcur->energy << " -> ";
			rcur = rcur->next;
		}
		cout << tr->name << tr->energy;
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


	void swap(customer* n1, customer* n2) {
		customer* temp = new customer;
		temp->name = n1->name;
		temp->energy = n1->energy;

		n1->name = n2->name;
		n1->energy = n2->energy;

		n2->name = temp->name;
		n2->energy = temp->energy;

		delete temp;
	}

	int shellSort(customer* head, customer* tail, int n) { // n = 4 => interval = 2;
		int num = 0; //so lan sort

		for (int gap = n / 2; gap > 0; gap /= 2) {
			for (int i = gap; i < n; i++) {

				//loop pretemp = node[i-gap]
				customer* temp = head;
				customer* pretemp = head;
				customer* prepretemp = head;
				int k1 = i - gap;
				while (k1 != 0) {
					pretemp = pretemp->next;
					k1--;
				}
				//temp = node[gap]
				int k = i; // k = 3, 2, 1
				while (k != 0) {
					temp = temp->next;
					k--;
				}

				//compare two node
				int j;
				for (j = i; j >= gap &&  abs(temp->energy) > abs(pretemp->energy); j -= gap) {
					swap(pretemp, temp);
					num++;
					pretemp = pretemp->prev;
					temp = temp->prev;
				}
			}
		}
		return num;
	}


public:
	imp_res() {
		first_cus = nullptr;
		x_cus = nullptr;
		count = 0;

		fqueue_cus = nullptr;
		tqueue_cus = nullptr;

		fr = nullptr;
		tr = nullptr;
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
				cus->prev = tqueue_cus;
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
			x_cus = nullptr;
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
			if (fr == tr) {
				delete fr;
				fr = nullptr;
				tr = nullptr;
			} 
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

				//update x_cus
				if (rev->energy > 0) x_cus = rev->next;
				else x_cus = rev->prev;

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
		//find customer has max energy
		customer* find_max = fqueue_cus;
		customer* temp = fqueue_cus->next;
		while (temp) {
			if (abs(find_max->energy) <= abs(temp->energy)) {
				find_max = temp;
			}
			temp = temp->next;
		}
		cout << "Cus_Max: " << find_max->name << find_max->energy << endl;

		//count node from fqueue -> find_max
		int count = 1;
		temp = fqueue_cus;
		cout << "Will be sorted: ";
		while (temp != find_max) {
			cout << temp->name << temp->energy << " ";
			temp = temp->next;
			count++;
		}
		cout << find_max->name << find_max->energy;
		cout << endl;
		cout << "count: " << count << endl;

		//thuc hien blue num_sort mod MAX_SIZE
		int num_sort = shellSort(fqueue_cus, find_max, count); // so lan sort
		BLUE(num_sort % MAXSIZE);

		//print list was sorted
		temp = fqueue_cus;
		cout << "sorted_list: ";
		while (temp != find_max) {
			cout << temp->name << temp->energy << " ";
			temp = temp->next;
		}
		cout << find_max->name << find_max->energy << endl;
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