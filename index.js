console.log("document is loaded");
//infix to postfix converter .......
var operatorStack = []; //for storing operators.......
var outputArr = []; //for storing output........
function isOperator(char) {
  switch (char) {
    case "++":
    case "--":
    case "~":
    case "!":
    case "&": //unary operator HIGHEST PRECEDENCE.......
    case "^":
    case "$": //2nd HIGHEST PRECIDENCE.....
    case "*":
    case "/":
    case "%": //3rd HIGHEST PRECEDENCE .......
    case "+":
    case "-": //4th HIGHTEST PRECEDENCE .........
    case "<":
    case ">":
    case "<=":
    case ">=": //5th HIGHEST PRECEDENCE ..........
    case "==":
    case "!=": //6th HIGHEST PRECEDENCE .............
    case "&&": //7th HIGHEST PRECEDENCE .............
    case "||": //8th HIGHEST PRECEDENCE .............
    case "?:": //9th HIGHEST PRECEDENCE .............
    case "=":
    case "+=":
    case "-=":
    case "*=": //10th HIGHTEST PRECEDENCE ............

    case "(":
    case "#":
      return 1;
    default:
      return 0;
  }
}
function operatorNo(char) {
  //assigning a number to the operators according to precedence........
  if (
    char === "++" ||
    char === "--" ||
    char === "~" ||
    char === "!" ||
    char === "&"
  )
    return 1;
  else if (char === "^" || char === "$") return 2;
  else if (char === "*" || char === "/" || char === "%") return 3;
  else if (char === "+" || char === "-") return 4;
  else if (char === ">" || char === "<" || char === "<=" || char === ">=")
    return 5;
  else if (char === "==" || char === "!=") return 6;
  else if (char === "&&") return 7;
  else if (char === "||") return 8;
  else if (char === "?:") return 9;
  else return 10;
}
function placeOperator(char) {
  if (char === "(") {
    operatorStack.push(char);
    return 0;
  }
  var currentOperatorReplacingPower = operatorNo(char);
  console.log(
    "currentOperatorReplacingPower is " + currentOperatorReplacingPower
  );
  var stackOperatorReplacingPower = operatorNo(
    operatorStack[operatorStack.length - 1]
  );
  if (currentOperatorReplacingPower < stackOperatorReplacingPower) {
    //if current operator percedence is highter than that in the stack top
    operatorStack.push(char);
  } else {
    while (
      currentOperatorReplacingPower >= stackOperatorReplacingPower &&
      operatorStack.length > 0
    ) {
      outputArr.push(operatorStack[operatorStack.length - 1]);
      operatorStack.pop();
      stackOperatorReplacingPower = operatorNo(
        operatorStack[operatorStack.length - 1]
      );
    }
    operatorStack.push(char);
  }
}
function handleClosingBracket(char) {
  for (let i = operatorStack.length - 1; i >= 0; i--) {
    if (operatorStack[i] === "(") {
      operatorStack.pop();
      break;
    } else {
      outputArr.push(operatorStack[i]);
      operatorStack.pop();
    }
  }
}
var table = document.getElementById("table");

function postfix(arr) {
  //main function ..........
  table.innerHTML = "";
  var tableHeader1 = document.createElement("th");
  tableHeader1.innerHTML = "expression";
  table.appendChild(tableHeader1);
  var tableHeader2 = document.createElement("th");
  tableHeader2.innerHTML = "stack";
  table.appendChild(tableHeader2);
  var tableHeader3 = document.createElement("th");
  tableHeader3.innerHTML = "output";
  table.appendChild(tableHeader3);

  for (let i = 0; i < arr.length; i++) {
    var row = table.insertRow(i);
    var cell1 = row.insertCell(0);
    var cell2 = row.insertCell(1);
    var cell3 = row.insertCell(2);
    let char = arr[i]; //picking every element of input individually......
    cell1.innerHTML = arr.join(" ");
    if (isOperator(char) === 1) {
      placeOperator(char); //placing the operator in the write position.........
    } else if (char == ")") {
      handleClosingBracket(char);
    } else outputArr.push(char);
    cell2.innerHTML = operatorStack.join(" ");
    cell3.innerHTML = outputArr.join(" ");
  }
}
function handleClick() {
  var input = document.getElementById("expression").value;
  var input = "( " + input + " )";
  var inputArr = input.split(" "); //splitting the input by spaces .......

  postfix(inputArr);
  console.log("outputArr " + outputArr);
  console.log("operatorStack " + operatorStack);
  var answer = outputArr.join(" ");
  var output = document.getElementById("displayOutput");
  output.innerHTML = answer;
  document.getElementById("answer").classList.remove("hidden");

  outputArr = [];
  operatorStack = [];
}
