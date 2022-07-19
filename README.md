# Kiraak

Who doesn't like programming when the code is actually speaking to you?! <b><i>Kiraak</i></b> does just that!

An engaging, exciting and fun language, made especially for <b>Hyderabadis</b>!
<br />

The fun part? You get to code in complete <i>Hyderabadi</i>!!

<i>Toot pado miyaan!</i>

## Grammar rules

* Conditional
  * <b><i>agar</i></b> Expression <b><i>tho</i></b> Expression <br />
    ( <b><i>ya phir</i></b> Expression tho Expression ) * <br />
    ( <b><i>nahi tho</i></b> Expression ) *


* Literal 
  * \<VAR>
  * Conditional
  * \<INT> | \<DOUBLE>
  * \<LPAREN> + Expression + \<RPAREN>


* Power
  * Literal + ( \<POW> + Factor )*
  

* Factor
  * ( \<PLUS> | \<MINUS> ) + Power


* Modulo
  * Factor + ( \<MOD> + Factor )*


* Term
  * Modulo + ( ( \<STAR> | \<DIV> ) + Modulo )*


* ArithmeticExpr
  * Term + ( ( \<PLUS> | \<MINUS> ) + Term )*


* Comparison
  * Comparison <b><i>nahi hai</i></b>
  * ArithmeticExpr + ArithmeticExpr + ( <b><i>EQ</i></b> | <b><i>LT</i></b> | <b><i>GT</i></b> | <b><i>LTE</i></b> | <b><i>GTE</i></b> )


* Conjunction
  * Comparison ( <b><i>aur</i></b> | <b><i>ya</i></b> ) Comparison


* Expression
  * \<VAR> <b><i>boletho</i></b> Expression 
  * Conjunction

<br />


### Variable Assignment
&lt;VAR> <b><i>boletho</i></b> Expression


### Comparison
* Equal to:
  * Expression Literal <b><i>hai</i></b>
  * Expression1 Expression2 <b><i>jitta hai</i></b>
  * Expression1 Expression2 <b><i>ke baraabar hai</i></b>
  * Expression1 Expression2 <b><i>jitta</i></b> ( <b><i>bada</i></b> | <b><i>chota</i></b> ) <b><i>hai</i></b>


* Not equal to:
  * Comparison <b><i>nahi hai</i></b>
  

* Less than: 
  * Expression1 Expression2 <b><i>se chota hai</i></b>
  

* Greater than: 
  * Expression1 Expression2 <b><i>se bada hai</i></b>
  

* Less than or equal to: 
  * Expression1 Expression2 <b><i>jitta ya chota hai</i></b>
  

* Greater than or equal to: 
  * Expression1 Expression2 <b><i>jitta ya bada hai</i></b>



### Logical Conjunction
* AND: Expression1 <b><i>aur</i></b> Expression2 <b><i>hai</i></b>
* OR: Expression1 <b><i>ya</i></b> Expression2 <b><i>hai</i></b>
* NOT: Expression <b><i>nahi hai</i></b>


## Operators

### Math
* a + b -> addition
* a - b -> subtraction
* a * b -> multiplication
* a / b -> division
* a ^ b -> power
* a % b -> modulo


