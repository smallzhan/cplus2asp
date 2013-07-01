%%%% File testrobot.cp which has multi-layer structure.

:-sorts
	location;
	object >> movableobject;
	absobject >> smallobject;
	movableobject >> smallobject.

:- objects
   robot,human					:: object;
   nothing						:: absobject.

:- variables
   L,L1	:: location;
   A,A1	:: absobject;
   O	:: object;
   S	:: smallobject.

:- constants
   loc(object)					:: inertialFluent(location);
   hold(absobject)				:: inertialFluent;
   inplate(absobject)			:: inertialFluent;

   goto(location),
   pickup(smallobject),
   putdown(smallobject),
   putintoplate(smallobject),
   takefromplate(smallobject)					:: exogenousAction.

caused loc(S) = L if hold(S) & loc(robot) = L.
caused loc(S) = L if inplate(S) & loc(robot) = L.
caused -hold(A) if hold(A1) & A \= A1.
caused -inplate(A) if inplate(A) & A \= A1.

goto(L) causes loc(robot) = L.
nonexecutable goto(L) if loc(robot) = L.


pickup(S) causes hold(S).
nonexecutable pickup(S) if -hold(nothing).
nonexecutable pickup(S) if inplate(S).
nonexecutable pickup(S) if loc(robot) \= loc(S).

putdown(S) causes hold(nothing).
nonexecutable putdown(S) if -hold(S).

putintoplate(S) causes hold(nothing).
putintoplate(S) causes inplate(S).
nonexecutable putintoplate(S) if -hold(S).
nonexecutable putintoplate(S) if -inplate(nothing).

takefromplate(S) causes hold(S).
takefromplate(S) causes inplate(nothing).
nonexecutable takefromplate(S) if -inplate(S).
nonexecutable takefromplate(S) if -hold(nothing).

noconcurrency.
