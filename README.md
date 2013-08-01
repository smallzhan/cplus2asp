cplus2asp
=========

Cplus2asp system, which translates the enhanced action language C+ to asp, and call the asp solver to solve it.
This project enhanced the cplus2asp v1. See
http://reasoning.eas.asu.edu/cplus2asp/ for detailed information. 

The enhancement including:
- Macro actions which represented as "A is a;b;c;..."
- Conditional macro actions represented as "A is a_0 if ac_0; a_1 if ac_1; a_2 if ac_2;..."
- The nested macro actions:
   A is B;C.
   B is b_0; b_1;...
   C is c_0 if cc_0; c_1 if cc_1;...


For details, please refer to the paper in the following:

- Xiaoping Chen, Guoqiang Jin, Fangkai Yang: Extending Action Language C+ by
  Formalizing Composite Actions. Correct Reasoning 2012:134-148
- Xiaoping Chen, Guoqiang Jin, Fangkai Yang: Extending C+ with Composite Actions
  for Robotic Task Planning. ICLP (Technical Communications) 2012:404-414EE27
