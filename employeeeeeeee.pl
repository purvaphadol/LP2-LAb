% Dynamic Predicates, here 2 indicates the number of parameters to the function
:- dynamic(employee/2).

% Initial facts (name, rating) -> 2 parameters, add as many employees as you want
employee('john', 4).
employee('mary', 6).

% Categorize employee -> this is like if-else part
category(Rating, 'Excellent') :-
    Rating >= 5.
category(4, 'Good').
category(_, 'Average').

% Evaluation function
evaluate(Name, Rating, Class) :-
    employee(Name, Rating),
    category(Rating, Class), !.
evaluate(_, _, 'Data Not found').

% Add Data
add(Name, Rating) :-
    assertz(employee(Name, Rating)),
    write('Added!'), nl.

% MENU
menu :-
    repeat,
    nl,
    write('1. Evaluate'), nl,
    write('2. Add data'), nl,
    write('Choice: '), 
    read_line_to_codes(user_input, ChoiceInput),
    atom_codes(ChoiceAtom, ChoiceInput),
    atom_number(ChoiceAtom, Choice),
    process_choice(Choice),
    Choice == 3, !.

% Process user choice
process_choice(1) :-
    nl, write('Enter employee name: '), 
    read_line_to_codes(user_input, Name),   %syntax for reading user-input
    atom_codes(NameAtom, Name),             %syntax for reading user-input
    evaluate(NameAtom, Rating, Class),
    write('Quality of Work Rating: '), write(Rating), nl,
    write('Category: '), write(Class), nl.

%Optional with 'Add Function'
process_choice(2) :- 
    nl, write('Enter employee name: '), 
    read_line_to_codes(user_input, Name),
    atom_codes(NameAtom, Name),
    write('Enter quality of work rating: '), 
    read_line_to_codes(user_input, RatingInput),
    atom_codes(RatingAtom, RatingInput),
    atom_number(RatingAtom, Rating),
    add(NameAtom, Rating).

process_choice(3) :-
    nl, write('Exiting...'), nl.

% Entry point
:- initialization(menu).

