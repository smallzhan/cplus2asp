% File 'gmb.cp'
% Generalized Monkey and Bananas ("Nonmonotonic Causal Theories," Figures  10-12)

:- sorts
  thing >> bananas;
  absthing >> bananas;
  location;
  level;
  agent.

:- objects
  monkey, ladder         :: thing;
  monkey                 :: agent;
  l1,l2,l3               :: location;
  nothing                :: absthing;
  floor, s1, s2          :: level;
  b1, b2                 :: bananas.

:- variables
  L                      :: location;
  H                      :: level;
  A, A1                  :: absthing;
  B                      :: bananas.

:- constants
  loc(thing)             :: inertialFluent(location);
  base(agent)            :: inertialFluent(level);
  height(bananas)        :: inertialFluent(level);
  folded                 :: inertialFluent;
  hold(absthing)         :: inertialFluent;
  inbag(bananas)         :: inertialFluent;

  transportladder(location),
  climbonladder,
  climboffladder        :: macroAction;

  walk(location),
  climbto(level),
  moveladder(location),
  fold,
  unfold,
  grasp(bananas),
  puttobag(bananas)      :: exogenousAction.


caused loc(B) = L if hold(B) & loc(monkey) = L.
caused loc(B) = L if inbag(B) & loc(monkey) = L.
caused height(B) = H if hold(B) & base(monkey) = H.
caused height(b) = H if inbag(B) & base(monkey) = H.
caused -hold(A) if hold(A1) & A \= A1.

walk(L) causes loc(monkey)=L.
nonexecutable walk(L) if loc(monkey)=L.
nonexecutable walk(L) if base(monkey) \= floor.

moveladder(L) causes loc(monkey)=L.
moveladder(L) causes loc(ladder)=L.
nonexecutable moveladder(L) if loc(ladder)=L.
nonexecutable moveladder(L) if loc(ladder) \= loc(monkey).
nonexecutable moveladder(L) if -hold(nothing).
nonexecutable moveladder(L) if -folded.

fold causes folded.
nonexecutable fold if loc(monkey) \= loc(ladder).
nonexecutable fold if -hold(nothing).
nonexecutable fold if base(monkey) \= floor.
nonexecutable fold if folded.

unfold causes -folded.
nonexecutable unfold if -folded.
nonexecutable unfold if -hold(nothing).
nonexecutable unfold if loc(monkey) \= loc(ladder).

climbto(H) causes base(monkey) = H.
nonexecutable climbto(floor) if base(monkey) = s2.
nonexecutable climbto(s2) if base(monkey) = floor.
nonexecutable climbto(H) if loc(monkey) \= loc(ladder).
nonexecutable climbto(H) if folded.

grasp(B) causes hold(B).
nonexecutable grasp(B) if base(monkey) \= height(B).
nonexecutable grasp(B) if loc(monkey)\=loc(B).
nonexecutable grasp(B) if -hold(nothing).

puttobag(B) causes inbag(B).
puttobag(B) causes hold(nothing).
nonexecutable puttobag(B) if -hold(B).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
transportladder(L) is fold; moveladder(L);unfold.
climbonladder is climbto(s1) if base(monkey) = floor;
                 climbto(s2) if base(monkey) = s1 & loc(monkey) = loc(B)
                 & height(B) = s2.
climboffladder is climbto(s1) if base(monkey) = s2;
                  climbto(floor) if base(monkey) = s1.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
noconcurrency.


% Planning
:- query
maxstep :: 1..20;
0: loc(monkey)=l1,
   base(monkey)=floor,
   loc(b1)=l2,
   loc(b2)=l2,
   height(b2)=s2,
   height(b1)=s1,
   -inbag(b1),
   -inbag(b2),
   loc(ladder)=l3;
maxstep: inbag(b1),
         inbag(b2).


% % Planning
% :- query
% label :: 3;
% maxstep :: 4;
% 0: loc(monkey)=l1,
%    loc(bananas)=l2,
%    loc(box)=l3;
% maxstep: hasBananas.
