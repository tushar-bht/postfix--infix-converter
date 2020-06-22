#include<bits/stdc++.h>
using namespace std;

stack<string> operatorStack; //for storing operators
stack<string> operandStack;  //for storing operands
string outputExpression;   //for storing result of operations
int operatorStackLength;   //for calculating lenth of operatorStack
	
         //...................................Prototypes....................................
void menu();
void infixToPreOrPost(string);
void preOrPostToInfix(string);
string inputExpression();
bool isOperator(string);
int operatorPrec(string);
int main()
{ 
   menu();
  
   //display output
   cout<<endl<<endl<<"  Output : "<<outputExpression;  

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
break;
    }
    
case 2 :{infixToPreOrPost("prefix");    
break;
    }
    
case 3 :{preOrPostToInfix("postfixToInfix");
break;
    }
    
case 4 :{preOrPostToInfix("prefixToInfix");
break;
   }
case 5 :{cout<<"evaluate ";
break;
  }
  


default : cout<<"\n Invalid selection";

}
	  } 
	
	  
//showing elements of operator stack	  
string displayOperatorStack()
   { 
     stack<string> temp;
	string currentContentsInStack;
	
	//getting the contents of the stack
	while(!operatorStack.empty()){
		temp.push(operatorStack.top());
		operatorStack.pop();
		
	}
	//putting back contents in operatorStack 
    while(!temp.empty()){
    	operatorStack.push(temp.top());
    	currentContentsInStack+=temp.top()+" ";
    	temp.pop();
	}	
	
	 return currentContentsInStack;
}	  

string inputExpression()           //For taking input expression
{	cout<<"\n";
	cout<<"Enter expression : ";
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
	 
	expression="( "+expression+" )"; 
	
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
        if(isOperator(st))
        operatorStack.push(st);
        else 
        outputExpression+=st+" ";
        
        //display of stack table
        cout<<"\n \n \n";
        cout<<"\n"<<"   "<<"Input"<<left<<"   "<<right<<setw(100)<<"Stack"<<"     "<<setw(50)<<right<<"Output"<<"\n";
        cout<<" "<<setw(100)<<left<<expression<<"     "<<left<<setw(40)<<displayOperatorStack()<<"              "<<outputExpression<<endl;
		}
		// If the scanned character is an ‘(‘, push it to the stack. 
		else if(st == "(") 
        {
		 operatorStack.push("(");
	    cout<<" "<<setw(100)<<left<<expression<<"     "<<left<<setw(40)<<displayOperatorStack()<<"              "<<outputExpression<<endl;
		
	}
        // If the scanned character is an ‘)’, pop the stack and add it to output string  
        // until an ‘(‘ is encountered. 
        else if(st == ")") 
        { 
            while(!operatorStack.empty() && operatorStack.top() != "(") 
            { 
                string c = operatorStack.top(); 
                operatorStack.pop(); 
               outputExpression += c+" "; 
            } 
            if(operatorStack.top() == "(") 
            {  
                operatorStack.pop(); 
            }
        cout<<" "<<setw(100)<<left<<expression<<"     "<<left<<setw(40)<<displayOperatorStack()<<"              "<<outputExpression<<endl;
		
        }           
        //If an operator is scanned 
        else if(isOperator(st)){ 
            while(operatorStack.top() != "(" && operatorPrec(st) <= operatorPrec(operatorStack.top())) 
            { 
                string c = operatorStack.top(); 
                operatorStack.pop(); 
                outputExpression += c+" "; 
            } 
            operatorStack.push(st); 
         cout<<" "<<setw(100)<<left<<expression<<"     "<<left<<setw(40)<<displayOperatorStack()<<"              "<<outputExpression<<endl;
		
        }
		else
		{
		     outputExpression+=st+" "; 
         cout<<" "<<setw(100)<<left<<expression<<"     "<<left<<setw(40)<<displayOperatorStack()<<"              "<<outputExpression<<endl;
	
	  } 
		}
    
   if(calculate=="prefix")   //again reversing output for prefix expression.
	reverse(outputExpression.begin(),outputExpression.end()); 
	
    }
   
   
   string displayOperandStack()   //display contents of operand stack
   {
   	 stack<string> temp;
	string currentContentsInStack="";
	
	//getting the contents of the stack
	while(!operandStack.empty()){
		temp.push(operandStack.top());
		operandStack.pop();
		
	}
	//putting back contents in operatorStack 
    while(!temp.empty()){
    	operandStack.push(temp.top());
    	currentContentsInStack+=temp.top()+" ";
    	temp.pop();
	}	
	
	 return currentContentsInStack;

   } 
    
    
	
	void preOrPostToInfix(string calculate)  //prefix or postfix to infix convert.
	{
	system("cls");
	string expression=inputExpression();
	
	if(calculate=="prefixToInfix")  //to convert prefix to infix. 
	reverse(expression.begin(),expression.end());
	
	istringstream stm(expression) ;
    string character;
    //seperating the string with spaces.
    vector <string> expressionVector;  
    
	while( stm >> character )
  {  // putting characters seperated by spaces into vector.
     expressionVector.push_back(character);
   }    
	 
	  //display of stack table
        cout<<"\n \n \n";
        cout<<"\n"<<"   "<<"Input"<<left<<"   "<<right<<setw(100)<<"Stack"<<endl;
        cout<<" "<<setw(100)<<left<<expression<<"     "<<displayOperandStack()<<endl;
	 
		for (int i=0; i<expressionVector.size() ; i++) 
    {   string st=expressionVector[i];
        // handle operators. 
        if (isOperator(st)) 
        { 
            string op1 = operandStack.top(); 
            operandStack.pop(); 
            string op2 = operandStack.top(); 
            operandStack.pop(); 
            operandStack.push("( " + op2 + " " + st + " " + op1 + " )"); 
         
            
        cout<<" "<<setw(100)<<left<<expression<<"     "<<displayOperandStack()<<endl;
        } 
        // push operands
        else
        { 
          operandStack.push(st);
          
        cout<<" "<<setw(100)<<left<<expression<<"     "<<displayOperandStack()<<endl;
        } 
    } 
  
    // There element left in the stack is the infix expression  
    outputExpression = operandStack.top();
    
    if(calculate=="prefixToInfix")  //reverse outputExpression in case of prefixToInfix.
     {reverse(outputExpression.begin(),outputExpression.end());
	  
	  for(int i=0;i<outputExpression.size();i++)  //converting '(' to ')' and ')' to '('
  	  {
	  	if(outputExpression[i]=='(')
	  	outputExpression[i]=')';
	  	
	  	else if(outputExpression[i]==')')
	  	outputExpression[i]='(';
	   } 
	 }
	
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
      
