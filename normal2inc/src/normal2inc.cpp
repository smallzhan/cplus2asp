#include <iostream>
#include "normal2inc.h"

using namespace std;


NormalTrans::NormalTrans() :
    actiontime("V_astep"),
    fluenttime("V_step"),
    querylabel("query_label"),
	input(cin.rdbuf()),
	output(cout.rdbuf())
{
//    input = input.rdbuf();
//    output = cout.rdbuf();

//	input(cin.rdbuf());
//	output(cout.rdbuf());
    declare.clear();
    init.clear();
    incr.clear();
    goal.clear();
}


NormalTrans::~NormalTrans()
{
}


void NormalTrans::setinput(ifstream &in)
{
	input.rdbuf(in.rdbuf());
}

void NormalTrans::setoutput(ofstream &out)
{
	output.rdbuf(out.rdbuf());
}



bool NormalTrans::inpair(string &line, int count)
{
	int num = 0;
	for (unsigned i = 0; i < count; ++i)
	{
		if (line[i] == '(') num++;
		else if (line[i] == ')') num--;
	}
//	cout << "num=" << num << endl;
	return (num != 0);
}

void NormalTrans::pushrules(vector<string> &vec, string line, bool flag/*=false*/)
{
    unsigned int dot = line.find_first_of(".");
	unsigned int odot = 0;
    while (dot != string::npos)
    {
		if (!inpair(line, dot))
		{
			string rule = line.substr(odot, dot-odot+1);
			if (!flag || rule.find("step") == string::npos)
			{
				vec.push_back(rule);
			}
			odot = dot;
		}
//        line = line.substr(dot+1);
		//odot = dot;
        dot = line.find_first_of(".", dot+1);

    }

}

bool NormalTrans::getlineofrule(string &line)
{
	line.clear();
	const string blank = " \n\t";
    string templine;
    unsigned beg = 0;
    unsigned end = 0;
	bool flag = false;
	while (getline(input, templine))
	{
		beg = templine.find_first_not_of(blank);
		if (beg == string::npos || templine[beg] == '%')
			continue;
		end = templine.find_last_not_of(blank);
		line += templine.substr(beg, end-beg+1);
		if (templine[end] == '.')
		{
			flag = true;
			break;
		}

	}

	return flag;
}

void NormalTrans::parse()
{
    string line;
    unsigned int beg = 0;
    unsigned int end = 0;

    while (getlineofrule(line))
    {
		//cout << "line is " << line << endl;

        if (line[0] == '#')
            pushrules(declare, line);
        else
        {
            beg = line.find(querylabel);
			if (beg != string::npos)
			{
				pushrules(goal, line);
			}
			else
			{
				beg = line.find(actiontime);
				end = line.find(fluenttime);
				if (beg == string::npos && end == string::npos)
				{
					pushrules(init, line, true);
				}
				else {

                    pushrules(incr, line);
				}
            }
        }
    }
}

void NormalTrans::outputrule(const vector<string> &vec)
{
	//cout << "Now output the rules in the vector" << endl;
    for (vector<string>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        output << *it << endl;
    }

}

void NormalTrans::transtoinc(int argc, char* argv[])
{

	ifstream ifile;
	//cout << "argc = " << argc << ", argv=" << argv << endl;
	if (argc > 1)
	{
		ifile.open(argv[1]);
		input.rdbuf(ifile.rdbuf());
	}

	parse();

	//unsigned int incrsize = incr.size();
	//unsigned int goalsize = goal.size();

	for (vector<string>::iterator it = incr.begin();
		 it != incr.end();++it)
	{
		if (it->find(actiontime) == string::npos)
		{
			//output << *it << endl;
			unsigned act = it->find(fluenttime);
			string initrule(*it);
			while (act != string::npos)
			{
				//cout << "Act is " << act << " >>> " << *it << endl;
				it->replace(act, fluenttime.size(), "t");
				initrule.replace(act, fluenttime.size(), "0");
				act = it->find(fluenttime);

			}
			init.push_back(initrule);
		}
		else
		{
			unsigned act = it->find(actiontime+"+1");
			while (act != string::npos)
			{
				it->replace(act, actiontime.size()+2, "t");
				act = it->find(actiontime+"+1");
			}
			act = it->find(actiontime);
			while (act != string::npos)
			{
				it->replace(act, actiontime.size(), "t-1");
				act = it->find(actiontime);
			}
		}

		if (it->find("false :-") == 0)
		{
			it->erase(0, 6);
		}

	}


	for (vector<string>::iterator it = goal.begin();
		 it != goal.end(); ++it)
	{
		unsigned act = it->find("maxstep");
		if (act != string::npos)
		{
			it->replace(act, 7, "t");
		}
		if (it->find("false :-") == 0)
		{
			it->erase(0, 6);
		}
		act = it->find(querylabel);
		if (act != string::npos)
		{
			if (act > 0 && (*it)[act-1] == ',')
				it->erase(act-1, 15);
			else if (act > 0)
				it->erase(act, 15);
		}
	}
	output << "#base .\n";
    outputrule(declare);
    outputrule(init);
	output << "#cumulative t.\n";
	outputrule(incr);
	output << "#volatile t.\n";
	outputrule(goal);
}
