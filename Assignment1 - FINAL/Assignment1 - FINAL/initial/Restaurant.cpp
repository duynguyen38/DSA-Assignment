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
	int qcount;
	int order; //thu tu customer vao queue

	//LL record customer (ghi lai thu tu cua customer vao cua hang, de delete)
	customer* fr; //first record
	customer* tr; //tail record
	int rcount;

public: //ham bo tro

	void print_list(customer* h, customer* t, int sum, int count) {
		customer* tmp = h;
		//cout << "\nChuoi sublist co sum la: " << sum << " ===>";
		for (int i = 0; i < count; i++) {
			cout << tmp->name << "-" << tmp->energy << "\n";
			tmp = tmp->next;
		}
	}

	void print_queue() {
		if (fqueue_cus && qcount != 0) {
			customer* qcur = fqueue_cus;
			//cout << "Customers in queue: ";
			while (qcur->next) {
				//cout << qcur->name << "-" << qcur->energy << "\n";
				qcur->print();
				qcur = qcur->next;
			}
			//cout << tqueue_cus->name << "-" << tqueue_cus->energy << "\n";
			tqueue_cus->print();
			//cout << endl;
		}
		else {
			//cout << "Customers in queue: 0" << endl;
		}
	}

	void print_Cus_inTable() {
		customer* cur = first_cus;
		cout << "Customers in table: ";
		for (int i = 0; i < count; i++) {
			cout << cur->name << "|" << cur->energy << " <=> ";
			cur = cur->next;
		}
		cout << endl;


		customer* rcur = fr;
		cout << "Order of customers entering the table: ";
		while (rcur->next) {
			cout << rcur->name << "|" << rcur->energy << " -> ";
			rcur = rcur->next;
		}
		cout << tr->name << "|" << tr->energy;
		cout << "\n";

	}

	bool is_name_duplicated(string name) {
		customer* cur = first_cus;
		for (int i = 0; i < count; i++) {

			if (name == cur->name) {
				//cout << "\nName bi trung voi customer trong table: " << cur->name << endl;
				return true;
			}
			cur = cur->next;
		}

		cur = fqueue_cus;
		while (cur && qcount != 0) {
			if (name == cur->name) {
				//cout << "\nName bi trung voi customer trong queue: " << cur->name << endl;
				return true;
			}
			cur = cur->next;
		}

		return false;
	}

	void arrange_seat(customer* cus) {
		customer* current = first_cus->next;


		//int index = 0;

		//cout << "Vi tri X Customer ban dau: " << x_cus->name << "|" << x_cus->energy;

		customer* x_cus = first_cus;
		int RES = cus->energy - first_cus->energy;
		//cout << "\nRES: " << RES << endl;

		//cout << "temp_RES: ";
		for (int i = 1; i < count; i++) {
			int temp_RES = cus->energy - current->energy;
			//cout << temp_RES << " ";
			if (abs(temp_RES) > abs(RES)) {
				RES = temp_RES;
				//index = i;
				x_cus = current;
			}
			current = current->next;
		}

		//cout << "\nRES: " << RES << " Vi tri tim duoc: " << x_cus->name << "|" << x_cus->energy;

		if (RES < 0) { // add to left 
			//cout << "\nAdd to left X customer: " << x_cus->name << "|" << x_cus->energy << endl;
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
			//cout << "\nAdd to right X customer: " << x_cus->name << "|" << x_cus->energy << endl;
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

	void swap(customer*& n1, customer*& n2) {

		customer* temp = new customer;
		temp->name = n1->name;
		temp->energy = n1->energy;
		//temp->prev->energy = n1->prev->energy; //order

		n1->name = n2->name;
		n1->energy = n2->energy;
		//n1->prev->energy = n2->prev->energy; //order

		n2->name = temp->name;
		n2->energy = temp->energy;
		//n2->prev->energy = temp->prev->energy;

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
				for (j = i; j >= gap && abs(temp->energy) > abs(pretemp->energy); j -= gap) {
					swap(pretemp, temp);
					num++;
					pretemp = pretemp->prev;
					temp = temp->prev;
				}
			}
		}

		return num;
	}

	void stable_sort(customer* head, customer* tail, int n) {

		//print
		customer* temp = head;
		/*cout << "\nList will be stable_sort: ";
		while (temp != tail) {
			cout  << temp->name << " " << temp->energy << " ->";
			temp = temp->next;
		}
		cout << tail->name << " " << tail->energy;*/


		//sort
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
				string or1 = "", or2 = "";
				for (int m = 0; m < pretemp->name.size(); m++) {
					if ('0' <= pretemp->name[m] && pretemp->name[m] <= '9') {
						or1 += pretemp->name[m];
					}
				}
				for (int m = 0; m < temp->name.size(); m++) {
					if ('0' <= temp->name[m] && temp->name[m] <= '9') {
						or2 += temp->name[m];
					}
				}


				int j;
				for (j = i; j >= gap && stoi(or1) > stoi(or2); j -= gap) {
					swap(pretemp, temp);
					num++;
					pretemp = pretemp->prev;
					temp = temp->prev;
				}
			}
		}

		//print after sort
		/*temp = head;
		cout << "\nList were stable_sorted: ";
		while (temp != tail) {
			cout << temp->name << " " << temp->energy << " ->";
			temp = temp->next;
		}
		cout << tail->name << " " << tail->energy;*/
	}

	void add_cus_from_queue() {
		//Chon cho ngoi cho khach if queue != nullptr, delete ra khoi queue
		while (fqueue_cus && count < MAXSIZE && qcount != 0) {
			customer* addcus = fqueue_cus;

			addcus->name = addcus->name.substr(0, addcus->name.size() - 1); //remove order trong queue

			if (fqueue_cus != tqueue_cus) {
				fqueue_cus = fqueue_cus->next;
			}
			else {
				fqueue_cus = nullptr;
				tqueue_cus = nullptr;
			}
			qcount--;
			//ngat node dau trong queue ra
			addcus->next = nullptr;

			RED(addcus);
		}
	}


public:
	imp_res() {
		first_cus = nullptr;
		x_cus = nullptr;
		count = 0;

		fqueue_cus = nullptr;
		tqueue_cus = nullptr;
		qcount = 0;
		order = 0;

		fr = nullptr;
		tr = nullptr;
		rcount = 0;
	};

	///////////////////////////////////////////////////
	void RED(customer* cus) {

		//cout << "\nADD CUSTOMER: " << cus->name << "|" << cus->energy << endl;

		if (count >= MAXSIZE) {
			if (qcount < MAXSIZE) {
				//cout << "So luong khach vuot qua MAXSIZE, add to queue " << cus->name << "|" << cus->energy << endl;
				order++;
				cus->name += to_string(order); //gan so thu tu cho customer trong queue

				if (qcount == 0) {
				
					fqueue_cus = cus;
					tqueue_cus = cus;
				}
				else {
					tqueue_cus->next = cus;
					cus->prev = tqueue_cus;
					tqueue_cus = cus;
				}
				qcount++;
			}
			else {
				//cout << "So luong queue >= MAXSIZE, ngung nhan customer!!!\n";
				delete cus;
			}
			//print_queue();
			//cout << "Count queue: " << MAXSIZE << " " << qcount << endl;
			return;
		}

		////Qua trinh them node!!!
		//Check khach hang dau tien hay khong?
		if (!first_cus) {
			first_cus = cus;
			//cout << "First customer: " << cus->name << "|" << cus->energy << endl;
		}
		else {
			//Count >= MAXSIZE/2 thi sap xep theo chien luoc khac
			if (count >= MAXSIZE / 2) {
				//cout << "So luong da >= MAXSIZE/2, doi chien luoc\n";
				arrange_seat(cus);
			}
			else {
				if (count == 1) {
					if (cus->energy >= x_cus->energy) {
						//cout << "Energy >= x_cus, add to right x_cus: " << x_cus->name << "|" << x_cus->energy << endl;

						x_cus->next = cus;
						x_cus->prev = cus;

						cus->next = x_cus;
						cus->prev = x_cus;
					}
					else {
						//cout << "Energy < x_cus, add to left x_cus: " << x_cus->name << "|" << x_cus->energy << endl;

						cus->next = x_cus;
						cus->prev = x_cus;

						x_cus->next = cus;
						x_cus->prev = cus;

					}
				}
				else {
					// neu la thuat su => add vao ben phai
					if (cus->energy >= x_cus->energy) {
						//cout << "Energy >= x_cus, add to right x_cus: " << x_cus->name << "|" << x_cus->energy << endl;
						cus->next = x_cus->next;
						cus->prev = x_cus;

						x_cus->next->prev = cus;
						x_cus->next = cus;
					}
					else { // neu la oan linh => add vao ben trai
						//cout << "Energy < x_cus, add to left x_cus: " << x_cus->name << "|" << x_cus->energy << endl;

						cus->next = x_cus;
						cus->prev = x_cus->prev;

						x_cus->prev->next = cus;
						x_cus->prev = cus;
					}
				}

			}

		}

		++count;
		x_cus = cus;
		//cout << "Vi tri X customer hien tai: " << x_cus->name << "|" << x_cus->energy << endl;


		//record customer
		customer* temp = new customer(cus->name, cus->energy, nullptr, nullptr);
		if (fr == nullptr) {
			fr = temp;
			tr = temp;
		}
		else {
			tr->next = temp;
			temp->prev = tr;
			tr = temp;
		}
		rcount++;


		//print_Cus_inTable();
		//print_queue();
		//cout << "Count table: " << MAXSIZE << " " << count << "\n\n";
	}

	void RED(string name, int energy)
	{

		if (energy == 0) {
			//cout << "Khong nhan customer co energy bang 0" << endl;
			return;
		}

		if (is_name_duplicated(name)) {
			return;
		}

		customer* cus = new customer(name, energy, nullptr, nullptr);
		RED(cus);

	}
	///////////////////////////////////////////////////

	///////////////////////////////////////////////////
	void BLUE_queue(string name) {
		if (qcount != 0) {
			customer* rev = tqueue_cus;
			while (rev->name != name) {
				rev = rev->prev;
			}

			if (qcount == 1) {
				if (rev = fqueue_cus) {
					delete fqueue_cus;
				}

			}
			else {
				if (rev == fqueue_cus) {
					fqueue_cus = fqueue_cus->next;
					fqueue_cus->prev = nullptr;

					rev->next = nullptr;
					delete rev;
				}
				else if (rev == tqueue_cus) {
					tqueue_cus = tqueue_cus->prev;
					tqueue_cus->next = nullptr;

					rev->prev = nullptr;
					rev->next = nullptr;
					delete rev;
				}
				else {
					rev->prev->next = rev->next;
					rev->next->prev = rev->prev;

					rev->next = nullptr;
					rev->prev = nullptr;
					delete rev;
				}
			}
			qcount--;
		}
	}

	void BLUE_OL() { //duoi all OAN LINH gan day nhat -> vao som nhat
		
		//delete in queue
		if(fqueue_cus && qcount != 0)
			fqueue_cus->prev = nullptr;

		customer* tmp = tqueue_cus;
		while (tmp && qcount != 0) {
			if (tmp->energy < 0) {
				//cout << tmp->name << "-" << tmp->energy << "\n";
				tmp->print();
				string n = tmp->name;
				tmp = tmp->prev;
				BLUE_queue(n);
			}
			else {
				tmp = tmp->prev;
			}
		}


		//delete in table
		if (fr)
			fr->prev = nullptr;

		customer* temp = tr;
		while (temp) {
			if (temp->energy < 0) {
				//cout << temp->name << "-" << temp->energy << "\n";
				temp->print();
				string n = temp->name;
				temp = temp->prev;
				BLUE(n);
			}
			else temp = temp->prev;
		}


		add_cus_from_queue();
	}

	void BLUE_TS() {

		if (fqueue_cus && qcount != 0)
			fqueue_cus->prev = nullptr;

		customer* tmp = tqueue_cus;
		while (tmp && qcount != 0) {
			if (tmp->energy > 0) {
				//cout << tmp->name << "-" << tmp->energy << "\n";
				tmp->print();
				string n = tmp->name;
				tmp = tmp->prev;
				BLUE_queue(n);
			}
			else {
				tmp = tmp->prev;
			}
		}

		if(fr)
			fr->prev = nullptr;

		customer* temp = tr;
		//cout << "THUAT SU bi moi ve la: ";
		while (temp != nullptr) {
			if (temp->energy > 0) {
				//cout << temp->name << "-" << temp->energy << "\n";
				temp->print();
				string n = temp->name;
				temp = temp->prev;
				BLUE(n);
			}
			else temp = temp->prev;
			
		}
		add_cus_from_queue();
	}

	void BLUE(string name) {
		customer* rev = first_cus;
		while (rev->name != name) {
			rev = rev->next;
		}

		customer* rrev = fr;
		while (rrev->name != name) {
			rrev = rrev->next;
		}

		//xoa khoi record
		if (rcount == 1) {
			if (rrev = fr) {
				delete fr;
			}
		}
		else {
			if (rrev == fr) {
				fr = fr->next;
				fr->prev = nullptr;

				rrev->next = nullptr;
				delete rrev;
			}
			else if (rrev == tr) {
				
				tr = tr->prev;
				tr->next->prev = nullptr;

				delete tr->next;
				tr->next = nullptr;
			}
			else {

				
				rrev->prev->next = rrev->next;
				rrev->next->prev = rrev->prev;

				rrev->next = nullptr;
				rrev->prev = nullptr;

				delete rrev;
			}
			rcount--;
		}

		//update x_cus
		if (rev->energy > 0) x_cus = rev->next;
		else x_cus = rev->prev;

		//cout << "\nCustomer bi moi ra ve: " << rev->name << "|" << rev->energy << endl;


		if (count != 1) {
			//cap nhap lai first cus theo record
			first_cus = rev->next;
			for (int i = 0; i < count; i++) {
				if (first_cus->name != fr->name) {
					first_cus = first_cus->next;
				}
			}

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
		//cout << MAXSIZE << " " << count << endl;
	}

	void BLUE(int num)
	{
		//print queue


		//func 2
		//cout << "blue " << num << endl;
		if (num >= count || num >= MAXSIZE) {
			//cout << "\nDuoi het khach hang ve" << endl;
			x_cus = nullptr;
			// remove
			while (first_cus && count != 0) {
				customer* rev = first_cus;
				if (first_cus->next) {
					first_cus = first_cus->next;

					rev->next = nullptr;
					rev->prev = nullptr;
					delete rev;
				}
				else {
					delete rev;
				}
				count--;
			}
			first_cus = nullptr;

			//giai phong toan bo record
			//cout << "Giai phong all record\n" << endl;
			if (fr) {
				while (fr->next) {
					customer* rev = fr;
					fr = fr->next;

					rev->next = nullptr;
					rev->prev = nullptr;
					delete rev;
				}
				if (fr == tr) {
					delete fr;
					fr = nullptr;
					tr = nullptr;
				}
			}
		}
		else {
			for (int i = 0; i < num; i++) {
				BLUE(fr->name);
			}

		}

		add_cus_from_queue();
	}
	///////////////////////////////////////////////////

	void PURPLE()
	{
		//print queue before sort
		//cout << "\nQueue before sort: ";
		//print_queue();

		if (fqueue_cus) {


			//find customer has max energy
			customer* find_max = fqueue_cus;
			customer* temp = fqueue_cus->next;
			while (temp) {
				if (abs(find_max->energy) <= abs(temp->energy)) {
					find_max = temp;
				}
				temp = temp->next;
			}

			//cout << "Cus_Max: " << find_max->name << "|" << find_max->energy << endl;

			//count node from fqueue -> find_max
			int count = 1;
			/*temp = fqueue_cus;
			cout << "List will be sorted: ";
			while (temp != find_max) {
				cout << temp->name << "|" << temp->energy << " ";
				temp = temp->next;
				count++;
			}
			cout << find_max->name << "|" << find_max->energy;
			cout << endl;*/
			//cout << "count: " << count << endl;





			int num_sort = shellSort(fqueue_cus, find_max, count); // so lan sort


			//print list was sorted
			/*temp = fqueue_cus;
			cout << "sorted_list: ";
			while (temp != find_max) {
				cout << temp->name << "|" << temp->energy << " ";
				temp = temp->next;
			}
			cout << find_max->name << "|" << find_max->energy << endl;*/
			
			//Check customer co cung energy
			customer* fcheck = fqueue_cus;
			customer* tcheck = fqueue_cus;
			for (int i = 0; i < qcount; i++) {
				int n = 1; // number of node from fcheck to tcheck
				if (tcheck->next != nullptr) {
					if (tcheck->energy == tcheck->next->energy) {
						while (abs(tcheck->energy) == abs(tcheck->next->energy)) {
							if (tcheck->next) {
								tcheck = tcheck->next;
								n++;
								if (tcheck->next == nullptr) break;
							}
						}
						cout << endl;
						//sap xep lai from fcheck to tcheck
						stable_sort(fcheck, tcheck, n);

						tcheck = tcheck->next;
						fcheck = tcheck;
					}
					else {
						fcheck = fcheck->next;
						tcheck = tcheck->next;
					}
				}
				else break;
			}



			//cout << "\nQueue after sort: ";
			//print_queue();

			

			//thuc hien blue num_sort mod MAX_SIZE

			//cout << "\nTHUC HIEN BLUE(num_sort % MAXSIZE): " << num_sort << " mod " << MAXSIZE << " = " << num_sort % MAXSIZE << endl;
			BLUE(num_sort % MAXSIZE);
		}
		else {
			//cout << "\nQueue dang null, khong sort!!!\n\n";
		}

		//func 3
		//cout << "purple" << endl;
	}

	void REVERSAL()
	{
		//save X value
		string ener = "";
		if (x_cus)
			ener = x_cus->name;

		customer* f_ol = nullptr; //oan linh
		customer* t_ol = nullptr;

		customer* f_ts = nullptr; //thuat su
		customer* t_ts = nullptr;

		customer* temp = x_cus;
		for (int i = 0; i < count; i++) {
			if (temp->energy < 0) {
				if (f_ol == nullptr) {
					f_ol = new customer{ temp->name, temp->energy, nullptr, nullptr };
					t_ol = f_ol;
				}
				else {
					customer* tp = new customer{ temp->name, temp->energy, nullptr, nullptr };
					t_ol->next = tp;
					tp->prev = t_ol;
					t_ol = tp;
				}

				temp->energy = 0; //set 0 cho OAN LINH
			}
			else {
				if (f_ts == nullptr) {
					f_ts = new customer{ temp->name, temp->energy, nullptr, nullptr };
					t_ts = f_ts;
				}
				else {
					customer* tp = new customer{ temp->name, temp->energy, nullptr, nullptr };
					t_ts->next = tp;
					tp->prev = t_ts;
					t_ts = tp;
				}
				temp->energy = 1; //set 1 cho THUAT SU
			}
			temp = temp->prev; //doc nguoc chieu kim dong ho
		}

		//PRINT
		/*cout << "Before REVERSAL: \n";

		temp = f_ol;
		cout << "List OAN LINH: ";
		while (temp) {
			cout << temp->name << " " << temp->energy << "<=>";
			temp = temp->next;
		}
		cout << endl;

		temp = f_ts;
		cout << "List THUAT SU: ";
		while (temp) {
			cout << temp->name << " " << temp->energy << "<=>";
			temp = temp->next;
		}
		cout << endl;*/
		

		//Xep customer vao lai ban
		temp = x_cus;
		for (int i = 0; i < count; i++) {
			if (temp->energy == 1) {
				temp->name = t_ts->name;
				temp->energy = t_ts->energy;

				//delete node nay
				if (t_ts != f_ts) {
					customer* rev = t_ts;
					t_ts = t_ts->prev;

					rev->next = nullptr;
					rev->prev = nullptr;
					delete rev;
				}
				else {
					delete f_ts;
				}
			}
			else if (temp->energy == 0) {
				temp->name = t_ol->name;
				temp->energy = t_ol->energy;

				//delete node nay
				if (t_ol != f_ol) {
					customer* rev = t_ol;
					t_ol = t_ol->prev;

					rev->next = nullptr;
					rev->prev = nullptr;
					delete rev;
				}
				else {
					delete f_ol;
				}
				
			}
			temp = temp->prev;
		}

		//cap nhap x_cus lai
		temp = x_cus;
		for (int i = 0; i < count; i++) {
			if (temp->name == ener) x_cus = temp;

			temp = temp->next;
		}
		//cout << "X_cus now is: " << x_cus->name << " " << x_cus->energy << endl;

		//print_Cus_inTable();

		//func 4
		//cout << "reversal" << endl;
	}

	void UNLIMITED_VOID()
	{
		//cout << "\n\n";
		//print_Cus_inTable();

		if (count >= 4) {
			customer* temp = x_cus;

			customer* head = temp;
			customer* tail = temp;
			int cnt = 1;

			int minsum = temp->energy;

			int loop = count; // loop = 5
			while (loop) {

				customer* h = temp;
				customer* t = temp;
				int co = 1;

				int sum = temp->energy;

				for (int i = 1; i < 4; i++) {
					t = t->next;
					co++;
					sum += t->energy;
				}
				if (sum <= minsum) {
					minsum = sum;
					head = h;
					tail = t;
					cnt = co;
				}
				//cout << "\nSUM cua 4 node dau tien: " << minsum;
				//print_list(h, t, minsum, co);


				customer* tmp = t->next;
				while (tmp != h) {
					co++;
					sum = sum + tmp->energy;
					if (sum <= minsum) {
						t = tmp;

						minsum = sum;
						head = h;
						tail = t;
						cnt = co;

						tmp = tmp->next;

						//cout << "\nCap nhap lai maxsum la: " << maxsum;
						//print_list(head, tail, maxsum, cnt);
					}
					else {
						//print_list(h, tmp, sum, co);
						tmp = tmp->next;
					}
				}


				temp = temp->next;
				loop--;
			}

			//customer* tmp = h;
			//cout << "\nChuoi sublist co maxsum la: " << maxsum << " ===>";
			if (cnt >= 4)
				print_list(head, tail, minsum, cnt);
		}
		
	}
	
	void DOMAIN_EXPANSION()
	{
		int sum_ts = 0;
		int sum_ol = 0;
		//Sum energy in table
		customer* temp = x_cus;
		for (int i = 0; i < count; i++) {
			if (temp->energy > 0) sum_ts += temp->energy;
			else sum_ol += temp->energy;
			
			temp = temp->next;
		}

		//sum energy in queue
		temp = fqueue_cus;
		while (temp && qcount != 0) {
			if (temp->energy > 0) sum_ts += temp->energy;
			else sum_ol += temp->energy;

			temp = temp->next;
		}

		//cout << "\nsum_ts: " << sum_ts << "----" << "sum_ol: " << sum_ol << endl;

		if (sum_ts >= abs(sum_ol)) BLUE_OL();
		else if (abs(sum_ol) >= sum_ts) BLUE_TS();


		//print_Cus_inTable();
		//print_queue();
	}

	void LIGHT(int num)
	{
		customer* temp = x_cus;
		if (num > 0) { //print theo chieu kim dong ho tu vi tri x_cus
			for (int i = 0; i < count; i++) {
				//cout << temp->name << "-" << temp->energy << "\n";
				temp->print();
				if (temp->next)
					temp = temp->next;
			}
		}
		else if (num < 0) { //print theo nguoc chieu kim dong ho tu vi tri x_cus
			for (int i = 0; i < count; i++) {
				//cout << temp->name << "-" << temp->energy << "\n";
				if (temp->prev)
					temp = temp->prev;
			}
		}
		else { // num == 0 print khach trong queue
			print_queue();
		}
	}

	~imp_res() {
		customer* rev = x_cus;
		while (rev && count != 0) {
			//cout << rev->name << " ";
			x_cus = x_cus->next;
			delete rev;
			rev = x_cus;
			count--;
		}

		//cout << endl;

		rev = fqueue_cus;
		while (rev && qcount != 0) {
			//cout << rev->name << " ";
			fqueue_cus = fqueue_cus->next;
			delete rev;
			rev = fqueue_cus;
			qcount--;
		}

		rev = fr;
		while (rev && rcount != 0) {
			//cout << rev->name << " ";
			fr = fr->next;
			delete rev;
			rev = fr;
			rcount--;
		}
	}
};