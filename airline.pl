% Dynamic predicates to store information
:- dynamic(flight_schedule/4).
:- dynamic(cargo_schedule/4).

% Schedule facts (flight, destination, departure_time, arrival_time)
flight_schedule('Flight 001', 'New York', '08:00', '12:00').
flight_schedule('Flight 002', 'Los Angeles', '10:00', '14:00').
flight_schedule('Flight 003', 'Chicago', '12:00', '16:00').
flight_schedule('Flight 004', 'Miami', '14:00', '18:00').
flight_schedule('Flight 005', 'Dallas', '16:00', '20:00').

% Cargo schedule facts (cargo, destination, departure_time, arrival_time)
cargo_schedule('Cargo 001', 'New York', '08:00', '12:00').
cargo_schedule('Cargo 002', 'Los Angeles', '10:00', '14:00').
cargo_schedule('Cargo 003', 'Chicago', '12:00', '16:00').
cargo_schedule('Cargo 004', 'Miami', '14:00', '18:00').
cargo_schedule('Cargo 005', 'Dallas', '16:00', '20:00').

% Find flight schedule
find_flight_schedule(Flight, Destination, DepartureTime, ArrivalTime) :-
    flight_schedule(Flight, Destination, DepartureTime, ArrivalTime), !.

find_flight_schedule(_, _, _, _) :-
    write('Flight not found in the schedule.'), nl.

% Find cargo schedule
find_cargo_schedule(Cargo, Destination, DepartureTime, ArrivalTime) :-
    cargo_schedule(Cargo, Destination, DepartureTime, ArrivalTime), !.

find_cargo_schedule(_, _, _, _) :-
    write('Cargo not found in the schedule.'), nl.

% Add flight
add_flight(Flight, Destination, DepartureTime, ArrivalTime) :-
    assertz(flight_schedule(Flight, Destination, DepartureTime, ArrivalTime)),
    write('Flight added successfully.'), nl.

% Update flight
update_flight(Flight, Destination, DepartureTime, ArrivalTime) :-
    retract(flight_schedule(Flight, _, _, _)),
    assertz(flight_schedule(Flight, Destination, DepartureTime, ArrivalTime)),
    write('Flight updated successfully.'), nl.

% Delete flight
delete_flight(Flight) :-
    retract(flight_schedule(Flight, _, _, _)),
    write('Flight deleted successfully.'), nl.

% Menu
menu :-
    repeat,
    nl, write('---------- Airline and Cargo Scheduling ----------'), nl,
    write('1. Find Flight Schedule'), nl,
    write('2. Find Cargo Schedule'), nl,
    write('3. Add Flight'), nl,
    write('4. Update Flight'), nl,
    write('5. Delete Flight'), nl,
    write('6. Exit'), nl,
    write('---------------------------------------------------'), nl,
    write('Enter your choice (1-6): '), read_line_to_codes(user_input, ChoiceInput),
    atom_codes(ChoiceAtom, ChoiceInput),
    atom_number(ChoiceAtom, Choice),
    process_choice(Choice),
    Choice == 6, !.

% Process user choice
process_choice(1) :-
    nl, write('Enter flight number: '), read_line_to_codes(user_input, FlightInput),
    atom_codes(FlightAtom, FlightInput),
    find_flight_schedule(FlightAtom, Destination, DepartureTime, ArrivalTime),
    write('Destination: '), write(Destination), nl,
    write('Departure Time: '), write(DepartureTime), nl,
    write('Arrival Time: '), write(ArrivalTime), nl.

process_choice(2) :-
    nl, write('Enter cargo number: '), read_line_to_codes(user_input, CargoInput),
    atom_codes(CargoAtom, CargoInput),
    find_cargo_schedule(CargoAtom, Destination, DepartureTime, ArrivalTime),
    write('Destination: '), write(Destination), nl,
    write('Departure Time: '), write(DepartureTime), nl,
    write('Arrival Time: '), write(ArrivalTime), nl.

process_choice(3) :-
    nl, write('Enter flight number: '), read_line_to_codes(user_input, FlightInput),
    atom_codes(FlightAtom, FlightInput),
    write('Enter destination: '), read_line_to_codes(user_input, DestinationInput),
    atom_codes(DestinationAtom, DestinationInput),
    write('Enter departure time: '), read_line_to_codes(user_input, DepartureTimeInput),
    atom_codes(DepartureTimeAtom, DepartureTimeInput),
    write('Enter arrival time: '), read_line_to_codes(user_input, ArrivalTimeInput),
    atom_codes(ArrivalTimeAtom, ArrivalTimeInput),
    add_flight(FlightAtom, DestinationAtom, DepartureTimeAtom, ArrivalTimeAtom).

process_choice(4) :-
    nl, write('Enter flight number: '), read_line_to_codes(user_input, FlightInput),
    atom_codes(FlightAtom, FlightInput),
    write('Enter new destination: '), read_line_to_codes(user_input, DestinationInput),
    atom_codes(DestinationAtom, DestinationInput),
    write('Enter new departure time: '), read_line_to_codes(user_input, DepartureTimeInput),
    atom_codes(DepartureTimeAtom, DepartureTimeInput),
    write('Enter new arrival time: '), read_line_to_codes(user_input, ArrivalTimeInput),
    atom_codes(ArrivalTimeAtom, ArrivalTimeInput),
    update_flight(FlightAtom, DestinationAtom, DepartureTimeAtom, ArrivalTimeAtom).

process_choice(5) :-
    nl, write('Enter flight number: '), read_line_to_codes(user_input, FlightInput),
    atom_codes(FlightAtom, FlightInput),
    delete_flight(FlightAtom).

process_choice(6) :-
    nl, write('Exiting...'), nl.

% Entry point
:- initialization(menu).