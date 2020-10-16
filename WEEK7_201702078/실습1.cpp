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
/* (�ǽ� 1-1) �м���� :
	������:	Executed in B
				Destructor execution: B
				Executed in A
				Destructor execution: A
	main�Լ����� funcA()�� ȣ���ϰ� funcA()���� Test ��ü r('A') �����ϰ� func(B)�� ȣ���Ѵ�.
	func(B)���� Test r(B)�� �����ϰ� cout ����ѵ� �����Ѵ�. �����Ҷ� ��ü�� �ڵ������� �Ҹ�Ǳ⶧���� ~Test�� �����Ѵ�.
	func(A)������ func(B)�� ȣ���ϰ� ���� ���� �� cout ����ϰ� ���������� �����Ҷ� ~Test�� �����Ѵ�.
	*/ 

/* (�ǽ� 1-2) �м���� :
	������ :	Destructor execution: B
				Destructor execution: A
				Exception : Exception from funcB!
	1-1�� ���������� func(B)���� ȣ��ȴ�. �̶� Test��ü r(B)�� �������� throw�� �߻��߱⶧���� 
	�ٷ� main�Լ��� ������ ��������. �Լ����� �ڵ������� �Ҹ�ǰ� ��ü ���� �Ҹ�Ǹ鼭 ~Test���� ���� ����ȴ�.
	throw�� ���� ������ catch���� �ް� ���� �������� ����Ѵ�.
	*/