% File 'monkey.cp'
% Monkey and Bananas ("Nonmonotonic Causal Theories," Figures  10-12)

:- sorts
  thing;
  location.

:- objects
  monkey,bananas,box     :: thing;
  l1,l2,l3               :: location.

:- variables
  L                      :: location.

:- constants
  loc(thing)             :: inertialFluent(location);
  hasBananas,onBox       :: inertialFluent;

  walk(location),
  pushBox(location),
  climbOn,
  climbOff,
  graspBananas           :: exogenousAction.

caused loc(bananas)=L if hasBananas & loc(monkey)=L.
caused loc(monkey)=L if onBox & loc(box)=L.

walk(L) causes loc(monkey)=L.
nonexecutable walk(L) if loc(monkey)=L.
nonexecutable walk(L) if onBox.

pushBox(L) causes loc(box)=L.
pushBox(L) causes loc(monkey)=L.
nonexecutable pushBox(L) if loc(monkey)=L.
nonexecutable pushBox(L) if onBox.
nonexecutable pushBox(L) if loc(monkey)\=loc(box).

climbOn causes onBox.
nonexecutable climbOn if onBox.
nonexecutable climbOn if loc(monkey)\=loc(box).

climbOff causes -onBox.
nonexecutable climbOff if -onBox.

graspBananas causes hasBananas.
nonexecutable graspBananas if hasBananas.
nonexecutable graspBananas if -onBox.
nonexecutable graspBananas if loc(monkey)\=loc(bananas).

nonexecutable walk(L) & pushBox(L).
nonexecutable walk(L) & climbOn.
nonexecutable pushBox(L) & climbOn.
nonexecutable climbOff & graspBananas.


% Prediction
:- query
maxstep :: 2;
0: loc(monkey)=l1,
   loc(bananas)=l2,
   loc(box)=l3,
   walk(l3);
1: pushBox(l2);
2: loc(monkey)\= loc(bananas) ++ loc(bananas)\=loc(box).

% Postdiction
:- query
label :: 1;
maxstep :: 2;
0: walk(l3);
1: [\/L | pushBox(L)];
0: loc(box)\=l3.

% Planning
:- query
label :: 2;
maxstep :: 1..100;
0: loc(monkey)=l1,
   loc(bananas)=l2,
   loc(box)=l3;
maxstep: hasBananas.

% Planning
:- query
label :: 3;
maxstep :: 4;
0: loc(monkey)=l1,
   loc(bananas)=l2,
   loc(box)=l3;
maxstep: hasBananas.
