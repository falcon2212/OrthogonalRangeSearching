#ifndef DATA
#define DATA
namespace project{
	class data
	{
		public:
			// variables
			double x, y, pc, sc;
			int id;
			// constructors
			data();
			data(double x1, double y1);
			data(double x1, double y1, int id);
			data(const data& cpy);
			// functions
			void setPrimaryCoordinate(int pc);
			bool operator<(const data&);
			bool operator>(const data&);
			bool operator==(const data&);
			bool operator<=(const data&);

	};
}
#endif