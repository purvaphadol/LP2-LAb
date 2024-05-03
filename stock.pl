% Dynamic predicates to store information
:- dynamic(stock_info/3).

% Initial facts (stock, price, trend)
stock_info('AAPL', 145.32, 'Up').
stock_info('GOOG', 2748.50, 'Up').
stock_info('MSFT', 300.20, 'Down').
stock_info('AMZN', 3200.00, 'Up').
stock_info('TSLA', 750.80, 'Down').

% Evaluate stock trend
evaluate_stock_trend(Stock, Trend) :-
    stock_info(Stock, _, Trend), !.

evaluate_stock_trend(_, 'Stock not found in the database.').

% Add new stock information
add_stock_info(Stock, Price, Trend) :-
    assertz(stock_info(Stock, Price, Trend)),
    write('New stock information added successfully.'), nl.

% Remove stock information
remove_stock_info(Stock) :-
    retractall(stock_info(Stock, _, _)),
    write('Stock information removed successfully.'), nl.

% Menu
menu :-
    repeat,
    nl, write('---------- Stock Market Trading ----------'), nl,
    write('1. Evaluate Stock Trend'), nl,
    write('2. Add Stock Information'), nl,
    write('3. Remove Stock Information'), nl,
    write('4. Exit'), nl,
    write('------------------------------------------'), nl,
    write('Enter your choice (1-4): '), read(Choice),
    process_choice(Choice),
    Choice == 4, !.

% Process user choice
process_choice(1) :-
    nl, write('Enter stock symbol (e.g., AAPL): '), read(Stock),
    evaluate_stock_trend(Stock, Trend),
    write('Trend: '), write(Trend), nl.

process_choice(2) :-
    nl, write('Enter stock symbol: '), read(Stock),
    write('Enter stock price: '), read(Price),
    write('Enter stock trend (Up/Down): '), read(Trend),
    add_stock_info(Stock, Price, Trend).

process_choice(3) :-
    nl, write('Enter stock symbol to remove: '), read(Stock),
    remove_stock_info(Stock).

process_choice(4) :-
    nl, write('Exiting...'), nl.

% Entry point
:- initialization(menu).
