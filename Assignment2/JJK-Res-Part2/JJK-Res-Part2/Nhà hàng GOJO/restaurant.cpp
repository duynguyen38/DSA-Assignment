#include "main.h"

int MAXSIZE = 0;

class JJK_RESTAURANT_OPERATIONS;
class RESTAURANT_Gojo;
class RESTAURANT_Sukuna;
class HuffTree_AVL;

//* nhà hàng của sư phụ GOJO
class RESTAURANT_Gojo
{
	class Tree_BST;

private:
	//* cứ hiểu mỗi phần tử areaTable là các khu ăn trong đó sẽ có 1 nhân viên quản lí thêm vào và xóa ra chủ không cần quản lí mấy này
	vector<Tree_BST> areaTable;

public:
	RESTAURANT_Gojo() : areaTable(MAXSIZE + 1) {}
	void insertAreaTable(int result)
	{
		//* khách mới vô thích chọn khu có ID = result % MAXSIZE + 1 dắt nó tới chỗ đó rồi nén vô cho nhân viên khu đó xử lí
		int ID = result % MAXSIZE + 1;
		areaTable[ID].insert(result);
	}

	void remove_KOKUSEN()
	{
		//* tới từng khu ăn kêu nhân viên tìm thằng nào gián điệp đấm nó rồi đuổi cổ nó đi
		for (int i = 1; i < MAXSIZE + 1; i++)
			areaTable[i].remove();
	}

	void print_LIMITLESS(int number)
	{
		//* tới khu number kêu nhân viên liệt kê tất cả khách hàng ra
		if (number <= 0 || number > MAXSIZE)
			return; //! quá kí tự
		areaTable[number].print();
	}

private:
	//* Tree_BST giống như các nhân viên
	class Tree_BST
	{
		class Node;

	private:
		Node *root;			  //! cây của khách hàng vị trí khách hàng
		queue<int> queueTime; //! thời gian khách hàng đến có thể hiểu như là sổ ghi thông tin khách hàng
	public:
		Tree_BST() : root(nullptr) {}
		int size()
		{
			return queueTime.size();
		}

		//^hàm thêm ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//* nhân viên được chủ giao cho bố trí khách hàng có result
		Node *insert_recursive(Node *node, int result)
		{
			// TODO TODO TODO  TODO TODO TODO
		}
		void insert(int result)
		{
			root = insert_recursive(root, result);
		}
		//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//^hàm xóa ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//* nhân viên sẽ tới tận nơi đuổi cổ khách hàng gián điệp ra khỏi nhà hàng với result là khách hàng gián điệp
		Node *remove_recursive(Node *node, int result)
		{
			// TODO TODO TODO  TODO TODO TODO
		}
		int CountNode(Node *node)
		{
			return node == NULL ? 0 : 1 + CountNode(node->left) + CountNode(node->right);
		}
		unsigned long long permutationFormula(int x, int n)
		{
			//! TODO TÍNH C(n,x)= x!(n-x)!/n! công thức chỉnh hợp
		}
		unsigned long long DFS(Node *node)
		{
			if (node == NULL)
				return 1;
			// TODO TODO TODO  TODO TODO TODO  đệ quy
		}
		//* nhân viên sẽ liệt kê ra các khách hàng gián điệp để dễ dàng đuổi
		void remove()
		{
			if (this->size() == 0)
				return; //! trường hợp rỗng bỏ qua
			//* bước 1: đếm số lượng node cần xóa
			//^ tìm hiểu : https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/
			// TODO: tính số lượng number
			unsigned long long number = DFS(root);
			//*: trường hợp mà postoder cũng tạo ra một cây giống đó thì chỉ có 1 node -> nên không tính
			if (this->size() == 1)
				return;

			//* bước 2: xóa node trong cây với số lượng đã tính trên
			//* kiểm tra xem đã xóa đủ số lượng chưa hay cây đã hết node để xóa
			while (number != 0 && !queueTime.empty())
			{
				int temp = queueTime.front();		 //! tìm khách hàng đầu tiên được lưu trong sổ và lấy được vị trí nó rồi
				queueTime.pop();					 //! xóa nó khỏi sổ
				root = remove_recursive(root, temp); //! tới chỗ nó cho nó cút khỏi nhà hàng
				number--;
			}
		}
		//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//^hàm in ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//* hàm này theo trung thứ tự (in-order) thôi không gì khó hết
		string print_recursive(Node *node)
		{
			if (node == nullptr)
				return "NULL"; //! trường hợp dừng print

			string left = print_recursive(node->left);
			solution << node->result << " ";
			string right = print_recursive(node->right);

			if (node->left == nullptr && node->right == nullptr)
				return to_string(node->result); //! tr
			return to_string(node->result) + "(" + left + "," + right + ")";
		}
		void print()
		{
			//! trường hợp rỗng bỏ qua
			if (this->size() == 0)
			{
				solution << "EMPTY";
				return;
			}
			solution << "inoder: ";
			string s = print_recursive(root);
			solution << "\nTree: " << s;
			std::queue<int> tempQueue = queueTime;
			solution << "\nQueue: ";
			while (!tempQueue.empty())
			{
				solution << tempQueue.front() << " ";
				tempQueue.pop();
			}
		}
		//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	private:
		class Node
		{
		private:
			int result;
			Node *left;
			Node *right;
			friend class Tree_BST;

		public:
			Node(int result) : result(result), left(NULL), right(NULL) {}
		};
	};
};

class RESTAURANT_Sukuna
{
	class Link_List;

private:
	vector<Link_List> areaTable;

private:
	void ReHeap_up(int index)
	{
	}

	void ReHeap_down(int index)
	{
	}

public:
	RESTAURANT_Sukuna() {}
	void insertAreaTable(int result)
	{
		int ID = result % MAXSIZE + 1;
		//* bước 1 kiểm tra khu vực ID có khách hay chưa
		bool ischeckCustomer = false;
		// TODO: kiểm tra thử khu vực ID đã có khách hay chưa dùng hàm size() của Link_List

		//* bước 2 thêm khách vào khu vực đó
		if (ischeckCustomer)
		{
			//* trường hợp chưa có bàn thì phải tạo bàn mới
			areaTable.push_back(Link_List(result, ID));
			this->ReHeap_up(areaTable.size());
		}
		else
		{
			//* trường hợp đã có khách trong bàn tìm bàn đó thôi
			for (int i = 0; i < areaTable.size(); i++)
			{
				if (areaTable[i].ID == ID)
				{
					areaTable[i].insert(result);
					return;
				}
			}
		}
	}

	void remove_KEITEIKEN()
	{
	}

	void print_LIMITLESS(int number)
	{
		if (number < 0 || number > MAXSIZE)
			return; //! quá kí tự
		areaTable[number].print(number);
	}

private:
	class Link_List
	{
		class Node;

	private:
		Node *head;
		int ID;
		queue<Node *> queueTime;
		friend class RESTAURANT_Sukuna;

	public:
		Link_List(int result, int ID)
		{
			this->ID = ID;
			head = new Node(result);
			queueTime.push(head);
		}
		int size() { return queueTime.size(); }

		void insert(int result)
		{
			// TODO: tự code đi các bạn: khi new nhớ push vào queueTime
			// TODO: Trường hợp phần tử cha có hai con, thì phần tử cha sẽ hoán đổi với phần tử con có giá trị lớn hơn
			// TODO: Nếu các phần tử có cùng giá trị NUM thì phần tử lớn hơn được quy ước là phần tử được thêm vào heap sớm hơn
		}

		void remove(int number)
		{
		}

		void print(int number) {}

	private:
		class Node
		{
		private:
			int result;
			Node *next;
			friend class Link_List;

		public:
			Node(int result) : result(result), next(NULL) {}
		};
	};
};

class JJK_RESTAURANT_OPERATIONS
{
private:
	// HuffTree_AVL New_customers_arrive;
	RESTAURANT_Gojo hash;
	RESTAURANT_Sukuna heap;

public:
	void LAPSE(string name)
	{

		int result = stoi(name);
		//* CODE CODE CODE BỎ QUẢ

		if (result % 2 == 1)
			hash.insertAreaTable(result);
		else
		{
		}
	}

	//* xử lí nhà hàng gojo
	void KOKUSEN() { hash.remove_KOKUSEN(); }
	void LIMITLESS(int num) { hash.print_LIMITLESS(num); }

	//* xử lí nhà hàng Sukuna
	void KEITEIKEN(int num) {}
	void CLEAVE(int num) {}

	void HAND() {}
};
