$Title Simple Plant Location Problem
$Ontext
The problem cosists weak/strong and binary relaxation
$offtext

Set i "plants"  /1*5/
    k "markets" /1*5/;

Table c(i,k) transportation cost from plant i to k
         1       2       3       4       5
1        300     1000    1000    900     1200
2        1000    800     700     1000    1000
3        1000    1000    600     900     1100
4        1200    600     500     700     900
5        1300    700     800     900     300

Parameter f(i) fixed cost of plant at i  /
1        500,
2        100,
3        200,
4        300,
5        250
/;

Parameter d(k) demand for market k/
1        0.25,
2        0.2,
3        0.2,
4        0.2,
5        0.15
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
p(i)..   y(i)=g=sum(k,(x(i,k)/d(k)))/5;

model splp/all/;
Solve splp using lp minimizing z;
display z.l, x.l;
