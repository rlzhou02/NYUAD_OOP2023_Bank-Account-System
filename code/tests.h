using namespace std;

//tests
void test1() {
	AccountStore<savingAccount> accounts;
	for (int i = 0; i < 10; i++) {
		accounts.CreateAccount(1000 + i * 10);
	}
	accounts.print();
	cout << accounts.GetNumberOfAccounts() << endl;
	cout << accounts.GetAccount(6)->getBalance() << endl;
	accounts.GetAccount(6)->credit(200);
	cout << accounts.GetAccount(6)->getBalance() << endl;
	accounts.DeleteAt(4);
	accounts.DeleteAt(4);
	accounts.DeleteAt(5);
	accounts.DeleteAt(6);

	for (int i = 0; i < 10; i++) {
		accounts.CreateAccount(100 + i * 10);
	}
	accounts.print();
	for (int i = 0; i < 10; i++) {
		accounts.GetAccount(i)->debit(150);
	}

	accounts.calinterest();

	accounts.print();
	cout << accounts.caltotal() << endl;
	for (int i = 0; i < 8; i++) {
		accounts.DeleteAt(i * 2);
	}
	accounts.GetAccount(100)->print();
	cout << accounts.GetNumberOfAccounts() << endl;
	accounts.CreateAccount(122);
	cout << accounts.GetNumberOfAccounts() << endl;
	cout << accounts.caltotal() << endl;
	savingAccount atest = accounts.getAccountById(1018);
	atest.printclose();


	const AccountStore<savingAccount> accountscopy = accounts;
	accountscopy.print();
	savingAccount savingtest = accountscopy.getAccountById(10002);
	savingtest.print();
	for (int i = 0; i < 10; i++) {
		accounts.GetAccount(i)->printHistory();
	}
}


void test2() {
	AccountStore<loanAccount> accounts;
	for (int i = 0; i < 10; i++) {
		accounts.CreateAccount(1000 + i * 10);
	}
	accounts.print();
	cout << accounts.GetNumberOfAccounts() << endl;
	cout << accounts.GetAccount(6)->getBalance() << endl;
	accounts.GetAccount(6)->credit(200);
	cout << accounts.GetAccount(6)->getBalance() << endl;
	for (int i = 0; i < 10; i++) {
		accounts.GetAccount(i)->repayment(1500);
	}
	for (int i = 0; i < 10; i++) {
		accounts.GetAccount(i)->credit(500 + i * 12.5);
	}
	for (int i = 5; i < 15; i++) {
		accounts.GetAccount(i)->credit(50 + i * 12.5);
	}
	accounts.DeleteAt(4);
	accounts.DeleteAt(4);
	accounts.DeleteAt(5);
	accounts.DeleteAt(6);
	accounts.print();
	cout << accounts.caltotal() << endl;
	for (int i = 0; i < 8; i++) {
		accounts.DeleteAt(i * 2);
	}
	for (int i = 0; i < 10; i++) {
		accounts.GetAccount(i)->repayment(1500);
	}

	accounts.GetAccount(100)->print();
	cout << accounts.GetNumberOfAccounts() << endl;
	accounts.CreateAccount(122);
	cout << accounts.GetNumberOfAccounts() << endl;
	cout << accounts.caltotal() << endl;

	for (int i = 0; i < 10; i++) {
		accounts.CreateAccount(1000 + i * 10);
	}

	accounts.print();
	accounts.calinterest();
	accounts.print();

	const AccountStore<loanAccount> accountscopy = accounts;
	accountscopy.print();
	loanAccount loantest = accountscopy.getAccountById(60016);
	loantest.print();
	for (int i = 0; i < 10; i++) {
		accounts.GetAccount(i)->printHistory();
	}

	cout << accounts.getAccountIndexById(6006) << endl;
	cout << accounts.getAccountIndexById(60016) << endl;
	accounts.DeleteById(60016);
	accounts.DeleteById(600);

}


void test3() {
	loanAccount testa(80036, 0.0);
	for (int i = 0; i < 5; i++) {
		testa.credit(50);
	}
	for (int i = 0; i < 10; i++) {
		testa.repayment(5 * i);
	}
	testa.printHistory();
}


void test4() {
	savingAccount testa(20735, 0.0);
	for (int i = 0; i < 5; i++) {
		testa.credit(50);
	}
	for (int i = 0; i < 10; i++) {
		testa.debit(5 * i);
	}
	testa.printHistory();


	savingAccount testb(0, 0.0);
	cout<<testb.Numtranctions()<<endl;

}