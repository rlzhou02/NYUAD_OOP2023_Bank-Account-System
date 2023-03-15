
#define accountstorenumber  10


using namespace std;



//Template class, OOP concept
template <class T>
class AccountStore {
private:
	//private members allows data hiding
	int max_index; //record the current allocated memory, the value increases due to need
	int currentIndex; //record the current index
	T** accounts;  /*dynamic memory allocation allow expansion of T* size, Optimization
				   each member in accounts is of type T*, record the address of T
				   such that when account is no longer needed, the space is freed and T* that used to record the address 
				   of the deleted account can record the address of newly created accounts*/
	int number_of_accounts;
	int allocateTimes;
	static int accountid;
	static double total; //total amount in the system
	vector<int> address; //this vector<int> is used to record the index of current empty T*
						 //the empty T* is caused due to account deletion
	T* emptyaccount;
	double rate; //rate for interest calculation

	//inline funtion, Optimization
	inline void creationdeletionprint(int i,string s) {
		cout << "----------------------------------------------------------" << endl;
		cout << "Account " <<s<< " at location " << i << " successfully." << endl;
		accounts[i]->printclose();
		cout << "----------------------------------------------------------" << endl;
	}


public:

	//constructor
	AccountStore() {
		cout << "Welcome to the account management system." << endl;
		cout << "----------------------------------------------------------" << endl;
		max_index = accountstorenumber - 1;
		currentIndex = 0;
		accounts = new T * [accountstorenumber];
		//initialize account
		for (int i = 0; i < accountstorenumber; i++) {
			accounts[i] = NULL;
		}
		number_of_accounts = 0;
		total = 0;
		allocateTimes = 1;
		rate = 0.05;
	}

	//copy constructor
	//allows the use of const objects for account system infomation backup at particular time, OOP concept
	AccountStore(AccountStore& accstr) {
		max_index = accstr.getmaxIndex();
		currentIndex = accstr.getcurrentIndex();
		accounts = new T * [currentIndex];
		for (int i = 0; i < currentIndex; i++) {
			accounts[i] = new T(accstr.GetAccount(i)->getAccountNumber(), accstr.GetAccount(i)->getBalance());
			if (accstr.GetAccount(i)->getAccountNumber() == 0) {
				delete accounts[i];
				accounts[i] = NULL;
			}
		}
		number_of_accounts = accstr.GetNumberOfAccounts();
	}

	//setters and getters
	void setrate(double r) {
		rate = r;
	}

	int getcurrentIndex() {
		return currentIndex;
	}


	//const function, OOP concept
	//allows the access of const objects for account system infomation backup
	int GetNumberOfAccounts() const {
		return number_of_accounts;
	}

	int Gettotal() {
		return total;
	}

	int getmaxIndex() {
		return max_index;
	}

	//create new account in this account system
	void CreateAccount(int balance) {
		if (number_of_accounts <= max_index) {
			accountid++;
			int pos;
			/*use vetors to manage account spaces, Optimization
			address is used to record the index of current empty T*
			address.back(); address.pop_back(); reduces the need to linear search for empty address */
			if (!address.empty()) {
				pos = address.back();
				address.pop_back();
				accounts[pos] = new T(accountid, balance);
				number_of_accounts++;
				creationdeletionprint(pos, "created");
			}
			//if there is no space from deleted accounts' address pointers, record the address in new space
			else {
				accounts[currentIndex] = new T(accountid, balance);
				number_of_accounts++;
				creationdeletionprint(currentIndex, "created");
				currentIndex++;
			}

		}
		else {
			//allocate new space equal to accountstorenumber for accounts, uses dynamic memory allocation, Optimization
			T** ptraccount;
			ptraccount = accounts;
			max_index = accountstorenumber + max_index;
			accounts = new T * [max_index + 1];
			for (int i = 0; i < currentIndex; i++) {
				accounts[i] = ptraccount[i];
			}
			accounts[currentIndex] = new T(accountid, balance);
			delete[] ptraccount;
			number_of_accounts++;
			creationdeletionprint(currentIndex, "created");
			currentIndex++;
		}

	}


	//delete account by index
	void DeleteAt(int i) {
		/*use vectors to manage account spaces, Optimization
			address is used to record the index of current empty T*
			address.push_back(i); record the index    */
		if (i <= max_index && accounts[i] != NULL) {
			creationdeletionprint(i,"deleted");
			delete accounts[i];  //use T* for array account type, Optimization
			                     //immediate free up of not needed memory
			accounts[i] = NULL;
			number_of_accounts--;
			address.push_back(i);
		}
		else {
			cout << "---WARNING!---" << endl;
			cout << "Deletion failure, no active account at index " << i << endl;
			cout << "--------------" << endl;
		}

	}
    
	//delete account by account index
	void DeleteById(int n){
		int i = getAccountIndexById(n);
		if (i>-1){
			DeleteAt(i);
		}else{
			cout << "---WARNING!---" << endl;
			cout << "Deletion failure, no active account with A/C no. " << n << endl;
			cout << "--------------" << endl;
		}

	}


	//return account, if invalid access, return empty account, this is to avoid access issues due to NULL pointers in case the 
	//GetAccount(int i) is followed by functions from Account/savingAccount/loanAccount class.
	T* GetAccount(int i) {
		if (i <= max_index && accounts[i] != NULL) {
			return accounts[i];
		}
		else {
			cout << "---WARNING!---" << endl;
			cout << "Invalid access, no active account at index " << i << ", empty account will be returned" << endl;
			cout << "--------------" << endl;
			emptyaccount = new T(0, 0);
			return emptyaccount;
		}
	}

	//another version of getaccount, copy is returned, invalid access results in returning NULL pointer
	T* GetAccountCopy(int i) {
		if (i <= max_index && accounts[i] != NULL) {
			emptyaccount = new T(accounts[i]->getAccountNumber(), accounts[i]->getBalance());
			return emptyaccount;
		}
		else {
			return NULL;
		}
	}

	//calculate the total number
	double caltotal() {
		total = 0;
		for (int i = 0; i < currentIndex; i++) {
			if (accounts[i] != NULL) {
				total = total + accounts[i]->getBalance();
			}
		}
		return total;
	}


	//calculat the interest
	void calinterest() {
		for (int i = 0; i < currentIndex; i++) {
			if (accounts[i] != NULL) {
				accounts[i]->credit(accounts[i]->getBalance() * rate);
			}
		}
	}

	//print function
	void print() const {
		cout << "----------------------------------------------------------" << endl;
		cout << "Here is the list of all the active accounts at current time." << endl;
		for (int i = 0; i < currentIndex; i++) {
			if (accounts[i] != NULL) {
				cout << i << endl;
				accounts[i]->printclose();
			}
		}
		cout << "----------------------------------------------------------" << endl;
	}

	//account search, linear search, return copy of the account
	T getAccountById(int n) const {
		for (int i = 0; i < currentIndex; i++) {
			if (accounts[i] != NULL) {
				if (accounts[i]->getAccountNumber() == n) {
					return T(accounts[i]->getAccountNumber(), accounts[i]->getBalance());
				};
			}
		}
		cout << "---WARNING!---" << endl;
		cout << "Requested account do not exist, empty account will be returned." << endl;
		cout << "--------------" << endl;
		return T(0, 0.0);
	}

	//account search, linear search, return the index
	int getAccountIndexById(int n) const {
		for (int i = 0; i < currentIndex; i++) {
			if (accounts[i] != NULL) {
				if (accounts[i]->getAccountNumber() == n) {
					return i;
				};
			}
		}
		cout << "---WARNING!---" << endl;
		cout << "Requested account do not exist, -1 returned." << endl;
		cout << "--------------" << endl;
		return -1;
	}

	//destructor
	~AccountStore() {
		for (int i = 0; i < currentIndex; i++) {
			if (accounts[i] != NULL) {
				delete accounts[i];
				accounts[i] = NULL;
			}
		}
		delete[] accounts;
	}

};

//static variables initialization
template<>
int AccountStore < savingAccount >::accountid = 10000; //starting value of accountid
template<>
int AccountStore < loanAccount >::accountid = 60000;
template<>
double AccountStore < savingAccount >::total = 0.0;
template<>
double AccountStore < loanAccount >::total = 0.0;

