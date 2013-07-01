:- sorts
    laches.

:- objects
    l1, l2 :: laches.

:- constants
    up(laches),open :: inertialFluent;
    toggle(laches) :: exogenousAction.

:- variables
    L   :: laches.

toggle(L) causes up(L) if -up(L).
toggle(L) causes -up(L) if up(L).

caused open if up(l1) & up(l2).
nonexecutable toggle(l1) & toggle(l2).

:- query
maxstep::0..10;
  0:  -up(l1),
      -up(l2),
      -open;
maxstep:
        open.
