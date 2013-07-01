#ifndef _NORMAL2INC_H_
#define _NORMAL2INC_H_

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class NormalTrans
{
public:
    NormalTrans();
    ~NormalTrans();

    void transtoinc(int argc, char* argv[]);
    void parse();

	void setinput(std::ifstream &in);
	void setoutput(std::ofstream &out);

private:
	std::istream input;
	std::ostream output;

    std::vector<std::string> declare;
    std::vector<std::string> init;
    std::vector<std::string> incr;
    std::vector<std::string> goal;


    std::string actiontime;
    std::string fluenttime;
    std::string querylabel;

    void outputrule(const std::vector<std::string> &vec);
    bool getlineofrule(std::string &line);
    void pushrules(std::vector<std::string> &vec, std::string line, bool flag=false);

	bool inpair(std::string &line, int count);

};


#endif // _NORMAL2INC_H_
















