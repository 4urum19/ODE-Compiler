#ifndef READODEH
#define READODEH

#include <vector>
#include <string>
#include <tuple>
#include <boost/numeric/odeint.hpp>

#include "expression.h"

struct ODE {
	//Name of a variable
	std::vector<std::string> varNames;
	//Expression associated with a variable
	std::vector<Expr*> varValues;
	//Interval of each variable
	std::vector<std::pair<double, double>> interval;
	//Time duration of the ODE
	double time;
};

class ODESystem {
public:
	~ODESystem() {
		for (int i = 0; i < (int)ODES.size(); i += 1) {
			for (auto& e: ODES[i].varValues) {
				delete e;
			}
		}
	}

	int readODESystem(std::ifstream& inp, const bool scaled);

	std::string parseVar(std::string& inp);
	std::pair<double, double> parseInterval(std::string &inp);
	double parseTime(std::string &inp);
	void parseEmit(std::string &inp);
	void setScalars(ODE o);

	void simulate();

	std::vector<var> extractConstants(const ODE& ode) const;
	std::vector<var> extractVariables(const ODE& ode) const;
private:
	std::vector<ODE> ODES;
	std::unordered_map<std::string, std::string> global;
};

#endif