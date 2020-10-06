#include "data.h"

using namespace project;
using namespace std;

data::data(){
	x=y=0;
	pc = x;
	sc = y;
}
data::data(double x1, double y1){
	x=x1;
	y=y1;
	pc = x;
	sc = y;
}
data::data(const data& cpy){
	x = cpy.x;
	y = cpy.y;
	id = cpy.id;
	pc = cpy.pc;
	sc = cpy.sc;
}
data::data(double x1, double y1, int id1){
	x = x1;
	y = y1;
	id = id1;
	pc = x;
	sc = y;
}
bool data::operator<(const data& d){
	if(pc < d.pc) return true;
	if(pc == d.pc && sc < d.sc) return true;
	return false;
}
bool data::operator==(const data& d){
	return (pc == d.pc) && (sc == d.sc);
}
bool data::operator>(const data& d){
	return !( ((*this) < d) || ((*this) == d));
}
bool data::operator<=(const data& d){
	return ((*this) < d) || ((*this) == d);
}
void data::setPrimaryCoordinate(int primaryCoordinate){
	if(primaryCoordinate == 1){
		pc = x;
		sc = y;
	}
	else if(primaryCoordinate == 2){
		pc = y;
		sc = x;
	}
}
