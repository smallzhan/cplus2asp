:- objects
   l1, l2, l3, l4, l5	:: location;
   box, cup, drink, food   :: smallobject;
   table, desk, sofa	   :: object.


:-query
maxstep ::1..20;
0: loc(robot)			= l1,
   loc(human)			= l2,
   loc(table)			= l3,
   loc(desk)			= l4,
   loc(sofa)			= l5,
   loc(box)				= l5,
   loc(cup)				= l4,
   loc(food)			= l4,
   loc(drink)			= l3,
   hold(nothing);
maxstep:
		loc(food)		= l2,
		loc(drink)		= l2,
		loc(robot)		= l5.
