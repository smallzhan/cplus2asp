pre-processor "cplus2asp.bin" "/home/smallqiang/Documents/HASP/cpp/Cplus2ASP/examples/monkey_macro.cp" >".cplus2asp_trans.out"
also pre-processor: "f2lp" "/home/smallqiang/cplus2asp/lib/cplus2asp/cplus2asp_std.f2lp" "/home/smallqiang/cplus2asp/lib/cplus2asp/cplus2asp_macro.f2lp" ".cplus2asp_trans.out" >".cplus2asp_pre.out"

% Running Query 2 with maxstep=1.
% Searching for 1 solution.
strTempCommand is: "gringo" -c query=2 -c maxstep=1 <".cplus2asp_pre.out" >".cplus2asp_gr.out"
SOLVER "clasp" 1 <".cplus2asp_gr.out" >".cplus2asp_so.out"
No solution.

UNSATISFIABLE
Models      : 0
Time        : 0.001s (Solving: 0.00s 1st Model: 0.00s Unsat: 0.00s)
CPU Time    : 0.000s

Post processor :as2transition -f ".cplus2asp_so.out"

% Running Query 2 with maxstep=2.
% Searching for 1 solution.
strTempCommand is: "gringo" -c query=2 -c maxstep=2 <".cplus2asp_pre.out" >".cplus2asp_gr.out"
SOLVER "clasp" 1 <".cplus2asp_gr.out" >".cplus2asp_so.out"
No solution.

UNSATISFIABLE
Models      : 0
Time        : 0.002s (Solving: 0.00s 1st Model: 0.00s Unsat: 0.00s)
CPU Time    : 0.000s

Post processor :as2transition -f ".cplus2asp_so.out"

% Running Query 2 with maxstep=3.
% Searching for 1 solution.
strTempCommand is: "gringo" -c query=2 -c maxstep=3 <".cplus2asp_pre.out" >".cplus2asp_gr.out"
SOLVER "clasp" 1 <".cplus2asp_gr.out" >".cplus2asp_so.out"
Solution 1:

0:  loc(bananas)=l2  loc(box)=l3  loc(monkey)=l1  

  ACTIONS:  walk(l3)  

0.1:  loc(bananas)=l2  loc(box)=l3  loc(monkey)=l1  

1:  loc(bananas)=l2  loc(box)=l3  loc(monkey)=l3  

  ACTIONS:  pushBox(l2)  

1.1:  loc(bananas)=l2  loc(box)=l3  loc(monkey)=l3  

2:  loc(bananas)=l2  loc(box)=l2  loc(monkey)=l2  

  ACTIONS:  climbgrasp  

  SUB-ACTIONS(0):  climbOn  

2.1:  loc(bananas)=l2  loc(box)=l2  loc(monkey)=l2  onBox  

  SUB-ACTIONS(1):  graspBananas  

3:  hasBananas  loc(bananas)=l2  loc(box)=l2  loc(monkey)=l2  onBox  


SATISFIABLE
Models      : 1
Time        : 0.003s (Solving: 0.00s 1st Model: 0.00s Unsat: 0.00s)
CPU Time    : 0.000s

Post processor :as2transition -f ".cplus2asp_so.out"
remove files rm ".cplus2asp_trans.out" ".cplus2asp_pre.out" ".cplus2asp_gr.out" ".cplus2asp_so.out"
