#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

//void outputallentry();

//vector<string> output;
//vector<string> jumplist;
vector<string> input;

/*struct Entry
{
	int history = 0;
	int bc2[4] = { 0 };
};
vector<Entry> entries;*/

//pc
int pc = 0;

//cycle;
int cycle = 0;

//register
//int reg[32] = { 0 };

//RF
double RF[6] = { 0 };

bool RAT_use[6];
int RAT[6];


struct RS_type
{
	char op;
	int rs;

	bool first_ready;
	double first_i;
	int first_s;

	bool second_ready;
	double second_i;
	int second_s;

	double ans;
};

bool RS_use[6];
RS_type RS[6];

bool ASB_use, MDB_use;
RS_type AS_Buffer, MD_Buffer;

bool AS_full()
{
	for (int i = 1; i <= 3; i++)
		if (!RS_use[i]) return false;
	return true;
}
bool AS_empty()
{
	for (int i = 1; i <= 3; i++)
		if (RS_use[i]) return false;
	return true;
}

bool MD_full()
{
	for (int i = 4; i <= 5; i++)
		if (!RS_use[i]) return false;
	return true;
}
bool MD_empty()
{
	for (int i = 4; i <= 5; i++)
		if (RS_use[i]) return false;
	return true;
}
/*
//binary轉換器 int轉string
string binary(long long n, int bits, bool sign = false)
{
	string a;
	bool s = false;
	if (sign && n < 0)
	{
		n = -n;
		s = !s;
	}

	for (int j = 0; j < bits; j++)   //迴圈過程的始終，判斷n是否能被2除盡
	{
		a += n % 2 + '0';   //用陣列儲存每次除以2之後的餘數，即斷定奇偶性，對應二進位制位上數值
		n = n / 2;
	}
	if (sign && s)
		a[bits - 1] = '1';
	else if (sign)
		a[bits - 1] = '0';
	reverse(a.begin(), a.end());
	return a;
}
*/
/*int label(string temp)
{
	for (int i = 0; i < jumplist.size(); i++)
		if (jumplist[i] == temp)
			return i;
	return -1;
}*/
/*
string type_i_offset(stringstream& ss, string opcode, string f3)
{
	string temp, rd, rs1, imm;

	ss >> temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('x'), 1);
	rd = binary(atoi(temp.c_str()), 5);

	getline(ss, temp, '(');
	imm = binary(atoi(temp.c_str()), 12, true);

	getline(ss, temp, ')');
	temp.erase(temp.find_first_of('x'), 1);
	rs1 = binary(atoi(temp.c_str()), 5);

	return imm + rs1 + f3 + rd + opcode;
}

string type_i(stringstream& ss, string opcode, string f3)
{
	string temp, rd, rs1, imm;

	ss >> temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('x'), 1);
	rd = binary(atoi(temp.c_str()), 5);

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('x'), 1);
	rs1 = binary(atoi(temp.c_str()), 5);

	ss >> temp;
	imm = binary(atoi(temp.c_str()), 12, true);

	return imm + rs1 + f3 + rd + opcode;
}

string type_sb(stringstream& ss, string opcode, string f3, int i)
{
	string temp, rs1, rs2, imm;

	ss >> temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('x'), 1);
	rs1 = binary(atoi(temp.c_str()), 5);

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('x'), 1);
	rs2 = binary(atoi(temp.c_str()), 5);

	ss >> temp;
	imm = binary(label(jumplist, temp, i), 13, true);

	string imm1, imm2;
	{
		imm1 += imm[0];
		imm1 += imm[2];
		imm1 += imm[3];
		imm1 += imm[4];
		imm1 += imm[5];
		imm1 += imm[6];
		imm1 += imm[7];

		imm2 += imm[8];
		imm2 += imm[9];
		imm2 += imm[10];
		imm2 += imm[11];
		imm2 += imm[1];
	}

	return imm1 + rs2 + rs1 + f3 + imm2 + opcode;
}

string type_s(stringstream& ss, string opcode, string f3)
{
	string temp, rs1, rs2, imm;

	ss >> temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('x'), 1);
	rs2 = binary(atoi(temp.c_str()), 5);

	getline(ss, temp, '(');
	imm = binary(atoi(temp.c_str()), 12, true);

	getline(ss, temp, ')');
	temp.erase(temp.find_first_of('x'), 1);
	rs1 = binary(atoi(temp.c_str()), 5);

	string imm1, imm2;
	{
		imm1 += imm[0];
		imm1 += imm[1];
		imm1 += imm[2];
		imm1 += imm[3];
		imm1 += imm[4];
		imm1 += imm[5];
		imm1 += imm[6];

		imm2 += imm[7];
		imm2 += imm[8];
		imm2 += imm[9];
		imm2 += imm[10];
		imm2 += imm[11];
	}

	return imm1 + rs2 + rs1 + f3 + imm2 + opcode;
}

string type_r(stringstream& ss, string opcode, string f3, string f2, string f5)
{
	string temp, rd, rs1, rs2;

	ss >> temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('x'), 1);
	rd = binary(atoi(temp.c_str()), 5);

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('x'), 1);
	rs1 = binary(atoi(temp.c_str()), 5);

	ss >> temp;
	if (temp.find('x') != -1)
	{
		temp.erase(temp.find_first_of('x'), 1);
		rs2 = binary(atoi(temp.c_str()), 5);
	}
	else
	{
		rs2 = binary(atoi(temp.c_str()), 5);
	}
	return f5 + f2 + rs2 + rs1 + f3 + rd + opcode;
}
*/
/*void history_predictor(bool taken)
{
	int this_entry = pc % entries.size();
	entries[this_entry].history = ((entries[this_entry].history << 1) & 3);

	if (taken)
		entries[this_entry].history++;
}

bool guess_predictor()
{
	int this_entry = pc % entries.size();

	bool guess = (entries[this_entry].bc2[entries[this_entry].history] >= 2);
	return guess;
}

void edit_predictor(bool taken)
{
	int this_entry = pc % entries.size();
	int this_history = entries[this_entry].history;

	bool guess = (entries[this_entry].bc2[this_history] >= 2);

	if ((guess == taken))
	{
		if (entries[this_entry].bc2[this_history] == 2)
			entries[this_entry].bc2[this_history] = 3;
		else if (entries[this_entry].bc2[this_history] == 1)
			entries[this_entry].bc2[this_history] = 0;
	}
	else
	{
		if (guess)
			entries[this_entry].bc2[this_history]--;
		else
			entries[this_entry].bc2[this_history]++;
	}

	//cout << "line:" << pc << "\tguess: " << ((guess) ? "T" : "N") << "\tfact: " << ((taken) ? "T" : "N") << endl;
	//outputallentry();
}
*/
/*void li(stringstream& ss)
{
	string temp, rd, imm;
	ss >> temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('R'), 1);
	rd = temp;

	ss >> temp;
	imm = temp;

	reg[atoi(rd.c_str())] = atoi(imm.c_str());
}*/

void addi(stringstream& ss)
{
	string temp, rd, rs1, imm;
	ss >> temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('F'), 1);
	rd = temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('F'), 1);
	rs1 = temp;

	ss >> temp;
	imm = temp;

	//reg[atoi(rd.c_str())] = reg[atoi(rs1.c_str())] + atoi(imm.c_str());
	
	for (int i = 1; i <= 3; i++)
		if (!RS_use[i])
		{
			RS_use[i] = true;
			RS[i].op = '+';
			
			if (!RAT_use[stoi(rs1)])
			{
				RS[i].first_ready = true;
				RS[i].first_i = RF[stoi(rs1)];
			}
			else
			{
				RS[i].first_ready = false;
				RS[i].first_s = RAT[stoi(rs1)];
			}

			RS[i].second_ready = true;
			RS[i].second_i = stod(imm);

			RAT_use[stoi(rd)] = true;
			RAT[stoi(rd)] = i;
			break;
		}
}

/*void andi(stringstream& ss)
{
	string temp, rd, rs1, imm;
	ss >> temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('R'), 1);
	temp.erase(temp.find_first_of(' '), 1);
	rd = temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('R'), 1);
	rs1 = temp;

	ss >> temp;
	imm = temp;
	reg[atoi(rd.c_str())] = reg[atoi(rs1.c_str())] & atoi(imm.c_str());
}*/

void add(stringstream& ss)
{
	string temp, rd, rs1, rs2;
	ss >> temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('F'), 1);
	rd = temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('F'), 1);
	rs1 = temp;

	ss >> temp;
	temp.erase(temp.find_first_of('F'), 1);
	rs2 = temp;

	//reg[atoi(rd.c_str())] = reg[atoi(rs1.c_str())] + reg[atoi(rs2.c_str())];

	for (int i = 1; i <= 3; i++)
		if (!RS_use[i])
		{
			RS_use[i] = true;
			RS[i].op = '+';

			if (!RAT_use[stoi(rs1)])
			{
				RS[i].first_ready = true;
				RS[i].first_i = RF[stoi(rs1)];
			}
			else
			{
				RS[i].first_ready = false;
				RS[i].first_s = RAT[stoi(rs1)];
			}

			if (!RAT_use[stoi(rs2)])
			{
				RS[i].second_ready = true;
				RS[i].second_i = RF[stoi(rs2)];
			}
			else
			{
				RS[i].second_ready = false;
				RS[i].second_s = RAT[stoi(rs2)];
			}

			RAT_use[stoi(rd)] = true;
			RAT[stoi(rd)] = i;
			break;
		}
}

/*void beq(stringstream& ss)
{
	string temp, rs1, rs2;
	ss >> temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('R'), 1);
	rs1 = temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('R'), 1);
	rs2 = temp;

	ss >> temp;

	bool taken = reg[atoi(rs1.c_str())] == reg[atoi(rs2.c_str())];
	cout << "\tfact:" << ((taken) ? "T" : "N") << endl;
	edit_predictor(taken);
	history_predictor(taken);
	if (taken)
	{
		pc = label(temp);
		pc--;
	}
}

void bne(stringstream& ss)
{
	string temp, rs1, rs2;
	ss >> temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('R'), 1);
	rs1 = temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('R'), 1);
	rs2 = temp;

	ss >> temp;

	bool taken = reg[atoi(rs1.c_str())] != reg[atoi(rs2.c_str())];
	cout << "\tfact:" << ((taken) ? "T" : "N") << endl;
	edit_predictor(taken);
	history_predictor(taken);
	if (taken)
	{
		pc = label(temp);
		pc--;
	}
}*/

/*void outputallentry()
{
	for (int i = 0; i < entries.size(); i++)
	{
		cout << "entries[" << i << "] = (";
		if (entries[i].history == 0)
			cout << "00";
		else if (entries[i].history == 1)
			cout << "01";
		else if (entries[i].history == 2)
			cout << "10";
		else if (entries[i].history == 3)
			cout << "11";
		for (int j = 0; j < 4; j++)
		{
			cout << ", ";
			if (entries[i].bc2[j] == 0)
				cout << "SN";
			else if (entries[i].bc2[j] == 1)
				cout << "WN";
			else if (entries[i].bc2[j] == 2)
				cout << "WT";
			else if (entries[i].bc2[j] == 3)
				cout << "ST";
		}
		cout << ")" << endl;
	}
	cout << endl;
}*/

void sub(stringstream& ss)
{
	string temp, rd, rs1, rs2;
	ss >> temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('F'), 1);
	rd = temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('F'), 1);
	rs1 = temp;

	ss >> temp;
	temp.erase(temp.find_first_of('F'), 1);
	rs2 = temp;

	for (int i = 1; i <= 3; i++)
		if (!RS_use[i])
		{
			RS_use[i] = true;
			RS[i].op = '-';

			if (!RAT_use[stoi(rs1)])
			{
				RS[i].first_ready = true;
				RS[i].first_i = RF[stoi(rs1)];
			}
			else
			{
				RS[i].first_ready = false;
				RS[i].first_s = RAT[stoi(rs1)];
			}

			if (!RAT_use[stoi(rs2)])
			{
				RS[i].second_ready = true;
				RS[i].second_i = RF[stoi(rs2)];
			}
			else
			{
				RS[i].second_ready = false;
				RS[i].second_s = RAT[stoi(rs2)];
			}

			RAT_use[stoi(rd)] = true;
			RAT[stoi(rd)] = i;
			break;
		}
}

void mul(stringstream& ss)
{
	string temp, rd, rs1, rs2;
	ss >> temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('F'), 1);
	rd = temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('F'), 1);
	rs1 = temp;

	ss >> temp;
	temp.erase(temp.find_first_of('F'), 1);
	rs2 = temp;

	for (int i = 4; i <= 5; i++)
		if (!RS_use[i])
		{
			RS_use[i] = true;
			RS[i].op = '*';

			if (!RAT_use[stoi(rs1)])
			{
				RS[i].first_ready = true;
				RS[i].first_i = RF[stoi(rs1)];
			}
			else
			{
				RS[i].first_ready = false;
				RS[i].first_s = RAT[stoi(rs1)];
			}

			if (!RAT_use[stoi(rs2)])
			{
				RS[i].second_ready = true;
				RS[i].second_i = RF[stoi(rs2)];
			}
			else
			{
				RS[i].second_ready = false;
				RS[i].second_s = RAT[stoi(rs2)];
			}

			RAT_use[stoi(rd)] = true;
			RAT[stoi(rd)] = i;
			break;
		}
}

void div(stringstream& ss)
{
	string temp, rd, rs1, rs2;
	ss >> temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('F'), 1);
	rd = temp;

	getline(ss, temp, ',');
	temp.erase(temp.find_first_of('F'), 1);
	rs1 = temp;

	ss >> temp;
	temp.erase(temp.find_first_of('F'), 1);
	rs2 = temp;

	for (int i = 4; i <= 5; i++)
		if (!RS_use[i])
		{
			RS_use[i] = true;
			RS[i].op = '/';

			if (!RAT_use[stoi(rs1)])
			{
				RS[i].first_ready = true;
				RS[i].first_i = RF[stoi(rs1)];
			}
			else
			{
				RS[i].first_ready = false;
				RS[i].first_s = RAT[stoi(rs1)];
			}

			if (!RAT_use[stoi(rs2)])
			{
				RS[i].second_ready = true;
				RS[i].second_i = RF[stoi(rs2)];
			}
			else
			{
				RS[i].second_ready = false;
				RS[i].second_s = RAT[stoi(rs2)];
			}

			RAT_use[stoi(rd)] = true;
			RAT[stoi(rd)] = i;
			break;
		}
}

void printcycle(string when)
{
	cout << "=====" << when << "=====" << endl;

	//RF RAT RS BUFFER

	for (int i = 1; i <= 5; i++)
		cout << "RF[" << i << "] = " << RF[i] << endl;
	cout << endl;

	for (int i = 1; i <= 5; i++)
	{
		if (RAT_use[i])
			cout << "RAT[" << i << "] = RS" << RAT[i] << endl;
		else
			cout << "RAT[" << i << "] = None" << endl;
	}
	cout << endl;

	for (int i = 1; i <= 3; i++)
	{
		if (RS_use[i])
		{
			cout << "RS[" << i << "] = " << RS[i].op << " ";

			if (RS[i].first_ready)
				cout << RS[i].first_i << " ";
			else
				cout << "RS" << RS[i].first_s << " ";

			if (RS[i].second_ready)
				cout << RS[i].second_i;
			else
				cout << "RS" << RS[i].second_s;
		}
		else
			cout << "RS[" << i << "] = None";
		cout << endl;
	}
	cout << "Buffer: ";
	if (ASB_use)
		cout << "RS" << AS_Buffer.rs << " = " << AS_Buffer.first_i << " " << AS_Buffer.op << " " << AS_Buffer.second_i << endl;
	else
		cout << "empty" << endl;
	cout << endl;

	for (int i = 4; i <= 5; i++)
	{
		if (RS_use[i])
		{
			cout << "RS[" << i << "] = " << RS[i].op << " ";

			if (RS[i].first_ready)
				cout << RS[i].first_i << " ";
			else
				cout << "RS" << RS[i].first_s << " ";

			if (RS[i].second_ready)
				cout << RS[i].second_i;
			else
				cout << "RS" << RS[i].second_s;
		}
		else
			cout << "RS[" << i << "] = None";
		cout << endl;
	}
	cout << "Buffer: ";
	if (MDB_use)
		cout << "RS" << MD_Buffer.rs << " = " << MD_Buffer.first_i << " " << MD_Buffer.op << " " << MD_Buffer.second_i << endl;
	else
		cout << "empty" << endl;
	cout << endl;
		

}

void iss()
{
	if (pc < input.size())
	{
		string c_input;
		stringstream ss;
		c_input = input[pc];
		ss << c_input;

		if (c_input.find("ADDI") != -1 && !AS_full())
		{
			addi(ss);
			pc++;
			printcycle("iss_ADDI");
		}
		else if (c_input.find("ADD") != -1 && !AS_full())
		{
			add(ss);
			pc++;
			printcycle("iss_ADD");
		}
		else if (c_input.find("SUB") != -1 && !AS_full())
		{
			sub(ss);
			pc++;
			printcycle("iss_SUB");
		}
		else if (c_input.find("MUL") != -1 && !MD_full())
		{
			mul(ss);
			pc++;
			printcycle("iss_MUL");
		}
		else if (c_input.find("DIV") != -1 && !MD_full())
		{
			div(ss);
			pc++;
			printcycle("iss_DIV");
		}
	}
}

void exe()
{
	if (!AS_empty())
	{
		for (int i = 1; i <= 3; i++)
			if (RS_use[i] && RS[i].first_ready && RS[i].second_ready)
			{
				ASB_use = true;
				AS_Buffer = RS[i];
				AS_Buffer.rs = i;
				break;
			}
	}

	if (!MD_empty())
	{
		for (int i = 4; i <= 5; i++)
			if (RS_use[i] && RS[i].first_ready && RS[i].second_ready)
			{
				MDB_use = true;
				MD_Buffer = RS[i];
				MD_Buffer.rs = i;
				break;
			}
	}

	if (!AS_empty() || !MD_empty())
		printcycle("exe");

	if (ASB_use)
	{
		if (AS_Buffer.op == '+')
		{
			AS_Buffer.ans = AS_Buffer.first_i + AS_Buffer.second_i;
		}
		else if (AS_Buffer.op == '-')
		{
			AS_Buffer.ans = AS_Buffer.first_i - AS_Buffer.second_i;
		}
	}

	if (MDB_use)
	{
		if (MD_Buffer.op == '*')
		{
			MD_Buffer.ans = MD_Buffer.first_i * MD_Buffer.second_i;
		}
		else if (MD_Buffer.op == '/')
		{
			if (MD_Buffer.second_i == 0)
			{
				cout << "div 0 error" << endl;
			}
			MD_Buffer.ans = MD_Buffer.first_i / MD_Buffer.second_i;
		}
	}
}

void wr()
{
	if (MDB_use)
	{
		//update RF
		for (int i = 1; i <= 5; i++)
		{
			if (RAT_use[i] && RAT[i] == MD_Buffer.rs)
			{
				RF[i] = MD_Buffer.ans;
				RAT_use[i] = false;
			}
		}

		//update RS
		for (int i = 1; i <= 5; i++)
		{
			if (RS[i].first_s == MD_Buffer.rs)
			{
				RS[i].first_i = MD_Buffer.ans;
				RS[i].first_ready = true;
			}
			if (RS[i].second_s == MD_Buffer.rs)
			{
				RS[i].second_i = MD_Buffer.ans;
				RS[i].second_ready = true;
			}
		}

		RS_use[MD_Buffer.rs] = false;
		MDB_use = false;
		printcycle("MD_wr");
	}
	else if (ASB_use)
	{
		//update RF
		for (int i = 1; i <= 5; i++)
		{
			if (RAT_use[i] && RAT[i] == AS_Buffer.rs)
			{
				RF[i] = AS_Buffer.ans;
				RAT_use[i] = false;
			}
		}

		//update RS
		for (int i = 1; i <= 5; i++)
		{
			if (RS[i].first_s == AS_Buffer.rs)
			{
				RS[i].first_i = AS_Buffer.ans;
				RS[i].first_ready = true;
			}
			if (RS[i].second_s == AS_Buffer.rs)
			{
				RS[i].second_i = AS_Buffer.ans;
				RS[i].second_ready = true;
			}
		}

		RS_use[AS_Buffer.rs] = false;
		ASB_use = false;
		printcycle("AS_wr");
	}
}

int main()
{
	string tempin;
	
	/*int tmpentriessize;
	cout << "enter the X entries ( X > 0 ) " << endl;
	cin >> tmpentriessize;
	entries.resize(tmpentriessize);*/
	std::cout << "plz enter all inst. ( end of EOF ) " << endl;

	while (getline(cin, tempin))
	{
		input.push_back(tempin);
	}

	//output.resize(input.size());
	//jumplist.resize(input.size());

	//jump label
	/*for (int i = 0; i < input.size(); i++)
	{
		//string opcode, rd, rs1, rs2, imm, f3, f2, f5;
		string temp, c_input;
		stringstream ss;
		c_input = input[i];
		ss << c_input;

		if (c_input.find(":") != -1)
		{
			ss >> temp;
			temp.erase(temp.find_first_of(':'), 1);
			jumplist[i] = temp;
		}
	}*/

	for (int i = 0; true; i = ++cycle)
	{
		//string opcode, rd, rs1, rs2, imm, f3, f2, f5, temp, c_input;
		

		//cout << "line:" << pc << "\tentry:" << pc % entries.size() << "\tguess:" << ((guess_predictor()) ? "T" : "N");

		cout << "----- cycle: " << cycle + 1 << " -----" << endl;
		
		wr();
		exe();
		iss();

		cout << endl;

		if (pc >= input.size() && AS_empty() && MD_empty() && !ASB_use && !MDB_use)
			break;

		/*if (c_input.find(":") != -1)
			ss >> temp;
		//li
		if (c_input.find("li") != -1)
		{
			li(ss);
		}
		else */
		/*else if (c_input.find("beq") != -1)
		{
			beq(ss);
			outputallentry();
			continue;
		}
		else if (c_input.find("bne") != -1)
		{
			bne(ss);
			outputallentry();
			continue;
		}*/
		/*else if (c_input.find("andi") != -1)
		{
			andi(ss);
		}*/
		/*history_predictor(false);
		cout << "\tnot branch!" << endl;
		outputallentry();*/
		/*
		//type_i_offset
		else if (c_input.find("lb") != -1 || c_input.find("lh") != -1 || c_input.find("lw") != -1)
		{
			opcode = "0000011";

			if (c_input.find("lbu") != -1)
				f3 = "100";
			else if (c_input.find("lhu") != -1)
				f3 = "101";
			else if (c_input.find("lb") != -1)
				f3 = "000";
			else if (c_input.find("lh") != -1)
				f3 = "001";
			else if (c_input.find("lw") != -1)
				f3 = "010";

			//output[i] = imm + " " + rs1 + " " + f3 + " " + rd + " " + opcode;
			//output[i] = type_i_offset(ss, opcode, f3);
		}
		//addi type_i
		else if (c_input.find("addi") != -1 || c_input.find("slti") != -1 || c_input.find("ori") != -1 || c_input.find("andi") != -1)
		{
			opcode = "0010011";

			if (c_input.find("sltiu") != -1)
				f3 = "011";
			else if (c_input.find("xori") != -1)
				f3 = "100";
			else if (c_input.find("addi") != -1)
				f3 = "000";
			else if (c_input.find("slti") != -1)
				f3 = "010";
			else if (c_input.find("ori") != -1)
				f3 = "110";
			else if (c_input.find("andi") != -1)
				f3 = "111";

			//output[i] = imm + " " + rs1 + " " + f3 + " " + rd + " " + opcode;
			//output[i] = type_i(ss, opcode, f3);
		}
		//type_s
		else if (c_input.find("sb") != -1 || c_input.find("sh") != -1 || c_input.find("sw") != -1)
		{
			opcode = "0100011";

			if (c_input.find("sb") != -1)
				f3 = "000";
			else if (c_input.find("sh") != -1)
				f3 = "001";
			else if (c_input.find("sw") != -1)
				f3 = "010";

			//output[i] = type_s(ss, opcode, f3);
		}
		//type_r
		else if (c_input.find("sl") != -1 || c_input.find("sr") != -1 || c_input.find("add") != -1 ||
			c_input.find("sub") != -1 || c_input.find("or") != -1 || c_input.find("and") != -1)
		{
			if (c_input.find("slli") != -1 || c_input.find("srli") != -1 || c_input.find("srai") != -1)
				opcode = "0010011";
			else
				opcode = "0110011";

			f2 = "00";

			if (c_input.find("sll") != -1)
				f3 = "001";
			else if (c_input.find("sr") != -1)
				f3 = "101";
			else if (c_input.find("add") != -1 || c_input.find("sub") != -1)
				f3 = "000";
			else if (c_input.find("sltu") != -1)
				f3 = "011";
			else if (c_input.find("slt") != -1)
				f3 = "010";
			else if (c_input.find("xor") != -1)
				f3 = "100";
			else if (c_input.find("or") != -1)
				f3 = "110";
			else if (c_input.find("and") != -1)
				f3 = "111";

			if (c_input.find("srai") != -1 || c_input.find("sub") != -1 || c_input.find("sra") != -1)
				f5 = "01000";
			else
				f5 = "00000";

			//output[i] = f5 + " " + f2 + " " + rs2 + " " + rs1 + " " + f3 + " " + rd + " " + opcode;
			//output[i] = type_r(ss, opcode, f3, f2, f5);
		}
		//beq type_sb
		else if (c_input.find("beq") != -1 || c_input.find("bne") != -1 || c_input.find("blt") != -1 || c_input.find("bge") != -1)
		{
			opcode = "1100011";

			if (c_input.find("beq") != -1)
				f3 = "000";
			else if (c_input.find("bne") != -1)
				f3 = "001";
			else if (c_input.find("bltu") != -1)
				f3 = "110";
			else if (c_input.find("bgeu") != -1)
				f3 = "111";
			else if (c_input.find("blt") != -1)
				f3 = "100";
			else if (c_input.find("bge") != -1)
				f3 = "101";

			//output[i] = imm1 + " " + rs2 + " " + rs1 + " " + f3 + " " + imm2 + " " + opcode;
			//output[i] = type_sb(ss, opcode, f3, i);
		}*/
		//system("pause");
	}
	/*for (int i = 0; i < output.size(); i++)
	{
		cout << output[i] << endl;
	}*/
	return 0;
}

/*
ADDI F1,F1,0
ADDI F2,F2,2
ADDI F3,F3,4
ADDI F4,F4,6
ADDI F5,F5,8
ADDI F1,F2,1
SUB F1,F3,F4
DIV F1,F2,F3
MUL F2,F3,F4
ADD F2,F4,F2
ADDI F4,F1,2
MUL F5,F5,F5
ADD F1,F4,F4
*/

/*
ADDI F2,F1,1
ADDI F3,F2,1
ADDI F4,F3,1
*/