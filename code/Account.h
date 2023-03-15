
using namespace std;


//this is the base class account 
class Account {
protected:
	int accountNumber;
	double balance;
	vector<double> History, Balance; //record the transaction history and repective balance
	vector<string> type; //record the transaction type
	int Num; //record the transaction number

public:

	//constructor
	Account(int num, double bal) {
		accountNumber = num;
		balance = bal;
		Num = 0;
	}

	//constructor
	Account(int num) {
		accountNumber = num;
		balance = 0.0;

	}

	//setters and getters
	int getAccountNumber() const {
		if (accountNumber != 0) {
			//accountNumber = 0  refers to the empty account that is created due to error handling of invalid access, 
			//this empty account is not a valid account for manipulation
			return accountNumber;
		}else{
			cout << "---WARNING!---" << endl;
		    cout << "Requested account is not valid, -1 returned." << endl;
		    cout << "--------------" << endl;
			return -1;
		}
		
	}

	double getBalance() const {
		if (accountNumber != 0) {
			return balance;
		}else{
			cout << "---WARNING!---" << endl;
		    cout << "Requested account is not valid, -1 returned." << endl;
		    cout << "--------------" << endl;
			return -1;
		}
	}

	int Numtranctions() const {
		if (accountNumber != 0) {
			return Num;
		}else{
			cout << "---WARNING!---" << endl;
		    cout << "Requested account is not valid, -1 returned." << endl;
		    cout << "--------------" << endl;
			return -1;
		}
	}

	void setBalance(double bal) {
		if (accountNumber != 0) {
			balance = bal;
		}

	}

	//credit function, for savingAccount class, this function is used to calculate the deposit
	//for loanAccount class, the credit refers to loans borrowed from bank
	void credit(double amount) {
		if (accountNumber != 0) {
			if (amount <= 0) {
				cout << "---NOTICE!---" << endl;
				cout << "Can't credit a non-positive amount.\n";
				cout << "-------------" << endl;
				return;
			}
			else {
				//record transaction
				balance = balance + amount;
				History.push_back(amount);
				Balance.push_back(balance);
				type.push_back("Credit");
				Num++;
			}
		}
	}



	//print function for transaction history
	void printHistory() {
		if (Num > 0) {
			cout << "----------------------------------------------------------" << endl;
			printclose();
			cout << "-------------" << endl;
			int i = 0;
			for (vector<double>::iterator p = History.begin(); p != History.end(); p++) {
				i++;
				cout << "NO. " << i << "   " << "Amount  : $" << History[i - 1] << endl;
				if (type[i - 1]=="Credit"){
					cout << "Balance before " << type[i - 1] << " : $" << Balance[i - 1] - History[i - 1] << endl;
				}else{
					cout << "Balance before " << type[i - 1] << " : $" << Balance[i - 1] + History[i - 1] << endl;
				}
				cout << "Balance after " << type[i - 1] << " : $" << Balance[i - 1] << endl;
				cout << "-------------" << endl;
			}
			cout << "----------------------------------------------------------" << endl;
		}
	}



	//those functions allow printing in 2 formats
	void print() const {
		if (accountNumber != 0) {
			cout << "----------------------------------------------------------" << endl;
			printclose();
			cout << "----------------------------------------------------------" << endl;
		}

	}

	//virtual function for overriding by derived class, OOP concept
	inline virtual void printclose() const {
		if (accountNumber != 0) {
			cout.setf(ios::fixed);
			cout << "Deposit_A/C no: " << accountNumber << " Balance= $" << setprecision(2) << balance << endl;
		}

	}

};


//inheritance, OOP concept
class savingAccount : public Account {
public:

	using Account::Account; //inherit constructor from Account class


	void debit(double amount) {
		if (accountNumber != 0) {
			if (amount <= 0) {
				cout << "---NOTICE!---" << endl;
				cout << "Can't debit a non-positive amount.\n";
				cout << "-------------" << endl;
				return;
			}
			else if (amount > balance) {
				//In case withdraw is greater than balance, print the notice.
				cout << "---NOTICE!---" << endl;
				cout << "Amount withdrawn exceeds the current balance!" << endl;
				cout << "-------------" << endl;
			}
			else {
				balance = balance - amount;
				//record transaction
				Num++;
				History.push_back(amount);
				Balance.push_back(balance);
				type.push_back("Debit");
			}
		}
	}



};


class loanAccount : public Account {
public:

	using Account::Account; //inherit constructor from Account class

	void repayment(double amount) {
		if (accountNumber != 0) {
			if (amount <= 0) {
				cout << "---NOTICE!---" << endl;
				cout << "Can't repay a non-positive amount.\n";
				cout << "-------------" << endl;
				return;
			}
			else if (amount > balance) {
				//In case repayment is greater than amount due, print the notice and return extra amount.
				cout.setf(ios::fixed);
				double difference = amount - balance;
				cout << "---NOTICE!---" << endl;
				cout << "The amount due is $" << balance << ", $ " << setprecision(2) << difference << " will be returned!" << endl;
				cout << "-------------" << endl;
				History.push_back(balance);
				balance = 0;
				Num++;
				Balance.push_back(balance);
				type.push_back("Repayment");
			}
			else {
				balance = balance - amount;
				//record transaction
				Num++;
				History.push_back(amount);
				Balance.push_back(balance);
				type.push_back("Repayment");
			}
		}

	}

	//override base class printclose() function
	inline void printclose() const {
		if (accountNumber != 0) {
			cout.setf(ios::fixed);
			cout << "Loan_A/C no: " << accountNumber << " Amount due = $" << setprecision(2) << balance << endl;
		}

	}
}; 
