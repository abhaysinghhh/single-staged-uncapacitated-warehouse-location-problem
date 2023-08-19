$Title Simple Plant Location Problem
$Ontext
The problem cosists weak/strong and binary relaxation
$offtext

Set i "plants"  /1*10/
    k "markets" /1*25/;

Table c(i,k) transportation cost from plant i to k
          1         2         3         4         5         6         7         8         9         10        11        12        13        14        15        16        17        18        19        20        21        22        23        24        25
1         29        38        35        25        33        28        36        39        30        25        39        35        27        34        31        39        40        29        33        28        38        39        34        27        40
2         38        28        32        30        38        38        34        23        35        38        40        33        30        34        39        25        23        24        25        34        24        25        37        37        27
3         30        25        23        36        31        25        34        33        24        27        34        35        25        33        30        30        37        28        32        28        25        25        23        35        27
4         26        25        34        34        30        37        34        31        25        38        30        37        38        24        40        37        37        31        34        38        40        26        35        30        28
5         34        29        30        34        33        29        31        29        32        35        32        36        38        35        24        36        35        25        27        35        25        23        33        34        37
6         24        27        40        30        34        27        35        30        39        34        24        34        31        32        39        27        33        33        34        34        32        36        23        32        28
7         36        40        24        40        34        27        32        36        24        40        29        30        23        40        35        32        30        35        34        37        38        35        39        28        29
8         28        34        38        29        24        36        31        38        24        28        37        27        28        36        40        25        26        25        25        37        40        34        40        29        24
9         33        27        34        36        33        36        29        37        25        37        37        23        30        28        29        38        35        34        38        26        25        34        29        40        29
10        25        27        35        33        29        28        27        36        36        27        35        40        31        24        34        37        25        35        23        36        37        37        29        29        36


Parameter f(i) fixed cost of plant at i  /
1         125,
2         190,
3         142,
4         134,
5         133,
6         176,
7         121,
8         196,
9         144,
10        168
/;

Parameter d(k) demand for market k/
1        0.247,
2        0.174,
3        0.217,
4        0.221,
5        0.117,
6        0.157,
7        0.194,
8        0.215,
9        0.145,
10       0.133,
11       0.155,
12       0.170,
13       0.237,
14       0.119,
15       0.164,
16       0.205,
17       0.100,
18       0.172,
19       0.163,
20       0.126,
21       0.154,
22       0.146,
23       0.129,
24       0.192,
25       0.227
/;

Variables x(i,k) transport quantity from plant i to market k
          y(i) location variable
          z total cost

Positive Variables x,y;

Equations cost objective function
          db demand balance
          dd(k) demand balance
          p(i) plant information;

cost..   z=e=sum((i,k),c(i,k)*x(i,k))+sum(i,f(i)*y(i));
db..     sum((i,k),x(i,k))=e=1;
dd(k)..  sum(i,x(i,k))=l=d(k);
p(i)..   y(i)=g=sum(k,(x(i,k)/d(k)))/25;

model splp/all/;
Solve splp using lp minimizing z;
display z.l,x.l;
