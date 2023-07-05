#include <iostream>
#include <cstdlib>
#include <sstream>
#include <memory>
#include <string>
#include <vector>
#include <stack>
#include <map>

class forth{
    public:
    void run();
    private:
    void execute_word(std::string& word);
    int pop();
    void push(int a);
    std::stack<int> data_stack;
    std::stack<int> return_stack;
    std::map<std::string,std::string> macros;
};
int forth::pop(){//although we have two stacks, this operates on the data stack only to save chars
    int temp = data_stack.top();
    data_stack.pop();
    return temp;
}
void forth::push(int a){
    data_stack.push(a);
}
void forth::execute_word(std::string& word){
    if(word == "."){std::cout << pop();}
    else if(word == "+"){push(pop() + pop());}
    else if(word == "-"){push(pop() - pop());}
    else if(word == "*"){push(pop() * pop());}
    else if(word == "/"){push(pop() / pop());}
    else if(word == "%"){push(pop() % pop());}
    else if(word == "=="){push(pop() == pop());}
    else if(word == "<"){push(pop() < pop());}
    else if(word == ">"){push(pop() > pop());}
    else if(word == "<="){push(pop() <= pop());}
    else if(word == ">="){push(pop() >= pop());}
    else if(word == "!="){push(pop() != pop());}
    else if(word == "&"){push(pop() & pop());}
    else if(word == "|"){push(pop() | pop());}
    else if(word == "~"){push(~pop());}
    else if(word == "^"){push(pop() ^ pop());}
    else if(word == ">>"){push(pop() >> pop());}
    else if(word == "<<"){push(pop() << pop());}
    else if(word == "CR"){std::cout << "\n";}//could be part of stdlib
    else if(word == "EMIT"){std::cout << (char)pop();}
    else if(word == "DROP"){pop();}
    else if(word == "NOP"){}
    else if(word == "DUP"){push(data_stack.top());}
    else if(word == "?DUP"){if(data_stack.top()){push(data_stack.top());}}
    else if(word == "ABS"){push(abs(pop()));}
    else if(word == "OVER"){
        int a = pop();
        int b = pop();
        push(b);
        push(a);
        push(b);
    }
    else if(word == "BYE"){std::cout << "exiting interpreter..\n";exit(0);}
    else if(word == "PICK"){
        int depth = pop();
        std::stack<int> temp;
        while(depth){temp.push(pop());depth--;}
        int to_dup = pop();
        while(!temp.empty()){push(temp.top());temp.pop();}
        push(to_dup);
    }
    else if(word == "ROLL"){}//TODO
    else if(word == "ROT"){}//TODO
    else if(word == "SWAP"){}//TODO
    else if(word == "R"){return_stack.push(pop());}
    else if(word == "R>"){
        push(return_stack.top());
        return_stack.pop();
    }
    else if(word == "R@"){push(return_stack.top());}
    else if(macros.count(word)){}//TODO IMPL
    else{
        push(stoi(word));
    }
}
void forth::run(){
    std::string line;
    while(1){
        std::string word;
        std::cout << "forth>>> ";
        std::getline(std::cin,line);
        std::stringstream words(line);
        while(words >> word){//todo add hijack if word == ":"
            execute_word(word);
        }
        
    }
}

int main(){   
    forth f;
    f.run();
}