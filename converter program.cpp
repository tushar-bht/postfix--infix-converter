#include<bits/stdc++.h>
using namespace std;

stack<string> operatorStack; //for storing operators
stack<string> operandStack;  //for storing operands
stack<double> evaluationStack; //for evaluation process.
string outputExpression;   //for storing result of operations

	
         //...................................Prototypes....................................
void menu();
string inputExpression();
bool isOperator(string);
int operatorPrec(string);
void infixToPreOrPost(string);
string displayOperandStack();
void handleUnaryOperator(string);
void preOrPostToInfix(string);

void evaluate();
void evaluateInfix();
void evaluatePostfix(string);
double operation(double,double,string);
string displayEvaluationStack();
void evaluatePrefix();
         
         //..............................Main function.................................
int main()
{ 
   int choice=1;
    while(choice==1)
	{
    menu();
    //display output
    cout<<endl<<endl<<"  Output : "<<outputExpression;  
  	
  	
  	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n";
  	cout<<" Enter 1 - to continue , 0 - to exit : ";
  	cin>>choice;
  	
  	system("cls");
  	
  	// Empty all stacks.
  	while(!operatorStack.empty()){
  		operatorStack.pop();
	  }
	
	while(!operandStack.empty()){
		operandStack.pop();
	  }
	
	while(!evaluationStack.empty()){
		evaluationStack.pop();
	  }
	
	outputExpression="";  
	    
	}
  
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

cout<<"\n \n  Enter selection: ";

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
case 5 :{evaluate();
break;
  }
  


default :{ cout<<"\n Invalid selection";
	exit(1);
  }

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
	cout<<"\n \n Enter expression : ";
	string expression;
	getline(cin >> ws, expression);
	return expression;
}

bool isOperator(string input) 
{ 
    if(input== "++"||input=="--" ||input=="~" ||input=="!" ||input=="^"||input=="*" ||input=="%" ||input=="/" || input=="+" || input=="-" ||input=="(" ||input== "<<" ||input==">>" || input==">" || input=="<" || input=="<=" ||input==">=" ||input=="==" ||input== "!=" ||input=="&&" ||input=="||" ||input=="?:" ||input=="=")
    return true; 
     else
    return false; 
} 
int operatorPrec(string ch)   //checking precedence of operator
{ 
    if(ch == "++" || ch=="--" || ch=="~" || ch=="!" || ch=="^") 
    return 10; 
    else if(ch == "*" || ch == "/" || ch =="%") 
    return 9; 
    else if(ch == "+" || ch == "-") 
    return 8;
	else if(ch == "<<" || ch == ">>" ) 
    return 7; 
    else if(ch == "<=" || ch == ">=" || ch== ">" || ch== "<") 
    return 6; 
    else if(ch == "==" || ch == "!=" ) 
    return 5; 
    else if(ch == "&&" ) 
    return 4; 
    else if(ch == "||" ) 
    return 3; 
    else if(ch == "?:" ) 
    return 2; 
    else if(ch == "=" || ch == "+=" || ch == "-=" || ch== "*=" || ch== "/=" || ch== "*=" || ch== "%=") 
    return 1; 
    else
    return -1; 

}

void infixToPreOrPost(string calculate)     //convering infix to posfix or prefix.
{    system("cls");
    string expression=inputExpression();
    
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
   
   if(calculate=="prefix")  // to calculate prefix
     {
     for(int i=0;i<expressionLength;i++){
     	if(expressionVector[i]=="(")
     	expressionVector[i]=")";
     	else if(expressionVector[i]==")")
     	expressionVector[i]="(";
	 }
	 reverse(expressionVector.begin(),expressionVector.end());
	 } 
	 
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
	{
	istringstream stm(outputExpression) ;  //seperating the string with spaces.
    
    string character;
    string temp;  
    
	while( stm >> character )
  {  // adding characters seperated by spaces int temp.
  
     temp=character +" " + temp;  //reversing the string.
   }
    outputExpression=temp; //reversed string.
	} 	
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
   
 void handleUnaryOperator(string unaryOperator,string calculate){
   	    string op1 = operandStack.top(); 
        operandStack.pop();
		if(calculate=="prefixToInfix")  //reverse push order.
        operandStack.push("( " + op1 + " " + unaryOperator + " )"); 
        else
       operandStack.push("( " + unaryOperator + " " + op1 + " )"); 
        
   }
    
   	
	void preOrPostToInfix(string calculate)  //prefix or postfix to infix convert.
	{
	system("cls");
	string expression=inputExpression();
	
	
	istringstream stm(expression) ;
    string character;
    //seperating the string with spaces.
    vector <string> expressionVector;  
    
	while( stm >> character )
  {  // putting characters seperated by spaces into vector.
     expressionVector.push_back(character);
   }
   
   if(calculate=="prefixToInfix")      //to convert prefix to infix. 
   reverse(expressionVector.begin(),expressionVector.end());
       
	 
	  //display of stack table
        cout<<"\n \n \n";
        cout<<"\n"<<"   "<<"Input"<<left<<"   "<<right<<setw(100)<<"Stack"<<endl;
        cout<<" "<<setw(100)<<left<<expression<<"     "<<displayOperandStack()<<endl;
	 
		for (int i=0; i<expressionVector.size() ; i++) 
    {   string st=expressionVector[i];
        // handle operators. 
        if (isOperator(st)) 
        {  
		   if(st=="++" || st=="--" || st=="~" || st=="!")
              handleUnaryOperator(st,calculate);
            
		   else{
            string op1 = operandStack.top(); 
            operandStack.pop(); 
            string op2 = operandStack.top(); 
            operandStack.pop(); 
            operandStack.push("( " + op2 + " " + st + " " + op1 + " )"); 
         
			} 
             
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
     {
	
    istringstream stm(outputExpression) ;  //seperating the string with spaces.
    
    string character;
    string temp;  
    
      while( stm >> character )
      {  // adding characters seperated by spaces int temp.
  
      temp=character +" " + temp;  //reversing the string.
      }
      outputExpression=temp; //reversed string.
	   	
   
	  for(int i=0;i<outputExpression.size();i++)  //converting '(' to ')' and ')' to '('
  	  {
	  	if(outputExpression[i]=='(')
	  	outputExpression[i]=')';
	  	
	  	else if(outputExpression[i]==')')
	  	outputExpression[i]='(';
	   } 
	 }
	
	}
	
	
	                                                                    //Functions for evaluation of expressions.............
	 
	
void evaluate()
{
	system("cls");
	cout<<"\n \n \n ";
	cout<<"  1 - Evaluate Infix  "<<endl;
	cout<<"   2 - Evaluate Postfix  "<<endl;
	cout<<"   3 - Evaluate Prefix  "<<endl;
	cout<<" \n Enter selection: ";
	int selection;
	cin>>selection;
	cout<<"\n";
		
	switch(selection)
{

case 1 :{ evaluateInfix();          
break;
    }
    
case 2 :{ evaluatePostfix("postfix");    
break;
    }
    
case 3 :{ evaluatePrefix();
break;
    }

default :{cout<<"\n Invalid selection";
      exit(1);
   }         
}

	}
	
	
 void evaluateInfix()  //evaluation of infix expression.
	{
		infixToPreOrPost("postfix");   //converting infix expression to postfix expression.
		
		//outputExpression contains the converted posfix form of input.
		
		evaluatePostfix("infix");   // evaluating the postfix converted from infix. 
	    
	}
	
		
 void evaluatePostfix(string type)  //evalutation of postfix expression.
	{   string expression;
	    
		if(type=="infix")    //infixExpression ->postfix ->evaluate.
	   {
		//outputExpression contains the converted posfix form of input.
		expression=outputExpression;   
	    cout<<endl<<endl;
		}
		else
		 {
		  system("cls");
		  expression=inputExpression();
	     }
	     
		istringstream stm(expression) ; //splitting characters seperated by spaces into a vector
        string character;
        //seperating the string with spaces
        vector<string>expressionVector;  
    
	    while( stm >> character )
        {  // put characters seperated by spaces into vector
             expressionVector.push_back(character);
        }
   	    
   	    cout<<"\n\n\n  Steps in evaluation - \n\n";
   	   
		cout<<"\n"<<"   "<<"Input"<<left<<"    "<<right<<setw(100)<<"Symbol"<<"   "<<setw(50)<<right<<"Stack"<<"\n";  //display table
        

   for(int i=0; i<expressionVector.size(); i++) 
   {
      //read elements and perform postfix evaluation
      string input=expressionVector[i];
            
      if(isOperator(input))     //input is a operator
	   {
         double op1 = evaluationStack.top();
         evaluationStack.pop();
         double op2 = evaluationStack.top();
         evaluationStack.pop();
         evaluationStack.push(operation( op1, op2, input ));   //performing operation on numbers.
      
           cout<<" "<<setw(100)<<left<<expression<<"     "<<left<<setw(40)<<input<<"              "<<displayEvaluationStack()<<endl;  //display table
	 
	  }
	  else    //input is a number. 
	   {
	   	stringstream toDouble(input);    //converting the string to double.
	   	double number;
	   	toDouble>>number;
         evaluationStack.push(number);
      
	    cout<<" "<<setw(100)<<left<<expression<<"     "<<left<<setw(40)<<input<<"              "<<displayEvaluationStack()<<endl;  //display table
	 
	  }
   }
       //top of evaluationStack contains the result.
       stringstream toString;
    
	    toString<<evaluationStack.top();   //convering output into string.
        
		toString>>outputExpression;   //storing output into outputExpression.
        
	}
	

    double operation(double a, double b, string op) {
   //Perform operation
   if(op == "+")
      return b+a;
   else if(op == "-")
      return b-a;
   else if(op == "*")
      return b*a;
   else if(op == "/")
      return b/a;
   else if(op == "^")
      return pow(b,a); //find b^a
   else if(op == "%")
      return fmod(b,a);
    else
      return 0;
}
	
 string displayEvaluationStack(){

 	stack<double> temp;
	string currentContentsInStack="";
	
	//getting the contents of the stack in temp.
	while(!evaluationStack.empty()){
		temp.push(evaluationStack.top());
		evaluationStack.pop();
		
	}
	//putting back contents in operatorStack 
    while(!temp.empty()){
    	string instance;
    	evaluationStack.push(temp.top());
    	
    	stringstream toString;   //converting double to string.
		toString<<temp.top();
		toString>>instance;
    	currentContentsInStack+=instance+" ";
    	
		temp.pop();
	}	
	
	 return currentContentsInStack;
 	
 }


	
 void evaluatePrefix(){
 	system("cls");
 	
 	string expression=inputExpression();
 	 	
 	istringstream stm(expression) ; //splitting characters seperated by spaces into a vector
        string character;

        vector<string>expressionVector;  
    
	    while( stm >> character )           //seperating the string with spaces
	    
        {  // put characters seperated by spaces into vector
             expressionVector.push_back(character);
        }
   	    
   	    cout<<"\n\n\n  Steps in evaluation - \n\n";
   	   
		cout<<"\n"<<"   "<<"Input"<<left<<"   "<<right<<setw(100)<<"Symbol"<<"     "<<setw(50)<<right<<"Stack"<<"\n";  //display table
        
   for(int i=expressionVector.size()-1; i>=0 ; i--) 
   {
      //read elements and perform postfix evaluation
      string input=expressionVector[i];
      
      if(isOperator(input))     //input is a operator
	   {
         double op1 = evaluationStack.top();
         evaluationStack.pop();
         double op2 = evaluationStack.top();
         evaluationStack.pop();
         evaluationStack.push(operation( op2, op1, input ));   //performing operation on numbers.
         
         cout<<" "<<setw(100)<<left<<expression<<"     "<<left<<setw(40)<<input<<"              "<<displayEvaluationStack()<<endl;  //display table
	 
      }
	  else    //input is a number. 
	   {
	   	stringstream toDouble(input);    //converting the string to double.
	   	double number;
	   	toDouble>>number;
        evaluationStack.push(number);
        
        cout<<" "<<setw(100)<<left<<expression<<"     "<<left<<setw(40)<<input<<"              "<<displayEvaluationStack()<<endl;  //display table
	 
      }
   }
       //top of evaluationStack contains the result.
       stringstream toString;
        string output;
	    toString<<evaluationStack.top();   //convering output into string.
        
		toString>>outputExpression;   //storing  into outputExpression.
        
 	
 }	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
      
