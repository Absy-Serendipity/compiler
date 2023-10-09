<a name="br1"></a> 

Co mpiler for

Simplifie d C language



<a name="br2"></a> 

1\.Regu lar Expre ssio n

( L exical Analyze r)



<a name="br3"></a> 

Sub regu lar expre ssio ns

• dig it  : 0|1|2|3|4|5|6|7|8|9

• dig it\_  : 1|2|3|4|5|6|7|8|9

• Lette r :

~~a|b|c|d|~~e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|

V|W|X|Y|Z



<a name="br4"></a> 

~~vtype~~

• alphabet: [a, b, c, h, i, l, n, o, r, s, t]

• regu lar expression: int|char|bool|string

i

ε

n

ε

t

ε

3

4

5

6

7

8

2

37

c

ε

ε

h

o

ε

ε

a

o

ε

ε

r

l

ε

9

10

18

11

19

12

20

13

21

14

22

15

23

16

24

1

38

b

ε

ε

17

0

39

s

ε t

ε

r

ε

i

ε n

25

26

27

28

29

30

31

32

33

34

ε

ε

g

35

36



<a name="br5"></a> 

~~bo olstr~~

• alphabet: [a, e, f, l, r, s, t, u]

• regu lar expression: true|false

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

0

19

w

ε

h

ε

i

ε

l

ε

e

9

10

11

12

13

14

15

16

17

18



<a name="br6"></a> 

~~if~~

• alphabet: [f, i]

• regu lar expression: if

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

• regu lar expression: else

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

• regu lar expression: while

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

~~retur n~~

• alphabet: [e, n, r, t, u]

• regu lar expression: return

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

10

11



<a name="br10"></a> 

~~num~~

• alphabet: [-, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ε]

• regu lar expression: 0|(ε|-)(dig it\_)(dig it)\*

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

ε

dig it\_

ε

ε

4

5

7

15

ε

8

9

10

\-

ε

ε

6

ε

ε

dig it

ε

11

12

13

14

ε



<a name="br11"></a> 

~~num~~

ε-closure(0) = {0, 1, 3, 4, 5, 6, 8, 9} = T0

ε-closure(δ(T0, 0)) = {2, 15} = T1

ε-closure(δ(T0, digit\_)) = {10, 11, 14, 15} = T2

ε-closure(δ(T0, -)) = { 7, 8, 9} = T3

ε-closure(δ(T0, dig it)) = ∅

ε-closure(δ(T1, 0)) = ∅

ε-closure(δ(T1, digit\_)) = ∅

ε-closure(δ(T1, -)) = ∅

ε-closure(δ(T1, dig it)) = ∅

ε-closure(δ(T2, 0)) = ∅

ε-closure(δ(T2, digit\_)) = ∅

ε-closure(δ(T2, -)) = ∅

ε-closure(δ(T2, dig it)) = {12, 13, 14 ,15} = T4



<a name="br12"></a> 

~~num~~

ε-closure(δ(T3, 0)) = ∅

ε-closure(δ(T3, digit\_)) = T2

ε-closure(δ(T3, -)) = ∅

ε-closure(δ(T3, dig it)) = ∅

ε-closure(δ(T4, 0)) = ∅

ε-closure(δ(T4, digit\_)) = ∅

ε-closure(δ(T4, -)) = ∅

ε-closure(δ(T4, dig it)) = T4



<a name="br13"></a> 

~~num~~

• DFA

T1

0

dig it

dig it\_

dig it

T2

T4

T0

\-

dig it\_

T3



<a name="br14"></a> 

~~characte r~~

• alphabet: [ε, , ‘, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V,

W,X,Y,Z,a,b,c,d,e,f,g,h,i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z]

• regu lar expression: 'lette r| |ε|dig it’

• NFA

lette r

5

7

6

8

ε

ε

ε

ε

4

13

dig it

ε

ε

14

3

ε

ε

ε

9

10

12

ε

ε

ε

'

'

15

16

17

2

0

1

ε

ε

ε

11



<a name="br15"></a> 

~~characte r~~

ε-closure(0) = {0} = T0

ε-closure(δ(T0, ')) = {0, 1, 2, 3, 4, 5, 7, 9, 11, 12, 15, 16} = T1

ε-closure(δ(T0, letter)) = ∅

ε-closure(δ(T0, dig it)) = ∅

ε-closure(δ(T0, )) = ∅

ε-closure(δ(T1, ')) = {17} = T2

ε-closure(δ(T1, letter)) = {6, 13, 14, 15, 16, 17} = T3

ε-closure(δ(T1, dig it)) = {8, 13, 14, 15, 16, 17} = T4

ε-closure(δ(T1, )) = {10, 14, 15, 16, 17} = T5

ε-closure(δ(T2, ')) = ∅

ε-closure(δ(T2, letter)) = ∅

ε-closure(δ(T2, dig it)) = ∅

ε-closure(δ(T2, )) = ∅



<a name="br16"></a> 

~~characte r~~

ε-closure(δ(T3, ')) = {17} = T2

ε-closure(δ(T3, letter)) = ∅

ε-closure(δ(T3, dig it)) = ∅

ε-closure(δ(T3, )) = ∅

ε-closure(δ(T4, ')) = {17} = T2

ε-closure(δ(T4, letter)) = ∅

ε-closure(δ(T4, dig it)) = ∅

ε-closure(δ(T4, )) = ∅

ε-closure(δ(T5, ')) = {17} = T2

ε-closure(δ(T5, letter)) = ∅

ε-closure(δ(T5, dig it)) = ∅

ε-closure(δ(T5, )) = ∅



<a name="br17"></a> 

~~characte r~~

• DFA

'

T3

lette r

dig it

'

'

T4

T5

T0

T1

T2



<a name="br18"></a> 

~~str ing~~

• alphabet: [ , ", 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X,

Y, Z, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z]

• regu lar expression: "(lette r| |dig it)\*"

lette r

5

7

9

6

8

ε

ε

ε

ε

4

11

dig it

ε

ε

ε

ε

ε

ε

"

"

12

13

14

15

0

1

2

3

ε

ε

10



<a name="br19"></a> 

~~str ing~~

ε-closure(0) = {0} = T0

ε-closure(δ(T0, ")) = {1, 2, 3, 4, 5, 7, 9, 13, 14} = T1

ε-closure(δ(T1, letter)) = {3, 4, 5, 6, 7, 9, 11, 12} = T2

ε-closure(δ(T1, dig it)) = {3, 4, 5, 7, 8, 9, 11, 12} = T3

ε-closure(δ(T1, )) = {3, 4, 5, 7, 9, 10, 12} = T4

ε-closure(δ(T1, ")) = {15} = T5

ε-closure(δ(T2, letter)) = {3, 4, 5, 6, 7, 9, 11, 12} = T2

ε-closure(δ(T2, dig it)) = {3, 4, 5, 7, 8, 9, 11, 12} = T3

ε-closure(δ(T2, )) = {3, 4, 5, 7, 9, 10, 12} = T4

ε-closure(δ(T2, ")) = {15} = T5



<a name="br20"></a> 

~~str ing~~

ε-closure(δ(T3, letter)) = {3, 4, 5, 6, 7, 9, 11, 12} = T2

ε-closure(δ(T3, dig it)) = {3, 4, 5, 7, 8, 9, 11, 12} = T3

ε-closure(δ(T3, )) = {3, 4, 5, 7, 9, 10, 12} = T4

ε-closure(δ(T3, ")) = {15} = T5

ε-closure(δ(T4, letter)) = {3, 4, 5, 6, 7, 9, 11, 12} = T2

ε-closure(δ(T4, dig it)) = {3, 4, 5, 7, 8, 9, 11, 12} = T3

ε-closure(δ(T4, )) = {3, 4, 5, 7, 9, 10, 12} = T4

ε-closure(δ(T4, ")) = {15} = T5

ε-closure(δ(T5, letter)) = {3, 4, 5, 6, 7, 9, 11, 12} = ∅

ε-closure(δ(T5, dig it)) = {3, 4, 5, 7, 8, 9, 11, 12} = ∅

ε-closure(δ(T5, )) = {3, 4, 5, 7, 9, 10, 12} = ∅

ε-closure(δ(T5, ")) = {15} = ∅



<a name="br21"></a> 

~~str ing~~

• DFA

"

T2

lette r

dig it

lette r

dig it

lette r

"

"

T3

T0

T1

T5

dig it

T4



<a name="br22"></a> 

~~id~~

• alphabet: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y,

Z, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z]

• regu lar expression: lette r(dig it|lette r)\*

dig it

ε

ε

ε

ε

4

6

5

7

lette r

ε

ε

ε

0

1

2

3

8

9

lette r



<a name="br23"></a> 

~~id~~

ε-closure(0) = {0} = T0

ε-closure(δ(T0, letter)) = {1, 2, 3, 4, 6, 9} = T1

ε-closure(δ(T0, dig it)) = ∅

ε-closure(δ(T1, letter)) = {3, 4, 6, 7, 8, 9} = T2

ε-closure(δ(T1, dig it)) = {3, 4, 5, 6, 8, 9} = T3

ε-closure(δ(T2, letter)) = {3, 4, 6, 7, 8, 9} = T2

ε-closure(δ(T2, dig it)) = {3, 4, 5, 6, 8, 9} = T3

ε-closure(δ(T3, letter)) = {3, 4, 6, 7, 8, 9} = T2

ε-closure(δ(T3, dig it)) = {3, 4, 5, 6, 8, 9} = T3



<a name="br24"></a> 

~~id~~

• DFA

lette r

T2

lette r

dig it

lette r

T0

T1

lette r

dig it

dig it

T3



<a name="br25"></a> 

~~co mp~~

• alphabet: [!, <, =, >]

• regu lar expression: ==|!=|<|>|<=|>=

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

ε

ε

5

9

6

7

8 ε

4

25

ε

ε

10

11

12

3

26

ε

<

\>

ε

ε

ε

13

17

14

18

15

19

16

20

2

27

ε

ε

ε

ε

1

28

ε

<

ε

ε

ε

21

23

22

0

29

\>

24

ε



<a name="br26"></a> 

~~co mp~~

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

~~co mp~~

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

~~co mp~~

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

~~co mp~~

• DFA

\=

\=

\=

\=

T1

T5

\=

!

T2

T3

T4

T6

T7

T8

T0

<

\>



<a name="br30"></a> 

~~a ddsub~~

• alphabet: [+, -]

• regu lar expression: +|-

\+

\-

ε

ε

ε

1

3

2

4

5

0

ε



<a name="br31"></a> 

~~a ddsub~~

• DFA

\+

1

2

0

\-



<a name="br32"></a> 

~~multidiv~~

• alphabet: [ \*, /]

• regu lar expression: \*|/

\*

/

ε

ε

ε

1

3

2

4

5

0

ε



<a name="br33"></a> 

~~multidiv~~

• DFA

\+

1

2

0

\-



<a name="br34"></a> 

~~w hite space~~

• alphabet:[ , \t,\n]

• regu lar expression: \t| |\n

2

3

ε

ε

ε

1

8

\t

\n

ε

ε

ε

4

6

5

7

0

9

ε

ε



<a name="br35"></a> 

~~w hite space~~

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

~~w hite space~~

• DFA

T1

T0

\t

T3

\n

T4



<a name="br37"></a> 

~~assign~~

• DFA

\=

0

1



<a name="br38"></a> 

~~merge d~~



<a name="br39"></a> 

~~merge d~~

ε-closure(0) = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 15, 20, 30, 35, 42, 49, 55} = T0

ε-closure(δ(T0, +)) = {10, 14, 19, 29, 34, 41, 48, 54, 57} = T1 (a ddsub)

ε-closure(δ(T0, -)) = {11, 14, 19, 29, 34, 41, 48, 52, 54, 57 } = T2 (a ddsub)

ε-closure(δ(T2, digit\_)) = {51, 54, 57} = T3 (nu m)

ε-closure(δ(T3, dig it)) = {53, 54, 57} = T4 (nu m)

ε-closure(δ(T4, dig it)) = {53, 54, 57} = T4 (nu m)

ε-closure(δ(T0, \*)) = {12, 14, 19, 29, 34, 41, 48, 54, 57} = T5 (arithmetic)

ε-closure(δ(T0, /)) = {13, 14, 19, 29, 34, 41, 48, 54, 57} = T6 (arithmetic)

ε-closure(δ(T0, )) = {16, 19, 29, 34, 41, 48, 52, 54, 57 } = T7 (whitespace)

ε-closure(δ(T0, \t)) = {17, 1 9, 2 9, 34, 41, 48, 52, 54, 57 } = T8 (whitespace)

ε-closure(δ(T0, \n)) = {18, 1 9, 29, 34, 41, 48, 52, 54, 57 } = T9 (whitespace)



<a name="br40"></a> 

~~merge d~~

ε-closure(δ(T0, =)) = {21, 56, 57} = T10 (assign)

ε-closure(δ(T10, =)) = {25, 29, 34, 41, 48, 54, 57} = T11 (comp)

ε-closure(δ(T0, !)) = {22} = T12

ε-closure(δ(T12, =)) = {26, 29, 34, 41, 48, 54, 57} = T13(comp)

ε-closure(δ(T0, <)) = {23, 29, 34, 41, 48, 54, 57} = T14 (comp)

ε-closure(δ(T14, =)) = {27, 29, 34, 41, 48, 54, 57} = T15 (comp)

ε-closure(δ(T0, >)) = {24, 29, 34, 41, 48, 54, 57} = T16 (comp)

ε-closure(δ(T16, =)) = {28, 29, 34, 41, 48, 54, 57} = T17 (comp)



<a name="br41"></a> 

~~merge d~~

ε-closure(δ(T0, letter)) = {31, 34, 41, 48, 54, 57} = T18 (vtype)

ε-closure(δ(T18, letter)) = {32, 34, 41, 48, 54, 57} = T19 (vtype)

ε-closure(δ(T18, dig it)) = {33, 34, 41, 48, 54, 57} = T20 (vtype)

ε-closure(δ(T19, letter)) = {32, 34, 41, 48, 54, 57} = T19 (vtype)

ε-closure(δ(T19, dig it)) = {33, 34, 41, 48, 54, 57} = T20 (vtype)

ε-closure(δ(T20, letter)) = {32, 34, 41, 48, 54, 57} = T19 (vtype)

ε-closure(δ(T20, dig it)) = {33, 34, 41, 48, 54, 57}} = T20 (vtype)



<a name="br42"></a> 

~~merge d~~

ε-closure(δ(T0, ")) = {36} = T21

ε-closure(δ(T21, letter)) = {37} = T22

ε-closure(δ(T21, dig it)) = {38} = T23

ε-closure(δ(T21, )) = {39} = T24

ε-closure(δ(T22, letter)) = {37} = T22

ε-closure(δ(T23, letter)) = {37} = T22

ε-closure(δ(T24, letter)) = {37} = T22

ε-closure(δ(T19, dig it)) = {38} = T23

ε-closure(δ(T19, dig it)) = {38} = T23

ε-closure(δ(T19, dig it)) = {38} = T23

ε-closure(δ(T19, )) = {39} = T24

ε-closure(δ(T19, )) = {39} = T24

ε-closure(δ(T19, )) = {39} = T24



<a name="br43"></a> 

~~merge d~~

ε-closure(δ(T21, ")) = {40, 41, 48, 54, 57} = T25 (string)

ε-closure(δ(T22, ")) = {40, 41, 48, 54, 57} = T25 (string)

ε-closure(δ(T23, ")) = {40, 41, 48, 54, 57} = T25 (string)

ε-closure(δ(T24, ")) = {40, 41, 48, 54, 57} = T25 (string)



<a name="br44"></a> 

~~merge d~~

ε-closure(δ(T0, ')) = {43} = T26

ε-closure(δ(T26, letter)) = {44} = T27

ε-closure(δ(T26, dig it)) = {45} = T28

ε-closure(δ(T26, )) = {46} = T29

ε-closure(δ(T27, ')) = { 47, 48, 54, 57} = T30 (char)

ε-closure(δ(T28, ')) = { 47, 48, 54, 57} = T30 (char)

ε-closure(δ(T29, ')) = { 47, 48, 54, 57} = T30 (char)



<a name="br45"></a> 

~~merge d~~

ε-closure(δ(T0, 0)) = {50, 54, 57} = T31 (nu m)

ε-closure(δ(T0, digit\_)) = {51, 54, 57} = T32 (nu m)

ε-closure(δ(T32, dig it)) = {53, 54, 57} = T33 (nu m)

ε-closure(δ(T33, dig it)) = {53, 54, 57} = T33 (nu m)



<a name="br46"></a> 

~~semi~~

;

0

1

~~comma~~

,

0

1

~~en dmark~~

$

0

1



<a name="br47"></a> 

~~laparen~~

(

0

1

~~r paren~~

)

0

1

~~lbrace~~

{

0

1

~~rb race~~

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

2\. Co ntext-free Gram mar

(Syntax Analyze r)



<a name="br50"></a> 

Pro ductio n Rules

1\. S -> CODE

12\. EXPR -> CALL

2\. CODE -> VDECL CODE

3\. CODE -> FDECL CODE

4\. CODE -> ''

13\. EXPR -> TERM addsub EXPR

14\. EXPR -> TERM

15\. TERM -> FACT multdiv TERM

16\. TERM -> FACT

5\. VDECL -> vtype id semi

6\. VDECL -> vtype ASSIGN semi

7\. ASSIGN -> id assign RHS

8\. RHS -> EXPR

17\. FACT -> num

18\. FACT -> lparen EXPR rparen

19\. FACT -> id

9\. RHS -> char

20\. FDECL -> vtype id lparen ARG rparen lbrace

BLOCK RETURN rbrace

10\. RHS -> string

21\. ARG -> vtype id MOREARGS

22\. ARG -> ''

11\. RHS -> boolstr



<a name="br51"></a> 

Pro ductio n Rules

23\. MOREARGS -> comma vtype id MOREARGS

24\. MOREARGS -> ''

35\. MOREARGVAL -> comma EXPR

MOREARGVAL

36\. MOREARGVAL -> ''

25\. BLOCK -> STMT BLOCK

26\. BLOCK -> ''

37\. COND -> COND\_EXPR LOGIC\_EXPR

38\. COND\_EXPR -> boolstr

39\. COND\_EXPR -> FACT comp FACT

40\. LOGIC\_EXPR -> ''

27\. STMT -> VDECL

28\. STMT -> ASSIGN semi

29\. STMT -> CALL semi

41\. LOGIC\_EXPR -> LOGIC\_OP COND

42\. LOGIC\_OP -> and

30\. STMT -> if lparen COND rparen lbrace BLOCK

rbrace ELSE

31\. STMT -> while lparen COND rparen lbrace

BLOCK rbrace

43\. LOGIC\_OP -> or

44\. ELSE -> else lbrace BLOCK rbrace

45\. ELSE -> ’’

32\. CALL -> id lparen ARGVAL rparen

33\. ARGVAL -> EXPR MOREARGVAL

34\. ARGVAL -> ''

46\. RETURN -> return RHS semi



<a name="br52"></a> 

Ter minals

1\. vtype for the types of variables and functions

2\. num for signed integers

3\. char for a single character

4\. boolstr for Boolean strings

5\. string for literal strings

6\. id for the identifiers of variables and functions

7\. if, else, while, and return for i f, else, while, and return statements respectively

8\. addsub for +, and -

9\. multidiv for \*, and /

10\. assign for assignment operators

11\. comp for comparison operators

12\. semi and comma for semicolons and commas respectively

13\. lparen, rparen, lbrace, and rbrace for (, ), {, and } respectively

14\. and, and or for & and |



<a name="br53"></a> 

No n-ter mianls

EXPR, VDECL, LOGIC\_EXPR, CODE, CALL, ELSE, ARGVAL, MOREARGVAL,

BLOCK, ASSIGN,STMT, FAC T, COND, MOREARGS, RHS, S, RETURN,

COND\_EXPR, TERM, FDECL, ARG, LOGIC\_OP



<a name="br54"></a> 

Descr iptio ns

1\. A file of source code is constructed with zero or more declarations of functions or variables

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

Descr iptio ns

7\. If and while statements include one or more conditions that comprise Boolean values generated by

comparison operations or logical operations

8\. If statement stands alone or with an else statement

9\. A return statement returns five types

a)

b)

c)

d)

e)

Expression

String

Character

Boolean

Function return value

