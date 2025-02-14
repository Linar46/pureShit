#include <iostream>
#include <string>
#include <istream>
#include <vector>
#include <chrono>
#include <typeinfo>
#include <random>
#include <algorithm>
#include <numeric>
#include <thread>



class Book {
public:
    std::string barCode;

	Book() : barCode("0000000000") {}
    Book(std::string barCode) {
        this->barCode = barCode;
    }
};

class Member {
public:
	std::string name;
	std::string id_card;

	Member() : name("John Doe"), id_card("0000000000") {}
    Member(std::string name, std::string id_card) {
        this->name = name;
        this->id_card = id_card;
    }
};

class Loan {
public:
    using nowTime = std::chrono::system_clock::time_point;
	Member member;
    Book book;
    nowTime start;
	double hours;

    Loan(Book book, Member member, double hours) {
		this->start = std::chrono::system_clock::now();
		this->member = member;
        this->book = book;
		this->hours = hours;
    }
    double check() {
        nowTime end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - this->start;
		return (this->hours - (elapsed_seconds.count() / 3600)); //hours left
    }
};

class Library {
public:
	std::vector<Book> books;
	std::vector<Member> members;
	std::vector<Loan> loans;

	void addBook(Book book) {
		books.push_back(book);
	}
	void addMember(Member member) {
		members.push_back(member);
	}
	void loanBook(Book book, Member member, double hours) {
		loans.push_back(Loan(book, member, hours));
	}

    void generteBooks() {
        for (int i = 0; i < 100; i++) {
            Book book(std::to_string(i));
            this->addBook(book);
        }
    }
    void generateMembers() {
        for (int i = 0; i < 10; i++) {
            Member member("Johny Depp", std::to_string(i));
            this->addMember(member);
        }
    }

	void generateLoans() {
		for (int i = 0; i < 10; i++) {
			this->loanBook(books[i], members[i], 10);
		}
	}

    void genAll() {
		this->generteBooks();
		this->generateMembers();
		this->generateLoans();
    }
    void print() {
		std::cout << std::to_string(this->loans[0].check()) << std::endl;
    }
};


int main()
{
    /*std::string name;
    std::getline(std::cin >> std::ws, name);
    std::string_view name2(name);
    std::cout << (name2.remove_suffix(1), name2.remove_prefix(1), name2);*/
	Library library;
	library.genAll();
    std::this_thread::sleep_for(std::chrono::seconds(5));
	library.print();
    
    return 0;
}
