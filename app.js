
class Calculator {
  constructor() {}

  run() {
    this.num1Input = document.getElementById("num1");
    this.num2Input = document.getElementById("num2");
    this.resultDisplay = document.getElementById("result");
    this.activeInput = this.num1Input;

    document.getElementById("num1").addEventListener("focus", () => {
      this.activeInput = this.num1Input;
    });
    document.getElementById("num2").addEventListener("focus", () => {
      this.activeInput = this.num2Input;
    });

    document.getElementById("btn0").addEventListener("click", () => this.appendNumber("0"));
    document.getElementById("btn1").addEventListener("click", () => this.appendNumber("1"));
    document.getElementById("btn2").addEventListener("click", () => this.appendNumber("2"));
    document.getElementById("btn3").addEventListener("click", () => this.appendNumber("3"));
    document.getElementById("btn4").addEventListener("click", () => this.appendNumber("4"));
    document.getElementById("btn5").addEventListener("click", () => this.appendNumber("5"));
    document.getElementById("btn6").addEventListener("click", () => this.appendNumber("6"));
    document.getElementById("btn7").addEventListener("click", () => this.appendNumber("7"));
    document.getElementById("btn8").addEventListener("click", () => this.appendNumber("8"));
    document.getElementById("btn9").addEventListener("click", () => this.appendNumber("9"));

    document.getElementById("addBtn").addEventListener("click", () => this.add());
    document.getElementById("subBtn").addEventListener("click", () => this.subtract());
    document.getElementById("mulBtn").addEventListener("click", () => this.multiply());
    document.getElementById("divBtn").addEventListener("click", () => this.divide());
    document.getElementById("powBtn").addEventListener("click", () => this.powerOperation());
  }

  appendNumber(number) {
    this.activeInput.value += number;
  }

  getFirstValue() {
    return parseFloat(this.num1Input.value);
  }

  getSecondValue() {
    return parseFloat(this.num2Input.value);
  }

  showResult(text, isError) {
    this.resultDisplay.textContent = "Result: " + text;
    if (isError) {
        this.resultDisplay.style.color = "red";
    } else {
        this.resultDisplay.style.color = "black";
    }
  }

  validate(a, b) {
    if (isNaN(a) || isNaN(b)) {
      this.showResult("Enter valid numbers", true);
      return false;
    }
    return true;
  }

  powerOperation() {
      const a = this.getFirstValue();
      const b = this.getSecondValue();
      if (this.validate(a, b)) {
          this.showResult(Math.pow(a, b));
      }
  }


  add() {
    var a = this.getFirstValue();
    var b = this.getSecondValue();
    if (this.validate(a, b)) this.showResult(a + b);
  }

  subtract() {
    var a = this.getFirstValue();
    var b = this.getSecondValue();
    if (this.validate(a, b)) this.showResult(a - b);
  }

  multiply() {
    var a = this.getFirstValue();
    var b = this.getSecondValue();
    if (this.validate(a, b)) this.showResult(a * b);
  }

  divide() {
    var a = this.getFirstValue();
    var b = this.getSecondValue();
    if (!this.validate(a, b)) return;
    if (b === 0) {
      this.showResult("Cannot divide by zero", true);
    } else {
      this.showResult(a / b);
    }
  }
}

// Create calculator object
var calc = new Calculator();
calc.run();
