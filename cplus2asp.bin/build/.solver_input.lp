% Standard description-independent declarations and laws to CCalc-ify ASP

% A derived binary relation between a constant and its domain objects,
% connected via constant_sort and sort_object

constant_object(V_constant,Object) :- constant_sort(V_constant,V_sort),sort_object(V_sort,Object).

%-------------------------------------------------------------

% Standard, description-independent declarations of sorts and domains

sort(boolean) :- true.
#domain boolean(V_boolean).
sort_object(boolean,V_boolean) :- true.

%------------------------------------------------------------

boolean(true) :- true.

%-------------------------------------------------------------

% Time steps

sort(step) :- true.
#domain step(V_step).
sort_object(step,V_step) :- true.

sort(astep) :- true.
#domain astep(V_astep).
sort_object(astep,V_astep) :- true.

% astep is a subsort of step

step(V_astep) :- true.

%-------------------------------------------------------------

step(0..maxstep).
astep(0..maxstep-1).

%------------------------------------------------------------

% Constants hierarchy

% Meta-constants to group categories of constants

sort(constant) :- true.
#domain constant(V_constant).
sort_object(constant,V_constant) :- true.

%----

% Rigid constants

sort(rigid) :- true.
#domain rigid(V_rigid).
sort_object(rigid,V_rigid) :- true.

%---

% Fluent-based constants

sort(fluent) :- true.
#domain fluent(V_fluent).
sort_object(fluent,V_fluent) :- true.

sort(simpleFluent) :- true.
#domain simpleFluent(V_simpleFluent).
sort_object(simpleFluent,V_simpleFluent) :- true.

sort(inertialFluent) :- true.
#domain inertialFluent(V_inertialFluent).
sort_object(inertialFluent,V_inertialFluent) :- true.

sort(sdFluent) :- true.
#domain sdFluent(V_sdFluent).
sort_object(sdFluent,V_sdFluent) :- true.

%---

% Action-based constants

sort(action) :- true.
#domain action(V_action).
sort_object(action,V_action) :- true.

sort(exogenousAction) :- true.
#domain exogenousAction(V_exogenousAction).
sort_object(exogenousAction,V_exogenousAction) :- true.

sort(abAction) :- true.
#domain abAction(V_abAction).
sort_object(abAction,V_abAction) :- true.

sort(attribute) :- true.
#domain attribute(V_attribute).
sort_object(attribute,V_attribute) :- true.

%---

% Subsort relations

constant(V_fluent) :- true.
constant(V_action) :- true.
constant(V_rigid) :- true.
fluent(V_simpleFluent) :- true.
simpleFluent(V_inertialFluent) :- true.
fluent(V_sdFluent) :- true.
action(V_exogenousAction) :- true.
action(V_abAction) :- true.
action(V_attribute) :- true.

%--------------------------------------------------------------

% Sort declaration: atomicFormula : eql(constant,value)

sort(atomicFormula) :- true.
#domain atomicFormula(V_atomicFormula).
sort_object(atomicFormula,V_atomicFormula) :- true.

%---

sort(fluentAtomicFormula) :- true.
#domain fluentAtomicFormula(V_fluentAtomicFormula).
sort_object(fluentAtomicFormula,V_fluentAtomicFormula) :- true.

sort(simpleFluentAtomicFormula) :- true.
#domain simpleFluentAtomicFormula(V_simpleFluentAtomicFormula).
sort_object(simpleFluentAtomicFormula,V_simpleFluentAtomicFormula) :- true.

sort(inertialFluentAtomicFormula) :- true.
#domain inertialFluentAtomicFormula(V_inertialFluentAtomicFormula).
sort_object(inertialFluentAtomicFormula,V_inertialFluentAtomicFormula) :- true.

sort(sdFluentAtomicFormula) :- true.
#domain sdFluentAtomicFormula(V_sdFluentAtomicFormula).
sort_object(sdFluentAtomicFormula,V_sdFluentAtomicFormula) :- true.

sort(rigidAtomicFormula) :- true.
#domain rigidAtomicFormula(V_rigidAtomicFormula).
sort_object(rigidAtomicFormula,V_rigidAtomicFormula) :- true.

%---

sort(actionAtomicFormula) :- true.
#domain actionAtomicFormula(V_actionAtomicFormula).
sort_object(actionAtomicFormula,V_actionAtomicFormula) :- true.

sort(exogenousActionAtomicFormula) :- true.
#domain exogenousActionAtomicFormula(V_exogenousActionAtomicFormula).
sort_object(exogenousActionAtomicFormula,V_exogenousActionAtomicFormula) :- true.

sort(abActionAtomicFormula) :- true.
#domain abActionAtomicFormula(V_abActionAtomicFormula).
sort_object(abActionAtomicFormula,V_abActionAtomicFormula) :- true.

sort(attributeAtomicFormula) :- true.
#domain attributeAtomicFormula(V_attributeAtomicFormula).
sort_object(attributeAtomicFormula,V_attributeAtomicFormula) :- true.

%--

% Subsort relations

fluentAtomicFormula(V_simpleFluentAtomicFormula) :- true.

simpleFluentAtomicFormula(V_inertialFluentAtomicFormula) :- true.

fluentAtomicFormula(V_sdFluentAtomicFormula) :- true.

actionAtomicFormula(V_exogenousActionAtomicFormula) :- true.

actionAtomicFormula(V_abActionAtomicFormula) :- true.

actionAtomicFormula(V_attributeAtomicFormula) :- true.

%-----------------------------------------------------------------

% Object declaration: atomicFormula

atomicFormula(h(V_rigidAtomicFormula)) :- true.

atomicFormula(h(V_fluentAtomicFormula,V_step)) :- true.

atomicFormula(h(V_actionAtomicFormula,V_astep)) :- true.

%---

rigidAtomicFormula(eql(V_rigid,Object)) :- constant_object(V_rigid,Object).

simpleFluentAtomicFormula(eql(V_simpleFluent,Object)) :- constant_object(V_simpleFluent,Object).

inertialFluentAtomicFormula(eql(V_inertialFluent,Object)) :- constant_object(V_inertialFluent,Object).

sdFluentAtomicFormula(eql(V_sdFluent,Object)) :- constant_object(V_sdFluent,Object).

actionAtomicFormula(eql(V_action,Object)) :- constant_object(V_action,Object).

exogenousActionAtomicFormula(eql(V_exogenousAction,Object)) :- constant_object(V_exogenousAction,Object).

abActionAtomicFormula(eql(V_abAction,Object)) :- constant_object(V_abAction,Object).

attributeAtomicFormula(eql(V_attribute,Object)) :- constant_object(V_attribute,Object).

%%% Description-independent rules to CCalc-ify ASP

% Exogeneity for exogenous actions
{h(V_exogenousActionAtomicFormula,V_astep)} :- true.
% Negative version for Booleans
{-h(eql(V_exogenousAction,true),V_astep)} :- constant_sort(V_exogenousAction,boolean).

% abActions default to false
{-h(eql(V_abAction,true),V_astep)} :- true.

% Exogeneity for attributes
{h(V_attributeAtomicFormula,V_astep)} :- true.

% Restriction that attributes must take on the value "none" if and only if their linked action does not execute
false :- {not h(eql(V_attribute,none),V_astep)}0,action_attribute(V_action,V_attribute),not -h(eql(V_action,true),V_astep).
false :- {not -h(eql(V_action,true),V_astep)}0,action_attribute(V_action,V_attribute),not h(eql(V_attribute,none),V_astep).

% Inertia for inertial fluents
{h(V_inertialFluentAtomicFormula,V_astep+1)} :- h(V_inertialFluentAtomicFormula,V_astep),not has_any_macroaction.
% Negative version for Booleans
{-h(eql(V_inertialFluent,true),V_astep+1)} :- -h(eql(V_inertialFluent,true),V_astep),constant_sort(V_inertialFluent,boolean),not has_any_macroaction.

%-----------------------------------------------------------

% anyInitialState: Exogeneity for simple fluents at time 0

{h(V_simpleFluentAtomicFormula,0)} :- true.
% Negative version for Booleans
{-h(eql(V_simpleFluent,true),0)} :- constant_sort(V_simpleFluent,boolean).

%------------------------------------------------------------

% exogenous: Grants exogeneity to a constant

% Rigids
{h(eql(V_rigid,Value))} :- exogenous(V_rigid),constant_object(V_rigid,Value).
% Negative version if it's Boolean
{-h(eql(V_rigid,true))} :- exogenous(V_rigid),constant_sort(V_rigid,boolean).

% Actions
{h(eql(V_action,Value),V_astep)} :- exogenous(V_action),constant_object(V_action,Value).
% Negative version if it's Boolean
{-h(eql(V_action,true),V_astep)} :- exogenous(V_action),constant_sort(V_action,boolean).

% Fluents
{h(eql(V_fluent,Value),V_step)} :- exogenous(V_fluent),constant_object(V_fluent,Value).
% Negative version if it's Boolean
{-h(eql(V_fluent,true),V_step)} :- exogenous(V_fluent),constant_sort(V_fluent,boolean).

%------------------------------------------------------------

% inertial: Grants inertia to a (non-rigid) fluent

{h(eql(V_fluent,Value),V_astep+1)} :- inertial(V_fluent),h(eql(V_fluent,Value),V_astep),constant_object(V_fluent,Value),not has_any_macroaction.
% Negative version if it's Boolean
{-h(eql(V_fluent,true),V_astep+1)} :- inertial(V_fluent),-h(eql(V_fluent,true),V_astep),constant_sort(V_fluent,boolean),not has_any_macroaction.

%------------------------------------------------------------

% noconcurrency: If stated as a fact, prevents concurrent execution of Boolean actions

 :- {not h(eql(V_action_1,true),V_astep)}0,{not h(eql(V_action,true),V_astep)}0,noconcurrency,action(V_action_1),V_action!=V_action_1.

%------------------------------------------------------------

% Existence and uniqueness for every constant relative to its domain

% Rigid

-h(eql(V_rigid,Object1)) :- h(eql(V_rigid,Object)),constant_object(V_rigid,Object),constant_object(V_rigid,Object1),Object!=Object1,not constant_sort(V_rigid,boolean).

% Fluents

-h(eql(V_fluent,Object1),V_step) :- h(eql(V_fluent,Object),V_step),constant_object(V_fluent,Object),constant_object(V_fluent,Object1),Object!=Object1,not constant_sort(V_fluent,boolean).

% Actions

-h(eql(V_action,Object1),V_astep) :- h(eql(V_action,Object),V_astep),constant_object(V_action,Object),constant_object(V_action,Object1),Object!=Object1,not constant_sort(V_action,boolean).

% Only complete interpretations allowed

false :- {h(V_rigidAtomicFormula),-h(V_rigidAtomicFormula)}0.

false :- {h(V_fluentAtomicFormula,V_step),-h(V_fluentAtomicFormula,V_step)}0.

false :- {h(V_actionAtomicFormula,V_astep),-h(V_actionAtomicFormula,V_astep)}0.

%-----------------------------------------------------------------------

% Hide most of the internal predicates to avoid cluttering the answer sets
#hide sort(step).
#hide sort(astep).
#hide sort(boolean).
#hide step/1.
#hide astep/1.
#hide boolean/1.

#hide sort(constant).
#hide sort(fluent).
#hide sort(action).
#hide sort(abAction).
#hide sort(attribute).
#hide sort(exogenousAction).
#hide sort(inertialFluent).
#hide sort(rigid).
#hide sort(sdFluent).
#hide sort(simpleFluent).
#hide constant/1.
%#hide action/1 % The post-processor needs this visible to properly transform the answer sets
%#hide fluent/1 % The post-processor needs this visible to properly transform the answer sets
%#hide constant_sort/2 % The post-processor needs this visible to properly transform the answer sets
#hide sort_object/2.
#hide constant_object/2.

#hide sort(atomicFormula).
#hide sort(actionAtomicFormula).
#hide sort(fluentAtomicFormula).
#hide sort(abActionAtomicFormula).
#hide sort(attributeAtomicFormula).
#hide sort(exogenousActionAtomicFormula).
#hide sort(inertialFluentAtomicFormula).
#hide sort(rigidAtomicFormula).
#hide sort(simpleFluentAtomicFormula).
#hide sort(sdFluentAtomicFormula).
#hide atomicFormula/1.
#hide actionAtomicFormula/1.
#hide fluentAtomicFormula/1.
#hide abActionAtomicFormula/1.
#hide attributeAtomicFormula/1.
#hide exogenousActionAtomicFormula/1.
#hide inertialFluentAtomicFormula/1.
#hide rigidAtomicFormula/1.
#hide sdFluentAtomicFormula/1.
#hide simpleFluentAtomicFormula/1.
%% There are macro actions in the description
has_any_macroaction :- macroAction(V_macroaction).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%TODO:: make a new sort maction
#domain macroAction(V_maction).
exogenousAction(V_maction) :- true.
sort_object(exogenousAction,V_maction) :- true.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#domain seqnumber(V_seqno).
#domain maxseqnumber(K_star).
#domain indexnumber(V_index).
#domain inmacroAction(V_maction_subaction_1).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
mactionnocon(X,Z) :- noncon(X,Y),firstactionof(Y,Z).
mactionnocon(X,Z) :- noncon(Y,X),firstactionof(Y,Z).
false :- mactionnocon(X,Z),h(eql(X,true),V_astep),h(eql(Z,true),V_astep).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%actions in subtimestamp, default to false
{-h(eql(V_maction_subaction_1,true),V_astep,V_seqno)} :- true.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Inertial for inertial fluents of sub-interval of macro_actions

{h(V_inertialFluentAtomicFormula,V_astep,V_seqno+1)} :- h(V_inertialFluentAtomicFormula,V_astep,V_seqno),has_any_macroaction.
% Negative version for Booleans
{-h(eql(V_inertialFluent,true),V_astep,V_seqno+1)} :- -h(eql(V_inertialFluent,true),V_astep,V_seqno),constant_sort(V_inertialFluent,boolean),has_any_macroaction.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%No concurrency of macro actions
false :- h(eql(V_maction,true),V_astep),h(eql(V_maction1,true),V_astep),macroAction(V_maction1),V_maction!=V_maction1.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%% exogenous fluents, nearly no occurrence
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
{h(eql(V_fluent,Value),V_astep,V_seqno)} :- exogenous(V_fluent),constant_object(V_fluent,Value),V_seqno!=0.
% Negative version if it's Boolean
{-h(eql(V_fluent,true),V_astep,V_seqno)} :- exogenous(V_fluent),constant_sort(V_fluent,boolean),V_seqno!=0.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%% Inertial of fluents which are not boolean
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
{h(eql(V_fluent,Value),V_astep,V_seqno+1)} :- inertial(V_fluent),h(eql(V_fluent,Value),V_astep,V_seqno),constant_object(V_fluent,Value),has_any_macroaction.
% Negative version if it's Boolean
{-h(eql(V_fluent,true),V_astep,V_seqno+1)} :- inertial(V_fluent),-h(eql(V_fluent,true),V_astep,V_seqno),constant_sort(V_fluent,boolean),has_any_macroaction.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
false :- {h(V_fluentAtomicFormula,V_astep,V_seqno),-h(V_fluentAtomicFormula,V_astep,V_seqno)}0,V_seqno!=0.

false :- {h(eql(V_maction_subaction_1,true),V_astep,V_seqno),-h(eql(V_maction_subaction_1,true),V_astep,V_seqno)}0.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


-h(eql(V_fluent,Object1),V_astep,V_seqno) :- h(eql(V_fluent,Object),V_astep,V_seqno),constant_object(V_fluent,Object),constant_object(V_fluent,Object1),Object!=Object1,not constant_sort(V_fluent,boolean),V_seqno!=0.

% % Actions, already in stdf2lp

% -h(eql(V_action,Object1),V_astep) <-
%    h(eql(V_action,Object),V_astep) &
%    constant_object(V_action,Object) &
%    constant_object(V_action,Object1) &
%    Object != Object1 &
%    not constant_sort(V_action,boolean)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%% The fluents which equal to each other
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
h(V_inertialFluentAtomicFormula,V_astep+1) :- h(V_inertialFluentAtomicFormula,V_astep,K_star+1),has_any_macroaction.
h(V_inertialFluentAtomicFormula,V_astep,K_star+1) :- h(V_inertialFluentAtomicFormula,V_astep+1),has_any_macroaction.

h(V_inertialFluentAtomicFormula,V_astep) :- h(V_inertialFluentAtomicFormula,V_astep,0),has_any_macroaction.
h(V_inertialFluentAtomicFormula,V_astep,0) :- h(V_inertialFluentAtomicFormula,V_astep),has_any_macroaction.

% Negative version for Booleans
-h(eql(V_inertialFluent,true),V_astep+1) :- -h(eql(V_inertialFluent,true),V_astep,K_star+1),constant_sort(V_inertialFluent,boolean),has_any_macroaction.
-h(eql(V_inertialFluent,true),V_astep,K_star+1) :- -h(eql(V_inertialFluent,true),V_astep+1),constant_sort(V_inertialFluent,boolean),has_any_macroaction.

-h(eql(V_inertialFluent,true),V_astep) :- -h(eql(V_inertialFluent,true),V_astep,0),constant_sort(V_inertialFluent,boolean),has_any_macroaction.
-h(eql(V_inertialFluent,true),V_astep,0) :- -h(eql(V_inertialFluent,true),V_astep),constant_sort(V_inertialFluent,boolean),has_any_macroaction.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
h(eql(V_fluent,Value),V_astep+1) :- h(eql(V_fluent,Value),V_astep,K_star+1),constant_object(V_fluent,Value),has_any_macroaction.
h(eql(V_fluent,Value),V_astep,K_star+1) :- h(eql(V_fluent,Value),V_astep+1),constant_object(V_fluent,Value),has_any_macroaction.

h(eql(V_fluent,Value),V_astep) :- h(eql(V_fluent,Value),V_astep,0),constant_object(V_fluent,Value),has_any_macroaction.
h(eql(V_fluent,Value),V_astep,0) :- h(eql(V_fluent,Value),V_astep),constant_object(V_fluent,Value),has_any_macroaction.

% -h(eql(V_fluent,Value),V_astep+1) <-
%    -h(eql(V_fluent,Value),V_astep,K_star+1) &
%    constant_object(V_fluent,Value) &
%    has_any_macroaction
% -h(eql(V_fluent,Value),V_astep,K_star+1) <-
%    -h(eql(V_fluent,Value),V_astep+1) &
%    constant_object(V_fluent,Value) &
%    has_any_macroaction

% -h(eql(V_fluent,Value),V_astep) <-
%    -h(eql(V_fluent,Value),V_astep,0) &
%    constant_object(V_fluent,Value) &
%    has_any_macroaction
% -h(eql(V_fluent,Value),V_astep,0) <-
%    -h(eql(V_fluent,Value),V_astep) &
%    constant_object(V_fluent,Value) &
%    has_any_macroaction
% File "/home/smallqiang/Documents/HASP/cpp/Cplus2ASP/cplus2aspbin/build/testrobotcp"
%%%% File testrobotcp which has multi-layer structure

sort(location) :- true.
#domain location(V_location).
sort_object(location,V_location) :- true.
sort(movableobject) :- true.
#domain movableobject(V_movableobject).
sort_object(movableobject,V_movableobject) :- true.
sort(object) :- true.
#domain object(V_object).
sort_object(object,V_object) :- true.
object(V_movableobject) :- true.
sort(smallobject) :- true.
#domain smallobject(V_smallobject).
sort_object(smallobject,V_smallobject) :- true.
sort(absobject) :- true.
#domain absobject(V_absobject).
sort_object(absobject,V_absobject) :- true.
absobject(V_smallobject) :- true.
movableobject(V_smallobject) :- true.

movableobject(robot) :- true.
location(l1) :- true.
location(l2) :- true.
location(l3) :- true.
location(l4) :- true.
location(l5) :- true.
absobject(nothing) :- true.
smallobject(box) :- true.
smallobject(cup) :- true.
smallobject(drink) :- true.
smallobject(food) :- true.
object(human) :- true.
object(table) :- true.
object(desk) :- true.
object(sofa) :- true.

#domain location(L).
#domain location(L1).
#domain absobject(A).
#domain absobject(A1).
#domain object(O).
#domain smallobject(S).

inertialFluent(loc(V_object)) :- true.
constant_sort(loc(V_object),location) :- true.
inertialFluent(hold(V_absobject)) :- true.
constant_sort(hold(V_absobject),boolean) :- true.

exogenousAction(goto(V_location)) :- true.
constant_sort(goto(V_location),boolean) :- true.
exogenousAction(pickup(V_smallobject)) :- true.
constant_sort(pickup(V_smallobject),boolean) :- true.
exogenousAction(putdown(V_smallobject)) :- true.
constant_sort(putdown(V_smallobject),boolean) :- true.

macroAction(bring(V_smallobject,V_location)) :- true.
constant_sort(bring(V_smallobject,V_location),boolean) :- true.
macroAction(fetch(V_smallobject,V_location)) :- true.
constant_sort(fetch(V_smallobject,V_location),boolean) :- true.


h(eql(loc(S),L),V_step) :- {not h(eql(loc(robot),L),V_step)}0,{not h(eql(hold(S),true),V_step)}0,true.
h(eql(loc(S),L),V_astep,V_seqno) :- {not h(eql(loc(robot),L),V_astep,V_seqno)}0,{not h(eql(hold(S),true),V_astep,V_seqno)}0,V_seqno!=0.
-h(eql(hold(A),true),V_step) :- A!=A1,{not h(eql(hold(A1),true),V_step)}0,true.
-h(eql(hold(A),true),V_astep,V_seqno) :- A!=A1,{not h(eql(hold(A1),true),V_astep,V_seqno)}0,V_seqno!=0.

h(eql(loc(robot),L),V_astep+1) :- h(eql(goto(L),true),V_astep).
h(eql(loc(robot),L),V_astep,V_seqno+1) :- h(eql(goto(L),true),V_astep,V_seqno).
false :- h(eql(goto(L),true),V_astep),h(eql(loc(robot),L),V_astep).
false :- h(eql(goto(L),true),V_astep,V_seqno),h(eql(loc(robot),L),V_astep,V_seqno).


h(eql(hold(S),true),V_astep+1) :- h(eql(pickup(S),true),V_astep).
h(eql(hold(S),true),V_astep,V_seqno+1) :- h(eql(pickup(S),true),V_astep,V_seqno).
false :- h(eql(pickup(S),true),V_astep),-h(eql(hold(nothing),true),V_astep).
false :- h(eql(pickup(S),true),V_astep,V_seqno),-h(eql(hold(nothing),true),V_astep,V_seqno).
#hide _new_pred_1(V_astep,S).
false :- h(eql(pickup(S),true),V_astep),not _new_pred_1(V_astep,S).
#hide _new_pred_2(V_astep,V_seqno,S).
false :- h(eql(pickup(S),true),V_astep,V_seqno),not _new_pred_2(V_astep,V_seqno,S).

h(eql(hold(nothing),true),V_astep+1) :- h(eql(putdown(S),true),V_astep).
h(eql(hold(nothing),true),V_astep,V_seqno+1) :- h(eql(putdown(S),true),V_astep,V_seqno).
false :- h(eql(putdown(S),true),V_astep),-h(eql(hold(S),true),V_astep).
false :- h(eql(putdown(S),true),V_astep,V_seqno),-h(eql(hold(S),true),V_astep,V_seqno).

noconcurrency :- true.

h(eql(pickup(S),true),V_astep,V_index) :- h(eql(bring(S,L),true),V_astep),index(bring(S,L),pickup(S),V_index).
h(eql(pickup(S),true),V_astep,V_seqno+V_index) :- h(eql(bring(S,L),true),V_astep,V_seqno),index(bring(S,L),pickup(S),V_index).
false :- h(eql(bring(S,L),true),V_astep),h(eql(pickup(S),true),V_astep).
inmacroAction(pickup(S)) :- true.
firstactionof(pickup(S),bring(S,L)) :- true.
h(eql(goto(L),true),V_astep,V_index) :- h(eql(bring(S,L),true),V_astep),index(bring(S,L),goto(L),V_index).
h(eql(goto(L),true),V_astep,V_seqno+V_index) :- h(eql(bring(S,L),true),V_astep,V_seqno),index(bring(S,L),goto(L),V_index).
false :- h(eql(bring(S,L),true),V_astep),h(eql(goto(L),true),V_astep).
inmacroAction(goto(L)) :- true.
h(eql(putdown(S),true),V_astep,V_index) :- h(eql(bring(S,L),true),V_astep),index(bring(S,L),putdown(S),V_index).
h(eql(putdown(S),true),V_astep,V_seqno+V_index) :- h(eql(bring(S,L),true),V_astep,V_seqno),index(bring(S,L),putdown(S),V_index).
false :- h(eql(bring(S,L),true),V_astep),h(eql(putdown(S),true),V_astep).
inmacroAction(putdown(S)) :- true.
h(eql(goto(L1),true),V_astep,V_index) :- h(eql(fetch(S,L),true),V_astep),h(eql(loc(S),L1),V_astep,V_index),-h(eql(loc(robot),L1),V_astep,V_index),index(fetch(S,L),goto(L1),V_index).
h(eql(goto(L1),true),V_astep,V_seqno+V_index) :- h(eql(fetch(S,L),true),V_astep,V_seqno),h(eql(loc(S),L1),V_astep,V_seqno+V_index),-h(eql(loc(robot),L1),V_astep,V_seqno+V_index),index(fetch(S,L),goto(L1),V_index).
false :- h(eql(fetch(S,L),true),V_astep),h(eql(goto(L1),true),V_astep).
inmacroAction(goto(L1)) :- true.
firstactionof(goto(L1),fetch(S,L)) :- true.
h(eql(bring(S,L),true),V_astep,V_index) :- h(eql(fetch(S,L),true),V_astep),index(fetch(S,L),bring(S,L),V_index).
h(eql(bring(S,L),true),V_astep,V_seqno+V_index) :- h(eql(fetch(S,L),true),V_astep,V_seqno),index(fetch(S,L),bring(S,L),V_index).
false :- h(eql(fetch(S,L),true),V_astep),h(eql(bring(S,L),true),V_astep).
inmacroAction(bring(S,L)) :- true.
index(bring(S,L),pickup(S),0) :- true.
indexnumber(0) :- true.
index(bring(S,L),goto(L),1) :- true.
indexnumber(1) :- true.
index(bring(S,L),putdown(S),2) :- true.
indexnumber(2) :- true.
index(fetch(S,L),goto(L1),0) :- true.
indexnumber(0) :- true.
index(fetch(S,L),bring(S,L),1) :- true.
indexnumber(1) :- true.
seqnumber(0..3).
maxseqnumber(3) :- true.

query_label(query) :- true.
% Selects which query to activate in a based on the value of the const "query"
% [Query: Label:0, Maxstep:1::20]
false :- not h(eql(loc(robot),l1),0),query_label(0).
false :- not h(eql(loc(human),l2),0),query_label(0).
false :- not h(eql(loc(table),l3),0),query_label(0).
false :- not h(eql(loc(desk),l4),0),query_label(0).
false :- not h(eql(loc(sofa),l5),0),query_label(0).
false :- not h(eql(loc(box),l5),0),query_label(0).
false :- not h(eql(loc(cup),l4),0),query_label(0).
false :- not h(eql(loc(food),l4),0),query_label(0).
false :- not h(eql(loc(drink),l3),0),query_label(0).
false :- not h(eql(hold(nothing),true),0),query_label(0).
false :- not h(eql(loc(food),l2),maxstep),query_label(0).
false :- not h(eql(loc(drink),l2),maxstep),query_label(0).
false :- not h(eql(loc(robot),l5),maxstep),query_label(0).




_new_pred_1(V_astep,S) :- h(eql(loc(robot),V_location),V_astep),h(eql(loc(S),V_location),V_astep).

_new_pred_2(V_astep,V_seqno,S) :- h(eql(loc(robot),V_location),V_astep,V_seqno),h(eql(loc(S),V_location),V_astep,V_seqno).
true.
:- false.
#hide true.
