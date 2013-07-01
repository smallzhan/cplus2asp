:- sorts
   mover;
   object;
   tool;
   article;
   thing >> mover;
   thing >> object;
   thing >> tool;
   thing >> article;
   level;
   location.

:- variables
   M			:: mover;
   O			:: object;
   L			:: location;
   T			:: tool;
   A			:: article;
   S			:: level.

:- constants
   base(thing)	:: inertialFluent(level);
   loc(thing)	:: inertialFluent(location);

   move(mover, object, location),
   mount(tool, article, level) :: action.



move(M, O, L) causes loc(M) = L.
move(M, O, L) causes loc(O) = L.
nonexecutable move(M, O, L) if loc(M) \= loc(O).
nonexecutable move(M, O, L) if loc(O) = L.
default -move(M, O, L).

mount(T, A, S) causes base(A) = S.
nonexecutable mount(T, A, S) if loc(T) \= loc(A).
nonexecutable mount(T, A, S) if base(A) = S.
default -mount(T, A, S).
