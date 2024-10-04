#include <unordered_map>
#include <deque>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

int main(){
	
	struct sOperator{
		uint8_t priority = 0;
		uint8_t narguments = 0;
	};

	std::unordered_map<char, sOperator> prioTable;

	prioTable['/'] = {4, 2};
	prioTable['*'] = {3, 2};
	prioTable['+'] = {2, 2};
	prioTable['-'] = {1, 2};

	std::string input = "1+2*3-3";

	struct sSymbol
	{
		std::string symbol = "";

		enum class Type : uint8_t{
			Numeric_literal,
			Operator,
			Unknown,
			Parenthesis_Open,
			Parenthesis_Close
		}type = Type::Unknown;
		sOperator op;
			
		sSymbol(const std::string& syn, Type t, sOperator o = {}):symbol(syn), type(t), op(o) {}
		
	};

	std::deque<sSymbol> stkHolding;
	std::deque<sSymbol> stkOutput;

	for(const char c: input){
		if(std::isdigit(c)){
			stkOutput.push_back({ std::string(1, c), sSymbol::Type::Numeric_literal});
		}
		else if(prioTable.contains(c)){
			const auto &new_ops = prioTable[c];
			while(!stkHolding.empty()){
				if(stkHolding.front().type == sSymbol::Type::Operator){
					const auto& holding_stack_op = stkHolding.front().op;
					if(holding_stack_op.priority >= new_ops.priority ){
						stkOutput.push_back(stkHolding.front());
						stkHolding.pop_front();
					}
					else{
						break;
					}
				}		
			}
			stkHolding.push_back({ std::string(1, c), sSymbol::Type::Operator, new_ops});
		}
		else if(c == '('){
			stkHolding.push_front({std::string(1, c), sSymbol::Type::Parenthesis_Open, {}});
		}
		else if(c == ')'){
			while(c != '('){
				stkOutput.push_front(stkHolding[0]);
				stkHolding.pop_front();	
			}
		}
		else{
		
			std::cout << "Bad symbol" << std::endl;
			break;
		}	
	}
	while(!stkHolding.empty()){
		stkOutput.push_front(stkHolding.front());
		stkHolding.pop_front();
	}

	std::cout << " the orignal input : " << input << std::endl;
	std::cout << "RPN..." << std::endl;
	for(const auto& s : stkOutput){
			//iterate through stkOutput here
		std::cout << s.symbol << std::endl;	
	}
	
	std::deque<double> stkSolve;

	for(const auto& inst : stkOutput){
		switch (inst.type){
			case sSymbol::Type::Numeric_literal:
			{
				stkSolve.push_front(std::stod(inst.symbol));
				break;
			}
			case sSymbol::Type::Operator:{
				std::array<double, 2> mem;
				for(int a =0; a < inst.op.narguments; a++){
					if(!stkSolve.empty()){
						mem[a] = stkSolve[0];
						stkSolve.pop_front();
					}	
					else{
						std::cout << "bad exoressuin" << std::endl;
					}
					double result = 0.;
					if(inst.op.narguments == 2){
						if(inst.symbol == '/'){result = mem[1]/mem[0];}
						if(inst.symbol == '*'){result = mem[1]*mem[0];}
						if(inst.symbol == '+'){result = mem[1]+mem[0];}
						if(inst.symbol == '-'){result = mem[1]-mem[0];}
					}
					stkSolve.push_front(result);
				}
				
			}
			break;
		}

	}

	std::cout << stkSolve[0] << std::endl;
}

