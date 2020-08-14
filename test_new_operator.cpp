#define _SELF_

class EquipmentPiece
{
private:
	int IDNumber;
public:
	EquipmentPiece() :IDNumber(0) {}
	EquipmentPiece(int IDNumber) :IDNumber(IDNumber) {}

	const int ID()
	{
		return this->IDNumber;
	}
};


#ifdef _SELF_

#include "new.cpp"
#include <stdio.h>

int main()
{
	void* raw_pointer = operator new(sizeof(EquipmentPiece));
	EquipmentPiece* e_pointer = static_cast<EquipmentPiece*>(raw_pointer);
	new(e_pointer)   EquipmentPiece(1234);
	printf("%d\n", e_pointer->ID());
	(*e_pointer).~EquipmentPiece();
	operator delete(raw_pointer);
	return 0;
}



#endif // _SELF_


#ifdef _STD_
#include <stdio.h>

int main(int argc, char** argv)
{
	void* raw_pointer_5 = operator new(5 * sizeof(int));
	int* int_pointer_5 = static_cast<int*>(raw_pointer_5);

	for (int i = 0; i < 5; ++i)
		int_pointer_5[i] = i + 2;

	for (int i = 0; i < 5; ++i)
		printf("%d  ", int_pointer_5[i]);

	operator delete(raw_pointer_5);

	return 0;
}

#endif // _STD_
