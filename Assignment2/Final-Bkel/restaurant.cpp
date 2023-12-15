#include "main.h"

int MAXSIZE = 0;

class JJK_RESTAURANT;
class Gojo_RESTAURANT;
class Sukuna_RESTAURANT;
class HuffTree_AVL;

//********************************************************************************************************************
class Gojo_RESTAURANT
{
	class Tree_BST;

private:
	vector<Tree_BST> Zone_Manage; //* xem là vector bao gồm các khu vực phục vụ

public:
	Gojo_RESTAURANT() : Zone_Manage(MAXSIZE + 1) {}
	void insert_to_AreaTable(int result)
	{
		//* khách mới vào sẽ chọn khu có ID = result % MAXSIZE + 1
		//* chỉ khách này tới chỗ đó rồi cho nhân viên khu đó xử lí
		int ID = result % MAXSIZE + 1;
		Zone_Manage[ID].insert(result);
	}
	void KOKUSEN() //* KOKUSEN == remove khách tại GOJO
	{
		for (int i = 1; i < MAXSIZE + 1; i++)
			Zone_Manage[i].remove();
	}

	void LIMITLESS(int number)
	{
		if (number <= 0 || number > MAXSIZE)
			return;
		Zone_Manage[number].print();
	}

private:
	class Tree_BST
	{
		class Node;

	private:
		Node *root;
		queue<int> recording; //* Xem là cuốn sổ dùng ghi thứ tự khách hàng nào vào trước, sau

	public:
		Tree_BST() : root(nullptr) {}
		~Tree_BST()
		{
			while (!recording.empty())
			{
				int temp = recording.front();
				recording.pop();
				root = remove_REC(root, temp);
			}
		}
		int size()
		{
			return recording.size();
		}
		Node *insert_REC(Node *node, int result) //* insert recursion
		{
			//* Step 1: kiểm tra cây rỗng hay không?
			if (node == nullptr)
			{
				recording.push(result); //*ghi vào sổ
				// COUNTDELETE--;
				return new Node(result);
			}

			//* Step 2: thêm vào bên phải
			if (result >= node->result)
			{
				node->right = insert_REC(node->right, result);
			}
			//* Step 3: thêm vào bên trái
			else
			{
				node->left = insert_REC(node->left, result);
			}

			return node;
		}

		void insert(int result)
		{
			root = insert_REC(root, result);
		}

		Node *remove_REC(Node *node, int result)
		{
			//* step 1: xét cây rỗng
			if (node == nullptr)
				return nullptr;

			//* step 2.1: xét case xoá cây con bên phải
			if (result > node->result)
			{
				node->right = remove_REC(node->right, result);
			}
			//* step 2.2: xét case xoá cây con bên trái
			else if (result < node->result)
			{
				node->left = remove_REC(node->left, result);
			}
			//* step 2.3: nếu tìm thấy rồi thì, tìm node nhỏ nhất bên phải để thay
			else if (result == node->result)
			{
				Node *del_node = node;
				//* nếu node cần xoá là node lá thì xoá luôn
				if (node->left == nullptr && node->right == nullptr)
				{
					node = nullptr;
				}
				else if (node->left == nullptr)
				{
					node = node->right;
				}
				else if (node->right == nullptr)
				{
					node = node->left;
				}
				else
				{
					Node *temp = node->right;

					while (temp->left != nullptr)
						temp = temp->left;

					int tmp = temp->result;
					temp->result = node->result;
					node->result = tmp;

					node->right = remove_REC(node->right, result);
					return node;
				}
				delete del_node;
				// COUNTDELETE++;
			}
			return node;
		}
		int Count_NodeNumber(Node *node)
		{
			return node == nullptr ? 0 : 1 + Count_NodeNumber(node->left) + Count_NodeNumber(node->right);
		}

		unsigned long long permutation(unsigned long long n, unsigned long long x)
		{
			//! TÍNH C(n,x)
			//* sử dụng tam giác pascal để tính C(n,x)
			vector<vector<unsigned long long>> pascal(n + 1, vector<unsigned long long>(n + 1, 0));

			for (unsigned long long i = 0; i <= n; i++)
			{
				for (unsigned long long j = 0; j <= i && j <= x; j++)
				{
					if (j == 0 || j == i)
						pascal[i][j] = 1;
					else
						pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
				}
			}
			return (pascal[n][x]) % MAXSIZE; //* trả về giá trị C(n,x)
		}

		unsigned long long DFS(Node *node) //* DFS = số hoán vị cần tính tại node
		{
			if (node == nullptr)
				return 1;

			//* tính n = tổng số node left + right
			unsigned long long n = Count_NodeNumber(node) - 1;

			//* tính x = số node left
			unsigned long long x = Count_NodeNumber(node->left);

			return (permutation(n, x) * DFS(node->left) * DFS(node->right)) % MAXSIZE;
		}
		void remove()
		{
			if (recording.empty())
				return;

			unsigned long long number = DFS(root) % MAXSIZE;

			while (number != 0 && !recording.empty())
			{
				int temp = recording.front();
				recording.pop();
				root = remove_REC(root, temp);
				number--;
			}
		}
		void print_REC(Node *node)
		{
			if (node != nullptr)
			{
				print_REC(node->left);
				solution << node->result << "\n";
				print_REC(node->right);
			}
		}
		void print() { print_REC(root); }

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
//*-------------------------------------------------------------------------------------------------------------------

//********************************************************************************************************************
class Sukuna_RESTAURANT
{
	class Node;

private:
	vector<Node *> Zone_Manage;
	list<Node *> LRU;

private:
	bool twoArea_Compare(int index1, int index2)
	{
		list<Node *>::iterator it1 = find(LRU.begin(), LRU.end(), Zone_Manage[index1]);
		list<Node *>::iterator it2 = find(LRU.begin(), LRU.end(), Zone_Manage[index2]);
		// bool flag = 0;
		if (it1 != LRU.end() && it2 != LRU.end())
		{
			if (distance(LRU.begin(), it1) < distance(LRU.begin(), it2))
			{
				return 1;
			}
		}
		return 0;
	}

	void reheapDown(unsigned int index)
	{
		//* areaTable.size() là số khu vực nhà hàng đang phục vụ
		//* Kiểm tra có tồn tại node con nào không, nếu không
		if (index * 2 + 1 >= Zone_Manage.size())
			return;
		//* Nếu chỉ có 1 node con trái
		else if (index * 2 + 1 == Zone_Manage.size() - 1) //* chỉ có root và left
		{												//* nếu key ở node left mà bé hơn, thì swap
			if (Zone_Manage[index * 2 + 1]->size() < Zone_Manage[index]->size())
			{
				swap(Zone_Manage[index * 2 + 1], Zone_Manage[index]);
			}
			else if (Zone_Manage[index * 2 + 1]->size() == Zone_Manage[index]->size())
			{
				//* flag == 1 thì LRU -> index*2+1 -> index; => size(index*2+1) > size(index) => nothing
				bool flag = twoArea_Compare(index * 2 + 1, index);
				if (!flag)
				{
					swap(Zone_Manage[index * 2 + 1], Zone_Manage[index]);
				}
			}
			return;
		}
		//* 3 node: root, left, right
		int leftChild_idx = index * 2 + 1;	//* left
		int rightChild_idx = index * 2 + 2; //* right

		//* tìm node có key nhỏ nhất giữa 2 node con
		int minChild = -1;
		if (Zone_Manage[leftChild_idx]->size() == Zone_Manage[rightChild_idx]->size())
		{
			bool flag = twoArea_Compare(leftChild_idx, rightChild_idx);
			//* flag == 1 thì LRU -> left -> right
			if (flag)
			{ //* chọn ra thằng vừa được thêm khách vào
				minChild = rightChild_idx;
			}
			else
				minChild = leftChild_idx;
		}
		else
		{
			minChild = Zone_Manage[leftChild_idx]->size() < Zone_Manage[rightChild_idx]->size() ? leftChild_idx : rightChild_idx;
		}

		//* Kiểm tra xem khu vực index hiện tại có size >= khu vực có size nhỏ nhất vừa tìm dc hay không?
		//* Nếu có thì swap

		if (Zone_Manage[index]->size() < Zone_Manage[minChild]->size())
			return;

		if (Zone_Manage[index]->size() > Zone_Manage[minChild]->size())
		{
			swap(Zone_Manage[index], Zone_Manage[minChild]);
		}
		//* 2 khu có số khách bằng nhau, thì xét LRU, khu nào vừa dc sử dụng thì chọn
		else if (Zone_Manage[index]->size() == Zone_Manage[minChild]->size())
		{
			//* dùng hàm list distance
			//* nếu flag == 1 thì khu index nằm trước khu minChild, => khu index > khu minChild => swap
			//* nếu flag == 0 thì khu index nằm sau khu minChild, => khu index < khu minChild => nothing
			bool flag = twoArea_Compare(index, minChild);
			if (flag)
			{
				swap(Zone_Manage[index], Zone_Manage[minChild]);
			}
		}
		reheapDown(minChild);
	}

	void reheapUp(int index)
	{

		int parent = (index - 1) / 2;

		//* Kiểm tra khu index có là khu đầu tiên trong heap, hoặc có size lớn hơn cha, thì do nothing
		if (index == 0 || Zone_Manage[index]->size() > Zone_Manage[parent]->size())
			return;

		if (Zone_Manage[index]->size() < Zone_Manage[parent]->size())
		{
			swap(Zone_Manage[index], Zone_Manage[parent]);
		}
		else
		{ //* 2 khu có size bằng nhau thì xét LRU
			//* flag == 1 khi khu index đứng trước trong LRU => khu index có size lớn hơn khu parent => do nothing
			//* flag == 0 khi khu index đứng sau trong LRU => khu index có size nhỏ hơn khu parent => swap
			bool flag = twoArea_Compare(index, parent);
			if (!flag)
			{
				swap(Zone_Manage[index], Zone_Manage[parent]);
			}
		}
		reheapUp(parent);
	}

	void move_to_Top(Node *node)
	{
		//* Step 1: Tìm vị trí của node trong danh sách
		bool flag = false; //* check có node trong LRU hay chưa?
		list<Node *>::iterator it;
		for (it = LRU.begin(); it != LRU.end(); it++)
		{
			if (node != nullptr && *it != nullptr && node == *it)
			{
				flag = true;
				break;
			}
		}

		//* Bước 2: nếu nó tồn tại thì chuyển nó lên đầu danh sách
		//*         nếu không thì insert vào đầu danh sách
		if (flag)
		{
			LRU.splice(LRU.begin(), LRU, it);
		}
		else
		{
			LRU.push_front(node);
		}
	}

	void removeNode(Node *node)
	{
		for (list<Node *>::iterator it = LRU.begin(); it != LRU.end(); it++)
		{
			if ((*it)->ID == node->ID)
			{
				LRU.erase(it);
				break;
			}
		}
	}

public:
	Sukuna_RESTAURANT() {}
	~Sukuna_RESTAURANT()
	{
		for (unsigned int i = 0; i < Zone_Manage.size(); i++)
		{
			delete Zone_Manage[i];
			// COUNTDELETE++;
		}
	}

	void insert_to_AreaTable(int result)
	{
		int ID = result % MAXSIZE + 1;
		//* Step 1: kiểm tra xem heap có đang quản lí khu ID hay không? nếu chưa quản lí thì phải thêm ở bước sau
		int index = -1;

		for (unsigned int i = 0; i < Zone_Manage.size(); i++)
		{
			if (ID == Zone_Manage[i]->ID)
			{
				index = i;
				break;
			}
		}

		//* Step 2: do chưa được quản lý nên phải thêm vô
		if (index == -1)
		{
			Zone_Manage.push_back(new Node(ID));
			// COUNTDELETE--;
			index = Zone_Manage.size() - 1;
			Zone_Manage[index]->insert(result);
			this->move_to_Top(Zone_Manage[index]);
			this->reheapUp(index);
		}
		//*bước 3: thêm khách hàng mới vào khu khách hàng muốn thêm vào
		//*        và tiến hành reheapDown bàn này xuống vì có số khách đông hơn
		else
		{
			Zone_Manage[index]->insert(result);
			this->move_to_Top(Zone_Manage[index]);
			this->reheapDown(index);
		}
	}

	void KEITEIKEN(int number) //* remove
	{
		if (Zone_Manage.size() <= 0)
			return;

		//* TẠO ra heap mới sao chép từ heap cũ
		vector<Node *> new_ZoneManage(Zone_Manage.begin(), Zone_Manage.end());
		queue<Node *> DeleteList; //! danh sách các khu cấn xóa
		for (int i = 0; Zone_Manage.size() && i < number; i++)
		{
			//* lấy ra phần tử đầu tiên trong heap
			Node *nodeDelete = Zone_Manage[0];
			swap(Zone_Manage[0], Zone_Manage[Zone_Manage.size() - 1]);
			Zone_Manage.pop_back();
			this->reheapDown(0);

			//* đưa vào danh sách cần xóa
			DeleteList.push(nodeDelete);
		}

		//* trả lại heap
		Zone_Manage = new_ZoneManage;

		//* đuổi num khách hàng tại num khu vực
		while (DeleteList.size())
		{
			//* lấy ra khu đang ở đầu đầu heap xóa number khách hàng đầu linklist
			Node *nodeDelete = DeleteList.front();
			DeleteList.pop();

			nodeDelete->remove(number);

			//* tìm vị trí của nó trong heap
			int index = 0;
			while (Zone_Manage[index] != nodeDelete)
				index++;

			//* trường hợp xóa hết thì xóa nó trong heap sau đó reheapDown khu xuống vì đang ở đầu hàng
			if (nodeDelete->size() == 0)
			{
				swap(Zone_Manage[index], Zone_Manage[Zone_Manage.size() - 1]);
				//! xóa nó khỏi danh sách liên kết
				this->removeNode(Zone_Manage[Zone_Manage.size() - 1]);
				delete Zone_Manage[Zone_Manage.size() - 1];
				// COUNTDELETE++;

				//! xóa trong heap nữa
				Zone_Manage.pop_back();
			}
			this->reheapDown(index);
		}
	}

	void print_preOrder(unsigned int index, int number)
	{
		if (index >= this->Zone_Manage.size() || number <= 0)
			return;
		this->Zone_Manage[index]->print(number);
		print_preOrder(index * 2 + 1, number);
		print_preOrder(index * 2 + 2, number);
	}
	void LIMITLESS(int number) { print_preOrder(0, number); }

private:
	class Node
	{
	private:
		int ID;
		list<int> head;
		friend class Sukuna_RESTAURANT;

	public:
		Node(int ID) : ID(ID) {}
		int size() const { return head.size(); }
		void insert(int result) { head.push_front(result); }
		void remove(int number)
		{
			while (number != 0 && !head.empty())
			{
				solution << head.back() << "-" << ID << "\n";
				head.pop_back();
				number--;
			}
		}
		void print(int number)
		{
			for (list<int>::iterator it = head.begin(); number > 0 && it != head.end(); ++it, --number)
			{
				solution << ID << "-" << *it << "\n";
			}
		}
	};
};
//*-------------------------------------------------------------------------------------------------------------------

//********************************************************************************************************************
class HuffTree_AVL
{
	class Node;

private:
	Node *root = nullptr;

public:
	~HuffTree_AVL() { clear(root); }
	void clear(Node *node)
	{
		if (node)
		{
			clear(node->left);
			clear(node->right);
			delete node;
			// COUNTDELETE++;
		}
	}

	vector<pair<char, int>> sort(vector<pair<char, int>> freq)
	{

		vector<pair<char, int>> newFreq;

		// int size = freq.size();
		while (!freq.empty())
		{
			pair<char, int> maxFreq = freq[0];
			for (auto &pair : freq)
			{
				if (pair.second > maxFreq.second)
				{
					maxFreq = pair;
				}
				else if (pair.second == maxFreq.second)
				{
					bool check1 = isupper(pair.first) ? true : false;
					bool check2 = isupper(maxFreq.first) ? true : false;

					if (check1 && !check2)
					{
						maxFreq = pair;
					}
					else if (!check1 && check2)
					{
						maxFreq = maxFreq;
					} //* pair thuong Max Hoa => giữ nguyên || pair Hoa max Hoa => so sánh giá trị
					  //*                                   || pair thường max thường => so sánh giá trị
					else if (pair.first > maxFreq.first)
					{
						maxFreq = pair;
					}
				}
			}
			newFreq.push_back(maxFreq);

			char remove = maxFreq.first;
			auto it = std::remove_if(freq.begin(), freq.end(),
									 [remove](const std::pair<char, int> &p)
									 { return p.first == remove; });
			freq.erase(it);
		}

		return newFreq;
	}

	//* đầu vào là 1 chuỗi -> đầu ra chuỗi name đã được mã hóa Caesar và trả về danh sách freq có thứ tự giảm dần
	vector<pair<char, int>> string_Processing(string &name)
	{
		//* bước 1: liệt kê tuần suất xuất hiện của các kí tự riêng biệt trong tên của khách hàng (phân biệt hoa và thường)
		//* tạo thành một danh sách theo vị trí của các kí tự vào trước và vào sau
		//! VD: name = "aDdbaaabbb" -> kết quả bước này: freq_prev = [{a, 4}, {D,1}, {d,1}, {b,4}]

		map<char, int> freq_char;
		for (char c : name)
		{
			freq_char[c]++;
		}

		vector<pair<char, int>> freq_prev;
		for (const auto &pair : freq_char)
		{
			freq_prev.push_back(pair);
		}


		if (freq_prev.size() < 3)
			return {};
		//* bước 2: mã hóa Caesar chuỗi name thành chuỗi mới và mã hóa luôn freq_prev
		//! VD : name = "aDdbaaabbb", freq_prev = [{a, 4}, {D,1}, {d,1}, {b,4}]
		//! kq : name = "eEefeeefff", freq_prev = [{e,4}, {E,1}, {e,1}, {f,4}]

		int k = 0;
		for (unsigned int i = k; i < name.size(); i++)
		{
			for (auto &pair : freq_prev)
			{
				if (name[i] == pair.first)
				{
					char base = isupper(pair.first) ? 'A' : 'a';
					name[i] = base + (name[i] - base + pair.second) % 26;
					k++;
					break;
				}
			}
		}

		for (auto &pair : freq_prev)
		{
			char base = isupper(pair.first) ? 'A' : 'a';
			pair.first = base + (pair.first - base + pair.second) % 26;
		}

		//* bước 3: + dồn freq_prev với các kí tự giống nhau sau khi mã hóa
		//! VD: freq_prev = [{e,4}, {E,1}, {e,1}, {f,4}] =>>>  freq = [{e,5}, {E,1}, {f,4}]
		vector<pair<char, int>> freq;
		for (auto &pair : freq_prev)
		{
			if (freq.empty())
			{
				freq.push_back(pair);
			}
			else
			{
				bool flag = false; //* chưa có trong freq
				for (auto &pair1 : freq)
				{
					if (pair1.first == pair.first)
					{
						pair1.second += pair.second;
						flag = true;
						break;
					}
				}

				if (!flag)
				{
					freq.push_back(pair);
				}
			}
		}

		//* bước 4: sort chuỗi freq mới tìm được phía trên theo chiều giảm dần
		//^ chú ý nếu tuần suất hiện bằng nhau thì kí tự nào lớn hơn thì lớn hơn, kí tự hoa lớn hơn kí tự thường
		freq = sort(freq);

		return freq;
	}

	int getHeight(Node *node)
	{
		if (node == nullptr)
			return 0;

		return 1 + max(getHeight(node->left), getHeight(node->right));
	}

	int getBalance(Node *node)
	{
		//* node null thì cây balanced
		if (node == nullptr)
			return 0;

		//* Get left height và right height để tính độ cân bằng balance
		int leftHei = getHeight(node->left);
		int rightHei = getHeight(node->right);

		return (leftHei - rightHei);
	}

	Node *leftRotate(Node *node, int &count)
	{
		//* trước khi xoay, kiểm tra count >=3 chưa? rồi thì ko xoay => return node;
		if (count >= 3)
		{
			return node;
		}
		//* chưa thì tăng count và tiến hành xoay
		count++;

		Node *k1 = node->right;
		Node *k2 = k1->left;

		node->right = k2;
		k1->left = node;

		//*Cập nhập Height cho node rồi tới k1
		node->height = getHeight(node);
		k1->height = getHeight(k1);

		return k1;
	}

	Node *rightRotate(Node *node, int &count)
	{
		if (count >= 3)
		{
			return node;
		}

		count++;

		Node *k1 = node->left;
		Node *k2 = k1->right;

		node->left = k2;
		k1->right = node;

		//* Cập nhập Height cho node trước rồi tới k1
		node->height = getHeight(node);
		k1->height = getHeight(k1);

		return k1;
	}

	Node *balanceNode(Node *node, int &count)
	{

		//* Xét xem đang cân bằng loại nào? và nếu count >= 3 thì stop
		int balance = getBalance(node);
		if (count >= 3)
			return node;

		//* Left of Left (LL) => Mất cân bằng trái => xoay phải
		if (balance > 1 && getBalance(node->left) >= 0)
		{
			return rightRotate(node, count);
		}
		//* Right of Right (RR) => mất cân bằng phải => xoay trái
		if (balance < -1 && getBalance(node->right) <= 0)
		{
			return leftRotate(node, count);
		}
		//* Left of Right (LR) => thì xoay trái thằng node->left trước, rồi xoay phải node
		if (balance > 1 && getBalance(node->left) < 0)
		{
			node->left = leftRotate(node->left, count);
			return rightRotate(node, count);
		}
		//* Right of Left (RL) => thì xoay phải thằng node->right trước, rồi xoay trái node
		if (balance < -1 && getBalance(node->right) > 0)
		{
			node->right = rightRotate(node->right, count);
			return leftRotate(node, count);
		}

		return node;
	}

	//* tiến hành đệ quy theo preOrder -> nếu count >= 3 thì dừng lại không cân bằng nữa
	Node *balanceTree(Node *node, int count = 0)
	{
		if (count == 1 || node == nullptr)
		{
			return node;
		}

		node = balanceNode(node, count);

		if (node->left)
			node->left = balanceTree(node->left, count);

		if (node->right)
			node->right = balanceTree(node->right, count);

		return node;
	}

	Node *buildHuffTree(vector<pair<char, int>> freq)
	{
		//* Step 1 : chuyển freq thành build (thành các node riêng biệt)
		vector<Node *> build;
		for (const auto &pair : freq)
		{
			build.push_back(new Node(pair.second, pair.first));
			// COUNTDELETE--;
		}

		while (build.size() > 1)
		{

			Node *newNode = nullptr;

			Node *left = build[build.size() - 1];
			build.pop_back();
			Node *right = build[build.size() - 1];
			build.pop_back();

			int weight = left->weight + right->weight;
			// int height = right->height + 1;

			newNode = new Node{weight, '\0', left, right};
			newNode->height = getHeight(newNode);
			// COUNTDELETE--;
			//* Cân bằng AVL TREE
			newNode = balanceTree(newNode);
			newNode = balanceTree(newNode);
			newNode = balanceTree(newNode);

			//* sau khi có newNode thì thêm vào build
			//* Sau đó so sánh với các node hiện có
			//^ nếu key bằng nhau thì xem newnode lớn hơn
			build.push_back(newNode);
			for (int i = build.size() - 1; i > 0; i--)
			{
				if (build[i - 1]->weight <= build[i]->weight)
				{
					std::swap(build[i - 1], build[i]);
				}
				else
				{
					break;
				}
			}
		}
		return build[0];
	}

	void encoding_REC(vector<string> &encoding, Node *node, string s = "")
	{
		if (node->left == nullptr && node->right == nullptr)
		{
			encoding[node->c] = s;
			return;
		}

		encoding_REC(encoding, node->left, s += '0');

		s = s.erase(s.size() - 1);
		encoding_REC(encoding, node->right, s += '1');
	}
	//* đầu vào là 1 cây và name đã được mã hóa Caesar -> đầu ra là result kết quả cần tìm.
	int encodingHuff(Node *root, string nameCaesar)
	{
		if (root->left == nullptr && root->right == nullptr)
			return 0;

		//* Step 1: đi tính chuỗi mã hoá binary của các kí tự đã mã hóa
		vector<string> encoding_to_binary(256, "");
		encoding_REC(encoding_to_binary, root);

		//* Step 2: lấy ra 10 kí tự nhị phân cuối sau khi mã hóa nameCaesar thành mã nhị phân lấy từ phải đên trái
		//* nameCaesar = "aab"; => 001
		string encod;
		for (int i = nameCaesar.size(); i >= 0; i--)
		{
			encod = encoding_to_binary[nameCaesar[i]] + encod;

			if (encod.length() > 10)
			{
				break;
			}
		}
		if (encod.length() > 10)
		{
			int lenCut = 10;
			int startIndex = encod.length() - lenCut;
			encod = encod.substr(startIndex, lenCut);
		}
		reverse(encod.begin(), encod.end());

		//* bước 3 mã hóa binary sang thập phân, dùng std::stoi
		int result = 0;
		if (!(root->left == nullptr && root->right == nullptr))
		{
			result = std::stoi(encod, nullptr, 2);
		}

		return result;
	}

	int encode(string name)
	{

		//* bước 1 xử lí chuỗi thu được list để tới phần sau
		vector<pair<char, int>> freq = this->string_Processing(name);
		if (freq.size() == 0)
			return -1;

		this->clear(root);
		root = this->buildHuffTree(freq);
		if (root->left == nullptr && root->right == nullptr)
			return 0;

		int result = this->encodingHuff(root, name);

		return result;
	}

	void print_REC(Node *node)
	{
		if (node == nullptr)
			return;
		print_REC(node->left);
		if (node->c == '\0')
			solution << node->weight << "\n";
		else
			solution << node->c << "\n";
		print_REC(node->right);
	}
	void print_HAND() { print_REC(root); }

private:
	class Node
	{
	public:
		int weight;
		int height;
		char c;
		Node *left;
		Node *right;
		friend class HuffTree_AVL;

	public:
		Node(int weight, char c = '\0', Node *left = nullptr, Node *right = nullptr) : weight(weight), c(c), left(left), right(right) {}
	};
};
//*-------------------------------------------------------------------------------------------------------------------

class JJK_RESTAURANT
{
private:
	HuffTree_AVL New_Customer;
	Gojo_RESTAURANT hash;
	Sukuna_RESTAURANT heap;

public:
	void LAPSE(string name)
	{

		if (name[0] >= '0' && name[0] <= '9') //! BỎ lúc nộp
		{
			int result = stoi(name);
			if (result % 2 == 1)
				hash.insert_to_AreaTable(result);
			else
				heap.insert_to_AreaTable(result);
			return;
		}

		int result = New_Customer.encode(name);
		if (result == -1)
			return;

		if (result % 2 == 1)
			hash.insert_to_AreaTable(result);
		else
			heap.insert_to_AreaTable(result);
	}

	//* Xử lý các Command ở nhà hàng GOJO
	void KOKUSEN()
	{
		hash.KOKUSEN();
	}
	void LIMITLESS(int num)
	{
		hash.LIMITLESS(num);
	}

	//* Xử lý các Command ở nhà hàng SUKUNA
	void KEITEIKEN(int num)
	{
		heap.KEITEIKEN(num);
	}
	void CLEAVE(int num)
	{
		heap.LIMITLESS(num);
	}

	//* in ra HuffTree_AVL
	void HAND()
	{
		New_Customer.print_HAND();
	}
};

void simulate(string filename)
{

	ifstream ss(filename);
	string input_str, name;
	int num;

	ss >> input_str;
	ss >> MAXSIZE;

	JJK_RESTAURANT *CALL_COMMAND = new JJK_RESTAURANT();

	while (ss >> input_str)
	{
		if (input_str == "LAPSE") // LAPSE <NAME>
		{
			ss >> name;
			CALL_COMMAND->LAPSE(name);
		}
		else if (input_str == "KOKUSEN") // KOKUSEN
		{
			CALL_COMMAND->KOKUSEN();
		}
		else if (input_str == "KEITEIKEN") // KEITEIKEN <NUM>
		{
			ss >> num;
			CALL_COMMAND->KEITEIKEN(num);
		}
		else if (input_str == "HAND") // HAND
		{
			CALL_COMMAND->HAND();
		}
		else if (input_str == "LIMITLESS") // LIMITLESS <NUM>
		{
			ss >> num;
			CALL_COMMAND->LIMITLESS(num);
		}
		else if (input_str == "CLEAVE") // CLEAVE <NUM>
		{
			ss >> num;
			CALL_COMMAND->CLEAVE(num);
		}
	}
	delete CALL_COMMAND;
}
