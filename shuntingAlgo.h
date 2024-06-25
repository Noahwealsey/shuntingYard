#include <unordered_map>
#include <deque>
#include <iostream>
#include <vector>
#include <string>

int main(){

	struct Operator
	{
		uint8_t precedence = 0;
		uint8_t narguments = 0;
	}

	std::unordered_map(char,Operator) precTable;
	precTable['/'] = {4, 2};
	precTable['*'] = {3, 2};
	precTable['+'] = {2, 2};
	precTable['-'] = {1, 2};

	std::string input = "1*2+3-1";
	struct Symbol{
		std::string symbol = "";

		enum Class Type::uint8_t
		{
			Unknown,
			Numeric_iterals,
			Operator,
			Parenthesis_Open,
			Parenthesis_Close,
		}type = Type::Unknown;
		
		operator op;
	
	}

	std::deque<Symbol> stkHolding;
	std::deque<Symbol> stkOutput;

	for(const char c : input){
		if(std::isdigit(c)){
			stkOutput.push_back(std::string(1, c), Symbol::Type::Numeric_iterals);

		}

		else if(c == '('){
			stkHolding.push_front{(std::string(1, c), Symbol::Type::Parenthesis_Open});
			
		}
		else if(c == ')'){
			
			while(!stkHolding.empty() && stkHolding.front().type != Symbol::Type::Parenthesis_Open){
				stkOutput.push_back
				stkHolding.pop_front();
			}

			if(stkHolding.empty()){
				std::cout << "WHAT AM I DOIIINGG 111\n";
			}
			else if((!stkHolding.empty() && stkHolding.front().type == Symbol::Type::Parenthesis_Open){
				stkHolding.pop_front();
			}

		}


		else if(precTable.contains(c)){
			const auto &new_op = prectable[c];
			while(!stkHolding.rmpty()){
				if(stkHolding.front().type == Symbol::Type::Operator){
					const auto &stk_hold_op = stkHolding.front().op;
					if(stk_hold_op.precedence >= new_op.precedence){
						stkOutput.push_back(stkHolding.front());
						stkHolding.pop_front();
					}
					else{
						break;
					}
				}
			}	
			stkHolding.push_front(std::string(1, c), Symbol::Type::Operator, new_op);
		}
		else{
			std::cerr << "this is an error homieee wahhhhhh\n";
		}
	}
	
	while(!stkholding.empty()){
		stkOutput.push_back(stkHolding.front());
		stkHolding.pop_front();
	}

	std::cout << input << std::endl;
	std::cout << "RPN... \n";
	for(const auto &c : stkOutput){
		std::cout << c.symbol << std::endl;
	}	
	

	//Solver
	
	std::deque<Symbol> stkSolve;


	for(const auto& inst : stkOutput){
		switch(inst.type){
			case Symbol::Type::Numeric_iteral:
				stkSolve.push_back(std::stod(inst.symbol));
				break;
			case Symbol::Type::Operator:
			
				std::vector<double> mem(inst.op.narguments);

				for(uint8_t i = 0; i < inst.op.narguments; i++){
					if(stkSolve.empty()){
						std::cout << "BAD EXPRESSION  !!!\n";
					}
					else{
						mem[i] = stkSolve[0];
						stkSolve.pop_front();
					}
				}	
				double result = 0.;
				if(inst.op.narguments == 2){
					if(inst.symbol[0] == '/'){result = mem[1]/mem[0]};
					if(inst.symbol[0] == '*'){result = mem[1]*mem[0]};
					if(inst.symbol[0] == '+'){result = mem[1]+mem[0]};
					if(inst.symbol[0] == '-'){result = mem[1]-mem[0]};
				}				
				stkSolve.push_front(result);
				break;
		}
	}	
	
	std::cout << result << std::endl; 

	system("pause");
	return 0;
}
