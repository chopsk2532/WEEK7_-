#include <iostream> 
#include <stdexcept> 

class Test { 
public: 
	Test(char id) : id_(id) {} 
	~Test() { std::cout << "Destructor execution: " << id_ << std::endl; } 
private: char id_; 
}; 

int funcB() {
	Test r('B');
	throw std::runtime_error("Exception from funcB!\n"); 
	std::cout << "Executed in B" << std::endl; 
	return 0;
} 
int funcA() {
	Test r('A'); 
	funcB();
	std::cout << "Executed in A" << std::endl; 
	return 0;
} 

int main() { 
	try { 
		funcA(); 
	} 
	catch (std::exception& e) { 
		std::cout << "Exception : " << e.what(); 
	} 
}
/* (실습 1-1) 분석결과 :
	실행결과:	Executed in B
				Destructor execution: B
				Executed in A
				Destructor execution: A
	main함수에서 funcA()를 호출하고 funcA()에서 Test 객체 r('A') 생성하고 func(B)를 호출한다.
	func(B)에서 Test r(B)를 생성하고 cout 출력한뒤 리턴한다. 리턴할때 객체가 자동적으로 소멸되기때문에 ~Test를 실행한다.
	func(A)에서도 func(B)를 호출하고 리턴 받은 뒤 cout 출력하고 마찬가지로 리턴할때 ~Test를 실행한다.
	*/ 

/* (실습 1-2) 분석결과 :
	실행결과 :	Destructor execution: B
				Destructor execution: A
				Exception : Exception from funcB!
	1-1과 마찬가지로 func(B)까지 호출된다. 이때 Test객체 r(B)가 생성난뒤 throw가 발생했기때문에 
	바로 main함수로 오류가 던져진다. 함수들은 자동적으로 소멸되고 객체 또한 소멸되면서 ~Test들이 각각 실행된다.
	throw가 보낸 오류를 catch에서 받고 무슨 오류인지 출력한다.
	*/