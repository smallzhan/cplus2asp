:- sorts
   value.

:- objects
   1, 2, 3, 4 :: value.

:- variables
   C :: value.

:- constants
   p    :: inertialFluent(value);
   a :: exogenousAction.

a causes p=C+1 if p=C.
nonexecutable a if p=4.

:- query
maxstep :: 1..20;
0: p=1;
maxstep: p=4.
