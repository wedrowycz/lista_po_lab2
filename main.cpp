#include "List.h"
#include "Point.h"
int main() {
	List list;

	//List::Error error = list.pop_back();
	//List::Error error = list.push_back();
	List::Error error;
	Point* punkt = new Point(19,19,19);

	Point punkt2 = Point(17,17,17);

	Point punkt3 = Point(21, 21, 21);

	error = list.push_back(*punkt);
	error = list.push_back(punkt2);
	//error = list.push_back(punkt3);
	const int j = 2;
	List druga = list * 3;
	/*while (j <= 2) 
	{
		Point* p = new Point(14, 14, 14);
		for (int i = 1; i <= 1000; i++) {
			list.push_back(*p);
		}
		for (int i=1; i <= 1000; i++)
		{
			list.pop_back();
		}
	}*/

}
