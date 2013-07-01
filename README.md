cplus2asp
=========

Cplus2asp system, which translates the enhanced action language C+ to asp, and call the asp solver to solve it.

The enhancement including:
- Macro actions which represented as "A is a;b;c;..."
- Conditional macro actions represented as "A is a_0 if ac_0; a_1 if ac_1; a_2 if ac_2;..."
- The nested macro actions:
   A is B;C.
   B is b_0; b_1;...
   C is c_0 if cc_0; c_1 if cc_1;...

