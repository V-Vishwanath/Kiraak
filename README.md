# Kiraak

Who doesn't like programming when the code is actually speaking to you?! <b><i>Kiraak</i></b> does just that!

An engaging, exciting and fun language, made especially for <b>Hyderabadis</b>!
<br />

The fun part? You get to code in complete <i>Hyderabadi</i>!!

<i>Toot pado miyaan!</i>

## Grammer rules

* Literal 
  * \<VAR> 
  * \<INT> | \<DOUBLE>
  * \<LPAREN> + Expression + \<RPAREN>


* Power
  * Literal + ( \<POW> + Factor )*
  

* Factor
  * ( \<ADD> | \<SUB> ) + Power


* Modulo
  * Factor + ( \<MOD> + Factor )*


* Term
  * Modulo + ( ( \<MUL> | \<DIV> ) + Modulo )*


* Expression
  * \<VAR> \<KW: <i>boletho</i>> Expression 
  * Term + ( ( \<ADD> | \<SUB> ) + Term )*

<br />


### Variable Assignment
&lt;VAR> <i>boletho</i> Expression


## Operators

### Math
* a + b -> addition
* a - b -> subtraction
* a * b -> multiplication
* a / b -> division
* a ^ b -> power
* a % b -> modulo


