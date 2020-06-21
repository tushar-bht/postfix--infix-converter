#include<bits/stdc++.h>

using namespace std;
stack<string> operatorStack; //for storing operators
string outputExpression;   //for storing result of operations
	
         //...................................Prototypes....................................
void menu();
void infixToPreOrPost(string);
string inputExpression();
bool isOperator(string);
int operatorPrec(string);
int main()
{ 
   menu();
   cout<<endl<<outputExpression;  


return 0;

}
          //..................................Functions..................................
      
 void menu()
  {	  	
int selection;
cout<<"\n Menu";

cout<<"\n========";

cout<<"\n 1 - Infix to Postfix";

cout<<"\n 2 - Infix to Prefix";

cout<<"\n 3 - Postfix to Infix";

cout<<"\n 4 - Prefix to Infix";

cout<<"\n 5 - Evaluate";

cout<<"\n Enter selection: ";

// read the input

cin>>selection;
cout<<"\n";

switch(selection)
{

case 1 :{infixToPreOrPost("postfix");          
		 } 

break;

case 2 :{infixToPreOrPost("prefix");
         }

break;

case 3 :{cout<<"\n To delete a record";}

break;

case 4 :{cout<<"\n To exit the menu";}

break;

// other than 1, 2,3,4 and 5...

default : cout<<"\n Invalid selection";

}



	  }    

string inputExpression()           //For taking input expression
{	cout<<"\n";
	cout<<"Enter Infix expression ";
	string expression;
	std::getline(std::cin >> std::ws, expression);
	return expression;
}

bool isOperator(string input) 
{ 
    if(input== "+"||input=="-" ||input=="*" ||input=="%"||input=="/"||input=="(" ||input=="^")
    return true; 
     else
    return false; 
} 
int operatorPrec(string ch){ 
    if(ch == "^") 
    return 3; 
    else if(ch == "*" || ch == "/" || ch =="%") 
    return 2; 
    else if(ch == "+" || ch == "-") 
    return 1; 
    else
    return -1; 

}

void infixToPreOrPost(string calculate) 
{    system("cls");
    string expression=inputExpression();
    
	 if(calculate=="prefix")  // to calculate prefix
     {
     for(int i=0;i<expression.size();i++){
     	if(expression[i]=='(')
     	expression[i]=')';
     	else if(expression[i]==')')
     	expression[i]='(';
	 }
	 reverse(expression.begin(),expression.end());
	 } 
	 
	
	istringstream stm(expression) ;
    string character;
    //seperating the string with spaces
    vector<string>expressionVector;  
    
	while( stm >> character )
  {  // put characters seperated by spaces into vector
     expressionVector.push_back(character);
   }
   
    int expressionLength = expressionVector.size(); 
   
    for(int i = 0; i < expressionLength; i++) 
    {    // Sepearating by spaces.
		 string st=expressionVector[i];
		if(operatorStack.empty())
		{  
		operatorStack.push("N"); 
        if(isOperator(st))
        operatorStack.push(st);
        else 
        outputExpression+=st+" ";
		}
		// If the scanned character is an ‘(‘, push it to the stack. 
		else if(st == "(") 
        operatorStack.push("(");
		 
        // If the scanned character is an ‘)’, pop the stack and add it to output string  
        // until an ‘(‘ is encountered. 
        else if(st == ")") 
        { 
            while(operatorStack.top() != "N" && operatorStack.top() != "(") 
            { 
                string c = operatorStack.top(); 
                operatorStack.pop(); 
               outputExpression += c+" "; 
            } 
            if(operatorStack.top() == "(") 
            {  
                operatorStack.pop(); 
            } 
        }           
        //If an operator is scanned 
        else if(isOperator(st)){ 
            while(operatorStack.top() != "N" && operatorPrec(st) <= operatorPrec(operatorStack.top())) 
            { 
                string c = operatorStack.top(); 
                operatorStack.pop(); 
                outputExpression += c+" "; 
            } 
            operatorStack.push(st); 
        }
		else 
		outputExpression+=st+" "; 
    }
    
    //Pop all the remaining elements from the stack 
    while(operatorStack.top()!="N") 
    { 
        string c = operatorStack.top(); 
        operatorStack.pop(); 
        outputExpression += c+" "; 
    }
	if(calculate=="prefix")   //again reversing output for prefix expression.
	reverse(outputExpression.begin(),outputExpression.end()); 
      
} 
