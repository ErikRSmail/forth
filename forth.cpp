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
    void execute_primitive(std::string& word);
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
void forth::push(int a){//as does this
    data_stack.push(a);
}
void forth::execute_primitive(std::string& word){
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
    else if(word == "CR"){std::cout << "\n";}
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
        int to_dup = data_stack.top();
        while(!temp.empty()){push(temp.top());temp.pop();}
        push(to_dup);
    }
    else if(word == "ROLL"){
        int depth = pop();
        std::stack<int> temp;
        while(depth){temp.push(pop());depth--;}
        int to_move = pop();
        while(!temp.empty()){push(temp.top());temp.pop();}
        push(to_move);
    }//TODO
    else if(word == "ROT"){
        int a = pop();
        int b = pop();
        int c = pop();
        push(b);
        push(a);
        push(c);
    }
    else if(word == "SWAP"){
        int a = pop();
        int b = pop();
        push(a);
        push(b);
    }//TODO
    else if(word == "R"){return_stack.push(pop());}
    else if(word == "R>"){
        push(return_stack.top());
        return_stack.pop();
    }
    else if(word == "R@"){push(return_stack.top());}
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
        while(words >> word){
            if(word == ":"){ // case we have a new macro being defined
                std::string macro_id;
                std::string macro_body;
                std::string to_append;
                words >> macro_id;
                words >> to_append;
                while(to_append != ";"){//TODO brutal. 
                    macro_body.push_back(' ');
                    macro_body += to_append;
                    words >> to_append;
                }
                macro_body.push_back(' ');
                macros[macro_id] = macro_body;
            }
            else if(macros.count(word)){//TODO has to be a better way to do this.
                std::string temp(macros.at(word));
                std::string to_append;
                while(words >> to_append){
                    temp +=to_append;
                    temp.push_back(' ');
                }
                words.str(std::string());
                words.clear();
                words << temp;
            }
            else if(word == "IF"){
                if(!pop()){
                    while(word != "THEN"){words >> word;}//if you forget the THEN an infinite LOOP occurs
                }
            }
            else if(word == "DO"){
                int a = pop();
                int b = pop();
                if(!(b-1)){
                    while(word != "LOOP"){words >> word;}// same deal as THEN
                } else {
                    std::string loop_body;
                    std::string temp;
                    std::string to_append;
                    words >> to_append;
                    while(to_append != "LOOP"){
                        loop_body += to_append;
                        loop_body.push_back(' ');
                        words >> to_append;
                    }
                    for(int i=0;i<b-a;i++){
                        loop_body.push_back(' ');
                        //std::cout <<"b-a"<<b-a;
                        //std::cout <<"i"<<i;
                        temp += loop_body;
                    }
                    while(words >> to_append){
                        temp.push_back(' ');
                        temp += to_append;
                    }
                    //std::cout << "loop body:" << loop_body << "\n";
                    words.str(std::string());
                    words.clear();
                    words << temp;
                }
                
            }
            else if(word == "LOOP" || word == "THEN"){
                //ignore
            }
            else{
                execute_primitive(word);
            }
        }
        
    }
}

int main(){   
    forth f;
    f.run();
}