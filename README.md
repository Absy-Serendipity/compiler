<a name="br1"></a> 

**Compiler for Simplified**

**C language**



<a name="br2"></a> 

**1.Regular Expression**

**(Lexical Analyzer)**



<a name="br3"></a> 

Sub regular expressions

• digit : 0|1|2|3|4|5|6|7|8|9

• digit\_ : 1|2|3|4|5|6|7|8|9

• Letter :

a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|

Y|Z



<a name="br4"></a> 

~~vtype~~

• alphabet: [a, b, c, h, i, l, n, o, r, s, t]

• regular expression: int|char|bool|string

i

ε

n

ε

t

ε

3

9

4

5

6

7

8

3

7

2

c

ε

ε

h

o

ε

ε

a

ε

ε

r

l

1

0

1

1

1

2

1

3

1

4

1

5

1

6

ε

3

8

1

b

o

1

7

1

8

1

9

2

0

2

1

2

2

2

3

2

4

ε

ε

3

0

9

s

ε

t

ε

r

ε

i

ε

n

2

5

2

6

2

7

2

8

2

9

3

0

3

1

3

2

3

3

3

4

ε

ε

g

3

3

6

5



<a name="br5"></a> 

~~boolstr~~

• alphabet: [a, e, f, l, r, s, t, u]

• regular expression: true|false

e

ε

l

ε

s

ε

e

1

2

3

4

5

6

7

8

1

9

0

w

ε

h

ε

i

ε

l

ε

e

1

0

1

1

1

2

1

3

1

4

1

5

1

6

1

7

1

8

9



<a name="br6"></a> 

~~if~~

• alphabet: [f, i]

• regular expression: if

i

ε

f

0

1

2

3



<a name="br7"></a> 

~~else~~

• alphabet: [e, l, s]

• regular expression: else

e

ε

l

ε

s

ε

e

0

1

2

3

4

5

6

7



<a name="br8"></a> 

~~while~~

• alphabet: [e, h, i, l, w]

• regular expression: while

w

ε

h

ε

i

ε

l

ε

e

0

1

2

3

4

5

6

7

8

9



<a name="br9"></a> 

~~return~~

• alphabet: [e, n, r, t, u]

• regular expression: return

r

ε

e

ε

t

ε

u

ε

r

0

1

2

3

4

5

6

7

8

9

ε

n

1

0

1

1



<a name="br10"></a> 

~~num~~

• alphabet: [-, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ε]

• regular expression: 0|(ε|-)(digit\_)(digit)\*

• NFA

0

1

3

2

ε

ε

0

ε

ε

1

5

ε

digit\_

ε

4

5

7

ε

1

0

8

9

\-

ε

ε

6

ε

ε

ε

digit

ε

1

1

1

2

1

3

1

4

ε



<a name="br11"></a> 

~~num~~

ε-closure(0) = {0, 1, 3, 4, 5, 6, 8, 9} = T0

ε-closure(δ(T0, 0)) = {2, 15} = T1

ε-closure(δ(T0, digit\_)) = {10, 11, 14, 15} = T2

ε-closure(δ(T0, -)) = {7, 8, 9} = T3

ε-closure(δ(T0, digit)) = ∅

ε-closure(δ(T1, 0)) = ∅

ε-closure(δ(T1, digit\_)) = ∅

ε-closure(δ(T1, -)) = ∅

ε-closure(δ(T1, digit)) = ∅

ε-closure(δ(T2, 0)) = ∅

ε-closure(δ(T2, digit\_)) = ∅

ε-closure(δ(T2, -)) = ∅

ε-closure(δ(T2, digit)) = {12, 13, 14 ,15} = T4



<a name="br12"></a> 

~~num~~

ε-closure(δ(T3, 0)) = ∅

ε-closure(δ(T3, digit\_)) = T2

ε-closure(δ(T3, -)) = ∅

ε-closure(δ(T3, digit)) = ∅

ε-closure(δ(T4, 0)) = ∅

ε-closure(δ(T4, digit\_)) = ∅

ε-closure(δ(T4, -)) = ∅

ε-closure(δ(T4, digit)) = T4



<a name="br13"></a> 

~~num~~

• DFA

T

1

0

digit

digit\_

digit

T

2

T

4

T

0

\-

digit\_

T

3



<a name="br14"></a> 

~~character~~

• alphabet: [ε, , ‘, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y,

Z, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z]

• regular expression: 'letter| |ε|digit’

• NFA

letter

5

7

9

6

8

ε

ε

ε

ε

1

3

4

digit

ε

ε

1

4

3

ε

1

0

ε

ε

ε

ε

'

ε

1

5

1

6

1

7

'

2

0

1

ε

ε

1

1

1

2

ε



<a name="br15"></a> 

~~character~~

ε-closure(0) = {0} = T0

ε-closure(δ(T0, ')) = {0, 1, 2, 3, 4, 5, 7, 9, 11, 12, 15, 16} = T1

ε-closure(δ(T0, letter)) = ∅

ε-closure(δ(T0, digit)) = ∅

ε-closure(δ(T0, )) = ∅

ε-closure(δ(T1, ')) = {17} = T2

ε-closure(δ(T1, letter)) = {6, 13, 14, 15, 16, 17} = T3

ε-closure(δ(T1, digit)) = {8, 13, 14, 15, 16, 17} = T4

ε-closure(δ(T1, )) = {10, 14, 15, 16, 17} = T5

ε-closure(δ(T2, ')) = ∅

ε-closure(δ(T2, letter)) = ∅

ε-closure(δ(T2, digit)) = ∅

ε-closure(δ(T2, )) = ∅



<a name="br16"></a> 

~~character~~

ε-closure(δ(T3, ')) = {17} = T2

ε-closure(δ(T3, letter)) = ∅

ε-closure(δ(T3, digit)) = ∅

ε-closure(δ(T3, )) = ∅

ε-closure(δ(T4, ')) = {17} = T2

ε-closure(δ(T4, letter)) = ∅

ε-closure(δ(T4, digit)) = ∅

ε-closure(δ(T4, )) = ∅

ε-closure(δ(T5, ')) = {17} = T2

ε-closure(δ(T5, letter)) = ∅

ε-closure(δ(T5, digit)) = ∅

ε-closure(δ(T5, )) = ∅



<a name="br17"></a> 

~~character~~

• DFA

'

T

3

letter

T

T

0

T

1

T

2

'

'

digit 4

T

5



<a name="br18"></a> 

~~string~~

• alphabet: [ , ", 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, a,

b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z]

• regular expression: "(letter| |digit)\*"

letter

5

7

9

6

8

ε

ε

ε

ε

1

1

4

digit

ε

ε

ε

ε

ε

ε

1 " 1

1

2

1

3

"

0

1

2

3

4

5

1

0

ε

ε



<a name="br19"></a> 

~~string~~

ε-closure(0) = {0} = T0

ε-closure(δ(T0, ")) = {1, 2, 3, 4, 5, 7, 9, 13, 14} = T1

ε-closure(δ(T1, letter)) = {3, 4, 5, 6, 7, 9, 11, 12} = T2

ε-closure(δ(T1, digit)) = {3, 4, 5, 7, 8, 9, 11, 12} = T3

ε-closure(δ(T1, )) = {3, 4, 5, 7, 9, 10, 12} = T4

ε-closure(δ(T1, ")) = {15} = T5

ε-closure(δ(T2, letter)) = {3, 4, 5, 6, 7, 9, 11, 12} = T2

ε-closure(δ(T2, digit)) = {3, 4, 5, 7, 8, 9, 11, 12} = T3

ε-closure(δ(T2, )) = {3, 4, 5, 7, 9, 10, 12} = T4

ε-closure(δ(T2, ")) = {15} = T5



<a name="br20"></a> 

~~string~~

ε-closure(δ(T3, letter)) = {3, 4, 5, 6, 7, 9, 11, 12} = T2

ε-closure(δ(T3, digit)) = {3, 4, 5, 7, 8, 9, 11, 12} = T3

ε-closure(δ(T3, )) = {3, 4, 5, 7, 9, 10, 12} = T4

ε-closure(δ(T3, ")) = {15} = T5

ε-closure(δ(T4, letter)) = {3, 4, 5, 6, 7, 9, 11, 12} = T2

ε-closure(δ(T4, digit)) = {3, 4, 5, 7, 8, 9, 11, 12} = T3

ε-closure(δ(T4, )) = {3, 4, 5, 7, 9, 10, 12} = T4

ε-closure(δ(T4, ")) = {15} = T5

ε-closure(δ(T5, letter)) = {3, 4, 5, 6, 7, 9, 11, 12} = ∅

ε-closure(δ(T5, digit)) = {3, 4, 5, 7, 8, 9, 11, 12} = ∅

ε-closure(δ(T5, )) = {3, 4, 5, 7, 9, 10, 12} = ∅

ε-closure(δ(T5, ")) = {15} = ∅



<a name="br21"></a> 

~~string~~

• DFA

"

T

2

letter

letter

digit

digit

letter

digit

T

3

T

0

T

1

T

5

"

"

T

4



<a name="br22"></a> 

~~id~~

• alphabet: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, a, b,

c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z]

• regular expression: letter(digit|letter)\*

digit

4

6

5

7

ε

ε

ε

ε

letter

ε

ε

ε

0

1

2

3

8

9

letter



<a name="br23"></a> 

~~id~~

ε-closure(0) = {0} = T0

ε-closure(δ(T0, letter)) = {1, 2, 3, 4, 6, 9} = T1

ε-closure(δ(T0, digit)) = ∅

ε-closure(δ(T1, letter)) = {3, 4, 6, 7, 8, 9} = T2

ε-closure(δ(T1, digit)) = {3, 4, 5, 6, 8, 9} = T3

ε-closure(δ(T2, letter)) = {3, 4, 6, 7, 8, 9} = T2

ε-closure(δ(T2, digit)) = {3, 4, 5, 6, 8, 9} = T3

ε-closure(δ(T3, letter)) = {3, 4, 6, 7, 8, 9} = T2

ε-closure(δ(T3, digit)) = {3, 4, 5, 6, 8, 9} = T3



<a name="br24"></a> 

~~id~~

• DFA

letter

T

2

letter

digit

letter

T

0

T

1

letter

digit

digit

T

3



<a name="br25"></a> 

~~comp~~

• alphabet: [!, <, =, >]

• regular expression: ==|!=|<|>|<=|>=

\=

!

ε

ε

ε

ε

\=

\=

\=

\=

5

9

6

7

8

ε

ε

ε

ε

2

5

4

1

0

1

1

1

2

ε

ε

2

6

3

ε

<

\>

1

3

1

4

1

5

1

6

ε

ε

2

7

2

ε

1

7

1

8

1

9

2

0

ε

ε

2

8

1

ε

<

\>

2

1

2

2

ε

ε

ε

2

9

0

2

3

2

4

ε

ε



<a name="br26"></a> 

~~comp~~

ε-closure(0) = {0, 1, 2, 3, 4, 5, 9, 13, 17, 21, 23} = T0

ε-closure(δ(T0, =)) = {6, 7} = T1

ε-closure(δ(T0, !)) = {10, 11} = T2

ε-closure(δ(T0, <)) = {14, 15, 22, 28, 29} = T3

ε-closure(δ(T0, >)) = {18, 19, 24, 29} = T4

ε-closure(δ(T1, =)) = {8, 25, 26, 27, 28, 29} = T5

ε-closure(δ(T1, !)) = ∅

ε-closure(δ(T1, <)) = ∅

ε-closure(δ(T1, >)) = ∅

ε-closure(δ(T2, =)) ={12, 25, 26, 27, 28, 29} = T6

ε-closure(δ(T2, !)) = ∅

ε-closure(δ(T2, <)) = ∅

ε-closure(δ(T2, >)) = ∅



<a name="br27"></a> 

~~comp~~

ε-closure(δ(T3, =)) = {16, 26, 27, 28, 29} = T7

ε-closure(δ(T3, !)) = ∅

ε-closure(δ(T3, <)) = ∅

ε-closure(δ(T3, >)) = ∅

ε-closure(δ(T4, =)) = {20, 27, 28, 29} = T8

ε-closure(δ(T4, !)) = ∅

ε-closure(δ(T4, <)) = ∅

ε-closure(δ(T4, >)) = ∅

ε-closure(δ(T5, =)) = ∅

ε-closure(δ(T5, !)) = ∅

ε-closure(δ(T5, <)) = ∅

ε-closure(δ(T5, >)) = ∅



<a name="br28"></a> 

~~comp~~

ε-closure(δ(T6, =)) = ∅

ε-closure(δ(T6, !)) = ∅

ε-closure(δ(T6, <)) = ∅

ε-closure(δ(T6, >)) = ∅

ε-closure(δ(T7, =)) = ∅

ε-closure(δ(T7, !)) = ∅

ε-closure(δ(T7, <)) = ∅

ε-closure(δ(T7, >)) = ∅

ε-closure(δ(T8, =)) = ∅

ε-closure(δ(T8, !)) = ∅

ε-closure(δ(T8, <)) = ∅

ε-closure(δ(T8, >)) = ∅



<a name="br29"></a> 

~~comp~~

• DFA

T

1

\=

\=

\=

\=

T

5

\=

T

2

T

6

!

T

0

<

T

3

T

7

\>

T

4

T

8



<a name="br30"></a> 

~~addsub~~

• alphabet: [+, -]

• regular expression: +|-

\+

\-

1

3

2 ε

ε

5

0

ε

ε

4



<a name="br31"></a> 

~~addsub~~

• DFA

1

2

\+

0

\-



<a name="br32"></a> 

~~multidiv~~

• alphabet: [\*, /]

• regular expression: \*|/

\*

/

1

3

2 ε

ε

5

0

ε

ε

4



<a name="br33"></a> 

~~multidiv~~

• DFA

1

2

\+

0

\-



<a name="br34"></a> 

~~whitespace~~

• alphabet:[ , \t, \n]

• regular expression: \t| |\n

2

3

ε

ε

ε

1

8

\t

ε

4

6

5

7

ε

ε

0

9

\n

ε

ε



<a name="br35"></a> 

~~whitespace~~

ε-closure(0) = {0, 1, 2, 4, 6} = T0

ε-closure(δ(T0, )) = {3, 8, 9} = T1

ε-closure(δ(T0, \n)) = {5, 8, 9} = T2

ε-closure(δ(T0, \t)) = {7, 9} = T3

ε-closure(δ(T1, )) = ∅

ε-closure(δ(T1, \n)) = ∅

ε-closure(δ(T1, \t)) = ∅

ε-closure(δ(T2, )) = ∅

ε-closure(δ(T2, \n)) = ∅

ε-closure(δ(T2, \t)) = ∅

ε-closure(δ(T3, )) = ∅

ε-closure(δ(T3, \n)) = ∅

ε-closure(δ(T3, \t)) = ∅



<a name="br36"></a> 

~~whitespace~~

• DFA

T

1

T

0

T

3

\t

\n

T

4



<a name="br37"></a> 

~~assign~~

• DFA

\=

0

1



<a name="br38"></a> 

~~merged~~



<a name="br39"></a> 

~~merged~~

ε-closure(0) = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 15, 20, 30, 35, 42, 49, 55} = T0

ε-closure(δ(T0, +)) = {10, 14, 19, 29, 34, 41, 48, 54, 57} = T1 (addsub)

ε-closure(δ(T0, -)) = {11, 14, 19, 29, 34, 41, 48, 52, 54, 57 } = T2 (addsub)

ε-closure(δ(T2, digit\_)) = {51, 54, 57} = T3 (num)

ε-closure(δ(T3, digit)) = {53, 54, 57} = T4 (num)

ε-closure(δ(T4, digit)) = {53, 54, 57} = T4 (num)

ε-closure(δ(T0, \*)) = {12, 14, 19, 29, 34, 41, 48, 54, 57} = T5 (arithmetic)

ε-closure(δ(T0, /)) = {13, 14, 19, 29, 34, 41, 48, 54, 57} = T6 (arithmetic)

ε-closure(δ(T0, )) = {16, 19, 29, 34, 41, 48, 52, 54, 57 } = T7 (whitespace)

ε-closure(δ(T0, \t)) = {17, 19, 29, 34, 41, 48, 52, 54, 57 } = T8 (whitespace)

ε-closure(δ(T0, \n)) = {18, 19, 29, 34, 41, 48, 52, 54, 57 } = T9 (whitespace)



<a name="br40"></a> 

~~merged~~

ε-closure(δ(T0, =)) = {21, 56, 57} = T10 (assign)

ε-closure(δ(T10, =)) = {25, 29, 34, 41, 48, 54, 57} = T11 (comp)

ε-closure(δ(T0, !)) = {22} = T12

ε-closure(δ(T12, =)) = {26, 29, 34, 41, 48, 54, 57} = T13(comp)

ε-closure(δ(T0, <)) = {23, 29, 34, 41, 48, 54, 57} = T14 (comp)

ε-closure(δ(T14, =)) = {27, 29, 34, 41, 48, 54, 57} = T15 (comp)

ε-closure(δ(T0, >)) = {24, 29, 34, 41, 48, 54, 57} = T16 (comp)

ε-closure(δ(T16, =)) = {28, 29, 34, 41, 48, 54, 57} = T17 (comp)



<a name="br41"></a> 

~~merged~~

ε-closure(δ(T0, letter)) = {31, 34, 41, 48, 54, 57} = T18 (vtype)

ε-closure(δ(T18, letter)) = {32, 34, 41, 48, 54, 57} = T19 (vtype)

ε-closure(δ(T18, digit)) = {33, 34, 41, 48, 54, 57} = T20 (vtype)

ε-closure(δ(T19, letter)) = {32, 34, 41, 48, 54, 57} = T19 (vtype)

ε-closure(δ(T19, digit)) = {33, 34, 41, 48, 54, 57} = T20 (vtype)

ε-closure(δ(T20, letter)) = {32, 34, 41, 48, 54, 57} = T19 (vtype)

ε-closure(δ(T20, digit)) = {33, 34, 41, 48, 54, 57}} = T20 (vtype)



<a name="br42"></a> 

~~merged~~

ε-closure(δ(T0, ")) = {36} = T21

ε-closure(δ(T21, letter)) = {37} = T22

ε-closure(δ(T21, digit)) = {38} = T23

ε-closure(δ(T21, )) = {39} = T24

ε-closure(δ(T22, letter)) = {37} = T22

ε-closure(δ(T23, letter)) = {37} = T22

ε-closure(δ(T24, letter)) = {37} = T22

ε-closure(δ(T19, digit)) = {38} = T23

ε-closure(δ(T19, digit)) = {38} = T23

ε-closure(δ(T19, digit)) = {38} = T23

ε-closure(δ(T19, )) = {39} = T24

ε-closure(δ(T19, )) = {39} = T24

ε-closure(δ(T19, )) = {39} = T24



<a name="br43"></a> 

~~merged~~

ε-closure(δ(T21, ")) = {40, 41, 48, 54, 57} = T25 (string)

ε-closure(δ(T22, ")) = {40, 41, 48, 54, 57} = T25 (string)

ε-closure(δ(T23, ")) = {40, 41, 48, 54, 57} = T25 (string)

ε-closure(δ(T24, ")) = {40, 41, 48, 54, 57} = T25 (string)



<a name="br44"></a> 

~~merged~~

ε-closure(δ(T0, ')) = {43} = T26

ε-closure(δ(T26, letter)) = {44} = T27

ε-closure(δ(T26, digit)) = {45} = T28

ε-closure(δ(T26, )) = {46} = T29

ε-closure(δ(T27, ')) = {47, 48, 54, 57} = T30 (char)

ε-closure(δ(T28, ')) = {47, 48, 54, 57} = T30 (char)

ε-closure(δ(T29, ')) = {47, 48, 54, 57} = T30 (char)



<a name="br45"></a> 

~~merged~~

ε-closure(δ(T0, 0)) = {50, 54, 57} = T31 (num)

ε-closure(δ(T0, digit\_)) = {51, 54, 57} = T32 (num)

ε-closure(δ(T32, digit)) = {53, 54, 57} = T33 (num)

ε-closure(δ(T33, digit)) = {53, 54, 57} = T33 (num)



<a name="br46"></a> 

~~semi~~

;

0

1

~~comma~~

,

0

1

~~endmark~~

$

0

1



<a name="br47"></a> 

~~laparen~~

(

0

1

~~rparen~~

)

0

1

~~lbrace~~

{

0

1

~~rbrace~~

}

0

1



<a name="br48"></a> 

~~and~~

&

0

~~or~~

0

1

1

|



<a name="br49"></a> 

**2. Context-free Grammar**

**(Syntax Analyzer)**



<a name="br50"></a> 

Production Rules

**1. S -> CODE**

**12.EXPR -> CALL**

**2. CODE -> VDECL CODE**

**3. CODE -> FDECL CODE**

**4. CODE -> ''**

**13.EXPR -> TERM addsub EXPR**

**14.EXPR -> TERM**

**15.TERM -> FACT multdiv TERM**

**16.TERM -> FACT**

**5. VDECL -> vtype id**

**semi**

**17.FACT -> num**

**6. VDECL -> vtype**

**ASSIGN semi**

**18.FACT -> lparen EXPR rparen**

**19.FACT -> id**

**7. ASSIGN -> id assign**

**RHS**

**20.FDECL -> vtype id lparen ARG**

**rparen lbrace BLOCK RETURN**

**rbrace**

**8. RHS -> EXPR**

**9. RHS -> char**

**10.RHS -> string**

**11.RHS -> boolstr**

**21.ARG -> vtype id MOREARGS**

**22.ARG -> ''**



<a name="br51"></a> 

Production Rules

**23.MOREARGS -> comma vtype id 35.MOREARGVAL -> comma EXPR**

**MOREARGS**

**MOREARGVAL**

**24.MOREARGS -> ''**

**25.BLOCK -> STMT BLOCK**

**26.BLOCK -> ''**

**36.MOREARGVAL -> ''**

**37.COND**

**->**

**COND\_EXPR**

**LOGIC\_EXPR**

**38.COND\_EXPR -> boolstr**

**39.COND\_EXPR -> FACT comp FACT**

**40.LOGIC\_EXPR -> ''**

**27.STMT -> VDECL**

**28.STMT -> ASSIGN semi**

**29.STMT -> CALL semi**

**41.LOGIC\_EXPR -> LOGIC\_OP**

**COND**

**30.STMT -> if lparen COND rparen**

**lbrace BLOCK rbrace ELSE**

**42.LOGIC\_OP -> and**

**43.LOGIC\_OP -> or**

**31.STMT -> while lparen COND**

**rparen lbrace BLOCK rbrace**

**32.CALL -> id lparen ARGVAL rparen 44.ELSE -> else lbrace BLOCK**

**rbrace**

**33.ARGVAL -> EXPR MOREARGVAL**

**34.ARGVAL -> ''**

**45.ELSE -> ’’**



<a name="br52"></a> 

Terminals

**1. vtype** for the types of variables and functions

**2. num** for signed integers

**3. char** for a single character

**4. boolstr** for Boolean strings

**5. string** for literal strings

**6. id** for the identifiers of variables and functions

**7. if**, **else**, **while**, and **return** for if, else, while, and return statements

respectively

**8. addsub** for +, and -

**9. multidiv** for \*, and /

**10.assign** for assignment operators

**11.comp** for comparison operators

**12.semi** and **comma** for semicolons and commas respectively

**13.lparen, rparen, lbrace**, and **rbrace** for (, ), {, and } respectively

**14.and,** and **or** for & and |



<a name="br53"></a> 

Non-termianls

EXPR, VDECL, LOGIC\_EXPR, CODE, CALL, ELSE, ARGVAL,

MOREARGVAL,

BLOCK, ASSIGN,STMT, FACT, COND, MOREARGS, RHS, S,

RETURN,

COND\_EXPR, TERM, FDECL, ARG, LOGIC\_OP



<a name="br54"></a> 

Descriptions

1\. A file of source code is constructed with zero or more declarations of functions or

variables

2\. Declaration of a variable is allowed regardless of initialization

3\. Five types of the right-hand side of a variable

a) Expression

b) String

c) Character

d) Boolean

e) Function return value

4\. A function has zero or more arguments

5\. A function block includes zero or more statements

6\. Five types of statements

a) Variable declaration

b) Assignment operation

c) Function call

d) If-else statement

e) While statement



<a name="br55"></a> 

Descriptions

7\. If and while statements include one or more conditions that comprise Boolean

values generated by comparison operations or logical operations

8\. If statement stands alone or with an else statement

9\. A return statement returns five types

a) Expression

b) String

c) Character

d) Boolean

e) Function return value

