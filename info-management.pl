% Dynamic predicates to store information
:- dynamic(info/2).

% Facts
% Define information about various topics.
info('Prolog', 'Prolog is a logic programming language associated with artificial intelligence and computational linguistics.').
info('Expert System', 'An expert system is a computer system that emulates the decision-making ability of a human expert.').
info('Knowledge Base', 'A knowledge base is a central repository where information and data are collected, organized, and shared.').
info('Database Management System', 'A database management system (DBMS) is software that enables users to define, create, maintain, and control access to databases.').

% Add information
add_info(Topic, Information) :-
    assertz(info(Topic, Information)),
    write('Information added successfully for '), write(Topic), write('.'), nl.

% Delete information
delete_info(Topic) :-
    retract(info(Topic, _)),
    write('Information deleted successfully for '), write(Topic), write('.'), nl.

% Update information
update_info(Topic, NewInformation) :-
    retract(info(Topic, _)),
    assertz(info(Topic, NewInformation)),
    write('Information updated successfully for '), write(Topic), write('.'), nl.

% Query information
query_info(Topic) :-
    (   info(Topic, Info) ->
        write(Info), nl
    ;   write('Sorry, no information found for '), write(Topic), write('.'), nl
    ).

% List all available topics
list_topics :-
    write('Available topics: '), nl,
    forall(info(Topic, _), (write(Topic), nl)),
    nl.

% Menu
menu :-
    repeat,
    nl, write('---------- Information Management System ----------'), nl,
    write('1. Add Information'), nl,
    write('2. Delete Information'), nl,
    write('3. Update Information'), nl,
    write('4. Query Information'), nl,
    write('5. List Available Topics'), nl,
    write('6. Exit'), nl,
    write('---------------------------------------------------'), nl,
    write('Enter your choice: '), read(Choice),
    process_choice(Choice),
    Choice == 6, !.

% Process user choice
process_choice(1) :-
    write('Enter topic: '), read(Topic),
    write('Enter information: '), read(Info),
    add_info(Topic, Info).

process_choice(2) :-
    write('Enter topic to delete: '), read(Topic),
    delete_info(Topic).

process_choice(3) :-
    write('Enter topic to update: '), read(Topic),
    write('Enter new information: '), read(NewInfo),
    update_info(Topic, NewInfo).

process_choice(4) :-
    write('Enter topic to query: '), read(Topic),
    query_info(Topic).

process_choice(5) :-
    list_topics.

process_choice(6) :-
    write('Exiting...'), !.

% Entry point
:- initialization(menu).
