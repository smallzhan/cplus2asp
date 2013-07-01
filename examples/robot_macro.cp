:- constants
   bring(smallobject, location),
   fetch(smallobject, location) :: macroAction.

bring(S, L) is pickup(S); goto(L); putdown(S).
fetch(S, L) is goto(L1) if loc(S) = L1 & loc(robot) \= L1; bring(S, L).
