#ifndef _ASSOLIST_H_
#define _ASSOLIST_H_

#include <vector>
#include <string>
#include <ostream>

class AssoList
{
public:
AssoList(std::string & mactionName)
	:macroActionName(mactionName),
		realActionName("")
	{
		assoListA.clear();
		assoListB.clear();
	}

	std::string getListName() const {return macroActionName;}

	void printAssoList(std::ostream &out) const
	{
		out << "###LIST###" << "[" <<
			macroActionName << ", {";

		for (int i = 0; i < assoListA.size()-1; ++i)
		{
			out << assoListA[i] << ",";
		}
		out << assoListA.back() << "}, {";
		for (int i = 0; i < assoListB.size()-1; ++i)
		{
			out << assoListB[i] << ",";
		}
		out << assoListB.back() << "}]" << std::endl;
	}

	std::string macroActionName;
	std::string realActionName;

	std::vector<std::string> assoListA;
	std::vector<std::string> assoListB;
};

#endif // _ASSOLIST_H_
