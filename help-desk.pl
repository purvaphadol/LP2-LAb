% Dynamic predicates to store information
:- dynamic(known/2).

% Initial facts
known('What is Prolog?', 'Prolog is a logic programming language associated with artificial intelligence and computational linguistics.').
known('What is an expert system?', 'An expert system is a computer system that emulates the decision-making ability of a human expert.').
known('How do I define rules in Prolog?', 'In Prolog, rules are defined using the syntax: head :- body.').

% Handle questions
handle_question(Question, Answer) :-
    known(Question, Answer), !.

handle_question(_, 'Sorry, I do not have an answer to that question.').

% Add new question-answer pair
add_question_answer(Question, Answer) :-
    assertz(known(Question, Answer)),
    write('New question-answer pair added successfully.'), nl.

% Remove question-answer pair
remove_question_answer(Question) :-
    retract(known(Question, _)),
    write('Question-answer pair removed successfully.'), nl.

% Menu
menu :-
    repeat,
    nl, write('---------- Help Desk Management System ----------'), nl,
    write('1. Ask a Question'), nl,
    write('2. Add New Question-Answer Pair'), nl,
    write('3. Remove Question-Answer Pair'), nl,
    write('4. Exit'), nl,
    write('--------------------------------------------------'), nl,
    write('Enter your choice (1-4): '), read(Choice),
    process_choice(Choice),
    Choice == 4, !.

% Process user choice
process_choice(1) :-
    nl, write('Enter your question: '), read_line_to_codes(user_input, Question),
    atom_codes(QuestionAtom, Question),
    handle_question(QuestionAtom, Answer),
    write('Answer: '), write(Answer), nl.

process_choice(2) :-
    nl, write('Enter new question: '), read_line_to_codes(user_input, NewQuestion),
    atom_codes(NewQuestionAtom, NewQuestion),
    nl, write('Enter answer for the question: '), read_line_to_codes(user_input, Answer),
    atom_codes(AnswerAtom, Answer),
    add_question_answer(NewQuestionAtom, AnswerAtom).

process_choice(3) :-
    nl, write('Enter question to remove: '), read_line_to_codes(user_input, Question),
    atom_codes(QuestionAtom, Question),
    remove_question_answer(QuestionAtom).

process_choice(4) :-
    nl, write('Exiting...'), nl.

% Entry point
:- initialization(menu).
